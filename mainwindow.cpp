#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polygondrawer.h"

#include "linedrawer.h"
#include "mousefollower.h"
#include "hintboxdrawer.h"


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


#include <QColorDialog>

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


