#include "editor/components/slider.hpp"
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>

Slider::Slider(QWidget* parent, const QString& labelText, const int initial, const int min, const int max)
    : QWidget(parent) {
  const auto layout = new QVBoxLayout(this);
  const auto label = new QLabel(labelText + ":", this);

  const auto slider = new QSlider(Qt::Horizontal, this);
  slider->setRange(min, max);
  slider->setValue(initial);
  slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  layout->addWidget(label);
  layout->addWidget(slider);
  layout->setSizeConstraint(QLayout::SetMinimumSize);

  connect(slider, &QSlider::valueChanged, this, &Slider::changed);
}
