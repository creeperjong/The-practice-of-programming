#ifndef _ROBOT_H_
#define _ROBOT_H_

enum Direction {
    UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3
};

class Robot {
    public:
        Robot(const int _x, const int _y, const int _mazeW, const int _mazeH);
        int getPosition_X() const;
        int getPosition_Y() const;
        Direction getDirection() const;
        void moveForward();
        void turnLeft();
        void turnRight();
        long long checkVisitedStep(const int _x, const int _y) const;
        Direction checkVisitedDir(const int _x, const int _y) const;
        void setVisitedStep(const int _x, const int _y, const long long _step);
    private:
        int x = 0;
        int y = 0;
        Direction dir = UP;
        long long** stepRec = nullptr;
        Direction** dirRec = nullptr;
};

#endif