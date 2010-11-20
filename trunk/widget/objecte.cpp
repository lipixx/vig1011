#include "objecte.h"
#include "box.h"
#include <QtOpenGL/qgl.h>
#include "scene.h"

 Objecte::Objecte (std::string n, int mod, Point p, float scl, float ori):
nom (n),
model (mod),
pos (p),
scale (scl),
orientation (ori) 
{
  
Point pos_valid = *(new Point (p.x, p.y, p.z));
seleccionat = false;
} 

Objecte::~Objecte (void) 
{
} 

void
Objecte::validarPosicio () 
{
pos_valid.x = pos.x;
pos_valid.y = pos.y;
pos_valid.z = pos.z;
seleccionat = false;

}

void
Objecte::setSeleccionat(bool s)
{
    seleccionat = s;
}

void

Objecte::setLastPosicioValida () 
{
pos.x = pos_valid.x;
pos.y = pos_valid.y;
pos.z = pos_valid.z;
} 

void

Objecte::Render (std::vector < Model > &lmodels, GLenum mode, bool seleccionant, int idobj)
{
  
    //L'objecte té les dades de "modificació" que aplicarem
    //al model del seu objecte: scale, position, orientation
    //per tant agafarem el model i farem la transformació
    Model m = lmodels[this->getModelId ()];

    glMatrixMode (GL_MODELVIEW);
    Box caixa = m.boundingBox ();

    if (seleccionat)
    {
         Box capsaModel = this->getCapsaObjecte(m);
         capsaModel.Render(true);
    }
    else
    {
    //Per debugar, descomentem aquestes 2 linies
    //Box capsaModel = this->getCapsaObjecte(m);
    //capsaModel.Render(false);
    }

    glPushMatrix ();
    glTranslatef (pos.x, pos.y, pos.z);
    glRotatef (orientation, 0, 1, 0);
    glScalef (scale, scale, scale);
    glTranslatef (-(caixa.maxb.x + caixa.minb.x) / 2, -caixa.minb.y,
                     -(caixa.maxb.z + caixa.minb.z) / 2);
    m.Render (mode, seleccionant, idobj);
    glPopMatrix ();
} 

std::string Objecte::getNom () 
{
return nom;
}



int
Objecte::getModelId () 
{
    return model;
}



Point Objecte::getPosition () 
{ 
return pos;
}



void
Objecte::setPosition (Point p) 
{
pos.x = p.x;
pos.y = p.y;
pos.z = p.z;
} 

float
Objecte::getScale () 
{
return scale;
}



float
Objecte::getOrientation () 
{
return orientation;
}



void
Objecte::setOrientation (float ori) 
{
orientation = ori;
} 

Box & Objecte::getCapsaObjecte (Model & model) 
{
  //1.Agafem la bounding box del model
  Box caixaModel = model.boundingBox ();
  
  //2.Preparem la matriu (posició, scale i orientation)
  //per transformar la bounding del model. La setejem igual que al Render()
  //i hem de tenir en compte el glLoadIdentity ja que sino ens calcula
  //la caixa amb la matriu GL_MODELVIEW actual i que està "bruta".
  glMatrixMode (GL_MODELVIEW);
  glPushMatrix ();
  glLoadIdentity ();
  glTranslatef (pos.x, pos.y, pos.z);
  glRotatef (orientation, 0, 1, 0);
  glScalef (scale, scale, scale);
  glTranslatef (-(caixaModel.maxb.x + caixaModel.minb.x) / 2,
		 -caixaModel.minb.y,
		 -(caixaModel.maxb.z + caixaModel.minb.z) / 2);
  
    //3.Haurem de transformar cada punt de la bounding box, per això
    //haurem de crear una matriu amb el punt, i fer la multiplicació
    //a mà:
    vector < Vertex > &verts = model.vertices;  
    Box & capsaObj = *(new Box (Point (0, 0, 0), Point (0, 0, 0)));

    //Creem la matriu amb el punt
    GLfloat p1[16];
  
 for (unsigned int i = 0; i < verts.size (); ++i)
  {
    //Agafem el punt del vèrtex actual
    Point punt (verts[i].coord.x, verts[i].coord.y, verts[i].coord.z);

    //Inicialització
    for (int j = 4; j < 16; ++j)
        p1[j] = 0.0f;

    p1[0] = punt.x;
    p1[1] = punt.y;
    p1[2] = punt.z;
    p1[3] = 1;
    //Copiem la matriu actual per no perdre-la
    glPushMatrix ();
    //Multiplica la MODELVIEW per p1
    glMultMatrixf (p1);
    //El resultat de l'actual MODELVIEW el posem dins p1
    glGetFloatv (GL_MODELVIEW_MATRIX, p1);
    punt.x = p1[0];
    punt.y = p1[1];
    punt.z = p1[2];
    //Restaurem la matriu per tornar al punt inicial
    glPopMatrix ();
    if (i == 0) capsaObj.init(punt);
    else capsaObj.update (punt);
  }
glPopMatrix ();
   //4.Retornem la capsa
   return capsaObj;
}


