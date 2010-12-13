#ifndef _OBJECTE_H_
#define _OBJECTE_H_
#include <vector>
#include <stdio.h>
#include <QtOpenGL/qgl.h>
#include "point.h"
#include "model.h"
#include "box.h"

 
using namespace std;


class Objecte 
{

protected:
std::string nom;
  
int model;			// identificador del model
  Point pos;			// posicio sobre el terra
  Point pos_valid;		// posició validada o la última bona
  float scale;			// mida en unitats
  float orientation;		//orientació respecte Y
  bool seleccionat;

public:
Objecte (std::string nom, int idmod, Point p, float scl,
	    float ori);
  
~Objecte (void);
  

void Render (std::vector < Model > &, GLenum mode, bool seleccionant, int idobj);
  
std::string getNom ();
int getModelId ();
Point getPosition ();
float getScale ();
float getOrientation ();
void setSeleccionat(bool s);
void setOrientation (float);
void setPosition (Point p);
void validarPosicio ();
void getPosicioValida ();
void setLastPosicioValida ();
  
Box & getCapsaObjecte (Model & model);

};



#endif	/* 
 */