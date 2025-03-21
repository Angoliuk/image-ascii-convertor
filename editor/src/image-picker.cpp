#include "editor/image-picker.hpp"
#include <QFileDialog>
#include <QVBoxLayout>

ImagePicker::ImagePicker(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent)
    : QWidget(parent), image(image) {
}

void ImagePicker::openFilePicker() {
  if (const auto filePath = QFileDialog::getOpenFileName(this, "Select an Image", "", "Images (*.png *.jpg *.jpeg)");
    !filePath.isEmpty()) {
    const auto path = std::filesystem::path(filePath.toStdString());
    image->openFile(path);
    emit selected();
  }
}
