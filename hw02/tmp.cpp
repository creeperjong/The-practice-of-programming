#include <stdio.h>
#include <string.h>
#include <vector>

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
        val /= 8;
        if(ma < val){
            ma = val;
            idx = i;
        }
    }
    return list[idx];
}

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

void readCustomerList(Customers& cus_list, Customer& cus_max){
    int num_customers;
    scanf("%d", &num_customers);
    cus_list = Customers(num_customers);
    for (int i = 0; i < num_customers; i++) {
        char customer_item[101] = "";
        int customer_award;
        scanf("%s%d", customer_item, &customer_award); fgetc(stdin);
        cus_list.setCustomer(i, Customer(customer_item, customer_award));
    }
    cus_max = cus_list.getMaxCustomer();
}

void readKitchen(Kitchen& kitchen){
    char map[7][11] = {0};
    for (int i = 0; i < 7; i++) {
        scanf("%s", map[i]); fgetc(stdin);
    }
    kitchen = Kitchen(map);
}

void readChef(Chef& chef){
    int player_x;
    int player_y;
    char player_item[101];
    scanf("%d%d%s", &player_x, &player_y, player_item);
    chef = Chef(player_x, player_y, player_item);
}

void readItemList(Items& item_list){
    int num_tables_with_items;
    scanf("%d", &num_tables_with_items);
    item_list = Items(num_tables_with_items + 1);
    item_list.setItem(0, Item("NONE"));
    for (int i = 1; i <= num_tables_with_items; i++) {
        int table_x;
        int table_y;
        char item_s[101];
        scanf("%d%d%s", &table_x, &table_y, item_s);
        item_list.setItem(i, Item(table_x, table_y, item_s));
    }
}

bool isPartOfItem(const Items& _item_list, const char* _name){
    return strstr(_item_list.getItem_part(_name).getName(), _name);
}

bool isOrderFinish(const Chef& _my, const Customer& _cus){
    int n = _cus.getItemNum();
    for(int i = 0;i < n;i++){
        if(!_my.isItemExist(_cus.getItem(i).getName())) return false;
    }
    return true;
}

bool isAllOnTable(const Chef& _my, const Customer& _cus, const Items& _item_list){
    int n = _cus.getItemNum();
    for(int i = 1;i < n;i++){
        if(!strncmp(_cus.getItem(i).getName(), "BLUEBERRIES", 11)) continue;
        if(!strncmp(_cus.getItem(i).getName(), "ICE_CREAM", 9)) continue;
        if(!_item_list.isItemExist(_cus.getItem(i).getName())){
            if(_my.isItemExist("DISH") && !_my.isItemExist(_cus.getItem(i).getName())){
                return false;
            }
        }
    }
    return true;
}

bool isProperItem(const Item& _item, const Customer& _cus){
    char tmp[101] = "";
    memcpy(tmp, _item.getName(), sizeof(tmp));
    char* p = strtok(tmp, "- ");
    while(p){
        if(!_cus.isItemExist(p)) return false;
        p = strtok(NULL, "- ");
    }
    return true;
}

void insertSlot(const Kitchen& _kitchen, const Chef& _my, const Items& _item_list){
    int nx = _kitchen.getTable_X(_my.getX(), _my.getY(), _item_list);
    int ny = _kitchen.getTable_Y(_my.getX(), _my.getY(), _item_list);
    for(int i = 0;i < 7 && nx != -1 && ny != -1;i++){
        for(int j = 0;j < 11 && nx != -1 && ny != -1;j++){
            nx = _kitchen.getTable_X(j, i, _item_list);
            ny = _kitchen.getTable_Y(j, i, _item_list);
        }
    }
    printf("USE %d %d\n", nx, ny);
}

