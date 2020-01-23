#ifndef ITEM_H
#define ITEM_H

class Item
{
public:
    Item();
    Item(const Item & o);
    ~Item();
    Item& operator=(const Item & o);

private:
    void debug(const char * str);
};

#endif // ITEM_H
