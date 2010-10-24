#include "glwidget.h"
#include <math.h>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    filferros = GL_POLYGON;
    posicionantObjecte = false;
}

void GLWidget::resetCamera()
{
    setDefaultCamera();
    updateGL();
}

void GLWidget::setFilferros()
{
  filferros = GL_LINE_LOOP;
  updateGL();
}

void GLWidget::unsetFilferros()
{
  filferros = GL_POLYGON;
  updateGL();
}

void GLWidget::setDefaultCamera()
{
    scene.calculaEsfera(VRP,radi);
    dist = 2*radi;
    zFar = 3*radi;
    zNear = 1*radi;
    angleX = 15;
    angleY = -30;
    fovy = (float) 2.2 * atanf(radi/dist) * RAD2DEG;
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
  aspect = (float) width/ (float) height;

  if (aspect < 1)
      dynamic_fovy=atan(tan(fovy*DEG2RAD/2)/aspect)*RAD2DEG*2;

  updateGL();
}

void GLWidget::paintGL( void )
{
  // Esborrem els buffers
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 if (aspect < 1)
     gluPerspective(dynamic_fovy,aspect,zNear,zFar);
   else
     gluPerspective(fovy,aspect,zNear,zFar);

 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 glTranslatef(0,0,-dist);
 glRotatef(angleX,1,0,0);
 glRotatef(angleY,0,1,0);
 glTranslatef(-VRP.x,-VRP.y,-VRP.z);

 // dibuixar eixos aplicacio
  glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
  glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(20,0,0); // X
  glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,20,0); // Y
  glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,20); // Z
  glEnd();

  scene.Render(filferros);
}

void GLWidget::mousePressEvent( QMouseEvent *e)
{
  xClick = e->x();
  yClick = e->y();

  if (e->button()&Qt::RightButton && posicionantObjecte)
    posicionantObjecte = false;

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
      filferros = GL_LINE_LOOP;
      updateGL();
      break;
    case Qt::Key_S:
      filferros = GL_POLYGON;
      updateGL();
      break;   
    default: e->ignore();
    }
  
  if (posicionantObjecte)
    {
      int value = -1;
      
      if (e->modifiers()&Qt::ShiftModifier)
	{
	  switch (e->key())
	    {
	    case Qt::Key_X:
	      value = XPOS;
	      break;
	    case Qt::Key_Z:
	      value = ZPOS;
	      break;	      
	    default:
	      break;
	    }
	}
	  else
	    {
	      switch (e->key())
		{		  
		case Qt::Key_X:
		  value = XNEG;
		  break;
		case Qt::Key_Z:
		  value = ZNEG;
		  break;
		default: break;
		}
	    }
      scene.mouDarrerObjecte(value);
      updateGL();
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
    const char *mod = (model.toStdString()).c_str();
    scene.carregaModel(mod);
    setDefaultCamera();
    posicionantObjecte = true;
    updateGL();
  }
}
