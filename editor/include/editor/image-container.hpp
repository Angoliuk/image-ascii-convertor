#pragma once

#include "editor/edited-image-preview.hpp"
#include "editor/image.hpp"
#include "editor/original-image-preview.hpp"
#include "editor/utils.hpp"
#include <QWidget>

class ImageContainer final : public QWidget {
  Q_OBJECT

public:
  explicit ImageContainer(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent);

public slots:
  void openedNewImage() const;
  void filtersChanged() const;

private:
  OriginalImagePreview* originalImagePreview;
  EditedImagePreview* editedImagePreview;
  std::shared_ptr<ImageWithFilters> image;
};
