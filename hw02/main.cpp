#include <stdio.h>
#include <string.h>
#include "customer.h"
#include "kitchen.h"
#include "chef.h"
#include "item.h"
#include <vector>

void readCustomerList(Customers& cus_list, Customer& cus_max){
    int num_customers;
    scanf("%d", &num_customers);
    cus_list = Customers(num_customers);
    for (int i = 0; i < num_customers; i++) {
        char customer_item[101];
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
    printf("USE %d %d\n", _kitchen.getTable_X(nx, ny, _item_list), _kitchen.getTable_Y(nx, ny, _item_list));
}

int main(){

    Kitchen kitchen;
    Customers cus_list;
    Customer cus_max;
    Chef my;
    Chef partner;
    Items item_list;
    bool baking = false;
    
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
        
        if(cus_max.isItemExist("CROISSANT")){
            if(!item_list.isItemExist("CROISSANT")){
                if(!my.isItemExist("CROISSANT")){
                    if(!strncmp(oven_contents, "NONE", sizeof(oven_contents))){
                        if(my.isItemExist("DOUGH")) printf("USE %d %d\n", kitchen.getEquip_X(OVEN), kitchen.getEquip_Y(OVEN)), baking = true;
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
                        if(baking){
                            printf("WAIT\n");
                            continue;
                        }
                        else if(my.isItemExist("DOUGH")){
                            printf("USE %d %d\n", kitchen.getEquip_X(OVEN), kitchen.getEquip_Y(OVEN));
                            continue;
                        }
                    }
                    else{
                        printf("USE %d %d\n", kitchen.getEquip_X(OVEN), kitchen.getEquip_Y(OVEN));
                        baking = false;
                        continue;
                    }
                }
                else if(!my.isItemExist("DISH")){
                    insertSlot(kitchen, my, item_list);
                    continue;
                }
            }
        }

        if(cus_max.isItemExist("TART")){
            if(!item_list.isItemExist("TART")){
                if(!my.isItemExist("TART")){
                    if(!strncmp(oven_contents, "NONE", sizeof(oven_contents))){
                        if(my.isItemExist("RAW_TART")) printf("USE %d %d\n", kitchen.getEquip_X(OVEN), kitchen.getEquip_Y(OVEN)), baking = true;
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
                        if(baking){
                            printf("WAIT\n");
                            continue;
                        }
                        else if(my.isItemExist("RAW_TART")){
                            printf("USE %d %d\n", kitchen.getEquip_X(OVEN), kitchen.getEquip_Y(OVEN));
                            continue;
                        }
                    }
                    else{
                        printf("USE %d %d\n", kitchen.getEquip_X(OVEN), kitchen.getEquip_Y(OVEN));
                        baking = false;
                        continue;
                    }
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
        if(cus_max.isItemExist("CHOPPED_STRAWBERRIES") && !my.isItemExist("CHOPPED_STRAWBERRIES")){
            Item it = item_list.getItem("CHOPPED_STRAWBERRIES");
            printf("USE %d %d\n", it.getX(), it.getY());
        }
        else if(cus_max.isItemExist("CROISSANT") && !my.isItemExist("CROISSANT")){
            Item it = item_list.getItem("CROISSANT");
            printf("USE %d %d\n", it.getX(), it.getY());
        }
        else if(cus_max.isItemExist("TART") && !my.isItemExist("TART")){
            Item it = item_list.getItem("TART");
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