#include "Taget.h"
#include <random>
Taget:: Taget(int x, int y)
{
    _x = x;
    _y = y;
    r = 16;
    pos = new Vector2D(x, y);
    vel = new Vector2D(0, 0);
    acc = new Vector2D(0, 0);

}
void Taget::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);


    filledCircleColor(renderer, _x, _y, 16, 0xFFFFFFFF);


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
void Taget::update()
{
    Edge();
    Vector2D dirF(50.0f,10.0f);
    applyForce(&dirF);

    *vel += *acc;
    vel->limit(10.0f);

    Vector2D aa(vel->getX(), vel->getY());
    *pos += aa;

    _x = pos->getX();
    _y = pos->getY();

}
void Taget::applyForce(Vector2D* force)
{
    *acc += *force;
}
Vector2D Taget::Rotate(float x, float y, float rad)
{
    Vector2D t(0, 0);

    return t;
}
void Taget::Edge()
{
    if (pos->getX() > 600 + r)
    {
        pos->setX(-r);
    }
    else if (pos->getX() < -r)
    {
        pos->setX(600 + r);
    }

    if (pos->getY() > 400 + r)
    {
        pos->setY(-r);
    }
    else if (pos->getY() < -r)
    {
        pos->setY(400 + r);
    }

}
Vector2D Taget::getPos()
{
     Vector2D a(_x, _y);
     return a;
}
Vector2D Taget::getVel()
{
    Vector2D a(vel->getX(), vel->getY());
    return a;
}

