#include "scene.h"
#include <math.h>


MaterialLib
  Scene::matlib;

Scene::Scene ()
{
}

void
Scene::Init ()
{
  construirBase ();
}

void
Scene::construirBase ()
{
  Model b ("Base");

  // Construim el poligon base
  Vertex v1 (Point (-5, 0, -5));
  Vertex v2 (Point (-5, 0, 5));
  Vertex v3 (Point (5, 0, 5));
  Vertex v4 (Point (5, 0, -5));
  b.vertices.push_back (v1);
  b.vertices.push_back (v2);
  b.vertices.push_back (v3);
  b.vertices.push_back (v4);

  Face face (0, 1, 2, 3);
  face.normal = Vector (0, 1, 0);
  face.material = 0;
  b.faces.push_back (face);

  b.updateBoundingBox ();

  AddModel (b);
  Objecte oref ("Base", 0, Point (0, 0, 0), 1, 0);
  AddObjecte (oref);
}

void
Scene::Render (GLenum mode)
{
  int numObjs = lobjectes.size ();

  // Cal pintar tots els objectes de l'escena que es troben al vector
  for (int i = 0; i < numObjs; i++)
    lobjectes[i].Render (lmodels, mode);
}

void
Scene::calculaEsfera (Point & centreEscena, double &radi)
{
  int numObjs = lobjectes.size ();
  Box capsaEscena = *(new Box (Point (0, 0, 0), Point (0, 0, 0)));
  Box b;

  for (int i = 0; i < numObjs; i++)
    {
      b = lobjectes[i].getCapsaObjecte (lmodels[lobjectes[i].getModelId ()]);
      capsaEscena.update (b.minb);
      capsaEscena.update (b.maxb);
    }

  //Volem sumar dos Point i fer la meitat
  centreEscena = (capsaEscena.maxb + capsaEscena.minb) / 2;

  //Volem la longitut entre dos punts, Point.cpp ens ofereix length()
  //que executa la fórmula de càlcul del mòdul d'un vector
  radi = (capsaEscena.maxb - capsaEscena.minb).length () / 2.f;
}

void
Scene::AddModel (Model & o)
{
  lmodels.push_back (o);
}

void
Scene::AddObjecte (Objecte & oref)
{
  lobjectes.push_back (oref);
}

void
Scene::carregaModel (const char *filename)
{
  //1.Agafar el nom del model
  //2.Si NO existeix dins lmodel, crear-lo i inserir-lo
  Model m (filename);
  m.readObj (filename, Scene::matlib);

  int numModels = lmodels.size ();
  bool trobat = false;
  int i = 0;
  for (; i < numModels && !trobat; i++)
    {
      if (lmodels[i].getName () == filename)
	trobat = true;
    }
  if (!trobat)
    {
      this->AddModel (m);
      i = numModels;
    }
  else
    i--;
  //Calculem l'escalat. El costat més llarg de la base ha de ser 1.0
  Box caixa = m.boundingBox ();
  float sx = caixa.maxb.x - caixa.minb.x;
  float sz = caixa.maxb.z - caixa.minb.z;
  float scale;
  if (sx > sz)
    scale = 1.0 / sx;
  else
    scale = 1.0 / sz;

  //3.Amb l'identificador lmodel[i] corresponent, crear un objecte (centre000,escalat,orient0º)
  Objecte obj (filename, i, Point (0, 0, 0), scale, 0);
  this->AddObjecte (obj);
  idPosicionantObjecte = lobjectes.size () - 1;
}

void
Scene::mouDarrerObjecte (int sentit)
{
  Point p (0, 0, 0);
  switch (sentit)
    {
    case XNEG:
      p.x = -0.2;
      break;
    case XPOS:
      p.x = 0.2;
      break;
    case ZNEG:
      p.z = -0.2;
      break;
    case ZPOS:
      p.z = 0.2;
      break;
    case POS_INICIAL:
      lobjectes[idPosicionantObjecte].setLastPosicioValida ();
      break;
    default:
      break;
    }
  if (sentit != POS_INICIAL)
    {
      Point actual = lobjectes[idPosicionantObjecte].getPosition ();
      lobjectes[idPosicionantObjecte].setPosition (actual + p);
    }
}

void
Scene::mouDarrerObjecte (Point u, Point v)
{
  u /= 50;
  v /= 50;
  Point actual = lobjectes[idPosicionantObjecte].getPosition ();
  lobjectes[idPosicionantObjecte].setPosition (actual + u + v);
}

void
Scene::orientaDarrerObjecte (int sentit)
{
  float gir;
  if (sentit == YPOS)
    gir = -10;
  else
    gir = 10;
  lobjectes[idPosicionantObjecte].
    setOrientation (lobjectes[idPosicionantObjecte].getOrientation () + gir);
}

bool Scene::detectaColisio(Box &obj1, Box &obj2)
{
    bool resultat = false;

    cout << "Obj1 min: " << obj1.minb << " Obj1 max: " << obj1.maxb << endl;
    cout << "Obj2 min: " << obj2.minb << " Obj2 max: " << obj2.maxb << endl;
    //Pla X
    if (obj1.maxb.x > obj2.maxb.x)
    {
       if (obj1.minb.x < obj2.maxb.x) resultat = true;
       if (obj1.minb.x == obj2.maxb.x) resultat = false;
       if (obj1.minb.x > obj2.maxb.x) resultat = false;
    }
   if (obj1.maxb.x == obj2.maxb.x)
    {
        resultat = true;
    }

    if (obj1.maxb.x < obj2.maxb.x)
    {
        if (obj2.minb.x < obj1.maxb.x) resultat = true;
        if (obj2.minb.x > obj1.maxb.x) resultat = false;
        if (obj2.minb.x == obj1.maxb.x) resultat = false;
    }

    //Pla Z
    if (resultat) //Si colisiona en X
    {
        if (obj1.maxb.z > obj2.maxb.z)
           {
              if (obj1.minb.z < obj2.maxb.z) resultat = true;
              if (obj1.minb.z == obj2.maxb.z) resultat = false;
              if (obj1.minb.z > obj2.maxb.z) resultat = false;
           }
          if (obj1.maxb.z == obj2.maxb.z)
           {
               resultat = true;
           }

           if (obj1.maxb.z < obj2.maxb.z)
           {
               if (obj2.minb.z < obj1.maxb.z) resultat = true;
               if (obj2.minb.z > obj1.maxb.z) resultat = false;
               if (obj2.minb.z == obj1.maxb.z) resultat = false;
           }
    }
    return resultat;
}

bool
Scene::validarPosicio ()
{
  bool colisio = false;
  Box capsaUltimObjectePosicionat = lobjectes[idPosicionantObjecte].getCapsaObjecte (lmodels[lobjectes[idPosicionantObjecte].getModelId ()]);

  for (unsigned int i = 1; i < lobjectes.size () && !colisio; i++)
    {
      if ((int) i != idPosicionantObjecte)
	{
          Box capsaObjecte = lobjectes[i].getCapsaObjecte (lmodels[lobjectes[i].getModelId ()]);
          colisio = detectaColisio(capsaUltimObjectePosicionat,capsaObjecte);
	}
    }


  if (colisio)			//Si les caixes intercepten, no validar!
    {
      cout << "Pos. NO-VALIDADA, SEGUEIX POSICIONANT" << endl;
      return false;
    }
  else
    {
      lobjectes[idPosicionantObjecte].validarPosicio ();
      cout << "Pos. VALIDADA" << endl;
      return true;
    }
}
