#include "Walker.h"
#include <random>

Walker::Walker(int x, int y) 
{
  _x = x;
  _y = y;
  
  _taget=new Vector2D(0,0);
  
  pos=new Vector2D(x,y);
  vel=new Vector2D(0,0);
  acc=new Vector2D(0,0);
  
  maxspeed=1; 
  maxforce=0.05f;
 r=32;
 radian=0;

F=new Vector2D(0,0);
  
dot1=new Vector2D(0,0);
dot2=new Vector2D(0,0);
dot3=new Vector2D(0,0);
}

void Walker::update() 
{
  Edge();
  _taget=InputHandler::Instance()->getMousePosition();



  seek();  
  
   radian=atan2(vel->getY(),vel->getX());
  *dot1=Rotate(-r,-r/2,radian);
  *dot2=Rotate(-r,r/2,radian);
  *dot3=Rotate(r,0,radian);

  *vel += *acc;
  vel->limit(maxspeed);

  *pos += *vel;
  _x=pos->getX();
  _y=pos->getY();



 // *acc *=0;
  



}

void Walker::draw(SDL_Renderer* renderer)
{

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 

  
 filledCircleColor(renderer, _taget->getX(),_taget->getY(),16, 0xFFFFFFFF); 

/*
filledCircleColor(renderer, -r+dot1->getX(),-r/2+dot1->getY(), r, 0xFFFFFFFF); 
  
filledCircleColor(renderer,-r+dot2->getX(),r+dot2->getY(), r, 0xFFFFFFFF); 
  
filledCircleColor(renderer,dot3->getX(),r+dot3->getY(), r, 0xFFFFFFFF); 
  */
  

  
  /*
filledTrigonColor(renderer,dot1->getX()+pos->getX(),dot1->getY()+pos->getY(),dot2->getX()+pos->getX(),dot2->getY()+pos->getY(),dot3->getX()+pos->getX(),dot3->getY()+pos->getY(),0xFFFFFFFF);
  */
  
  filledTrigonColor(renderer,dot1->getX()+_x,dot1->getY()+_y,dot2->getX()+_x,dot2->getY()+_y,dot3->getX()+_x,dot3->getY()+_y,0xFFFFFFFF);
  
  
 SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
  
}
void Walker::seek()
{
  *F=*_taget - *pos;
  
  F->normalize();
  *F *= maxspeed;

  *F-=*vel;

  F->limit(maxforce);
  applyForce(F);
  
}
void Walker::applyForce(Vector2D* force)
{
  *acc+=*force;
}
Vector2D Walker::Rotate(float x,float y,float rad)
{
  Vector2D t(0,0);

  t.setX(cos(radian)*x-sin(radian)*y);
  t.setY(sin(radian)*x+cos(radian)*y);
  return t;
}
void Walker::Edge()
{
  if(pos->getX()>600+r)
  {
    pos->setX(-r);
  }
  else if(pos->getX()<-r)
  {
    pos->setX(600+r);
  }

  if(pos->getY()>400+r)
  {
    pos->setY(-r);
  }
  else if(pos->getY()<-r)
  {
    pos->setY(400+r);
  }

  
  
}

