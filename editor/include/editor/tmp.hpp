// #pragma once
//
// #include "editor/image.hpp"
// #include "editor/utils.hpp"
// #include "tmp.hpp"
//
// #include <QApplication>
// #include <QCheckBox>
// #include <QFileDialog>
// #include <QLabel>
// #include <QMainWindow>
// #include <QPixmap>
// #include <QPushButton>
// #include <QSlider>
// #include <QVBoxLayout>
// #include <QWidget>
//
// class Checkbox final : public QWidget {
//   Q_OBJECT
//
// public:
//   explicit Checkbox(QWidget* parent, const QString& labelText = "", const bool initial = false) : QWidget(parent) {
//     const auto layout = new QVBoxLayout(this);
//
//     const auto checkbox = new QCheckBox(labelText, this);
//     checkbox->setCheckState(initial ? Qt::Checked : Qt::Unchecked);
//
//     layout->addWidget(checkbox);
//
//     connect(checkbox, &QCheckBox::checkStateChanged, this, &Checkbox::changed);
//   };
//
// signals:
//   void changed(Qt::CheckState value);
//
// private:
// };
//
// class Slider final : public QWidget {
//   Q_OBJECT
//
// public:
//   explicit Slider(
//     QWidget* parent, const QString& labelText = "", const int initial = 0, const int min = 0, const int max = 100)
//       : QWidget(parent) {
//     const auto layout = new QVBoxLayout(this);
//     const auto label = new QLabel(labelText + ":", this);
//
//     const auto slider = new QSlider(Qt::Horizontal, this);
//     slider->setRange(min, max);
//     slider->setValue(initial);
//
//     layout->addWidget(label);
//     layout->addWidget(slider);
//
//     connect(slider, &QSlider::valueChanged, this, &Slider::changed);
//   };
//
// signals:
//   void changed(int value);
//
// private:
// };
//
// class FiltersContainer final : public QWidget {
//   Q_OBJECT
//
// public:
//   explicit FiltersContainer(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent)
//       : QWidget(parent), image(image) {
//     const auto layout = new QVBoxLayout(this);
//     const auto gammaSlider = new Slider(this, "Gamma", image->gamma * 100, 0, 300);
//     const auto brightnessSlider = new Slider(this, "Brightness", image->brightness * 100, 0, 500);
//     const auto contrastSlider = new Slider(this, "Contrast", image->contrast * 100, 0, 300);
//     const auto blurSlider = new Slider(this, "Blur", image->blur, 0, 5);
//     const auto grayscaleSwitcher = new Checkbox(this, "Grayscale", image->isGrayscale);
//
//     layout->addWidget(gammaSlider);
//     layout->addWidget(brightnessSlider);
//     layout->addWidget(contrastSlider);
//     layout->addWidget(blurSlider);
//     layout->addWidget(grayscaleSwitcher);
//
//     connect(gammaSlider, &Slider::changed, this, [&, image](const int v) {
//       image->setGamma(v / 100.f);
//       emit changed();
//     });
//     connect(brightnessSlider, &Slider::changed, this, [&, image](const int v) {
//       image->setBrightness(v / 100.f);
//       emit changed();
//     });
//     connect(contrastSlider, &Slider::changed, this, [&, image](const int v) {
//       image->setContrast(v / 100.f);
//       emit changed();
//     });
//     connect(blurSlider, &Slider::changed, this, [&, image](const int v) {
//       image->setBlur(v);
//       emit changed();
//     });
//     connect(grayscaleSwitcher, &Checkbox::changed, this, [&, image](const Qt::CheckState v) {
//       image->setGrayscale(v == Qt::CheckState::Checked);
//       emit changed();
//     });
//   };
//
// signals:
//   void changed();
//
// private:
//   std::shared_ptr<ImageWithFilters> image;
// };
//
// class OriginalImagePreview final : public QWidget {
//   Q_OBJECT
//
// public:
//   explicit OriginalImagePreview(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent)
//       : QWidget(parent), image(image) {
//     const auto layout = new QVBoxLayout(this);
//     label = new QLabel(this);
//     label->setAlignment(Qt::AlignCenter);
//     label->setStyleSheet("border: 1px solid black;");
//
//     updateImageView();
//
//     layout->addWidget(label);
//   };
//   void updateImageView() const {
//     if (image->original) {
//       const auto img = QImage(image->original->data.data(),
//         image->original->width,
//         image->original->height,
//         image->original->width * image->original->channels,
//         image->isGrayscale ? QImage::Format_Grayscale8 : QImage::Format_RGB888);
//       QPixmap pixmap(QPixmap::fromImage(img));
//       label->setPixmap(pixmap);
//       label->setScaledContents(true);
//     }
//   };
//
// public slots:
//   void updateImage() const {
//     updateImageView();
//   }
//
// private:
//   QLabel* label;
//   std::shared_ptr<ImageWithFilters> image;
// };
//
// class EditedImagePreview final : public QWidget {
//   Q_OBJECT
//
// public:
//   explicit EditedImagePreview(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent)
//       : QWidget(parent), image(image) {
//     const auto layout = new QVBoxLayout(this);
//
//     label = new QLabel(this);
//     label->setAlignment(Qt::AlignCenter);
//     label->setStyleSheet("border: 1px solid black;");
//
//     updateImageView();
//
//     layout->addWidget(label);
//   };
//
//   void updateImageView() const {
//     if (image->edited) {
//       image->use();
//
//       const auto img = QImage(image->edited->data.data(),
//         image->edited->width,
//         image->edited->height,
//         image->edited->width * image->edited->channels,
//         image->isGrayscale ? QImage::Format_Grayscale8 : QImage::Format_RGB888);
//       const QPixmap pixmap(QPixmap::fromImage(img));
//       label->setPixmap(pixmap);
//       label->setScaledContents(true);
//     }
//   };
//
// public slots:
//   void updateImage() const {
//     updateImageView();
//   }
//
// private:
//   QLabel* label;
//   std::shared_ptr<ImageWithFilters> image;
// };
//
// class ImageContainer final : public QWidget {
//   Q_OBJECT
//
// public:
//   explicit ImageContainer(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent)
//       : QWidget(parent), image(image) {
//     const auto layout = new QVBoxLayout(this);
//     originalImagePreview = new OriginalImagePreview(image, this);
//     editedImagePreview = new EditedImagePreview(image, this);
//
//     layout->addWidget(originalImagePreview);
//     layout->addWidget(editedImagePreview);
//   };
//
// public slots:
//   void openedNewImage() const {
//     originalImagePreview->updateImage();
//     editedImagePreview->updateImage();
//   }
//
//   void filtersChanged() const {
//     editedImagePreview->updateImage();
//   }
//
// private:
//   OriginalImagePreview* originalImagePreview;
//   EditedImagePreview* editedImagePreview;
//   std::shared_ptr<ImageWithFilters> image;
// };
//
// class ImagePicker final : public QWidget {
//   Q_OBJECT
//
// public:
//   explicit ImagePicker(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent)
//       : QWidget(parent), image(image) {
//     const auto layout = new QVBoxLayout(this);
//     const auto selectorButton = new QPushButton("Select Image", this);
//
//     layout->addWidget(selectorButton);
//
//     connect(selectorButton, &QPushButton::clicked, this, &ImagePicker::openFilePicker);
//   }
//
// signals:
//   void selected();
//
// private slots:
//   void openFilePicker() {
//     if (const auto filePath = QFileDialog::getOpenFileName(this, "Select an Image", "", "Images (*.png *.jpg
//     *.jpeg)");
//       !filePath.isEmpty()) {
//       const auto path = std::filesystem::path(filePath.toStdString());
//       image->openFile(path);
//       emit selected();
//     }
//   }
//
// private:
//   std::shared_ptr<ImageWithFilters> image;
// };
//
// class ImageEditorContainer final : public QWidget {
//   Q_OBJECT
//
// public:
//   explicit ImageEditorContainer(const std::shared_ptr<ImageWithFilters>& image, QWidget* parent)
//       : QWidget(parent), image(image) {
//     const auto layout = new QHBoxLayout(this);
//     const auto imageContainer = new ImageContainer(image, this);
//     const auto imagePicker = new ImagePicker(image, this);
//     const auto filtersContainer = new FiltersContainer(image, this);
//
//     layout->addWidget(imagePicker);
//     layout->addWidget(filtersContainer);
//     layout->addWidget(imageContainer);
//
//     connect(imagePicker, &ImagePicker::selected, imageContainer, &ImageContainer::openedNewImage);
//     connect(filtersContainer, &FiltersContainer::changed, imageContainer, &ImageContainer::filtersChanged);
//   };
//
// private:
//   std::shared_ptr<ImageWithFilters> image;
// };
//
// class MainWindow final : public QMainWindow {
//   Q_OBJECT
//
// public:
//   explicit MainWindow() : QMainWindow() {
//     setWindowTitle("Image Editor");
//     resize(400, 400);
//
//     const auto centralWidget = new QWidget;
//     setCentralWidget(centralWidget);
//
//     const auto layout = new QVBoxLayout(centralWidget);
//
//     const auto image = std::make_shared<ImageWithFilters>();
//     const auto imageEditorContainer = new ImageEditorContainer(image, this);
//
//     layout->addWidget(imageEditorContainer);
//   };
//
// private:
// };
