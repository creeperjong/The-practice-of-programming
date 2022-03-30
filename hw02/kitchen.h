#ifndef _KITCHEN_H_
#define _KITCHEN_H_
#include "item.h"

enum Equip {
    WASHER = 1, WINDOW = 2, CHOP = 3, BLUEBERRIES = 4, ICE_CREAM = 5, STRAWBERRIES = 6,
    DOUGH = 7, OVEN = 8
};

class Kitchen {
    public:
        Kitchen(){}
        Kitchen(const char (*_map)[11]);
        int getEquip_X(const Equip _equip) const;
        int getEquip_Y(const Equip _equip) const;
        int getTable_X(const int _x, const int _y, const Items& _item_list) const;
        int getTable_Y(const int _x, const int _y, const Items& _item_list) const;
    private:
        static constexpr int width = 11;
        static constexpr int height = 7;
        int equip_x[9] = {0}, equip_y[9] = {0};
        char map[7][11] = {0};
};

#endif