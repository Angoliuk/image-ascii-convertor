#pragma once

#include "editor/image.hpp"
#include "editor/utils.hpp"
#include <QWidget>

class ImageEditorContainer final : public QWidget {
  Q_OBJECT

public:
  explicit ImageEditorContainer(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent);

private:
  std::shared_ptr<ImageWithFilters> image;
};
