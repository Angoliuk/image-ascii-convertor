#include "editor/image-editor-container.hpp"
#include "editor/filters-container.hpp"
#include "editor/image-container.hpp"
#include "editor/image-picker.hpp"
#include <QVBoxLayout>

ImageEditorContainer::ImageEditorContainer(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent)
    : QWidget(parent), image(image) {
  const auto layout = new QHBoxLayout(this);
  const auto imageContainer = new ImageContainer(image, this);
  const auto imagePicker = new ImagePicker(image, this);
  const auto filtersContainer = new FiltersContainer(image, this);

  layout->addWidget(imagePicker);
  layout->addWidget(filtersContainer);
  layout->addWidget(imageContainer);

  connect(imagePicker, &ImagePicker::selected, imageContainer, &ImageContainer::openedNewImage);
  connect(filtersContainer, &FiltersContainer::changed, imageContainer, &ImageContainer::filtersChanged);
};
