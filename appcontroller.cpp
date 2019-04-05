#include "appcontroller.h"
#include "vertexholderdrawer.h"


// ==================================================================================================
// PUBLIC MEMBERS
// ==================================================================================================
AppController::AppController(MainWindow* window) {
    this->window = window;
    canvas = window->Canvas();
    mouseFollower = new MouseFollower(canvas);

    beginDrawing();
    subscribeMouseActions();

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
    if (((key == Qt::Key_Escape) || (key == Qt::Key_Enter) || (key == Qt::Key_Return)) &&
            state == eAppState::DRAWING) {
        endDrawing();
        beginWaiting();
    }
}

// ==================================================================================================
void AppController::onClearPressed() {
    mouseFollower->RemovePoint(vertices.back());
    clearAllData();
    canvas->ClearScreen();

    // reset canvas
    beginDrawing();
}

// ==================================================================================================
void AppController::subscribeMouseActions() {
    // DRAWING BEHAVIOUR
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

    // START VERTEX HIGHLIGHT
    canvas->OnMouseMoved.push_back([this](QMouseEvent* e) {
        if (state != eAppState::WAITING) { return; }

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

    // SETUP WAITING TRANSITION
    canvas->OnMousePressed.push_back([this](QMouseEvent* e) {
       if (state != eAppState::WAITING) { return; }

       for (auto h : holders)
           if (h->IsSelected()) {
               mouseFollower->AddPoint(h->Vertex());
               endWaiting();
               beginEditing();
           }
    });

    // SETUP EDITING TRANSITION
    canvas->OnMouseReleased.push_back([this](QMouseEvent* e) {
        if (state != eAppState::EDITING) { return; }
        endEditing();
        beginWaiting();
    });
}

// ==================================================================================================
// STATE MACHINE
// ==================================================================================================
void AppController::beginDrawing() {
    // creates polygon drawer and subcribes to on mouse click event in canvas
    state = eAppState::DRAWING;

    polygonDrawer = new PolygonDrawer(canvas);
    canvas->AddDrawer(polygonDrawer);

    auto point = createNewPoint(QPoint(-10, -10));
    mouseFollower->AddPoint(point);
}

void AppController::beginWaiting() {
    state = eAppState::WAITING;
}
void AppController::beginEditing() {
    state = eAppState::EDITING;
}

void AppController::endDrawing() {
    mouseFollower->RemovePoint(polygonDrawer->Vertices.back());
    hintBox->Dismiss();
}

void AppController::endWaiting() {

}
void AppController::endEditing() {
    for (auto h : holders)
       if (h->IsSelected()) {
           mouseFollower->RemovePoint(h->Vertex());
       }
}
