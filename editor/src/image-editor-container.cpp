#include "editor/image-editor-container.hpp"
#include "editor/filters-container.hpp"
#include "editor/image-container.hpp"
#include "editor/image-picker.hpp"
#include <QVBoxLayout>

ImageEditorContainer::ImageEditorContainer(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent)
    : QWidget(parent), image(image) {
  const auto layout = new QHBoxLayout(this);
  layout->setSizeConstraint(QLayout::SetMinimumSize);

  const auto imageContainer = new ImageContainer(image, this);
  imagePicker = new ImagePicker(image, this);
  filtersContainer = new FiltersContainer(image, this);

  layout->addWidget(imagePicker);
  layout->addWidget(filtersContainer);
  layout->addStretch();
  layout->addWidget(imageContainer);

  connect(imagePicker, &ImagePicker::selected, imageContainer, &ImageContainer::openedNewImage);
  connect(filtersContainer, &FiltersContainer::changed, imageContainer, &ImageContainer::filtersChanged);
}

void ImageEditorContainer::saveAction() const {
  image->edited->save(100);
}

void ImageEditorContainer::openAction() const {
  imagePicker->openFilePicker();
}
