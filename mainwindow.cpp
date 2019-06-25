#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polygondrawer.h"

#include "linedrawer.h"
#include "mousefollower.h"
#include "hintboxdrawer.h"

#include <QColorDialog>


// ==================================================================================================
// PUBLIC MEMBERS
// ==================================================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    color(255, 255, 255) {

    ui->setupUi(this);

    setWindowTitle(tr("Scan Line Algorithm Tester"));
    openGlCanvas = ui->centralWidget->findChild<CanvasOpenGL*>();

    onReset();
}

// ==================================================================================================
MainWindow::~MainWindow() {
    delete ui;
    delete openGlCanvas;
}

// ==================================================================================================
CanvasOpenGL* MainWindow::Canvas() const {
    return openGlCanvas;
}

// ==================================================================================================
// PRIVATE MEMBERS
// ==================================================================================================
void MainWindow::keyReleaseEvent(QKeyEvent* e) {
    emit keyReleased(e->key());
}


// ==================================================================================================
// PRIVATE MEMBERS (SLOTS)
// ==================================================================================================
void MainWindow::on_ClearButton_clicked() {
    // OBS: Qt defines on_<Button>_<Signal> as default callbacks for any UI element in the same object
    // To automatically create one, right click in the button/object and select "Go to slot"
    // and select the desired event. It will create the corresponding fct.
    emit clearPressed();
}

// ==================================================================================================
void MainWindow::on_changeColor_released() {
    //QColorDialogTester color_test;
    //color_test.onColor();

    QColor color = QColorDialog::getColor(this->color, this );
    if( color.isValid() )
    {
        this->color = color;
        openGlCanvas->SetPointsColor(color);
    }
}


// ==================================================================================================
void MainWindow::on_obsXValue_valueChanged(double x) {
    emit cameraRotationChanged(static_cast<int>(x),
                               static_cast<int>(this->ui->obsYValue->value()),
                               static_cast<int>(this->ui->obsZValue->value()));
}

void MainWindow::on_obsYValue_valueChanged(double y) {
    emit cameraRotationChanged(static_cast<int>(this->ui->obsXValue->value()),
                               static_cast<int>(y),
                               static_cast<int>(this->ui->obsZValue->value()));
}

void MainWindow::on_obsZValue_valueChanged(double z) {
    emit cameraRotationChanged(static_cast<int>(this->ui->obsXValue->value()),
                               static_cast<int>(this->ui->obsYValue->value()),
                               static_cast<int>(z));
}

// ==================================================================================================
void MainWindow::on_lightValueX_valueChanged(double x) {
    emit lightingValueChanged(static_cast<int>(x),
                              static_cast<int>(this->ui->lightValueY->value()),
                              static_cast<int>(this->ui->lightValueZ->value()));
}

void MainWindow::on_lightValueY_valueChanged(double y) {
    emit lightingValueChanged(static_cast<int>(this->ui->lightValueX->value()),
                              static_cast<int>(y),
                              static_cast<int>(this->ui->lightValueZ->value()));
}

void MainWindow::on_lightValueZ_valueChanged(double z) {
    emit lightingValueChanged(static_cast<int>(this->ui->lightValueX->value()),
                              static_cast<int>(this->ui->lightValueY->value()),
                              static_cast<int>(z));
}


// ==================================================================================================
void MainWindow::on_toningValue_currentTextChanged(const QString &shading) {
    emit shadingChanged(shading);
}

// ==================================================================================================
void MainWindow::on_ResetButton_released() {
    onReset();
}


void MainWindow::onReset() {
    // Observer
    this->ui->obsXValue->setValue(0.0);
    this->ui->obsYValue->setValue(0.0);
    this->ui->obsZValue->setValue(0.0);
    emit cameraRotationChanged(0, 0, 0);

    // Lighting
    this->ui->lightValueX->setValue(openGlCanvas->width()/2);
    this->ui->lightValueY->setValue(openGlCanvas->height()/2);
    this->ui->lightValueZ->setValue(-100);
    emit lightingValueChanged(openGlCanvas->width()/2, openGlCanvas->height()/2, -100);
    this->ui->toningValue->setCurrentIndex(0);
    emit shadingChanged("Flat");
}

void MainWindow::on_editButton_released() {
    emit editPressed();
}
