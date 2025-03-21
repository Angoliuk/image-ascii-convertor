#pragma once

#include "editor/image.hpp"
#include "editor/utils.hpp"
#include <QTextBrowser>
#include <QWidget>

class AsciiPreview final : public QWidget {
  Q_OBJECT

public:
  explicit AsciiPreview(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent);
  void updatePreview() const;

public slots:
  void updateImage() const;

private:
  QTextBrowser* text;
  std::shared_ptr<ImageWithFilters> image;
};
