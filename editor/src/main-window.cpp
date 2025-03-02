#include "editor/main-window.hpp"
#include "editor/image-editor-container.hpp"
#include "editor/image.hpp"
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>

MainWindow::MainWindow() : QMainWindow() {
  setWindowTitle("Image Editor");
  resize(400, 400);

  QMenuBar* menuBar = this->menuBar();
  QMenu* fileMenu = menuBar->addMenu("&File");
  QAction* openAction = new QAction("Open...", this);
  QAction* saveAction = new QAction("Save", this);
  QAction* saveToAction = new QAction("Save To...", this);

  //
  fileMenu->addAction(openAction);
  fileMenu->addAction(saveAction);
  fileMenu->addAction(saveToAction);
  fileMenu->addSeparator();
  // fileMenu->addAction(exitAction);
  //
  // // Connect exit action
  // connect(exitAction, &QAction::triggered, this, &QMainWindow::close);

  const auto centralWidget = new QWidget;
  setCentralWidget(centralWidget);

  const auto layout = new QVBoxLayout(centralWidget);

  const auto image = std::make_shared<ImageWithFilters>();
  const auto imageEditorContainer = new ImageEditorContainer(image, this);

  layout->addWidget(imageEditorContainer);
};
