#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

// ==================================================================================================
// PUBLIC MEMBERS
// ==================================================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    color(255, 255, 255){

    ui->setupUi(this);

    setWindowTitle(tr("Teste QT OK"));

    //auto widget = ui->centralWidget->findChild<QWidget*>("CanvasOpenGL", Qt::FindChildrenRecursively);
    openGlCanvas = ui->centralWidget->findChild<CanvasOpenGL*>();
}

MainWindow::~MainWindow() {
    delete ui;
    delete openGlCanvas;
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
    if(openGlCanvas == nullptr) {
        std::cout << "NULL " << std::endl;
        return;
    }
    color.setRed(static_cast<int>(red));
    openGlCanvas->SetPointsColor(color);
    std::cout << "red" << red << std::endl;
}

// ==================================================================================================
void MainWindow::on_ColorG_valueChanged(double green) {
    if(openGlCanvas == nullptr) {
        std::cout << "NULL " << std::endl;
        return;
    }
    color.setGreen(static_cast<int>(green));
    openGlCanvas->SetPointsColor(color);
    std::cout << "green" << green << std::endl;
}

// ==================================================================================================
void MainWindow::on_ColorB_valueChanged(double blue) {
    if(openGlCanvas == nullptr) {
        std::cout << "NULL " << std::endl;
        return;
    }
    color.setBlue(static_cast<int>(blue));
    openGlCanvas->SetPointsColor(color);
    std::cout << "blue" << blue << std::endl;
}
