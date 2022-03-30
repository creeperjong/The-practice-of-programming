#include "customer.h"

Customer::Customer(const char* _item, const int _award){
    award = _award;
    char tmp[101] = "";
    memcpy(tmp, _item, strlen(_item));
    char* p = strtok(tmp, " -");
    while(p){
        item.push_back(Item(p));
        p = strtok(NULL, " -");
    }
}

int Customer::getAward() const{
    return award;
}

int Customer::getItemNum() const{
    return item.size();
}

const Item& Customer::getItem(const int _pos) const{
    return item[_pos];
}

bool Customer::isItemExist(const char* _item) const{
    for(const Item i : item){
        if(!strncmp(i.getName(), _item, strlen(_item))) return true;
    }
    return false;
}

Customers::Customers(const int _n){
    list = new Customer[_n]();
    num = _n;
}


void Customers::setCustomer(const int _pos, const Customer& _cus){
    list[_pos] = Customer(_cus);
}

const Customer& Customers::getMaxCustomer() const{
    int ma = -1, idx = -1;
    for(int i = 0;i < num;i++){
        int val = list[i].getAward(), cnt = 0;
        if(list[i].isItemExist("BLUEBERRIES")) cnt += 2;
        if(list[i].isItemExist("ICE_CREAM")) cnt += 2;
        if(list[i].isItemExist("CROISSANT")) cnt += 4;
        if(list[i].isItemExist("CHOPPED_STRAWBERRIES")) cnt += 4;
        if(list[i].isItemExist("TART")) cnt += 8;
        val /= cnt;
        if(ma < val){
            ma = val;
            idx = i;
        }
    }
    return list[idx];
}