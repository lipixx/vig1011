#include "glwidget.h"
#include <math.h>

GLWidget::GLWidget (QWidget * parent):
QGLWidget (parent)
{
  filferros = GL_POLYGON;
  posicionantObjecte = false;
  cameraOrtho = false;
  modificant_materials = false;  
}

void
GLWidget::resetCamera ()
{
  setDefaultCamera ();
  updateGL ();
}

void
GLWidget::setFilferros (bool activar)
{
  if (activar) filferros = GL_LINE_LOOP;
  else filferros = GL_POLYGON;
  updateGL ();
}

void
GLWidget::setPartsAmagades (bool activar)
{
    if (activar){
    glEnable (GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    }
    else {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    }
    updateGL();
}

void
GLWidget::setCameraOrtho ()
{
  if (cameraOrtho)
    {
      cameraOrtho = false;
      glViewport (0, 0, (float) width (), (float) height ());
    }
  else
    cameraOrtho = true;
  updateGL ();
}

void
GLWidget::setDefaultCamera ()
{
  scene.calculaEsfera (VRP, radi);
  dist = 2 * radi;
  zFar = 3 * radi;
  zNear = 1 * radi;
  angleX = 15;
  angleY = -30;
  fovy = (float) 2.2 *atanf (radi / dist) * RAD2DEG;
  dynamic_fovy = fovy;
}

void
GLWidget::initializeGL ()
{
  glClearColor (0.4f, 0.4f, 0.8f, 1.0f);

  glEnable (GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  //Iniciem LIGHT0
  amb_light[0][0] = 0.025f;
  amb_light[0][1] = 0.025f;
  amb_light[0][2] = 0.025f;
  amb_light[0][3] = 0.025f;
  diff_light[0][0] = 0.5f;
  diff_light[0][1] = 0.5f;
  diff_light[0][2] = 0.5f;
  diff_light[0][3] = 0.5f;
  spec_light[0][0] = 0.5f;
  spec_light[0][1] = 0.5f;
  spec_light[0][2] = 0.5f;
  spec_light[0][3] = 0.5f;
  pos_light[0][0] = 0.0f;
  pos_light[0][1] = 5.0f;
  pos_light[0][2] = 0.0f;
  pos_light[0][3] = 0.0f;

  //Iniciem LIGHT1
  amb_light[1][0] = 0.015f;
  amb_light[1][1] = 0.015f;
  amb_light[1][2] = 0.015f;
  amb_light[1][3] = 0.015f;
  diff_light[1][0] = 0.3f;
  diff_light[1][1] = 0.3f;
  diff_light[1][2] = 0.3f;
  diff_light[1][3] = 0.3f;
  spec_light[1][0] = 0.3f;
  spec_light[1][1] = 0.3f;
  spec_light[1][2] = 0.3f;
  spec_light[1][3] = 0.3f;
  pos_light[1][0] = 0.0f;
  pos_light[1][1] = 0.0f;
  pos_light[1][2] = 0.0f;
  pos_light[1][3] = 0.0f;

  //Transparències
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //Model de colorat, GL_FLAT: ilum. constant, GL_SMOOTH: ilum. Gouraud.
  //glShadeModel(GL_SMOOTH);
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
  glEnable (GL_LIGHT1);
  glEnable(GL_NORMALIZE);
  scene.Init ();
  setDefaultCamera ();
}

void
GLWidget::resizeGL (int width, int height)
{
  glViewport (0, 0, width, height);
  aspect = (float) width / (float) height;

  if (aspect < 1)
    dynamic_fovy = atan (tan (fovy * DEG2RAD / 2) / aspect) * RAD2DEG * 2;

  updateGL ();
}

void
GLWidget::setModelView (int casView)
{

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  glTranslatef (0, 0, -dist);

  //Si volem veure on està el llum 1
  pintarCub(1);
  glLightfv(GL_LIGHT1,GL_AMBIENT,amb_light[1]);
  glLightfv(GL_LIGHT1,GL_DIFFUSE,diff_light[1]);
  glLightfv(GL_LIGHT1,GL_SPECULAR,spec_light[1]);
  glLightfv(GL_LIGHT1,GL_POSITION,pos_light[1]);

  switch (casView)
    {
    case CAM_PERSPECTIVE:
      glRotatef (angleX, 1, 0, 0);
      glRotatef (angleY, 0, 1, 0);
      break;
    case CAM_ORTHO_LEFT:
      glRotatef (90, 1, 0, 0);
      break;
    case CAM_ORTHO_RIGHT:
      //Do Nothing - For future implementations
      break;
    default:
      break;
    }

  glTranslatef (-VRP.x, -VRP.y, -VRP.z);

  //Si volem veure on està el llum 0
  pintarCub(0);

  glLightfv(GL_LIGHT0,GL_AMBIENT,amb_light[0]);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,diff_light[0]);
  glLightfv(GL_LIGHT0,GL_SPECULAR,spec_light[0]);
  glLightfv(GL_LIGHT0,GL_POSITION,pos_light[0]);

  // dibuixar eixos aplicacio
  glDisable (GL_LIGHTING);
  glBegin (GL_LINES);
  glColor3f (1, 0, 0);
  glVertex3f (0, 0, 0);
  glVertex3f (20, 0, 0);	// X
  glColor3f (0, 1, 0);
  glVertex3f (0, 0, 0);
  glVertex3f (0, 20, 0);	// Y
  glColor3f (0, 0, 1);
  glVertex3f (0, 0, 0);
  glVertex3f (0, 0, 20);	// Z
  glEnd ();
  glEnable(GL_LIGHTING);  
}

void
GLWidget::paintGL (void)
{
  // Esborrem els buffers
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  if (!cameraOrtho)
    {
      if (aspect < 1)
	gluPerspective (dynamic_fovy, aspect, zNear, zFar);
      else
	gluPerspective (fovy, aspect, zNear, zFar);
        setModelView (CAM_PERSPECTIVE);
        scene.Render (filferros);
    }
  else
    {
      float h = (float) height () / 2;
      float w = (float) width () / 2;
      glOrtho (-radi, radi, -radi / aspect, radi / aspect, zNear, zFar);
      //Part esquerra
      glViewport (0, h / 2, w, h);
      setModelView (CAM_ORTHO_LEFT);
      scene.Render (filferros);
      //Part dreta
      glViewport (w, h / 2, w, h);
      setModelView (CAM_ORTHO_RIGHT);
      scene.Render (filferros);
    }
}

void
GLWidget::mousePressEvent (QMouseEvent * e)
{
  xClick = e->x ();
  yClick = e->y ();

  if (e->button () & Qt::RightButton && posicionantObjecte && !modificant_materials)
    if (scene.validarPosicio ())
      {
        posicionantObjecte = false;
        updateGL();
      }

  if (e->button () & Qt::LeftButton
      && !(e->
	   modifiers () & (Qt::ShiftModifier | Qt::AltModifier | Qt::
			   ControlModifier)))
    {
      DoingInteractive = ROTATE;
    }
  else if (posicionantObjecte && e->button () & Qt::LeftButton
	   && e->modifiers () & Qt::ShiftModifier
	   && e->modifiers () & Qt::AltModifier)
    {
      DoingInteractive = MOV;
    }
  else if (e->button () & Qt::LeftButton
	   && e->modifiers () & Qt::ShiftModifier)
    {
      DoingInteractive = ZOOM;
    }
  else if (e->button () & Qt::LeftButton
	   && e->modifiers () & Qt::ControlModifier)
    {
      DoingInteractive = PAN;
    }
  else if (e->button() & Qt::MidButton && !modificant_materials)
  {
      if (posicionantObjecte)
          posicionantObjecte = !scene.validarPosicio();
      if (!posicionantObjecte)
      {
      char pixel;
      glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
      glDisable(GL_LIGHTING);
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      //Fem el render de l'escena falsament al back buffer
      scene.Render (filferros,true);
      //Llegim del backbuffer les coordenades
      glReadPixels(xClick,height()-yClick,1,1,GL_RED,GL_UNSIGNED_BYTE,&pixel);
      //Restaurem el color de fons
      glClearColor (0.4f, 0.4f, 0.8f, 1.0f);
      glEnable(GL_LIGHTING);
       if (scene.nouSeleccionat(pixel))
       {
           posicionantObjecte = true;
           updateGL();
       }
   }
  }
}

void
GLWidget::keyPressEvent (QKeyEvent * e)
{
  switch (e->key ())
    {
    case Qt::Key_F:
      filferros = GL_LINE_LOOP;
      emit filferrosChanged(true);
      break;
    case Qt::Key_S:
      filferros = GL_POLYGON;
      emit filferrosChanged(false);
      break;
    default:
      e->ignore ();
    }

  if (posicionantObjecte)
    {
      int value = -1;
      if (e->modifiers () & Qt::ShiftModifier)
	{
	  switch (e->key ())
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
	  switch (e->key ())
	    {
	    case Qt::Key_X:
	      value = XNEG;
	      break;
	    case Qt::Key_Z:
	      value = ZNEG;
	      break;
            case Qt::Key_Delete:
              if (!modificant_materials)
                {
                 scene.mouDarrerObjecte(AL_INFINIT);
                 posicionantObjecte = false;
                }
              break;
	    case Qt::Key_Escape:
              scene.mouDarrerObjecte(POS_INICIAL);
              if (scene.validarPosicio ())
              {
                  posicionantObjecte = false;
                  updateGL();
              }
	      break;
	    case Qt::Key_D:
	      scene.orientaDarrerObjecte (YPOS);
	      break;
	    case Qt::Key_E:
	      scene.orientaDarrerObjecte (YNEG);
	      break;
	    default:
	      break;
	    }
	}
      scene.mouDarrerObjecte (value);
    }
  updateGL ();
}

void
GLWidget::mouseReleaseEvent (QMouseEvent *)
{
  DoingInteractive = NONE;
}

void
GLWidget::mouseMoveEvent (QMouseEvent * e)
{
  // Aqui cal que es calculi i s'apliqui la rotaci, el zoom o el pan
  // com s'escaigui...
  if (DoingInteractive == ROTATE)
    {
      // Fem la rotacio
      angleX = angleX + (e->y () - yClick) / 2.0;
      angleY = angleY + (e->x () - xClick) / 2.0;
    }
  else if (DoingInteractive == ZOOM && !cameraOrtho)
    {
      // Fem el zoom
      if (dynamic_fovy + (e->y () - yClick) / 2 > 0
	  && dynamic_fovy + (e->y () - yClick) / 2 < 180)
	{
	  dynamic_fovy = dynamic_fovy + (e->y () - yClick) / 2;
	  fovy = dynamic_fovy;
	}
    }
  else if (DoingInteractive == PAN && !cameraOrtho)
    {
      // Fem el pan
      float m[4][4];
      glGetFloatv (GL_MODELVIEW_MATRIX, &m[0][0]);
      //Recordem que la primera fila de Modelview és la X d'observador en coord. d'app.(X0,X1,X2)
      //la segona fila és la Y d'observador (Y0,Y1,Y2)
      //la tercera fila és la z d'observador (Z0,Z1,Z2)
      //I que és un accés per columnes, no per files.
      Point x_obs = Point (m[0][0], m[1][0], m[2][0]) * (xClick - e->x ());
      Point y_obs = Point (m[0][1], m[1][1], m[2][1]) * (e->y () - yClick);
      VRP += (x_obs + y_obs) * 0.05;	//Multipliquem per obtenir suavitat
    }
  else if (DoingInteractive == MOV)
    {
      float m[4][4];
      glGetFloatv (GL_MODELVIEW_MATRIX, &m[0][0]);
      //Veure DOC per explicació
      Point u = Point (m[0][0], m[1][0], m[2][0]) * (e->x () - xClick);
      Point v = Point (m[2][0], m[1][0], -m[0][0]) * (yClick - e->y ());
      scene.mouDarrerObjecte (u, v);
    }
  xClick = e->x ();
  yClick = e->y ();
  updateGL ();
}

void GLWidget::LoadObject ()
{
 QString model = QFileDialog::getOpenFileName (this, tr ("Open File"), "../data",tr ("Objectes (*.obj)"));
 LoadObject(model);
}

void GLWidget::LoadObject(QString model)
{
    bool podemCarregar = true;

     if (posicionantObjecte)
     {
        podemCarregar = scene.validarPosicio();
     }
     if (model != "" && podemCarregar)
       {
         // Aquí cal fer el codi per a carregar el model escollit
         const char *mod = (model.toStdString ()).c_str ();
         scene.carregaModel (mod);
         //setDefaultCamera ();
         posicionantObjecte = true;
         updateGL ();
       }
}
void GLWidget::carregaCub(){ LoadObject(QString("../models/cub.obj"));}
void GLWidget::carregaPrisma(){ LoadObject(QString("../models/prisma.obj"));}
void GLWidget::carregaDoor(){ LoadObject(QString("../models/door.obj"));}
void GLWidget::carregaWindow(){ LoadObject(QString("../models/window.obj"));}
void GLWidget::carregaPyramid(){ LoadObject(QString("../models/pyramid.obj"));}


void
GLWidget::wheelEvent (QWheelEvent * e)
{
  //Descomentar si volem que s'hagi de pitjar shift per fer zoom
  //amb la roda.
  //  if (e->modifiers()&Qt::ShiftModifier)
  if (!cameraOrtho)
    {
      {
	//apropa_allunya és un enter + si hem d'apropar, i - si hem
	//d'allunyar
	int apropa_allunya = -1 * e->delta () / 15 / 8;

	//Factor de zoom de 3.2
	float factor_zoom = apropa_allunya * 3.2;

	if (dynamic_fovy + factor_zoom > 0
	    && dynamic_fovy + factor_zoom < 180)
	  {
	    dynamic_fovy = dynamic_fovy + factor_zoom;
	    fovy = dynamic_fovy;
	  }
      }

      e->accept ();

      xClick = e->x ();
      yClick = e->y ();
      updateGL ();
    }
}

int GLWidget::getIdPosicionantObjecte()
{
    if (posicionantObjecte)
        return scene.getSeleccionat();
    else
        return -1;
}

void GLWidget::getMaterialObj(int idObjecte, Material * c)
{
    scene.getMaterialObj(idObjecte,c);
}

void GLWidget::setMaterialObj(int idObjecte, Material * c)
{
    scene.setMaterialObj(idObjecte,c);
    updateGL();
}

void GLWidget::modificantMaterials(bool b)
{
    modificant_materials = b;
}

/***************DEBUG FUNCTIONS***************/
void
GLWidget::pintarCub(int element)
{
    float x,y,z;
    //Pintar el llum 0
    switch (element)
    {
       case 0:
          x = pos_light[0][0];
          y = pos_light[0][1];
          z = pos_light[0][2];
        break;
        case 1:
          x = pos_light[1][0];
          y = pos_light[1][1];
          z = pos_light[1][2];
        break;
        default:
        break;
    }


    glDisable (GL_LIGHTING);
     glBegin(GL_QUADS);	// Start Drawing The Cube
     glColor3f(0.0f,1.0f,0.0f);	// Set The Color To Green

     glVertex3f(x, y,z-1.0f);	// Top Right Of The Quad (Top)
     glVertex3f(x-1.0f, y,z-1.0f);	// Top Left Of The Quad (Top)
     glVertex3f(x-1.0f, y,z);	// Bottom Left Of The Quad (Top)
     glVertex3f(x, y,z);	// Bottom Right Of The Quad (Top)

     glColor3f(1.0f,0.5f,0.0f);	// Set The Color To Orange

     glVertex3f(x,y-1.0f,z);	// Top Right Of The Quad (Bottom)
     glVertex3f(x-1.0f,y-1.0f,z);	// Top Left Of The Quad (Bottom)
     glVertex3f(x-1.0f,y-1.0f,z-1.0f);	// Bottom Left Of The Quad (Bottom)
     glVertex3f(x,y-1.0f,z-1.0f);	// Bottom Right Of The Quad (Bottom)

     glColor3f(1.0f,0.0f,0.0f);	// Set The Color To Red

     glVertex3f(x, y,z);	// Top Right Of The Quad (Front)
     glVertex3f(x-1.0f, y,z);	// Top Left Of The Quad (Front)
     glVertex3f(x-1.0f,y-1.0f,z);	// Bottom Left Of The Quad (Front)
     glVertex3f(x,y-1.0f,z);	// Bottom Right Of The Quad (Front)

     glColor3f(1.0f,1.0f,0.0f);	// Set The Color To Yellow

     glVertex3f(x,y-1.0f,z-1.0f);	// Bottom Left Of The Quad (Back)
     glVertex3f(x-1.0f,y-1.0f,z-1.0f);	// Bottom Right Of The Quad (Back)
     glVertex3f(x-1.0f,y,z-1.0f);	// Top Right Of The Quad (Back)
     glVertex3f(x,y,z-1.0f);	// Top Left Of The Quad (Back)

     glColor3f(0.0f,0.0f,1.0f);	// Set The Color To Blue

     glVertex3f(x-1.0f,y,z);	// Top Right Of The Quad (Left)
     glVertex3f(x-1.0f,y,z-1.0f);	// Top Left Of The Quad (Left)
     glVertex3f(x-1.0f,y-1.0f,z-1.0f);	// Bottom Left Of The Quad (Left)
     glVertex3f(x-1.0f,y-1.0f,z);	// Bottom Right Of The Quad (Left)

     glColor3f(1.0f,0.0f,1.0f);	// Set The Color To Violet

     glVertex3f(x,y,z-1.0f);	// Top Right Of The Quad (Right)
     glVertex3f(x,y,z);	// Top Left Of The Quad (Right)
     glVertex3f(x,y-1.0f,z);	// Bottom Left Of The Quad (Right)
     glVertex3f(x,y-1.0f,z-1.0f);	// Bottom Right Of The Quad (Right)

     glEnd();// Done Drawing The Quad
     glEnable(GL_LIGHTING);
}
