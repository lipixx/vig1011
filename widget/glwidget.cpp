#include "glwidget.h"
#include <math.h>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    filferros = false;
}

void GLWidget::resetCamera()
{
    setDefaultCamera();
    updateGL();
}

void GLWidget::setFilferros(bool toggle)
{
    if (toggle)
    {
    if (filferros)
        filferros = false;
    else
        filferros = true;
}
    cout << "togle:" << toggle << endl;
    cout << "fil:" << filferros << endl;
}

void GLWidget::setDefaultCamera()
{
    scene.calculaEsfera(VRP,radi);
    dist = 2*radi;
    zFar = radi;
    zNear = 3*radi;
    angleX = 15;
    angleY = -30;
    fovy = (float) 2 * atanf(radi/dist) * RAD2DEG;
    dynamic_fovy = fovy;
}

void GLWidget::initializeGL()
{
  glClearColor(0.4f, 0.4f, 0.8f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  scene.Init();
  setDefaultCamera();
}

void GLWidget::resizeGL (int width, int height)
{
  glViewport (0, 0, width, height);
  aspect = (float) width/height;

  if (aspect < 1)
      dynamic_fovy=atan(tan(fovy*DEG2RAD/2)/aspect)*RAD2DEG*2;

  updateGL();
}

void GLWidget::paintGL( void )
{
  // Esborrem els buffers
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 glTranslatef(0,0,-dist);
 glRotatef(angleX,1,0,0);
 glRotatef(angleY,0,1,0);
 glTranslatef(-VRP.x,-VRP.y,-VRP.z);

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 if (aspect < 1)
     gluPerspective(dynamic_fovy,aspect,zNear,zFar);
   else
     gluPerspective(fovy,aspect,zNear,zFar);

 // dibuixar eixos aplicacio
  glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
  glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(20,0,0); // X
  glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,20,0); // Y
  glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,20); // Z
  glEnd();

  scene.Render();
}

void GLWidget::mousePressEvent( QMouseEvent *e)
{
  xClick = e->x();
  yClick = e->y();

  if (e->button()&Qt::LeftButton &&
      ! (e->modifiers()&(Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
  {
    DoingInteractive = ROTATE;
  }
  else if (e->button()&Qt::LeftButton &&  e->modifiers() &Qt::ShiftModifier)
  {
    DoingInteractive = ZOOM;
  }
  else if (e->button()&Qt::LeftButton &&  e->modifiers() &Qt::ControlModifier)
  {
    DoingInteractive = PAN;
  }
}

void GLWidget::keyPressEvent(QKeyEvent *e)
{
  switch (e->key())
  {
    case Qt::Key_F:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        updateGL();
        break;
    case Qt::Key_S:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        updateGL();
        break;
    default: e->ignore();
  }
}

void GLWidget::mouseReleaseEvent( QMouseEvent *)
{
  DoingInteractive = NONE;
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
  // Aqui cal que es calculi i s'apliqui la rotaci, el zoom o el pan
  // com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotacio
      angleX= angleX + (e->y()-yClick)/2.0;
      angleY= angleY + (e->x()-xClick)/2.0;
  }
  else if (DoingInteractive == ZOOM)
  {
    // Fem el zoom

  }
  else if (DoingInteractive==PAN)
  {
    // Fem el pan

  }
  xClick = e->x();
  yClick = e->y();
  updateGL();

}

void GLWidget::LoadObject()
{
  QString model = QFileDialog::getOpenFileName(this, tr("Open File"), "../data", tr("Objectes (*.obj)"));
  if (model != "")
  {
    // Aquí cal fer el codi per a carregar el model escollit

  }
}
