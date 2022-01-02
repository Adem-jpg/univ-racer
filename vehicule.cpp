#include "vehicule.hpp"
#include <stdio.h>

Vehicule::Vehicule(){
    x = 100;
    y = 100;
    vitesse = 0;
    vitesseY = 0;
    vitesseX = 0;
    angle = 90;
    angleSpeed = ANGLE_SPEED;
    rightTurn = 0;
    leftTurn = 0;
}

void Vehicule::deplacer(){
    // printf("Left:%i, Right:%i\n",leftTurn,rightTurn);

    if(leftTurn){
        angle -= angleSpeed;
    }
    if(rightTurn){
        angle += angleSpeed;
    }
    if(angle < 0){
        angle = 360;
    }
    if(angle > 360){
        angle = 0;
    }


    if(angle == 0 || angle == 360){
        y -= vitesse;
    } else if(angle > 0 && angle < 90){
        // angle: 90 | 45 | 37 | 0
        // %:    100 |    |    | 0
        vitesseY = 1. - (angle / 90.);
        vitesseX = ( angle / 90.);
        y -= vitesse * vitesseY;
        x += vitesse * vitesseX;
        // printf("vitesseX: %lf, vitesseY: %lf\n",vitesseX,vitesseY);

    } else if(angle == 90){
        x += vitesse;
    } else if(angle > 90 && angle < 180){
        double anglebis = angle - 90.;
        vitesseX = 1. - ( anglebis / 90.);
        vitesseY = (anglebis / 90.);
        x += vitesse * vitesseX;
        y += vitesse * vitesseY;
        // printf("vitesseX: %lf, vitesseY: %lf\n",vitesseX,vitesseY);
    } else if (angle == 180){
        y += vitesse;
    } else if (angle > 180 && angle < 270){
        double anglebis = angle - 180.;
        vitesseX = ( anglebis / 90.);
        vitesseY = 1. - (anglebis / 90.);
        y += vitesse * vitesseY;
        x -= vitesse * vitesseX;
    } else if( angle == 270){
        x -= vitesse;
    } else if ( angle > 270 && angle < 360){
        double anglebis = angle - 270.;
        vitesseX = 1. - ( anglebis / 90.);
        vitesseY = (anglebis / 90.);
        y -= vitesse * vitesseY;
        x -= vitesse * vitesseX;
    }
}

void Vehicule::setForward(int f){
    vitesse = VEHICULE_SPEED * f;
}

void Vehicule::backward(){
    vitesse = -1;
}

double Vehicule::getX(){
    return x;
}

double Vehicule::getY(){
    return y;
}

void Vehicule::setLeftTurn(int isTurning){
    leftTurn = isTurning;
}

void Vehicule::setRightTurn(int isTurning){
    rightTurn = isTurning;
}

double Vehicule::getAngle(){
    return angle;
}

void Vehicule::setX(double newX){
    x = newX;
}

void Vehicule::setY(double newY){
    y = newY;
}
