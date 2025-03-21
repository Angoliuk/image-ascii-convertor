#include "editor/ascii-preview.hpp"
#include <QVBoxLayout>

AsciiPreview::AsciiPreview(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent)
    : QWidget(parent), image(image) {
  const auto layout = new QVBoxLayout(this);

  text = new QTextBrowser(this);
  text->setFixedWidth(1200);
  text->setFixedHeight(1024);
  text->setFont(QFont("Courier", 9));

  updatePreview();

  layout->addWidget(text);
}

void AsciiPreview::updatePreview() const {
  auto asciiArt = image->getASCII();
  auto ascii = QString::fromStdString(asciiArt);
  text->setPlainText(ascii);
}

void AsciiPreview::updateImage() const {
  updatePreview();
}
