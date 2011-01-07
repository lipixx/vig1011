#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define PI 3.1415926535898
#define RAD2DEG 180/PI
#define DEG2RAD PI/180
#define NUM_LIGHTS 5

typedef  enum {NONE, ROTATE, ZOOM, PAN, MOV} InteractiveAction;
typedef  enum {CAM_PERSPECTIVE,CAM_ORTHO_LEFT,CAM_ORTHO_RIGHT} camSelection;
typedef  enum {XPOS,XNEG,ZPOS,ZNEG,YPOS,YNEG,POS_INICIAL,AL_INFINIT} universeStates;

#endif // CONSTANTS_H
