#include "Walker.h"
#include <random>

Walker::Walker(int x, int y,Taget* t) 
{
  _x = x;
  _y = y;
  
  _taget = t;
  
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
  

  seek();  
  
   radian=atan2(vel->getY(),vel->getX());
  *dot1=Rotate(-r,-r/2,radian);
  *dot2=Rotate(-r,r/2,radian);
  *dot3=Rotate(r,0,radian);

  
  *vel += *acc;
  vel->limit(maxspeed);
  
  //여기서 T를 매프레임마다 설정해주면 됨 타깃과의 거리에따라 T값의 조정 단 -가되면안됨

  float T = TimeClac();
 
  Vector2D aa(vel->getX(), vel->getY());

  Vector2D dir(_taget->getVel().getX(), _taget->getVel().getY());
  dir.normalize();

  aa.setX(aa.getX() + dir.getX());
  aa.setY(aa.getY() + dir.getY());

  aa.Mul(T);


  *pos += aa;

  _x=pos->getX();
  _y=pos->getY();

}

void Walker::draw(SDL_Renderer* renderer)
{

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 

  
 //filledCircleColor(renderer, _taget->getX(),_taget->getY(),16, 0xFFFFFFFF); 

 filledTrigonColor(renderer,dot1->getX()+_x,dot1->getY()+_y,dot2->getX()+_x,dot2->getY()+_y,dot3->getX()+_x,dot3->getY()+_y,0xFFFFFFFF);
  
 SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
  
}
void Walker::seek()
{
   Vector2D a= _taget->getPos();
    *F = a -*pos;
  
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

float Walker::TimeClac()
{

    //거리계산
    Vector2D *distance=new Vector2D(0,0);
    distance->setX(_x - _taget->getPos().getX());
    distance->setY(_y - _taget->getPos().getY());

    
    float D=distance->length();
    float T=10;


    //특정거리에따른 예측값의 감소 코드
    if (D < 0)
        T = 0;
    if (D < 10)
        T--;
    else if(D>100)

   

    return T;
    
}

/*
 예측이동의 구현 





(워커의 진행방향백터+워커의 속도) 를 타깃으로 잡고 진행하는 바이클을 생성

근데 워커에 접근할수록 타깃으로 향하는 힘을 줄여주어야한다.

기존의 코드가 
바이클의 position이 taget의 position을 따라가는position=taget.position;이라면 
 (워커의 진행방향백터+워커의 속도) 를 T로 만들어

position=taget.position*T; 의 형태로 나타낼수있고 
T를 위치에따라 감소시키는 방향으로 구현 해야한다.


배회하기 알고리즘

1.현재 이동하고있는 방향
2.랜덤으로 범위를 이동하는 타깃 
3.타깃이 움직일수있는 범위를 나타내는 원
 

3.원위에서 점을 움직이는 방법은 4단계를 거처서 구현된다.

*/
