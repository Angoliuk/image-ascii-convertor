#pragma once

#include "editor/utils.hpp"
#include <QWidget>

class Checkbox final : public QWidget {
  Q_OBJECT

public:
  explicit Checkbox(QWidget* parent, const QString& labelText = "", bool initial = false);

signals:
  void changed(Qt::CheckState value);
};
