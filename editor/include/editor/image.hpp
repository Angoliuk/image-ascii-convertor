#pragma once

#include "editor/utils.hpp"
#include "stb_image.h"
#include "stb_image_write.h"
#include <stb_image_resize.h>

struct Image {
  explicit Image(const std::filesystem::path& path, int desiredChannels = 3, int desiredWidth = 620);

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
  void load(int desiredChannels = 3, int desiredWidth = 620);
};

class ImageWithFilters {
public:
  void openFile(const std::filesystem::path& path);

  std::shared_ptr<Image> original = nullptr;
  std::shared_ptr<Image> edited = nullptr;

  void apply();
  void resetFilters();
  void resize(int newWidth);
  void resetEdited() const;
  std::string getASCII(std::string chars = "@%#*+=-:. ") const;

  void setGrayscale(bool newIsGrayscale);
  void setBrightness(float newBrightness);
  void setContrast(float newContrast);
  void setGamma(float newGamma);
  void setBlur(int newBlur);
  void setSepia(float newSepia);
  void setRFactor(float newRFactor);
  void setGFactor(float newGFactor);
  void setBFactor(float newBFactor);
  void setROffset(float newROffset);
  void setGOffset(float newGOffset);
  void setBOffset(float newBOffset);

  bool getGrayscale() const;
  float getBrightness() const;
  float getContrast() const;
  float getGamma() const;
  int getBlur() const;
  float getSepia() const;
  float getRFactor() const;
  float getGFactor() const;
  float getBFactor() const;
  int getROffset() const;
  int getGOffset() const;
  int getBOffset() const;

  void applyGrayscale();
  void applyBrightness() const;
  void applyContrast() const;
  void applyGamma() const;
  void applyBlur() const;
  void applySepia() const;
  void applyColors() const;

private:
  std::shared_ptr<Image> originalDump = nullptr;

  bool isGrayscale = false;
  float brightness = 1;
  float sepia = 0;
  float contrast = 1;
  float gamma = 1;
  int blur = 1;

  int rOffset = 0;
  float rFactor = 1;
  int gOffset = 0;
  float gFactor = 1;
  int bOffset = 0;
  float bFactor = 1;

  int inColorRange(int value) const;
};
