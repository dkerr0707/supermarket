#include <iostream>
#include <vector>
#include <unordered_map>

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

    std::unordered_map<std::string, Item> item_map = {
        { "apple", Item("apple", 25, false) },
        { "bannana", Item("bannana", 25, false) },
        { "oatmeal", Item("oatmeal", 50, false) },
        { "bread", Item("bread", 75, false) }
    };

    //auto it = items_map.find("apple");
    //if (it == items_map.end()) { std::cout << "Item not in map" << "\n"; return EXIT_FAILURE; }
    
    //Item a = it->second;
    //std::cout << a.getSku() << " " << a.getCost() << " " << a.getSpecialPrice() << "\n";

    std::vector<std::string> item_list = { "apple", "bannana", "apple", "bread", "oatmeal", "apple" };
   
    unsigned int item_sum = 0; 
    for (auto& i: item_list) {
        std::cout << i << "\n";
        auto it = item_map.find(i);
        if (it == item_map.end()) { std::cout << "Not in map\n"; return EXIT_FAILURE; }
        Item a = it->second; 
        std::cout << a.getSku() << " " << a.getCost() << " " << a.getSpecialPrice() << "\n";
        item_sum += a.getCost();
    }

    std::cout << "Total : $ " << float(item_sum) / 100 << "\n";

    return EXIT_SUCCESS;
}

