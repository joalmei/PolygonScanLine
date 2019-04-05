#include "appcontroller.h"

// ==================================================================================================
// PUBLIC MEMBERS
// ==================================================================================================
AppController::AppController(MainWindow* window) {
    this->window = window;
    canvas = window->Canvas();
    mouseFollower = new MouseFollower(canvas);

    initCanvas();

    connect(window, &MainWindow::keyReleased, this, &AppController::onKeyReleased);
    connect(window, &MainWindow::clearPressed, this, &AppController::onClearPressed);
}

// ==================================================================================================
// PRIVATE MEMBERS
// ==================================================================================================
void AppController::initCanvas() {
    // creates polygon drawer and subcribes to on mouse click event in canvas
    polygonDrawer = new PolygonDrawer(canvas);
    polygonDrawer->Vertices.push_back(QPoint(0, 0));
    mouseFollower->AddPoint(&(polygonDrawer->Vertices.back()));

    canvas->OnMousePressed.push_back([this](QMouseEvent* e) {
        if (state != eAppState::DRAWING) { return; }

        mouseFollower->RemovePoint(&(polygonDrawer->Vertices.back()));
        polygonDrawer->Vertices.push_back(e->pos());
        mouseFollower->AddPoint(&(polygonDrawer->Vertices.back()));

        if (polygonDrawer->Vertices.size() == 3) {
            hintBox = new HintBoxDrawer(canvas);
            hintBox->Text = "Press \"Esc\" or \"Enter\" to quit edit mode";
            canvas->AddDrawer(hintBox);
        }
    });
    canvas->AddDrawer(polygonDrawer);

    state = eAppState::DRAWING;
}

// ==================================================================================================
// PUBLIC MEMBERS (SLOTS)
// ==================================================================================================
void AppController::onKeyReleased(int key) {
    if ((key == Qt::Key_Escape) || (key == Qt::Key_Enter) || (key == Qt::Key_Return)) {
        state = eAppState::WAITING;
        mouseFollower->RemovePoint(&(polygonDrawer->Vertices.back()));
        hintBox->Dismiss();
    }
}

// ==================================================================================================
void AppController::onClearPressed() {
    canvas->ClearScreen();
    mouseFollower->RemovePoint(&(polygonDrawer->Vertices.back()));
    initCanvas();
}
