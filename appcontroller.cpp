#include "appcontroller.h"
#include "vertexholderdrawer.h"


// ==================================================================================================
// PUBLIC MEMBERS
// ==================================================================================================
AppController::AppController(MainWindow* window) {
    this->window = window;
    mouseFollower = new MouseFollower(window->Canvas());
    hintBox = nullptr;

    beginDrawing();
    subscribeMouseActions();

    connect(window, &MainWindow::keyReleased, this, &AppController::onKeyReleased);
    connect(window, &MainWindow::clearPressed, this, &AppController::onClearPressed);
    connect(window, &MainWindow::editPressed, this, &AppController::onEditPressed);
    connect(window, &MainWindow::lightingValueChanged, this, &AppController::onLightingValueChanged);
    connect(window, &MainWindow::cameraRotationChanged, this, &AppController::onCameraRotationChanged);
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

    auto vertex = new VertexHolderDrawer(window->Canvas(), point);
    holders.push_back(vertex);
    vertices.push_back(point);
    window->Canvas()->AddDrawer(vertex);

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
    if(hintBox != nullptr) {
        delete hintBox;
        hintBox = nullptr;
    }

    delete lighting;
    delete camera;
}

// ==================================================================================================
// PUBLIC MEMBERS (SLOTS)
// ==================================================================================================
void AppController::onKeyReleased(int key) {
    if (((key == Qt::Key_Escape) || (key == Qt::Key_Enter) || (key == Qt::Key_Return))) {
        if (state == eAppState::DRAWING)
            endDrawing();
        else if (state == eAppState::WAITING)
            endWaiting();
        else if (state == eAppState::EDITING)
            endEditing();

        //beginWaiting();
        beginVisualizing();
    }
}

// ==================================================================================================
void AppController::onClearPressed() {
    if (vertices.size() > 0)
        mouseFollower->RemovePoint(vertices.back());
    clearAllData();
    window->Canvas()->ClearScreen();

    // reset canvas
    beginDrawing();
}

// ==================================================================================================
void AppController::onEditPressed() {
    if (state != eAppState::VISUALIZING) return;
    endVisualizing();
    beginWaiting();
}

// ==================================================================================================
void AppController::onLightingValueChanged(int x, int y, int z) {
    light.setX(x);
    light.setY(y);
    light.setZ(z);

    window->Canvas()->update();
}

void AppController::onCameraRotationChanged(int x, int y, int z) {
    QVector3D rot(x, y, z);
    camera->SetRotation(rot);

    window->Canvas()->update();
}

// ==================================================================================================

#include <iostream>
void AppController::subscribeMouseActions() {
    // DRAWING BEHAVIOUR
    window->Canvas()->OnMousePressed.push_back([this](QMouseEvent* e) {
        if (state != eAppState::DRAWING) { return; }

        mouseFollower->RemovePoint(vertices.back());
        auto point = createNewPoint(e->pos());
        mouseFollower->AddPoint(point);

        if (polygonDrawer->Vertices.size() == 3) {
            hintBox = new HintBoxDrawer(window->Canvas());
            hintBox->Text = "Press \"Esc\" or \"Enter\" to quit edit mode";
            window->Canvas()->AddDrawer(hintBox);
        }
    });

    // START VERTEX HIGHLIGHT
    window->Canvas()->OnMouseMoved.push_back([this](QMouseEvent* e) {
        if (state != eAppState::WAITING) { return; }

        size_t closest = 0;
        float minDist = 100000000;

        for (size_t i = 0; i < vertices.size(); i++) {
            auto dist = QVector2D(*vertices[i] - e->pos()).lengthSquared();
            if (dist < minDist) {
                closest = i;
                minDist = dist;
            }
        }

        if (minDist > 500) { closest = 0; }

        for (size_t i = 0; i < holders.size(); i++)
            holders[i]->setIsSelected(i == closest);
    });

    // SETUP WAITING TRANSITION
    window->Canvas()->OnMousePressed.push_back([this](QMouseEvent* e) {
       if (state != eAppState::WAITING) { return; }

       for (auto h : holders)
           if (h->IsSelected()) {
               mouseFollower->AddPoint(h->Vertex());
               endWaiting();
               beginEditing();
           }

       (void) e;
    });

    // SETUP EDITING TRANSITION
    window->Canvas()->OnMouseReleased.push_back([this](QMouseEvent* e) {
        if (state != eAppState::EDITING) { return; }
        endEditing();
        beginWaiting();

        (void) e;
    });

    // SETUP VISUALIZATION
    window->Canvas()->OnMouseMoved.push_back([this](QMouseEvent* e) {
        if (state != eAppState::VISUALIZING) { return; }
        GLint dx = e->x() - this->mousePos.x();
        GLint dy = e->y() - this->mousePos.y();

        if (e->buttons() & Qt::LeftButton) {
            QVector3D rot(2*dy, 2*dx, 0);
            camera->Rotate(rot);
            std::cout << dx << " " << dy << std::endl;
        }

        this->mousePos = e->pos();

        window->Canvas()->update();
    });
}
// ==================================================================================================
// STATE MACHINE
// ==================================================================================================
void AppController::beginDrawing() {
    // creates polygon drawer and subcribes to on mouse click event in canvas
    state = eAppState::DRAWING;

    camera = new Camera(QVector3D(0, 0, 0), QVector3D(0, 0, 0));
    light.setZ(1);
    lighting = new LightSource(LightSource::Type::DIRECTIONAL, &light, 1.0);


    polygonDrawer = new PolygonDrawer(window->Canvas(), lighting, camera);
    window->Canvas()->AddDrawer(polygonDrawer);

    auto point = createNewPoint(QPoint(-10, -10));
    mouseFollower->AddPoint(point);
}

void AppController::beginWaiting() {
    state = eAppState::WAITING;

    if (polygonDrawer->Vertices.size() == 3) {
        hintBox = new HintBoxDrawer(window->Canvas());
        hintBox->Text = "Press \"Esc\" or \"Enter\" to quit edit mode";
        window->Canvas()->AddDrawer(hintBox);
    }
}

void AppController::beginEditing() {
    state = eAppState::EDITING;
}

void AppController::beginVisualizing() {
    state = eAppState::VISUALIZING;
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

void AppController::endVisualizing() {
    window->onReset();
}
