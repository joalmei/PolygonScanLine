#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "mainwindow.h"

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

    MouseFollower* mouseFollower;
    PolygonDrawer* polygonDrawer;
    HintBoxDrawer* hintBox;

public:
    AppController(MainWindow*);

private:
    void initCanvas();

private slots:
    void onKeyReleased(int key);
    void onClearPressed();
};

#endif // APPCONTROLLER_H
