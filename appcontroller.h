#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "mainwindow.h"
#include "vertexholderdrawer.h"

#include "lightsource.h"
#include "camera.h"

#include <QVector3D>

class AppController : public QObject {
    Q_OBJECT
private:
    enum eAppState {
        DRAWING,
        WAITING,
        EDITING,
        VISUALIZING,
    };

    eAppState state = eAppState::WAITING;

    MainWindow* window;

    // UI
    HintBoxDrawer* hintBox;

    // EDIT MODE
    MouseFollower* mouseFollower;

    // POLYGON DATA
    PolygonDrawer* polygonDrawer;
    std::vector<VertexHolderDrawer*> holders;
    std::vector<QPoint*> vertices;

    // LIGHTING DATA
    //std::vector<QPoint*> lights;
    QVector3D light;
    LightSource* lighting;
    Camera* camera;
    QPoint mousePos;
    PolygonDrawer::Shading shading;

public:
    AppController(MainWindow*);
    ~AppController();

private:
    QPoint* createNewPoint(QPoint);
    void clearAllData();
    void subscribeMouseActions();

    void beginDrawing();
    void beginWaiting();
    void beginEditing();
    void beginVisualizing();

    void endDrawing();
    void endWaiting();
    void endEditing();
    void endVisualizing();

private slots:
    void onKeyReleased(int key);
    void onClearPressed();
    void onEditPressed();
    void onShadingChanged(const QString&);

    void onLightingValueChanged(int x, int y, int z);
    void onCameraRotationChanged(int x, int y, int z);

    void onCameraClippingChanged(int, int);
    void onCameraLimitsChanged(int, int, int, int);
    void onCameraFovChanged(double);
    void onCameraPerspectiveChanged(bool);
};

#endif // APPCONTROLLER_H
