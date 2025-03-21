#include "editor/main-window.hpp"

#include "editor/ascii-preview.hpp"
#include "editor/filters-container.hpp"
#include "editor/image-editor-container.hpp"
#include "editor/image.hpp"
#include <QAction>
#include <QMenuBar>
#include <QVBoxLayout>

MainWindow::MainWindow() : QMainWindow() {
  setWindowTitle("Image Editor");
  resize(1200, 800);
  this->setMinimumWidth(1200);
  this->setMinimumHeight(800);

  const auto menuBar = this->menuBar();
  const auto fileMenu = menuBar->addMenu("&File");
  const auto openAction = new QAction("Open...", this);
  const auto saveAction = new QAction("Save", this);

  fileMenu->addAction(openAction);
  fileMenu->addAction(saveAction);

  auto tabWidget = new QTabWidget(this);

  auto editorTab = new QWidget();
  const auto editorLayout = new QVBoxLayout(editorTab);

  const auto image = std::make_shared<ImageWithFilters>();
  const auto imageEditorContainer = new ImageEditorContainer(image, this);

  editorLayout->addWidget(imageEditorContainer);

  connect(openAction, &QAction::triggered, imageEditorContainer, &ImageEditorContainer::openAction);
  connect(saveAction, &QAction::triggered, imageEditorContainer, &ImageEditorContainer::saveAction);

  auto asciiTab = new QWidget();
  const auto asciiLayout = new QVBoxLayout(asciiTab);

  const auto asciiPreview = new AsciiPreview(image, this);
  asciiLayout->addWidget(asciiPreview);

  connect(imageEditorContainer->imagePicker, &ImagePicker::selected, asciiPreview, &AsciiPreview::updatePreview);
  connect(
    imageEditorContainer->filtersContainer, &FiltersContainer::changed, asciiPreview, &AsciiPreview::updatePreview);

  tabWidget->addTab(editorTab, "Editor");
  tabWidget->addTab(asciiTab, "Ascii");

  this->setCentralWidget(tabWidget);
}
