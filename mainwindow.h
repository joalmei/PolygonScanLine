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

// ATRIBUTES
private:
    Ui::MainWindow *ui;
    CanvasOpenGL* openGlCanvas;
    QColor color;


// METHODS
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    CanvasOpenGL* Canvas() const;

private:
    void keyReleaseEvent(QKeyEvent*);


// SIGNALS / SLOTS
signals:
    void keyReleased(int);
    void clearPressed();

private slots:
    void on_ClearButton_clicked();
    void on_changeColor_released();
};

#endif // MAINWINDOW_H
