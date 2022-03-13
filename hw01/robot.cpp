#include "robot.h"

Robot::Robot(const int _x, const int _y, const int _mazeW, const int _mazeH){
    x = _x, y = _y, dir = UP;
    stepRec = new long long*[_mazeH];
    dirRec = new Direction*[_mazeH];
    for(int i = 0;i < _mazeH;i++){
        stepRec[i] = new long long[_mazeW]();
        dirRec[i] = new Direction[_mazeW]();
    }
    stepRec[_y][_x] = 1;
}

int Robot::getPosition_X() const{
    return x;
}

int Robot::getPosition_Y() const{
    return y;
}

Direction Robot::getDirection() const{
    return dir;
}

void Robot::moveForward(){
    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {-1, 0, 1, 0};
    x  = x + dx[dir], y = y + dy[dir];
}

void Robot::turnLeft(){
    switch (dir){
        case UP:
            dir = LEFT;
            break;
        case RIGHT:
            dir = UP;
            break;
        case DOWN:
            dir = RIGHT;
            break;
        case LEFT:
            dir = DOWN;
            break;
    }
}

void Robot::turnRight(){
    switch (dir){
        case UP:
            dir = RIGHT;
            break;
        case RIGHT:
            dir = DOWN;
            break;
        case DOWN:
            dir = LEFT;
            break;
        case LEFT:
            dir = UP;
            break;
    }
}

long long Robot::checkVisitedStep(const int _x, const int _y) const{
    return stepRec[_y][_x];
}

Direction Robot::checkVisitedDir(const int _x, const int _y) const{
    return dirRec[_y][_x];
}


void Robot::setVisitedStep(const int _x, const int _y, const long long _step){
    stepRec[_y][_x] = _step;
    dirRec[_y][_x] = dir;
}