#include "kitchen.h"

Kitchen::Kitchen(const char (*_map)[11]){
    for(int i = 0;i < height;i++){
        for(int j = 0;j < width;j++){
            map[i][j] = _map[i][j];
            if(map[i][j] == 'D') equip_x[WASHER] = j, equip_y[WASHER] = i;
            if(map[i][j] == 'W') equip_x[WINDOW] = j, equip_y[WINDOW] = i;
            if(map[i][j] == 'C') equip_x[CHOP] = j, equip_y[CHOP] = i;
            if(map[i][j] == 'B') equip_x[BLUEBERRIES] = j, equip_y[BLUEBERRIES] = i;
            if(map[i][j] == 'I') equip_x[ICE_CREAM] = j, equip_y[ICE_CREAM] = i;
            if(map[i][j] == 'S') equip_x[STRAWBERRIES] = j, equip_y[STRAWBERRIES] = i;
            if(map[i][j] == 'H') equip_x[DOUGH] = j, equip_y[DOUGH] = i;
            if(map[i][j] == 'O') equip_x[OVEN] = j, equip_y[OVEN] = i;
        }
    }
}

int Kitchen::getEquip_X(const Equip _equip) const{
    return equip_x[_equip];
}

int Kitchen::getEquip_Y(const Equip _equip) const{
    return equip_y[_equip];
}

int Kitchen::getTable_X(const int _x, const int _y, const Items& _item_list) const{
    for(int i = -1;i <= 1;i++){
        for(int j = -1;j <= 1;j++){
            if(!i && !j) continue;
            int nx = _x + i, ny = _y + j;
            if(nx >= 0 && nx < 11 && ny >= 0 && ny < 7 && map[ny][nx] == '#'){
                if(!strncmp(_item_list.getItem(nx, ny).getName(), "NONE", 4)) return nx;
            }
        }
    }
    return -1;
}

int Kitchen::getTable_Y(const int _x, const int _y, const Items& _item_list) const{
    for(int i = -1;i <= 1;i++){
        for(int j = -1;j <= 1;j++){
            if(!i && !j) continue;
            int nx = _x + i, ny = _y + j;
            if(nx >= 0 && nx < 11 && ny >= 0 && ny < 7 && map[ny][nx] == '#'){
                if(!strncmp(_item_list.getItem(nx, ny).getName(), "NONE", 4)) return ny;
            }
        }
    }
    return -1;
}

