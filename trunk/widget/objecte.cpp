#include "objecte.h"
#include "box.h"
#include <QtOpenGL/qgl.h>
#include "scene.h"

Objecte::Objecte(std::string n, int mod, Point p, float scl, float ori):
  nom(n), model(mod), pos(p), scale(scl), orientation(ori)
{}

Objecte::~Objecte(void)
{}

void Objecte::Render(std::vector<Model> &lmodels, GLenum mode)
{
  //L'objecte té les dades de "modificació" que aplicarem
  //al model del seu objecte: scale, position, orientation
  //per tant agafarem el model i farem la transformació
  Model m = lmodels[this->getModelId()];

 //(nom, model, pos,scale,orientation)
  Box caixa = m.boundingBox();

  float sx = caixa.maxb.x-caixa.minb.x;
  float sz = caixa.maxb.z-caixa.minb.z;

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  glTranslatef(pos.x,pos.y,pos.z);
  glRotatef(orientation,0,1,0);
  /*Definim la mida de l'obecte. El càlcul es fa amb el factor que té l'objecte
   que s'ha obtingut de l'XML, respecte la mida actual de la caixa contenidora
   de l'objecte. Recordem que la mida no té unitats, per això ho hem d'escalar
   respecte alguna cosa.*/
  glScalef(sx/(sx*scale),1,sz/(sz*scale));
  glTranslatef(-(caixa.maxb.x+caixa.minb.x)/2,-caixa.minb.y,-(caixa.maxb.z+caixa.minb.z)/2);

  //DEBUG
  //caixa.Render();

  m.Render(mode);
  glPopMatrix();
}

std::string Objecte::getNom()
{
  return nom;
}

int Objecte::getModelId()
{
  return model;
}

Point Objecte::getPosition()
{
   return pos;
}

float Objecte::getScale()
{
   return scale;
}

float Objecte::getOrientation()
{
   return orientation;
}

Box& Objecte::getCapsaObjecte(Model &model)
{
    //1.Agafem la bounding box del model
    Box caixaModel = model.boundingBox();

    //2.Preparem la matriu (posició, scale i orientation)
    //per transformar la bounding del model. La setejem igual que al Render()
    //i hem de tenir en compte el glLoadIdentity ja que sino ens calcula
    //la caixa amb la matriu GL_MODELVIEW actual i que està "bruta".
    float sx = caixaModel.maxb.x-caixaModel.minb.x;
    float sz = caixaModel.maxb.z-caixaModel.minb.z;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(pos.x,pos.y,pos.z);
    glRotatef(orientation,0,1,0);
    glScalef(sx/(sx*scale),1,sz/(sz*scale));
    glTranslatef(-(caixaModel.maxb.x+caixaModel.minb.x)/2,-caixaModel.minb.y,-(caixaModel.maxb.z+caixaModel.minb.z)/2);

    //3.Haurem de transformar cada punt de la bounding box, per això
    //haurem de crear una matriu amb el punt, i fer la multiplicació
    //a mà:
    vector<Vertex> &verts = model.vertices;

    //Inicialitzem amb la caps del polígon base
    Box & capsaObj = *(new Box(Point(-5,0,-5),Point(5,0,5)));

    //Creem la matriu amb el punt
    GLfloat p1[16];

    //i = 1 perquè el del poligon 0 l'hem posat a mà, i sabem que sempre
    //és el primer.
    for (unsigned int i=1; i < verts.size(); ++i)
    {
      //Agafem el punt del vèrtex actual
      Point punt(verts[i].coord.x, verts[i].coord.y, verts[i].coord.z);

      //Inicialització
      for (int i=4; i<16; ++i) p1[i]=0.0f;

      p1[0] = punt.x;
      p1[1] = punt.y;
      p1[2] = punt.z;
      p1[3] = 1;

      //Copiem la matriu actual per no perdre-la
      glPushMatrix();

      //Multiplica la MODELVIEW per p1
      glMultMatrixf(p1);

      //El resultat de l'actual MODELVIEW el posem dins p1
      glGetFloatv(GL_MODELVIEW_MATRIX, p1);
      punt.x = p1[0];
      punt.y = p1[1];
      punt.z = p1[2];

      //Restaurem la matriu per tornar al punt inicial
      glPopMatrix();

      //Maxb i Minb
      capsaObj.update(punt);
    }
    glPopMatrix();

    //4.Retornem la capsa
    return capsaObj;
}
