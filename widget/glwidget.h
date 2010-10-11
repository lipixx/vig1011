#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFileDialog>
#include "point.h"
#include "scene.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);

protected:
    void initializeGL ();

    void setDefaultCamera();
    void paintGL ();
    void resizeGL (int width, int height);

    virtual void mousePressEvent (QMouseEvent *e);
    virtual void mouseReleaseEvent (QMouseEvent *e);
    virtual void mouseMoveEvent (QMouseEvent *e);
    virtual void keyPressEvent (QKeyEvent *event);

    double dist, zNear, zFar, radi, angleX, angleY, fovy, aspect;
    Point VRP;
    Scene scene;

    typedef  enum {NONE, ROTATE, ZOOM, PAN} InteractiveAction;
    InteractiveAction DoingInteractive;

    int   xClick, yClick;

 public slots:
     void LoadObject ();
};

#endif
