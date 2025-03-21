#include "editor/edited-image-preview.hpp"
#include <QVBoxLayout>

EditedImagePreview::EditedImagePreview(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent)
    : QWidget(parent), image(image) {
  const auto layout = new QVBoxLayout(this);

  label = new QLabel(this);
  label->setAlignment(Qt::AlignCenter);
  label->setStyleSheet("border: 1px solid black;");

  updateImageView();

  layout->addWidget(label);
}

void EditedImagePreview::updateImageView() const {
  if (image->edited) {
    image->apply();

    const auto img = QImage(image->edited->data.data(),
      image->edited->width,
      image->edited->height,
      image->edited->width * image->edited->channels,
      image->getGrayscale() ? QImage::Format_Grayscale8 : QImage::Format_RGB888);
    const QPixmap pixmap(QPixmap::fromImage(img));
    label->setPixmap(
      pixmap.scaled(image->edited->width, image->edited->height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
  }
}

void EditedImagePreview::updateImage() const {
  updateImageView();
}
