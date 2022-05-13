#pragma once
#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
/*
#include "usr/include/SDL2/SDL.h"
#include "usr/include/SDL2/SDL2_gfxPrimitives.h"
#include "InputHandler.h"
*/
#include"Vector2D.h"
#include"InputHandler.h"



class Walker 
{
  int _x, _y;

  Vector2D* _taget;

  Vector2D* pos;
  Vector2D* vel;
  Vector2D* acc;

float maxspeed;
float maxforce;

int r;
float radian;

Vector2D*F;

Vector2D*dot1;
Vector2D*dot2;
Vector2D*dot3;



public:
  Walker(int x, int y);
  void draw(SDL_Renderer* renderer);
  void update();
  void seek();
void applyForce(Vector2D* force);
Vector2D Rotate(float x,float y,float rad);
void Edge();

};