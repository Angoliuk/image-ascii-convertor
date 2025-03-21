#include "editor/image.hpp"

std::vector<std::vector<float>> generateGaussianKernel(const int size) {
  std::vector kernel(size, std::vector<float>(size));
  float sum = 0.0f;
  const int halfSize = size / 2;

  for (int y = -halfSize; y <= halfSize; y++) {
    for (int x = -halfSize; x <= halfSize; x++) {
      const float exponent = -(x * x + y * y) / (size * 0.25);
      kernel[y + halfSize][x + halfSize] = std::exp(exponent);
      sum += kernel[y + halfSize][x + halfSize];
    }
  }

  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      kernel[y][x] /= sum;
    }
  }

  return kernel;
}

void ImageWithFilters::openFile(const std::filesystem::path& path) {
  resetFilters();
  edited = std::make_shared<Image>(path);
  originalDump = std::make_shared<Image>(path);
  original = std::make_shared<Image>(path);
}

std::string ImageWithFilters::getASCII(std::string chars) const {
  if (!edited) {
    return "";
  }

  constexpr int asciiWidth = 200;
  const float aspectRatio = static_cast<float>(edited->height) / static_cast<float>(edited->width);
  const int asciiHeight = asciiWidth * aspectRatio * 0.5;

  std::vector<unsigned char> resized(asciiWidth * asciiHeight);

  for (int y = 0; y < asciiHeight; ++y) {
    for (int x = 0; x < asciiWidth; ++x) {
      const int proportionedX = x * edited->width / asciiWidth;
      const int proportionedY = y * edited->height / asciiHeight;
      resized[y * asciiWidth + x] = edited->data[proportionedY * edited->width + proportionedX];
    }
  }

  std::string ascii = "";

  for (int y = 0; y < asciiHeight; y++) {
    for (int x = 0; x < asciiWidth; x++) {
      const int index = y * asciiWidth + x;
      const int gray = resized[index];

      const int charIndex = (gray * (chars.size() - 1)) / 255;
      ascii += chars[charIndex];
    }
    ascii += '\n';
  }

  return ascii;
}

void ImageWithFilters::resetFilters() {
  brightness = 1;
  contrast = 1;
  gamma = 1;
  isGrayscale = false;
  sepia = 0;
  blur = 1;

  rOffset = 0;
  rFactor = 1;
  gOffset = 0;
  gFactor = 1;
  bOffset = 0;
  bFactor = 1;
}

void ImageWithFilters::resetEdited() const {
  edited->path = originalDump->path;
  edited->data = originalDump->data;
  edited->width = originalDump->width;
  edited->height = originalDump->height;
  edited->channels = originalDump->channels;
  edited->colorMax = originalDump->colorMax;
  edited->colorMin = originalDump->colorMin;
  edited->colorMid = originalDump->colorMid;
}

// TODO: resize and applyGrayscale both load image again,
// maybe we should combine them in one function to avoid loading image twice
// But now we apply filters on each change, so we do not have situations when we load image twice
void ImageWithFilters::resize(const int newWidth) {
  if (!originalDump->width == newWidth) {
    return;
  }

  originalDump = std::make_shared<Image>(originalDump->path, isGrayscale ? 1 : 3, newWidth);
}

void ImageWithFilters::applyGrayscale() {
  if (isGrayscale && originalDump->channels == 1 || !isGrayscale && originalDump->channels != 1)
    return;

  originalDump = std::make_shared<Image>(originalDump->path, isGrayscale ? 1 : 3);
}

void ImageWithFilters::applyBrightness() const {
  for (int i = 0; i < edited->width * edited->height * edited->channels; i++) {
    const int newValue = edited->data[i] * brightness;
    edited->data[i] = inColorRange(newValue);
  }
}

void ImageWithFilters::applyContrast() const {
  for (int i = 0; i < edited->width * edited->height * edited->channels; i++) {
    const int newValue = (edited->data[i] - edited->colorMid) * contrast + edited->colorMid;
    edited->data[i] = inColorRange(newValue);
  }
}

void ImageWithFilters::applyGamma() const {
  for (int i = 0; i < edited->width * edited->height * edited->channels; i++) {
    const float normalized = edited->data[i] / static_cast<float>(edited->colorMax);
    edited->data[i] = static_cast<unsigned char>(inColorRange(std::pow(normalized, gamma) * edited->colorMax));
  }
}

void ImageWithFilters::applyColors() const {
  for (int i = 0; i < edited->width * edited->height * edited->channels; i += edited->channels) {
    const int r = edited->data[i] * rFactor + rOffset;
    const int g = edited->data[i + 1] * gFactor + gOffset;
    const int b = edited->data[i + 2] * bFactor + bOffset;

    edited->data[i] = inColorRange(r);
    edited->data[i + 1] = inColorRange(g);
    edited->data[i + 2] = inColorRange(b);
  }
}

