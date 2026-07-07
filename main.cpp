#include <iostream>
#include <vector>
#include <unordered_map>

class Item {

private:
    unsigned int m_cost; // in pennies
    bool m_special_price;

public:
    Item(unsigned int cost, bool special_price) : 
        m_cost(cost), m_special_price(special_price) {}

    unsigned int getCost() { return m_cost; }
    bool getSpecialPrice() { return m_special_price; }

};

int main() {

    std::unordered_map<std::string, Item> item_lookup = {
        { "apple", Item(25, false) },
        { "bannana", Item(25, false) },
        { "oatmeal", Item(50, false) },
        { "bread", Item(75, false) }
    };

    std::vector<std::string> item_list = { "apple", "bannana", "apple", "bread", "oatmeal", "apple" };
   
    unsigned int item_sum = 0; 
    for (auto& i: item_list) {
        std::cout << i << "\n";

        auto it = item_lookup.find(i);
        if (it == item_lookup.end()) { std::cout << "Not in map\n"; return EXIT_FAILURE; }

        std::string sku = it->first;
        Item a = it->second; 
        std::cout << sku << " " << a.getCost() << " " << a.getSpecialPrice() << "\n";
        item_sum += a.getCost();
    }

    std::cout << "\nTotal : $ " << float(item_sum) / 100 << "\n";

    return EXIT_SUCCESS;
}

