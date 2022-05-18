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
  
  //���⼭ T�� �������Ӹ��� �������ָ� �� Ÿ����� �Ÿ������� T���� ���� �� -���Ǹ�ȵ�

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

    //�Ÿ����
    Vector2D *distance=new Vector2D(0,0);
    distance->setX(_x - _taget->getPos().getX());
    distance->setY(_y - _taget->getPos().getY());

    
    float D=distance->length();
    float T=10;


    //Ư���Ÿ������� �������� ���� �ڵ�
    if (D < 0)
        T = 0;
    if (D < 10)
        T--;
    else if(D>100)

   

    return T;
    
}

/*
 �����̵��� ���� 





(��Ŀ�� ����������+��Ŀ�� �ӵ�) �� Ÿ������ ��� �����ϴ� ����Ŭ�� ����

�ٵ� ��Ŀ�� �����Ҽ��� Ÿ������ ���ϴ� ���� �ٿ��־���Ѵ�.

������ �ڵ尡 
����Ŭ�� position�� taget�� position�� ���󰡴�position=taget.position;�̶�� 
 (��Ŀ�� ����������+��Ŀ�� �ӵ�) �� T�� �����

position=taget.position*T; �� ���·� ��Ÿ�����ְ� 
T�� ��ġ������ ���ҽ�Ű�� �������� ���� �ؾ��Ѵ�.


��ȸ�ϱ� �˰���

1.���� �̵��ϰ��ִ� ����
2.�������� ������ �̵��ϴ� Ÿ�� 
3.Ÿ���� �����ϼ��ִ� ������ ��Ÿ���� ��
 

3.�������� ���� �����̴� ����� 4�ܰ踦 ��ó�� �����ȴ�.

*/
