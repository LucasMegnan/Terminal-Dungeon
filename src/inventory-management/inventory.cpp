#include "inventory.h"
#include <iostream>
#include <sstream>

// Backpack implementation
Backpack::Backpack() {}

void Backpack::addItem(const Item& item) {
    items.push_back(item);
}

void Backpack::removeItem(const std::string& itemName) {
    items.erase(std::remove_if(items.begin(), items.end(),
        [&itemName](const Item& item) { return item.getName() == itemName; }), items.end());
}

void Backpack::display(std::ostream& os) const {
    os << "+-------------------+\n";
    os << "|      Backpack     |\n";
    os << "+-------------------+\n";
    for (const auto& item : items) {
        os << "| - " << item.getName() << " (" << item.getType() << ")\n";
    }
    os << "+-------------------+\n";
}

// Equipment implementation
Equipment::Equipment() : head("None", "None", 0), neck("None", "None", 0), handL("None", "None", 0), handR("None", "None", 0), body("None", "None", 0), arms("None", "None", 0), ring1("None", "None", 0), ring2("None", "None", 0), feet("None", "None", 0) {}

void Equipment::setHead(const Item& item) { head = item; }
void Equipment::setNeck(const Item& item) { neck = item; }
void Equipment::setHandL(const Item& item) { handL = item; }
void Equipment::setHandR(const Item& item) { handR = item; }
void Equipment::setBody(const Item& item) { body = item; }
void Equipment::setArms(const Item& item) { arms = item; }
void Equipment::setRing1(const Item& item) { ring1 = item; }
void Equipment::setRing2(const Item& item) { ring2 = item; }
void Equipment::setFeet(const Item& item) { feet = item; }

void Equipment::display(std::ostream& os) const {
    os << "+-------------------+\n";
    os << "|     Equipment     |\n";
    os << "+-------------------+\n";
    os << "| Head: " << head.getName() << " (" << head.getType() << ")\n";
    os << "| Neck: " << neck.getName() << " (" << neck.getType() << ")\n";
    os << "| Hand (L): " << handL.getName() << " (" << handL.getType() << ")\n";
    os << "| Hand (R): " << handR.getName() << " (" << handR.getType() << ")\n";
    os << "| Body: " << body.getName() << " (" << body.getType() << ")\n";
    os << "| Arms: " << arms.getName() << " (" << arms.getType() << ")\n";
    os << "| Ring 1: " << ring1.getName() << " (" << ring1.getType() << ")\n";
    os << "| Ring 2: " << ring2.getName() << " (" << ring2.getType() << ")\n";
    os << "| Feet: " << feet.getName() << " (" << feet.getType() << ")\n";
    os << "+-------------------+\n";
}

// Inventory implementation
Inventory::Inventory() {}

void Inventory::addBackpackItem(const Item& item) {
    backpack.addItem(item);
}

void Inventory::removeBackpackItem(const std::string& itemName) {
    backpack.removeItem(itemName);
}

void Inventory::setEquipment(const std::string& slot, const Item& item) {
    if (slot == "head") equipment.setHead(item);
    else if (slot == "neck") equipment.setNeck(item);
    else if (slot == "handL") equipment.setHandL(item);
    else if (slot == "handR") equipment.setHandR(item);
    else if (slot == "body") equipment.setBody(item);
    else if (slot == "arms") equipment.setArms(item);
    else if (slot == "ring1") equipment.setRing1(item);
    else if (slot == "ring2") equipment.setRing2(item);
    else if (slot == "feet") equipment.setFeet(item);
}

void Inventory::display(std::ostream& os) const {
    backpack.display(os);
    equipment.display(os);
}