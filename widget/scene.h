#ifndef _Scene_H_
#define _Scene_H_
#include "objecte.h"
#include "model.h"
#include <QtOpenGL/qgl.h>
#include <box.h>

#define XPOS 0
#define XNEG 1
#define ZPOS 2
#define ZNEG 3

class Scene
{
 private:
	
  // Tindrem un vector amb els models geomètrics dels objectes geomètrics
  // i un altre amb instàncies seves (instàncies o referències a objectes).
  std::vector<Model> lmodels;
  std::vector<Objecte> lobjectes;
  int  idPosicionantObjecte;

public:
  static MaterialLib matlib;	  // col·lecció de materials

  Scene();

  void Init();
  void construirBase();
  void Render(GLenum mode);
  void AddModel(Model &);
  void AddObjecte(Objecte &);
  void carregaModel(const char* filename);
  void calculaEsfera(Point &centreEscena, double &radi);
  void mouDarrerObjecte(int);
};

#endif

