#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "canvasopengl.h"
#include "polygondrawer.h"

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
    Ui::MainWindow *ui;
    CanvasOpenGL* openGlCanvas;
    QColor color;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createPolygonDrawer();

private slots:
    void on_ClearButton_clicked();

    void on_ColorR_valueChanged(double arg1);
    void on_ColorG_valueChanged(double arg1);
    void on_ColorB_valueChanged(double arg1);
};

#endif // MAINWINDOW_H
