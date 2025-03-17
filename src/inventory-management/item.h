#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    Item(const std::string& name, const std::string& type, int value);
    std::string getName() const;
    std::string getType() const;
    int getValue() const;

private:
    std::string name;
    std::string type;
    int value;
};

#endif // ITEM_H