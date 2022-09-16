#include "entity.h"

#include <qopengl.h>
#include <vector>
/*
 * Classe dediee pour la création de la voiture et de sa gestion
 *
*/
class Car : public Entity
{
public:
    Car();
    Car(float colorR, float colorG, float colorB);
    ~Car();

    Position getPosition();
    BoxHitBox hitbox();
    void drawBarrel(bool);

protected:

    void drawCar();
    void drawWheel();

    Color* color_;
    GLUquadric* wheelQuadric_ = nullptr;

};

/*
 * Classe de la voiture du joueur
 *
*/
class Player : public Car
{
public:
    Player();
    ~Player();

    void draw();
    void beacon();// gestion du girofare
    void left();// gestion d'un mouvement à gauche
    void right();// gestion d'un mouvement à droite
    void resetX();// réinitialisation de la position
    bool wasHit=false;

private:
    void updatePos();
    short beaconTimer_;
};

/*
 * Classe des voitures opposées
*/
class EnnemyCar : public Car
{
public:
    EnnemyCar(float* speed);
    ~EnnemyCar();
    void restart();
    void setCanDraw(bool var){canDraw=var;};
    bool getCanDraw(){return canDraw;};
    void draw();

private:
    void updatePos();
    float* speed_;
    bool canDraw=false;
};
