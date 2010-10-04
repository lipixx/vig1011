#ifndef _Scene_H_
#define _Scene_H_
#include "objecte.h"
#include "model.h"
#include <QtOpenGL/qgl.h>


class Scene
{
 private:
	
  // Tindrem un vector amb els models geomètrics dels objectes geomètrics
  // i un altre amb instàncies seves (instàncies o referències a objectes).
  std::vector<Model> lmodels;
  std::vector<Objecte> lobjectes;
  
  
 public:
  static MaterialLib matlib;	  // col·lecció de materials

  Scene();

  void Init();
  void construirBase();
  void Render();
  void AddModel(Model &);
  void AddObjecte(Objecte &);
};

#endif

