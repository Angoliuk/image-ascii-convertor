#include "editor/checkbox.hpp"
#include <QCheckBox>
#include <QVBoxLayout>

Checkbox::Checkbox(QWidget* parent, const QString& labelText, const bool initial) : QWidget(parent) {
  const auto layout = new QVBoxLayout(this);

  const auto checkbox = new QCheckBox(labelText, this);
  checkbox->setCheckState(initial ? Qt::Checked : Qt::Unchecked);

  layout->addWidget(checkbox);

  connect(checkbox, &QCheckBox::checkStateChanged, this, &Checkbox::changed);
};
