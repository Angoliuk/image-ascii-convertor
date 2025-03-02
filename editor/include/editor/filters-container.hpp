#pragma once

#include "editor/image.hpp"
#include "editor/utils.hpp"
#include <QWidget>

class FiltersContainer final : public QWidget {
  Q_OBJECT

public:
  explicit FiltersContainer(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent);

signals:
  void changed();

private:
  std::shared_ptr<ImageWithFilters> image;
};
