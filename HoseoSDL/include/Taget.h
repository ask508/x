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

class Taget
{
	int _x, _y;
	int r;

	Vector2D* pos;
	Vector2D* vel;
	Vector2D* acc;



public:
	Taget(int x, int y);
	void draw(SDL_Renderer* renderer);
	void update();
	void applyForce(Vector2D* force);
	Vector2D Rotate(float x, float y, float rad);
	void Edge();
	Vector2D getPos();
	Vector2D getVel();


};