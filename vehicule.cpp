#include "vehicule.hpp"

Vehicule::Vehicule(){
    x = 800;
    y = 350;
    vitesse = 0;
    vitesseY = 0;
    vitesseX = 0;
    angle = 90;
    angleSpeed = 10;
    rightTurn = 0;
    leftTurn = 0;
}

void Vehicule::deplacer(){
    if(leftTurn){
        angle -= angleSpeed;
    }
    if(angle == 0){
        angle = 360;
    }

    if(rightTurn){
        angle += angleSpeed;
    }

    if(angle == 360){
        angle = 0;
    }


    if(angle == 0){
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

void Vehicule::forward(){
    vitesse = 1;
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

void Vehicule::turnLeft(){
    leftTurn = 1;
}

void Vehicule::turnRight(){
    rightTurn = 1;
}

void Vehicule::stopLeft(){
    leftTurn = 0;
}

void Vehicule::stopRight(){
    rightTurn = 0;
}

double Vehicule::getAngle(){
    return angle;
}

void Vehicule::stop(){
    vitesse = 0;
}
