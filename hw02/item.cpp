#include "item.h"

Item::Item(const char* _name){
    x = -1, y = -1;
    int len = strlen(_name) + 1;
    name = new char[len];
    memcpy(name, _name, sizeof(char) * len);
}

Item::Item(const int _x, const int _y, const char* _name){
    x = _x, y = _y;
    int len = strlen(_name) + 1;
    name = new char[len];
    memcpy(name, _name, sizeof(char) * len);
}

int Item::getX() const{
    return x;
}

int Item::getY() const{
    return y;
}

const char* Item::getName() const{
    return name;
}

bool Item::isContain(const char* _name) const{
    return strstr(name, _name);
}

Items::Items(const int _n){
    list = new Item[_n]();
    num = _n;
}

void Items::setItem(const int _pos, const Item& _item){
    list[_pos] = Item(_item);
}

bool Items::isItemExist(const char* _name) const{
    return !strncmp(getItem(_name).getName(), _name, sizeof(_name));
}

const Item& Items::getItem(const int _x, const int _y) const{
    for(int i = 0;i < num;i++){
        if(list[i].getX() == _x && list[i].getY() == _y) return list[i];
    }
    return list[0];
}

const Item& Items::getItem(const char* _name) const{
    for(int i = 0;i < num;i++){
        if(!strncmp(list[i].getName(), _name, sizeof(_name))){
            return list[i];
        }
    }
    return list[0];
}

const Item& Items::getItem_part(const char* _name) const{
    for(int i = 0;i < num;i++){
        if(strstr(list[i].getName(), _name)){
            return list[i];
        }
    }
    return list[0];
}