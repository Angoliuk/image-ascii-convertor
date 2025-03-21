#include "editor/original-image-preview.hpp"
#include <QVBoxLayout>

OriginalImagePreview::OriginalImagePreview(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent)
    : QWidget(parent), image(image) {
  const auto layout = new QVBoxLayout(this);
  label = new QLabel(this);
  label->setAlignment(Qt::AlignCenter);
  label->setStyleSheet("border: 1px solid black;");

  updateImageView();

  layout->addWidget(label);
}

void OriginalImagePreview::updateImageView() const {
  if (image->original) {
    const auto img = QImage(image->original->data.data(),
      image->original->width,
      image->original->height,
      image->original->width * image->original->channels,
      image->getGrayscale() ? QImage::Format_Grayscale8 : QImage::Format_RGB888);
    const QPixmap pixmap(QPixmap::fromImage(img));
    label->setPixmap(pixmap);
  }
}

void OriginalImagePreview::updateImage() const {
  updateImageView();
}
