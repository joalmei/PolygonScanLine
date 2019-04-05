#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "canvasopengl.h"
#include "polygondrawer.h"
#include "mousefollower.h"
#include "hintboxdrawer.h"

#include <QMainWindow>
#include <QtGui>
#include <QWidget>
#include <QOpenGLWidget>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    enum eAppState {
        DRAWING,
        WAITING,
        EDITING,
    };

    eAppState state = eAppState::WAITING;

    Ui::MainWindow *ui;
    CanvasOpenGL* openGlCanvas;
    QColor color;
    MouseFollower* mouseFollower;

    PolygonDrawer* polygonDrawer;
    HintBoxDrawer* hintBox;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initCanvas();
    void keyPressEvent(QKeyEvent*);

private slots:
    void on_ClearButton_clicked();

    void on_ColorR_valueChanged(double);
    void on_ColorG_valueChanged(double);
    void on_ColorB_valueChanged(double);
};

#endif // MAINWINDOW_H
