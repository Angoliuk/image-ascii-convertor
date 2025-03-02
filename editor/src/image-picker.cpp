#include "editor/image-picker.hpp"
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>

ImagePicker::ImagePicker(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent)
    : QWidget(parent), image(image) {
  const auto layout = new QVBoxLayout(this);
  const auto selectorButton = new QPushButton("Select Image", this);

  layout->addWidget(selectorButton);

  connect(selectorButton, &QPushButton::clicked, this, &ImagePicker::openFilePicker);
}

void ImagePicker::openFilePicker() {
  if (const auto filePath = QFileDialog::getOpenFileName(this, "Select an Image", "", "Images (*.png *.jpg *.jpeg)");
    !filePath.isEmpty()) {
    const auto path = std::filesystem::path(filePath.toStdString());
    image->openFile(path);
    emit selected();
  }
}
