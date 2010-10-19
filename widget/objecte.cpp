#include "objecte.h"
#include "box.h"
#include <QtOpenGL/qgl.h>
#include "scene.h"

Objecte::Objecte(std::string n, int mod, Point p, float scl, float ori):
  nom(n), model(mod), pos(p), scale(scl), orientation(ori)
{}

Objecte::~Objecte(void)
{}

void Objecte::Render(std::vector<Model> &lmodels)
{
  //L'objecte té les dades de "modificació" que aplicarem
  //al model del seu objecte: scale, position, orientation
  //per tant agafarem el model i farem la transformació
  Model m = lmodels[this->getModelId()];

 //(nom, model, pos,scale,orientation)
  Box caixa = m.boundingBox();

  float sx = caixa.maxb.x-caixa.minb.x;
  float sy = caixa.maxb.y-caixa.minb.y;
  float sz = caixa.maxb.z-caixa.minb.z;

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  glTranslatef(pos.x,pos.y,pos.z);
  glRotatef(orientation,0,1,0);
  glScalef(sx/(sx*scale),1,sz/(sz*scale));
  glTranslatef(-(caixa.maxb.x+caixa.minb.x)/2,-caixa.minb.y,-(caixa.maxb.z+caixa.minb.z)/2);

  m.Render();
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

Box& Objecte::getCapsaObjecte()
{
    Box &capsaObj = *(new Box(Point(0,0,0),Point(0,0,0)));
    return capsaObj;
}
