#ifndef VEHICULE_HPP
#define VEHICULE_HPP

class Vehicule
{
private:
    double x;
    double y;
    double vitesse;
    double vitesseX;
    double vitesseY;
    double angle;
    double angleSpeed; // a modifier en fonction de la vitesse
    int leftTurn;
    int rightTurn;
public:
    Vehicule();
    void deplacer();
    void forward();
    void backward();
    void turnLeft();
    void turnRight();
    void stopLeft();
    void stopRight();
    double getX();
    double getY();
    double getAngle();
    void stop();
};


#endif