void ImageWithFilters::applySepia() const {
  const auto intensity = std::max(0.0f, std::min(1.0f, sepia));

  for (int i = 0; i < edited->width * edited->height * edited->channels; i += edited->channels) {
    const unsigned char r = edited->data[i];
    const unsigned char g = edited->data[i + 1];
    const unsigned char b = edited->data[i + 2];

    // TODO: test, maybe use inColorRange for these 3 vars
    const int sepiaR = 0.393 * r + 0.769 * g + 0.189 * b;
    const int sepiaG = 0.349 * r + 0.686 * g + 0.168 * b;
    const int sepiaB = 0.272 * r + 0.534 * g + 0.131 * b;

    const unsigned char newR = inColorRange((1 - intensity) * r + intensity * sepiaR);
    const unsigned char newG = inColorRange((1 - intensity) * g + intensity * sepiaG);
    const unsigned char newB = inColorRange((1 - intensity) * b + intensity * sepiaB);

    edited->data[i] = newR;
    edited->data[i + 1] = newG;
    edited->data[i + 2] = newB;
  }
}

// gaussian
void ImageWithFilters::applyBlur() const {

  const auto copy = edited->data;

  const std::vector<std::vector<float>> kernel = generateGaussianKernel(blur);

  const int halfSize = blur / 2;

  for (int y = halfSize; y < edited->height - halfSize; y++) {
    for (int x = halfSize; x < edited->width - halfSize; x++) {
      for (int c = 0; c < edited->channels; c++) {
        float sum = 0.0f;

        for (int ky = -halfSize; ky <= halfSize; ky++) {
          for (int kx = -halfSize; kx <= halfSize; kx++) {
            const int pixelIndex = ((y + ky) * edited->width + (x + kx)) * edited->channels + c;
            sum += copy[pixelIndex] * kernel[ky + halfSize][kx + halfSize];
          }
        }

        const int pixelIndex = (y * edited->width + x) * edited->channels + c;
        edited->data[pixelIndex] =
          static_cast<unsigned char>(std::clamp(static_cast<int>(sum), edited->colorMin, edited->colorMax));
      }
    }
  }
}

void ImageWithFilters::apply() {
  applyGrayscale();
  resetEdited();
  applyColors();
  applyBrightness();
  applySepia();
  applyContrast();
  applyGamma();
  applyBlur();
}

void ImageWithFilters::setGrayscale(const bool newIsGrayscale) {
  isGrayscale = newIsGrayscale;
}

void ImageWithFilters::setSepia(const float newSepia) {
  sepia = newSepia;
}

void ImageWithFilters::setBrightness(const float newBrightness) {
  brightness = newBrightness;
}

void ImageWithFilters::setContrast(const float newContrast) {
  contrast = newContrast;
}

void ImageWithFilters::setGamma(const float newGamma) {
  gamma = newGamma;
}

void ImageWithFilters::setBlur(const int newBlur) {
  blur = newBlur * 2 + 1;
}

void ImageWithFilters::setRFactor(const float newRFactor) {
  rFactor = newRFactor;
}

void ImageWithFilters::setGFactor(const float newGFactor) {
  gFactor = newGFactor;
}

void ImageWithFilters::setBFactor(const float newBFactor) {
  bFactor = newBFactor;
}

void ImageWithFilters::setROffset(const float newROffset) {
  rOffset = newROffset;
}

void ImageWithFilters::setGOffset(const float newGOffset) {
  gOffset = newGOffset;
}

void ImageWithFilters::setBOffset(const float newBOffset) {
  bOffset = newBOffset;
}

bool ImageWithFilters::getGrayscale() const {
  return isGrayscale;
}

float ImageWithFilters::getSepia() const {
  return sepia;
}

float ImageWithFilters::getBrightness() const {
  return brightness;
}

float ImageWithFilters::getContrast() const {
  return contrast;
}

float ImageWithFilters::getGamma() const {
  return gamma;
}

int ImageWithFilters::getBlur() const {
  return blur;
}

float ImageWithFilters::getRFactor() const {
  return rFactor;
}

float ImageWithFilters::getGFactor() const {
  return gFactor;
}

float ImageWithFilters::getBFactor() const {
  return bFactor;
}

int ImageWithFilters::getROffset() const {
  return rOffset;
}

int ImageWithFilters::getGOffset() const {
  return gOffset;
}

int ImageWithFilters::getBOffset() const {
  return bOffset;
}

int ImageWithFilters::inColorRange(const int value) const {
  return std::clamp(value, edited->colorMin, edited->colorMax);
}

Image::Image(const std::filesystem::path& path, const int desiredChannels, const int desiredWidth) : path(path) {
  load(desiredChannels, desiredWidth);
}

void Image::save(const int quality) const {
  saveTo(path, quality);
}

void Image::saveTo(const std::filesystem::path& outputPath, const int quality) const {
  stbi_write_jpg(outputPath.string().c_str(), width, height, channels, data.data(), quality);
}

void Image::load(const int desiredChannels, const int desiredWidth) {
  auto initialHeight = 0;
  auto initialWidth = 0;
  const auto raw = stbi_load(path.string().c_str(), &initialWidth, &initialHeight, nullptr, desiredChannels);

  const float aspectRatio = static_cast<float>(initialHeight) / static_cast<float>(initialWidth);

  const int desiredHeight = desiredWidth * aspectRatio;

  std::vector<unsigned char> resized(desiredWidth * desiredHeight * desiredChannels);

  data.resize(desiredWidth * desiredHeight * desiredChannels);
  stbir_resize_uint8(raw, initialWidth, initialHeight, 0, data.data(), desiredWidth, desiredHeight, 0, desiredChannels);

  channels = desiredChannels;
  width = desiredWidth;
  height = desiredHeight;

  stbi_image_free(raw);
}
