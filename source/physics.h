#ifndef PHYSICS_H
#define PHYSICS_H


typedef struct {
	int x;
	int y;
}IVEC_t;

typedef struct {
	float x;
	float y;
}FVEC_t;

typedef struct {
	float x;
	float xp;
	float y;
	float yp;
	float a;
	float ap;
}ROCKET_STATE_t;

typedef struct {
	float Ft;
	float Tt;
}ROCKET_INPUT_t;



void physics_predict_orbit( IVEC_t * result, ROCKET_STATE_t x, int N);



#endif
