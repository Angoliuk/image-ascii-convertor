#include "editor/filters-container.hpp"
#include "editor/checkbox.hpp"
#include "editor/slider.hpp"
#include <QVBoxLayout>

FiltersContainer::FiltersContainer(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent)
    : QWidget(parent), image(image) {
  const auto layout = new QVBoxLayout(this);
  const auto gammaSlider = new Slider(this, "Gamma", image->gamma * 100, 0, 300);
  const auto brightnessSlider = new Slider(this, "Brightness", image->brightness * 100, 0, 500);
  const auto contrastSlider = new Slider(this, "Contrast", image->contrast * 100, 0, 300);
  const auto blurSlider = new Slider(this, "Blur", image->blur, 0, 5);
  const auto grayscaleSwitcher = new Checkbox(this, "Grayscale", image->isGrayscale);

  layout->addWidget(gammaSlider);
  layout->addWidget(brightnessSlider);
  layout->addWidget(contrastSlider);
  layout->addWidget(blurSlider);
  layout->addWidget(grayscaleSwitcher);

  connect(gammaSlider, &Slider::changed, this, [&, image](const int v) {
    image->setGamma(v / 100.f);
    emit changed();
  });
  connect(brightnessSlider, &Slider::changed, this, [&, image](const int v) {
    image->setBrightness(v / 100.f);
    emit changed();
  });
  connect(contrastSlider, &Slider::changed, this, [&, image](const int v) {
    image->setContrast(v / 100.f);
    emit changed();
  });
  connect(blurSlider, &Slider::changed, this, [&, image](const int v) {
    image->setBlur(v);
    emit changed();
  });
  connect(grayscaleSwitcher, &Checkbox::changed, this, [&, image](const Qt::CheckState v) {
    image->setGrayscale(v == Qt::CheckState::Checked);
    emit changed();
  });
};
