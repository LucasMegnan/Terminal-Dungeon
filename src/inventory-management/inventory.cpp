#include "inventory.h"
#include <iostream>
#include <sstream>

// Backpack implementation
Backpack::Backpack() {}

void Backpack::addItem(const std::string& item) {
    items.push_back(item);
}

void Backpack::removeItem(const std::string& item) {
    items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

void Backpack::display(std::ostream& os) const {
    os << "+-------------------+-------------------------+\n";
    os << "|      Backpack     |        Equipment       |\n";
    os << "+-------------------+-------------------------+\n";
    for (const auto& item : items) {
        os << "| - " << item << "\n";
    }
    os << "+-------------------+-------------------------+\n";
}

// Equipment implementation
Equipment::Equipment() : head(""), neck(""), handL("fist"), handR("fist"), body(""), arms(""), ring1(""), ring2(""), feet(""){}

void Equipment::setHead(const std::string& item) { head = item; }
void Equipment::setNeck(const std::string& item) { neck = item; }
void Equipment::setHandL(const std::string& item) { handL = item; }
void Equipment::setHandR(const std::string& item) { handR = item; }
void Equipment::setBody(const std::string& item) { body = item; }
void Equipment::setArms(const std::string& item) { arms = item; }
void Equipment::setRing1(const std::string& item) { ring1 = item; }
void Equipment::setRing2(const std::string& item) { ring2 = item; }
void Equipment::setFeet(const std::string& item) { feet = item; }

void Equipment::display(std::ostream& os) const {
    os << "| Head: " << head << "\n";
    os << "| Neck: " << neck << "\n";
    os << "| Hand (L): " << handL << "\n";
    os << "| Hand (R): " << handR << "\n";
    os << "| Body: " << body << "\n";
    os << "| Arms: " << arms << "\n";
    os << "| Ring 1: " << ring1 << "\n";
    os << "| Ring 2: " << ring2 << "\n";
    os << "| Feet: " << feet << "\n";
    os << "+-------------------+-------------------------+\n";
}

// Inventory implementation
Inventory::Inventory() {}

void Inventory::addBackpackItem(const std::string& item) {
    backpack.addItem(item);
}

void Inventory::removeBackpackItem(const std::string& item) {
    backpack.removeItem(item);
}

void Inventory::setEquipment(const std::string& slot, const std::string& item) {
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