int main(){

    Kitchen kitchen;
    Customers cus_list;
    Customer cus_max;
    Chef my;
    Chef partner;
    Items item_list;
    
    readCustomerList(cus_list, cus_max);
    readKitchen(kitchen);

    // game loop
    while (1) {
        int turns_remaining;
        scanf("%d", &turns_remaining);
        
        readChef(my), readChef(partner);
        readItemList(item_list);
        char oven_contents[101];
        int oven_timer;
        scanf("%s%d", oven_contents, &oven_timer);
        readCustomerList(cus_list, cus_max);

        if(isOrderFinish(my, cus_max)){
            printf("USE %d %d\n", kitchen.getEquip_X(WINDOW), kitchen.getEquip_Y(WINDOW));
            continue;
        }
        if(!isAllOnTable(my, cus_max, item_list) && my.isItemExist("DISH")){
            insertSlot(kitchen, my, item_list);
            continue;
        }
        if(cus_max.isItemExist("TART")){
            if(!item_list.isItemExist("TART")){
                if(!my.isItemExist("TART")){
                    if(!strncmp(oven_contents, "NONE", sizeof(oven_contents))){
                        if(my.isItemExist("RAW_TART")) printf("USE %d %d\n", kitchen.getEquip_X(OVEN), kitchen.getEquip_Y(OVEN));
                        else{
                            if(my.isItemExist("NONE")){
                                if(item_list.isItemExist("DOUGH")){
                                    Item dough = item_list.getItem("DOUGH");
                                    printf("USE %d %d\n", dough.getX(), dough.getY());
                                }    
                                else{
                                    printf("USE %d %d\n", kitchen.getEquip_X(DOUGH), kitchen.getEquip_Y(DOUGH));
                                }
                            }
                            else if(my.isItemExist("DOUGH")){
                                printf("USE %d %d\n", kitchen.getEquip_X(CHOP), kitchen.getEquip_Y(CHOP));
                            }
                            else if(my.isItemExist("CHOPPED_DOUGH")){
                                if(my.isItemExist("BLUEBERRIES")){
                                    Item bberries = item_list.getItem("BLUEBERRIES");
                                    printf("USE %d %d\n", bberries.getX(), bberries.getY());
                                }
                                else{
                                    printf("USE %d %d\n", kitchen.getEquip_X(BLUEBERRIES), kitchen.getEquip_Y(BLUEBERRIES));
                                }
                            }
                            else{
                                insertSlot(kitchen, my, item_list);
                            }
                        }
                        continue;
                    }
                    else if(!strncmp(oven_contents, "RAW_TART", sizeof(oven_contents))){
                        if(my.isItemExist("RAW_TART")){
                            insertSlot(kitchen, my, item_list);
                            continue;
                        }
                        else{
                            printf("WAIT\n");
                            continue;
                        }
                    }
                    else{
                        printf("USE %d %d\n", kitchen.getEquip_X(OVEN), kitchen.getEquip_Y(OVEN));
                        continue;
                    }
                }
                else if(!my.isItemExist("DISH")){
                    insertSlot(kitchen, my, item_list);
                    continue;
                }
            }
        }
        if(cus_max.isItemExist("CROISSANT")){
            if(!item_list.isItemExist("CROISSANT")){
                if(!my.isItemExist("CROISSANT")){
                    if(!strncmp(oven_contents, "NONE", sizeof(oven_contents))){
                        if(my.isItemExist("DOUGH")) printf("USE %d %d\n", kitchen.getEquip_X(OVEN), kitchen.getEquip_Y(OVEN));
                        else{
                            if(my.isItemExist("NONE")){
                                if(item_list.isItemExist("DOUGH")){
                                    Item dough = item_list.getItem("DOUGH");
                                    printf("USE %d %d\n", dough.getX(), dough.getY());
                                }    
                                else{
                                    printf("USE %d %d\n", kitchen.getEquip_X(DOUGH), kitchen.getEquip_Y(DOUGH));
                                }
                            }
                            else{
                                insertSlot(kitchen, my, item_list);
                            }
                        }
                        continue;
                    }
                    else if(!strncmp(oven_contents, "DOUGH", sizeof(oven_contents))){
                        if(my.isItemExist("DOUGH")){    
                            insertSlot(kitchen, my, item_list);
                            continue;
                        }
                        else{
                            printf("WAIT\n");
                            continue;
                        }
                    }
                    else{
                        printf("USE %d %d\n", kitchen.getEquip_X(OVEN), kitchen.getEquip_Y(OVEN));
                        continue;
                    }
                }
                else if(!my.isItemExist("DISH")){
                    
                    insertSlot(kitchen, my, item_list);
                    continue;
                }
            }
        }
        if(cus_max.isItemExist("CHOPPED_STRAWBERRIES")){
            if(!item_list.isItemExist("CHOPPED_STRAWBERRIES")){
                if(!my.isItemExist("CHOPPED_STRAWBERRIES")){
                    if(my.isItemExist("STRAWBERRIES")){
                        printf("USE %d %d\n", kitchen.getEquip_X(CHOP), kitchen.getEquip_Y(CHOP));
                    }
                    else{
                        if(my.isItemExist("NONE")){
                            if(item_list.isItemExist("STRAWBERRIES")){
                                Item straw = item_list.getItem("STRAWBERRIES");
                                printf("USE %d %d\n", straw.getX(), straw.getY());
                            }
                            else{
                                printf("USE %d %d\n", kitchen.getEquip_X(STRAWBERRIES), kitchen.getEquip_Y(STRAWBERRIES));
                            }
                        }
                        else{
                            insertSlot(kitchen, my, item_list);
                        }
                    }
                    continue;
                }
                else if(!my.isItemExist("DISH")){
                    insertSlot(kitchen, my, item_list);
                    continue;
                }
            }
        }

        if(!my.isItemExist("DISH")){
            if(my.isItemExist("NONE")){
                Item dish = item_list.getItem_part("DISH");
                if(isProperItem(dish, cus_max)){
                    printf("USE %d %d\n", dish.getX(), dish.getY());
                }
                else printf("USE %d %d\n", kitchen.getEquip_X(WASHER), kitchen.getEquip_Y(WASHER));
            }
            else{
                insertSlot(kitchen, my, item_list);
            }
            continue;
        }
        if(cus_max.isItemExist("TART") && !my.isItemExist("TART")){
            Item it = item_list.getItem("TART");
            printf("USE %d %d\n", it.getX(), it.getY());
        }
        else if(cus_max.isItemExist("CROISSANT") && !my.isItemExist("CROISSANT")){
            Item it = item_list.getItem("CROISSANT");
            printf("USE %d %d\n", it.getX(), it.getY());
        }
        else if(cus_max.isItemExist("CHOPPED_STRAWBERRIES") && !my.isItemExist("CHOPPED_STRAWBERRIES")){
            Item it = item_list.getItem("CHOPPED_STRAWBERRIES");
            printf("USE %d %d\n", it.getX(), it.getY());
        }
        else if(cus_max.isItemExist("BLUEBERRIES") && !my.isItemExist("BLUEBERRIES")){
            printf("USE %d %d\n", kitchen.getEquip_X(BLUEBERRIES), kitchen.getEquip_Y(BLUEBERRIES));
        }
        else if(cus_max.isItemExist("ICE_CREAM") && !my.isItemExist("ICE_CREAM")){
            printf("USE %d %d\n", kitchen.getEquip_X(ICE_CREAM), kitchen.getEquip_Y(ICE_CREAM));
        }
        
    }

    return 0;
}