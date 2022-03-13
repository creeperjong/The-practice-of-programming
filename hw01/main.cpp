#include <stdio.h>
#include "maze.h"
#include "robot.h"

int main(){
    int w = 0, h = 0, rx = 0, ry = 0;
    long long n = 0;
    char** mazeInput = nullptr;
    scanf("%d %d %lld", &w, &h, &n);
    mazeInput = new char*[h];
    for(int i = 0;i < h;i++){
        mazeInput[i] = new char[w];
        scanf("%s", mazeInput[i]);
        for(int j = 0;j < w;j++){
            if(mazeInput[i][j] == 'O') rx = j, ry = i;
        }
    }
    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {-1, 0, 1, 0};
    Maze maze(mazeInput, w, h);
    Robot robot(rx, ry, w, h);
    for(long long step = 2;step <= n + 1;step++){
        int nx = robot.getPosition_X() + dx[robot.getDirection()];
        int ny = robot.getPosition_Y() + dy[robot.getDirection()];
        int turnCnt = 0;

        //Turn until finding a way
        while(maze.isBlocked(nx, ny) && turnCnt < 4){
            robot.turnRight();
            nx = robot.getPosition_X() + dx[robot.getDirection()];
            ny = robot.getPosition_Y() + dy[robot.getDirection()];
            ++turnCnt;
        }
        if(turnCnt == 4){   
            printf("Error: Robot has no way to move!\n");
            return 0;
        }
        robot.moveForward();

        //memorize
        long long visStep = robot.checkVisitedStep(nx, ny); 
        if(visStep && robot.checkVisitedDir(nx, ny) == robot.getDirection()){
            step += (n + 1 - step) /  (step - visStep) * (step - visStep);
        }
        robot.setVisitedStep(nx, ny, step);

    }
    printf("%d %d\n", robot.getPosition_X(), robot.getPosition_Y());
    return 0;
}