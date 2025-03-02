#include "editor/image.hpp"

void ImageWithFilters::openFile(const std::filesystem::path& path) {
  edited = std::make_shared<Image>(path);
  originalDump = std::make_shared<Image>(path);
  original = std::make_shared<Image>(path);
  resetFilters();
};

void ImageWithFilters::setGrayscale(const bool newIsGrayscale) {
  isGrayscale = newIsGrayscale;
};

void ImageWithFilters::resetFilters() {
  brightness = 1;
  contrast = 1;
  gamma = 1;
  isGrayscale = false;
  blur = 1;
};

void ImageWithFilters::resetEdited() const {
  edited->path = originalDump->path;
  edited->data = originalDump->data;
  edited->width = originalDump->width;
  edited->height = originalDump->height;
  edited->channels = originalDump->channels;
  edited->colorMax = originalDump->colorMax;
  edited->colorMin = originalDump->colorMin;
  edited->colorMid = originalDump->colorMid;
};

Image::Image(const std::filesystem::path& path, const int desiredChannels) : path(path) {
  load(desiredChannels);
};

void ImageWithFilters::applyGrayscale(const bool isGrayscale) {
  if (isGrayscale && originalDump->channels == 1 || !isGrayscale && originalDump->channels != 1)
    return;

  originalDump = std::make_shared<Image>(originalDump->path, isGrayscale ? 1 : 3);
};

void ImageWithFilters::applyBrightness(const float brightness) const {
  for (int i = 0; i < edited->width * edited->height * edited->channels; i++) {
    int newValue = edited->data[i] * brightness;
    edited->data[i] = inColorRange(newValue);
  }
};

void ImageWithFilters::applyContrast(const float contrast) const {
  for (int i = 0; i < edited->width * edited->height * edited->channels; i++) {
    const int newValue = (edited->data[i] - edited->colorMid) * contrast + edited->colorMid;
    edited->data[i] = inColorRange(newValue);
  }
};

void ImageWithFilters::applyGamma(const float gamma) const {
  for (int i = 0; i < edited->width * edited->height * edited->channels; i++) {
    const float normalized = edited->data[i] / static_cast<float>(edited->colorMax);
    edited->data[i] = static_cast<unsigned char>(inColorRange(std::pow(normalized, gamma) * edited->colorMax));
  }
};

void ImageWithFilters::use() {
  applyGrayscale(isGrayscale);
  resetEdited();
  applyBrightness(brightness);
  applyContrast(contrast);
  applyGamma(gamma);
  applyBlur(blur);
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

std::vector<std::vector<float>> generateGaussianKernel(const int size) {
  std::vector<std::vector<float>> kernel(size, std::vector<float>(size));
  float sum = 0.0f;
  const int halfSize = size / 2;

  for (int y = -halfSize; y <= halfSize; y++) {
    for (int x = -halfSize; x <= halfSize; x++) {
      float exponent = -(x * x + y * y) / (size * 0.25);
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

// gaussian
void ImageWithFilters::applyBlur(const int blur) const {

  const auto copy = edited->data;

  const std::vector<std::vector<float>> kernel = generateGaussianKernel(blur);

  const int halfSize = blur / 2;

  for (int y = halfSize; y < edited->height - halfSize; y++) {
    for (int x = halfSize; x < edited->width - halfSize; x++) {
      for (int c = 0; c < edited->channels; c++) {
        float sum = 0.0f;

        for (int ky = -halfSize; ky <= halfSize; ky++) {
          for (int kx = -halfSize; kx <= halfSize; kx++) {
            int pixelIndex = ((y + ky) * edited->width + (x + kx)) * edited->channels + c;
            sum += copy[pixelIndex] * kernel[ky + halfSize][kx + halfSize];
          }
        }

        int pixelIndex = (y * edited->width + x) * edited->channels + c;
        edited->data[pixelIndex] =
          static_cast<unsigned char>(std::clamp(static_cast<int>(sum), edited->colorMin, edited->colorMax));
      }
    }
  }
};

void Image::save(int quality) const {
  saveTo(path, quality);
};

void Image::saveTo(const std::filesystem::path& outputPath, const int quality) const {
  stbi_write_jpg(outputPath.string().c_str(), width, height, channels, data.data(), quality);
};

void Image::load(const int desiredChannels) {
  const auto raw = stbi_load(path.string().c_str(), &width, &height, nullptr, desiredChannels);
  channels = desiredChannels;
  data.assign(raw, raw + (width * height * channels));
  stbi_image_free(raw);
};

int ImageWithFilters::inColorRange(const int value) const {
  return std::clamp(value, edited->colorMin, edited->colorMax);
};
