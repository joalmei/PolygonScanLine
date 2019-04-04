#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polygondrawer.h"


// ==================================================================================================
// PUBLIC MEMBERS
// ==================================================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    color(255, 255, 255){

    ui->setupUi(this);

    setWindowTitle(tr("Teste QT OK"));

    openGlCanvas = ui->centralWidget->findChild<CanvasOpenGL*>();
    canvasDrawer = new PolygonDrawer();
    openGlCanvas->AddDrawer(canvasDrawer);
}

// ==================================================================================================
MainWindow::~MainWindow() {
    delete ui;
    delete openGlCanvas;
    delete canvasDrawer;
}

// ==================================================================================================
// PRIVATE MEMBERS (slots)
// ==================================================================================================
void MainWindow::on_ClearButton_clicked() {
    // OBS: Qt defines on_<Button>_<Signal> as default callbacks for any UI element in the same object
    // To automatically create one, right click in the button/object and select "Go to slot"
    // and select the desired event. It will create the corresponding fct.
    this->ui->Canvas->ClearScreen();
}

// ==================================================================================================
void MainWindow::on_ColorR_valueChanged(double red) {
    color.setRed(static_cast<int>(red));
    openGlCanvas->SetPointsColor(color);
}

// ==================================================================================================
void MainWindow::on_ColorG_valueChanged(double green) {
    color.setGreen(static_cast<int>(green));
    openGlCanvas->SetPointsColor(color);
}

// ==================================================================================================
void MainWindow::on_ColorB_valueChanged(double blue) {
    color.setBlue(static_cast<int>(blue));
    openGlCanvas->SetPointsColor(color);
}
