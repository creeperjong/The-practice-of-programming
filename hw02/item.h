#ifndef _ITEM_H_
#define _ITEM_H_
#include <string.h>

class Item {
    public:
        Item(){}
        Item(const char* _name);
        Item(const int _x, const int _y, const char* _name);
        int getX() const;
        int getY() const;
        const char* getName() const;
        bool isContain(const char* _name) const;
    private:
        int x = 0, y = 0;
        char* name = nullptr;
};

class Items {
    public:
        Items(){}
        Items(const int _n);
        void setItem(const int _pos, const Item& _item);
        bool isItemExist(const char* _name) const;
        const Item& getItem(const int _x, const int _y) const;
        const Item& getItem(const char* _name) const;
        const Item& getItem_part(const char* _name) const;
    private:
        int num = 0;
        Item* list = nullptr;
};

#endif