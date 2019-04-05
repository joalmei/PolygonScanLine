#include "appcontroller.h"
#include "vertexholderdrawer.h"


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
AppController::~AppController() {
    clearAllData();
}

// ==================================================================================================
// PRIVATE MEMBERS
// ==================================================================================================
void AppController::initCanvas() {
    // creates polygon drawer and subcribes to on mouse click event in canvas
    state = eAppState::DRAWING;

    polygonDrawer = new PolygonDrawer(canvas);
    canvas->AddDrawer(polygonDrawer);

    auto point = createNewPoint(QPoint());
    mouseFollower->AddPoint(point);

    canvas->OnMousePressed.push_back([this](QMouseEvent* e) {
        if (state != eAppState::DRAWING) { return; }

        mouseFollower->RemovePoint(vertices.back());
        auto point = createNewPoint(e->pos());
        mouseFollower->AddPoint(point);

        if (polygonDrawer->Vertices.size() == 3) {
            hintBox = new HintBoxDrawer(canvas);
            hintBox->Text = "Press \"Esc\" or \"Enter\" to quit edit mode";
            canvas->AddDrawer(hintBox);
        }
    });
}

// ==================================================================================================
QPoint* AppController::createNewPoint(QPoint pos) {
    auto point  = new QPoint(pos);
    polygonDrawer->Vertices.push_back(point);

    auto vertex = new VertexHolderDrawer(canvas, point);
    holders.push_back(vertex);
    vertices.push_back(point);
    canvas->AddDrawer(vertex);

    return point;
}

// ==================================================================================================
void AppController::clearAllData() {
    for (auto v : vertices)
        delete v;
    vertices.clear();
    for (auto h : holders)
        delete h;
    holders.clear();
    delete polygonDrawer;
    delete hintBox;
}

// ==================================================================================================
// PUBLIC MEMBERS (SLOTS)
// ==================================================================================================
void AppController::onKeyReleased(int key) {
    if ((key == Qt::Key_Escape) || (key == Qt::Key_Enter) || (key == Qt::Key_Return)) {
        state = eAppState::WAITING;
        mouseFollower->RemovePoint(polygonDrawer->Vertices.back());
        hintBox->Dismiss();

        canvas->OnMouseMoved.push_back([this](QMouseEvent* e) {
            int closest = -1;
            float minDist = 100000000;

            for (int i = 0; i < vertices.size(); i++) {
                auto dist = QVector2D(*vertices[i] - e->pos()).lengthSquared();
                if (dist < minDist) {
                    closest = i;
                    minDist = dist;
                }
            }

            if (minDist > 500) { closest = -1; }

            for (int i = 0; i < holders.size(); i++)
                holders[i]->setIsSelected(i == closest);
        });
    }
}

// ==================================================================================================
void AppController::onClearPressed() {
    mouseFollower->RemovePoint(vertices.back());
    clearAllData();
    canvas->ClearScreen();

    // reset canvas
    initCanvas();
}
