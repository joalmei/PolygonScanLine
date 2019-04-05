#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "mainwindow.h"
#include "vertexholderdrawer.h"

class AppController : public QObject {
    Q_OBJECT
private:
    enum eAppState {
        DRAWING,
        WAITING,
        EDITING,
    };

    eAppState state = eAppState::WAITING;

    MainWindow* window;
    CanvasOpenGL* canvas;

    // UI
    HintBoxDrawer* hintBox;

    // EDIT MODE
    MouseFollower* mouseFollower;

    // POLYGON DATA
    PolygonDrawer* polygonDrawer;
    std::vector<VertexHolderDrawer*> holders;
    std::vector<QPoint*> vertices;

public:
    AppController(MainWindow*);
    ~AppController();

private:
    void initCanvas();
    QPoint* createNewPoint(QPoint);
    void clearAllData();

private slots:
    void onKeyReleased(int key);
    void onClearPressed();
};

#endif // APPCONTROLLER_H
