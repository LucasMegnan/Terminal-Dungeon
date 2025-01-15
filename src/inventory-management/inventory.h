#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

// Backpack class
class Backpack {
public:
    Backpack();
    void addItem(const std::string& item);
    void removeItem(const std::string& item);
    void display(std::ostream& os) const;

private:
    std::vector<std::string> items;
};

// Equipment class
class Equipment {
public:
    Equipment();
    void setHead(const std::string& item);
    void setNeck(const std::string& item);
    void setHandL(const std::string& item);
    void setHandR(const std::string& item);
    void setBody(const std::string& item);
    void setArms(const std::string& item);
    void setRing1(const std::string& item);
    void setRing2(const std::string& item);
    void setFeet(const std::string& item);
    void display(std::ostream& os) const;

private:
    std::string head;
    std::string neck;
    std::string handL;
    std::string handR;
    std::string body;
    std::string arms;
    std::string ring1;
    std::string ring2;
    std::string feet;
};

// Inventory class
class Inventory {
public:
    Inventory();
    void addBackpackItem(const std::string& item);
    void removeBackpackItem(const std::string& item);
    void setEquipment(const std::string& slot, const std::string& item);
    void display(std::ostream& os) const;

private:
    Backpack backpack;
    Equipment equipment;
};

#endif // INVENTORY_H