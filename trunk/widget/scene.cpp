#include "scene.h"
#include <math.h>


MaterialLib Scene::matlib;

Scene::Scene()
{}

void Scene::Init()
{
  construirBase ();
}

void Scene::construirBase ()
{
  Model b("Base");

  // Construim el poligon base
  Vertex v1(Point(-5,0,-5));
  Vertex v2(Point(-5,0,5));
  Vertex v3(Point(5,0,5));
  Vertex v4(Point(5,0,-5));
  b.vertices.push_back(v1);
  b.vertices.push_back(v2);
  b.vertices.push_back(v3);
  b.vertices.push_back(v4);

  Face face(0,1,2,3);
  face.normal = Vector(0,1,0);
  face.material = 0;
  b.faces.push_back(face);

  b.updateBoundingBox();

  AddModel(b);
  Objecte oref("Base", 0, Point(0,0,0), 1, 0);
  AddObjecte(oref);
}

void Scene::Render()
{
  int numObjs = lobjectes.size();

  // Cal pintar tots els objectes de l'escena que es troben al vector
  for (int i=0;i<numObjs;i++)
      lobjectes[i].Render(lmodels);
}

void Scene::calculaEsfera(Point &centreEscena, float &radi)
{
    int numObjs = lobjectes.size();
    Box capsaEscena = *(new Box(Point(0,0,0),Point(0,0,0)));
    Box b;

    for (int i=0;i<numObjs;i++)
    {
        b = lobjectes[i].getCapsaObjecte();
        capsaEscena.update(b.minb);
        capsaEscena.update(b.maxb);
    }

    //Volem sumar dos Point i fer la meitat
    centreEscena =  (capsaEscena.maxb + capsaEscena.minb)/2.0;

    //Volem la longitut entre dos punts, Point.cpp ens ofereix length().
    radi = (capsaEscena.maxb - capsaEscena.minb).length() /2.0;
}

void Scene::AddModel(Model &o)
{
  lmodels.push_back(o);
}

void Scene::AddObjecte(Objecte &oref)
{
  lobjectes.push_back(oref);
}
