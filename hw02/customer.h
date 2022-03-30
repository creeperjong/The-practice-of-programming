#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_
#include <string.h>
#include <vector>
#include "item.h"

class Customer {
    public:
        Customer(){}
        Customer(const char* _item, const int _award);
        int getAward() const;
        int getItemNum() const;
        const Item& getItem(const int _pos) const;
        bool isItemExist(const char* _item) const;
    private:
        std::vector<Item> item;
        int award = 0;
};

class Customers {
    public:
        Customers(){}
        Customers(const int _n);
        void setCustomer(const int _pos, const Customer& _cus);
        const Customer& getMaxCustomer() const;
    private:
        int num = 0;
        Customer* list = nullptr;
};

#endif