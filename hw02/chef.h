#ifndef _CHEF_H_
#define _CHEF_H_
#include <string.h>
#include <vector>
#include "item.h"

class Chef {
    public:
        Chef(){}
        Chef(const int _x, const int _y, const char* _item);
        int getX() const;
        int getY() const;
        int getItemNum() const;
        bool isItemExist(const char* _item) const;
    private:
        int x = 0;
        int y = 0;
        std::vector<Item> item;
};

#endif