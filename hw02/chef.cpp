#include "chef.h"

Chef::Chef(const int _x, const int _y, const char* _item){
    x = _x, y = _y;
    char tmp[101] = "";
    memcpy(tmp, _item, strlen(_item));
    char* p = strtok(tmp, " -");
    while(p){
        item.push_back(Item(p));
        p = strtok(NULL, " -");
    }
}

int Chef::getX() const{
    return x;
}

int Chef::getY() const{
    return y;
}

int Chef::getItemNum() const{
    return item.size();
}

bool Chef::isItemExist(const char* _item) const{
    int n = item.size();
    for(Item i : item){
        if(!strncmp(i.getName(), _item, strlen(_item))) return true;
    }
    return false;
}