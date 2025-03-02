#pragma once

#include "editor/utils.hpp"
#include <QWidget>

class Slider final : public QWidget {
  Q_OBJECT

public:
  explicit Slider(
    QWidget* parent, const QString& labelText = "", const int initial = 0, const int min = 0, const int max = 100);

signals:
  void changed(int value);

private:
};
