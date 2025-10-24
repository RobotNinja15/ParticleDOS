/* A port of my shitty flow field visualizer on an actual DOS */

/////////////////////////////////////////
//PROGRAM START
////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>

//#include "perlin.c"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

#define NB 500
#define NOISE_SCALE 0.005f
#define NOISE_ANGLE 23.0f
#define NOISE_SPEED 2.5f

///////////////////////////
//PARTICLE OBJECT
//////////////////////////

typedef struct {
	int x;
	int y;
	int vx;
	int vy;

}particle_t;

particle_t particles[NB];

//far pointer to the clock
unsigned long far *clock = (unsigned long far *)0x0000046CL;




//////////////////////////
//MAIN
/////////////////////////

int main(void){
  int done = 0, i;
  float n;
  int driver = 1,  mode=1;

  initgraph(&driver, &mode, "");

  srand(*clock);

  for ( i = 0; i < NB ; i++){
	particles[i].x = rand() % SCREEN_WIDTH;
	particles[i].y = rand() % SCREEN_HEIGHT;

  }

  while(!done){

  for ( i = 0; i <NB; ++i){
       //float n = NOISE_ANGLE * noise2d(NOISE_SCALE*particles[i].x, NOISE_SCALE*particle[i].y);
	n = NOISE_ANGLE * random(NOISE_SCALE * particles[i].x - NOISE_SCALE*particles[i].y);
	particles[i].vx = NOISE_SPEED * cos(n);
	particles[i].vy = NOISE_SPEED * sin(n);

	particles[i].x += particles[i].vx;
	particles[i].y += particles[i].vy;

       putpixel(particles[i].x, particles[i].y, rand() % 250);
       //circle(particles[i].x, particles[i].y, rand() % 2);

	if(particles[i].x < 0) particles[i].x = SCREEN_WIDTH -1;
	if(particles[i].x >= SCREEN_WIDTH) particles[i].x = 0;
	if(particles[i].y < 0) particles[i].y = SCREEN_HEIGHT -1;
	if(particles[i].y >= SCREEN_HEIGHT) particles[i].y = 0;
  }

  delay(100);
  //getch();

  if(kbhit())
	break;

  }
  getch();
  closegraph();
  return 0;
}
