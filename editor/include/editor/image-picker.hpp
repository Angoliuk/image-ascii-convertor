#pragma once

#include "editor/image.hpp"
#include "editor/utils.hpp"
#include <QWidget>

class ImagePicker final : public QWidget {
  Q_OBJECT

public:
  explicit ImagePicker(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent);

signals:
  void selected();

public slots:
  void openFilePicker();

private:
  std::shared_ptr<ImageWithFilters> image;
};
