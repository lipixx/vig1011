#ifndef _MODEL_H_
#define _MODEL_H_

#include <stdio.h>
#include <vector>
#include "vertex.h"
#include "box.h"
#include "face.h"
#include "material_lib.h"
#include <QtOpenGL/qgl.h>
  

// Model - permet representar un objecte 3D
  class Model 
{

  
    // llegeix un model en format OBJ
  void readObj (const char *filename, MaterialLib & matlib);
  
    // calcula la capsa del model
  void updateBoundingBox ();
  
    // retorna la capsa del model (previament s'ha d'haver calculat)
    Box boundingBox ()const;
  
  

  
  

				// vector amb els vertexs de l'objecte
  vector < Face > faces;	// vector amb les cares de l'objecte

  
};


#endif	/* 