#pragma once

#include "editor/utils.hpp"
#include "stb_image.h"
#include "stb_image_write.h"

struct Image {
  explicit Image(const std::filesystem::path& path, int desiredChannels = 3);

  std::filesystem::path path;
  std::vector<unsigned char> data;

  int width;
  int height;
  int channels;
  int colorMax = 255;
  int colorMin = 0;
  int colorMid = 128;

  void save(int quality) const;
  void saveTo(const std::filesystem::path& outputPath, int quality) const;
  void load(int desiredChannels = 3);
};

class ImageWithFilters {
public:
  void openFile(const std::filesystem::path& path);

  std::shared_ptr<Image> original = nullptr;
  std::shared_ptr<Image> edited = nullptr;

  void use();
  void resetFilters();
  void resetEdited() const;

  void setGrayscale(bool newIsGrayscale);
  void setBrightness(float newBrightness);
  void setContrast(float newContrast);
  void setGamma(float newGamma);
  void setBlur(int newBlur);

  void applyGrayscale(bool isGrayscale);
  void applyBrightness(float brightness) const;
  void applyContrast(float contrast) const;
  void applyGamma(float gamma) const;
  void applyBlur(int blur) const;

  bool isGrayscale = false;
  float brightness = 1;
  float contrast = 1;
  float gamma = 1;
  int blur = 1;

private:
  std::shared_ptr<Image> originalDump = nullptr;

  int inColorRange(int value) const;
};
