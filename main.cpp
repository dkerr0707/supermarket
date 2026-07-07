#include <iostream>

class Item {

private:
    std::string m_sku;
    unsigned int m_cost; // in pennies
    bool m_special_price;

public:
    Item(std::string sku, unsigned int cost, bool special_price) : 
        m_sku(sku), m_cost(cost), m_special_price(special_price) {}

    std::string getSku() { return m_sku; }
    unsigned int getCost() { return m_cost; }
    bool getSpecialPrice() { return m_special_price; }

};

int main() {
    Item a = Item("apple", 45, false);
    std::cout << a.getSku() << " " << a.getCost() << " " << a.getSpecialPrice() << "\n";
}
