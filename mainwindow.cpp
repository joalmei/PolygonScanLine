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

    setWindowTitle(tr("Mid Point Algorithm Tester"));

    openGlCanvas = ui->centralWidget->findChild<CanvasOpenGL*>();
    mouseFollower = new MouseFollower(openGlCanvas);
    initCanvas();
}

// ==================================================================================================
MainWindow::~MainWindow() {
    delete ui;
    delete openGlCanvas;
    delete mouseFollower;
}


// ==================================================================================================
// PRIVATE MEMBERS
// ==================================================================================================
void MainWindow::initCanvas() {
    // creates polygon drawer and subcribes to on mouse click event in canvas
    polygonDrawer = new PolygonDrawer(openGlCanvas);
    polygonDrawer->Vertices.push_back(QPoint(0, 0));
    mouseFollower->AddPoint(&(polygonDrawer->Vertices.back()));

    openGlCanvas->OnMousePressed.push_back([this](QMouseEvent* e) {
        if (state != eAppState::DRAWING) { return; }

        mouseFollower->RemovePoint(&(polygonDrawer->Vertices.back()));
        polygonDrawer->Vertices.push_back(e->pos());
        mouseFollower->AddPoint(&(polygonDrawer->Vertices.back()));

        if (polygonDrawer->Vertices.size() == 3) {
            hintBox = new HintBoxDrawer(openGlCanvas);
            hintBox->Text = "Press \"Esc\" or \"Enter\" to quit edit mode";
            openGlCanvas->AddDrawer(hintBox);
        }
    });
    openGlCanvas->AddDrawer(polygonDrawer);

    state = eAppState::DRAWING;

    /*
    auto line = new LineDrawer(openGlCanvas);
    auto startPoint = new QPoint(0, 0);
    auto finalPoint = new QPoint(openGlCanvas->width(),openGlCanvas->height());
    auto follower = MouseFollower(finalPoint, openGlCanvas);
    line->Points = make_pair(startPoint, finalPoint);
    openGlCanvas->AddDrawer(line);
    */

}


// ==================================================================================================
// PRIVATE MEMBERS (slots)
// ==================================================================================================
void MainWindow::on_ClearButton_clicked() {
    // OBS: Qt defines on_<Button>_<Signal> as default callbacks for any UI element in the same object
    // To automatically create one, right click in the button/object and select "Go to slot"
    // and select the desired event. It will create the corresponding fct.
    this->ui->Canvas->ClearScreen();
    initCanvas();
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

// ==================================================================================================
void MainWindow::keyPressEvent(QKeyEvent* e) {
    if ((e->key() == Qt::Key_Escape) || (e->key() == Qt::Key_Enter) || (e->key() == Qt::Key_Return)) {
        state = eAppState::WAITING;
        mouseFollower->RemovePoint(&(polygonDrawer->Vertices.back()));
        hintBox->Dismiss();
    }
}
