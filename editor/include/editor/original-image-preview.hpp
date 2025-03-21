#pragma once

#include "editor/image.hpp"
#include "editor/utils.hpp"
#include <QLabel>
#include <QWidget>

class OriginalImagePreview final : public QWidget {
  Q_OBJECT

public:
  explicit OriginalImagePreview(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent);
  void updateImageView() const;

public slots:
  void updateImage() const;

private:
  QLabel* label;
  std::shared_ptr<ImageWithFilters> image;
};
