#pragma once

#include "editor/image.hpp"
#include "editor/utils.hpp"
#include "filters-container.hpp"
#include "image-picker.hpp"
#include <QWidget>

class ImageEditorContainer final : public QWidget {
  Q_OBJECT

public:
  explicit ImageEditorContainer(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent);
  ImagePicker* imagePicker;
  FiltersContainer* filtersContainer;

public slots:
  void saveAction() const;
  void openAction() const;

private:
  std::shared_ptr<ImageWithFilters> image;
};
