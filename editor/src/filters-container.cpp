#include "editor/filters-container.hpp"
#include "editor/components/checkbox.hpp"
#include "editor/components/slider.hpp"
#include <QVBoxLayout>

FiltersContainer::FiltersContainer(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent)
    : QWidget(parent), image(image) {
  const auto layout = new QVBoxLayout(this);

  const auto rFactorSlider = new Slider(this, "R Factor", image->getRFactor() * 100, 0, 500);
  const auto gFactorSlider = new Slider(this, "G Factor", image->getGFactor() * 100, 0, 500);
  const auto bFactorSlider = new Slider(this, "B Factor", image->getBFactor() * 100, 0, 500);
  const auto sepiaSlider = new Slider(this, "Sepia", image->getSepia() * 100, 0, 100);
  const auto gammaSlider = new Slider(this, "Gamma", image->getGamma() * 100, 0, 300);
  const auto brightnessSlider = new Slider(this, "Brightness", image->getBrightness() * 100, 0, 500);
  const auto contrastSlider = new Slider(this, "Contrast", image->getContrast() * 100, 0, 300);
  const auto blurSlider = new Slider(this, "Blur", image->getBlur(), 0, 5);
  const auto grayscaleSwitcher = new Checkbox(this, "Grayscale", image->getGrayscale());

  layout->addWidget(rFactorSlider);
  layout->addWidget(gFactorSlider);
  layout->addWidget(bFactorSlider);
  layout->addWidget(gammaSlider);
  layout->addWidget(brightnessSlider);
  layout->addWidget(contrastSlider);
  layout->addWidget(blurSlider);
  layout->addWidget(grayscaleSwitcher);
  layout->addWidget(sepiaSlider);

  connect(rFactorSlider, &Slider::changed, this, [&, image](const int v) {
    image->setRFactor(v / 100.f);
    emit changed();
  });
  connect(gFactorSlider, &Slider::changed, this, [&, image](const int v) {
    image->setGFactor(v / 100.f);
    emit changed();
  });
  connect(bFactorSlider, &Slider::changed, this, [&, image](const int v) {
    image->setBFactor(v / 100.f);
    emit changed();
  });
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
  connect(sepiaSlider, &Slider::changed, this, [&, image](const int v) {
    image->setSepia(v / 100.f);
    emit changed();
  });
  connect(grayscaleSwitcher, &Checkbox::changed, this, [&, image](const Qt::CheckState v) {
    image->setGrayscale(v == Qt::CheckState::Checked);
    emit changed();
  });

  this->setMinimumWidth(500);
  this->setMaximumWidth(800);
  layout->setSpacing(0);
  layout->addStretch();
  layout->setContentsMargins(0, 0, 0, 0);
}
