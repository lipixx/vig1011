#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFileDialog>
#include <QtOpenGL/qgl.h>
#include "point.h"
#include "scene.h"
#include "constants.h"
#define PI 3.1415926535898
#define RAD2DEG 180/PI
#define DEG2RAD PI/180

class GLWidget:public QGLWidget
{
Q_OBJECT public:
  GLWidget (QWidget * parent = 0);

protected:
  void initializeGL ();
  void paintGL ();
  void resizeGL (int width, int height);

  virtual void mousePressEvent (QMouseEvent * e);
  virtual void mouseReleaseEvent (QMouseEvent * e);
  virtual void mouseMoveEvent (QMouseEvent * e);
  virtual void keyPressEvent (QKeyEvent * event);
  virtual void wheelEvent (QWheelEvent * e);

  double dist, zNear, zFar, radi, angleX, angleY, aspect;
  GLfloat fovy, dynamic_fovy;
  Point VRP;
  Scene scene;
  InteractiveAction DoingInteractive;
  int xClick, yClick;

private:
    GLenum filferros;
  void setDefaultCamera ();
  bool posicionantObjecte, cameraOrtho, modificant_materials;
  void setModelView (int);
  void LoadObject(QString model);
  void pintarCub(int);
  bool debug;

signals:
    void filferrosChanged(bool);
    void nouSeleccionat(double esc,double alt);


  public slots:
    void LoadObject ();
    void resetCamera ();
    void setFilferros (bool);
    void setCameraOrtho ();
    void setPartsAmagades(bool);
    void carregaCub();
    void carregaPrisma();
    void carregaDoor();
    void carregaWindow();
    void carregaPyramid();
    void setHeightFocus(int h);
    void initializeLights();
    void alturaObjecte(double);
    void escalatObjecte(double);
    void restauraTranspas();
public:
  int getIdPosicionantObjecte();
  void getMaterialObj(int idObjecte, Material * c);
  void setMaterialObj(int idObjecte, Material * c);
  void modificantMaterials(bool);
   void activarDebugLlums(bool);
   void redefineixLlum(int i,bool activar);
   GLfloat amb_light[NUM_LIGHTS][4];
   GLfloat diff_light[NUM_LIGHTS][4];
   GLfloat spec_light[NUM_LIGHTS][4];
   GLfloat pos_light[NUM_LIGHTS][4];
   bool light_state[NUM_LIGHTS];
   GLenum light[NUM_LIGHTS];
};

#endif
