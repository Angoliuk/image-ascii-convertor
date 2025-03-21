#include "editor/image-container.hpp"
#include "editor/edited-image-preview.hpp"
#include "editor/original-image-preview.hpp"
#include <QVBoxLayout>

ImageContainer::ImageContainer(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent)
    : QWidget(parent), image(image) {
  const auto layout = new QVBoxLayout(this);
  originalImagePreview = new OriginalImagePreview(image, this);
  editedImagePreview = new EditedImagePreview(image, this);

  layout->addWidget(originalImagePreview);
  layout->addWidget(editedImagePreview);
  layout->addStretch();
}

void ImageContainer::openedNewImage() const {
  originalImagePreview->updateImage();
  editedImagePreview->updateImage();
}

void ImageContainer::filtersChanged() const {
  editedImagePreview->updateImage();
}
