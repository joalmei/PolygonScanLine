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
void MainWindow::on_hMinValue_valueChanged(double h) {
    openGlCanvas->sethMin(h);
}

void MainWindow::on_hMaxValue_valueChanged(double h) {
    openGlCanvas->sethMax(h);
}

void MainWindow::on_vMinValue_valueChanged(double v) {
    openGlCanvas->setvMin(v);
}

void MainWindow::on_vMaxValue_valueChanged(double v) {
    openGlCanvas->setvMax(v);
}

void MainWindow::on_nearValue_valueChanged(double n) {
    openGlCanvas->setNear(n);
}

void MainWindow::on_farValue_valueChanged(double f) {
    openGlCanvas->setFar(f);
}

void MainWindow::on_fovyValue_valueChanged(double fov) {
    openGlCanvas->setFovY(fov);
}

void MainWindow::on_isPerspective_stateChanged(int state) {
    (void) state;
    openGlCanvas->toggleProjection();
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
    // Projection
    this->ui->hMinValue->setValue(-50.0);
    this->ui->hMaxValue->setValue(50.0);
    this->ui->vMinValue->setValue(-50.0);
    this->ui->vMaxValue->setValue(50.0);

    this->ui->nearValue->setValue(10.0);
    this->ui->farValue->setValue(50.0);

    this->ui->fovyValue->setValue(100.0);
    this->ui->isPerspective->setCheckState(Qt::Unchecked);

    // Observer
    this->ui->obsXValue->setValue(0.0);
    this->ui->obsYValue->setValue(0.0);
    this->ui->obsZValue->setValue(0.0);
    emit cameraRotationChanged(0, 0, 0);

    // Lighting
    this->ui->lightValueX->setValue(openGlCanvas->width()/2);
    this->ui->lightValueY->setValue(openGlCanvas->height()/2);
    this->ui->lightValueZ->setValue(-10);
    emit lightingValueChanged(0, 0, 1);
    this->ui->toningValue->setCurrentIndex(0);
    emit shadingChanged("Flat");

    openGlCanvas->sethMin(-50);
    openGlCanvas->sethMax(50);
    openGlCanvas->setvMin(-50);
    openGlCanvas->setvMax(50);
    openGlCanvas->setNear(10);
    openGlCanvas->setFar(50);
    openGlCanvas->setFovY(100);
    openGlCanvas->setxRot(0);
    openGlCanvas->setyRot(0);
    openGlCanvas->setzRot(0);
}

void MainWindow::on_editButton_released() {
    emit editPressed();
}
