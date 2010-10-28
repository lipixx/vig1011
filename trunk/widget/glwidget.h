#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFileDialog>
#include <QtOpenGL/qgl.h>
#include "point.h"
#include "scene.h"
#define PI 3.1415926535898
#define RAD2DEG 180/PI
#define DEG2RAD PI/180
#define CAM_PERSPECTIVE 0
#define CAM_ORTHO_LEFT 1
#define CAM_ORTHO_RIGHT 2
class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);

protected:
    void initializeGL ();
    void paintGL ();
    void resizeGL (int width, int height);

    virtual void mousePressEvent (QMouseEvent *e);
    virtual void mouseReleaseEvent (QMouseEvent *e);
    virtual void mouseMoveEvent (QMouseEvent *e);
    virtual void keyPressEvent (QKeyEvent *event);
    virtual void wheelEvent(QWheelEvent *e);

    double dist, zNear, zFar, radi, angleX, angleY, aspect;
    GLfloat fovy, dynamic_fovy;


    Point VRP;
    Scene scene;

    typedef  enum {NONE, ROTATE, ZOOM, PAN} InteractiveAction;
    InteractiveAction DoingInteractive;

    int   xClick, yClick;

private:
     void setDefaultCamera();
     GLenum filferros;
     bool posicionantObjecte, cameraOrtho;
     void setModelView(int);

 public slots:
     void LoadObject ();
     void resetCamera();
     void setFilferros();
     void setCameraOrtho();
     void unsetFilferros();
};

#endif
