#ifndef VEHICULE_HPP
#define VEHICULE_HPP

#define VEHICULE_SPEED 2
#define ANGLE_SPEED 3

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
    int forward;
public:
    Vehicule();
    void deplacer();
    void setForward(int f);
    void backward();
    void setLeftTurn(int isTurning);
    void setRightTurn(int isTurning);
    double getX();
    double getY();
    double getAngle();
    void setX(double newX);
    void setY(double newY);
};


#endif
