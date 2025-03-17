#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "item.h"

// Backpack class
class Backpack {
public:
    Backpack();
    void addItem(const Item& item);
    void removeItem(const std::string& itemName);
    void display(std::ostream& os) const;

private:
    std::vector<Item> items;
};

// Equipment class
class Equipment {
public:
    Equipment();
    void setHead(const Item& item);
    void setNeck(const Item& item);
    void setHandL(const Item& item);
    void setHandR(const Item& item);
    void setBody(const Item& item);
    void setArms(const Item& item);
    void setRing1(const Item& item);
    void setRing2(const Item& item);
    void setFeet(const Item& item);
    void display(std::ostream& os) const;

private:
    Item head;
    Item neck;
    Item handL;
    Item handR;
    Item body;
    Item arms;
    Item ring1;
    Item ring2;
    Item feet;
};

// Inventory class
class Inventory {
public:
    Inventory();
    void addBackpackItem(const Item& item);
    void removeBackpackItem(const std::string& itemName);
    void setEquipment(const std::string& slot, const Item& item);
    void display(std::ostream& os) const;

private:
    Backpack backpack;
    Equipment equipment;
};

#endif // INVENTORY_H