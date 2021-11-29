#ifndef VEHICULE_HPP
#define VEHICULE_HPP

#include "commun.hpp"


class Vehicule
{
private:
    double x;
    double y;
    double vitesse;
    double vitesseX;
    double vitesseY;
    double angle;
public:
    Vehicule();
    void deplacer();
    void forward();
    void backward();
    void left();
    void right();
    double getX();
    double getY();
    double getAngle();
    void stop();
};


#endif
