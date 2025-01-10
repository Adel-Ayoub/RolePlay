#pragma once
#include "corestats.h"
#include "buff.h"
#include <string>
#include <typeinfo>

class ItemDelegate {
public:
    std::string Name;
protected:
    virtual ~ItemDelegate() = 0 {}
    ItemDelegate(std::string name) : Name(name) {}
    friend class Item;
};

class EquipmentDelegate : public ItemDelegate {
public:
    const std::uint32_t UniqueId;
    CoreStats Stats;
protected:
    virtual ~EquipmentDelegate() = 0 {}
    EquipmentDelegate(std::string name, CoreStats cstats);
private:
};

// use this one in your runtime code
class Item final {
public:
    const ItemDelegate* GetData() { return _data; }
    bool GetMarkedForDeletion() const { return _marked_for_deletion; }
private:
    ~Item() {   // only ItemManger can clean this up
        if (_data) {
            delete _data;
            _data = nullptr;
        }
    }
    ItemDelegate* _data;
    bool _marked_for_deletion = false;
    Item(ItemDelegate* item) : _data(item) {}
    friend class ItemManager;

};


