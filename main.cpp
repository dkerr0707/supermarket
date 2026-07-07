#include <iostream>
#include <vector>
#include <unordered_map>

class SpecialPrice {

private:
    unsigned int m_quantity;
    unsigned int m_cost;

public:

    SpecialPrice(unsigned int quantity, unsigned int cost) :
        m_quantity(quantity), m_cost(cost) {}

    unsigned int getQuantity() { return m_quantity; }
    unsigned int getCost() { return m_cost; }

};

class Item {

private:
    unsigned int m_cost; // in pennies
    SpecialPrice m_special_price;

public:
    Item(unsigned int cost, SpecialPrice special_price) : 
        m_cost(cost), m_special_price(special_price) {}

    unsigned int getCost() { return m_cost; }
    SpecialPrice getSpecialPrice() { return m_special_price; }
    bool hasSpecialPrice() { return m_special_price.getQuantity() != 0; }

};

int main() {

    std::unordered_map<std::string, Item> item_lookup = {
        { "apple", Item(25, SpecialPrice(3, 50) ) },
        { "bannana", Item(25, SpecialPrice(0, 0) ) },
        { "oatmeal", Item(50, SpecialPrice(0, 0) ) },
        { "bread", Item(75, SpecialPrice(0, 0) ) }
    };
    for (const auto& [sku, item]: item_lookup) {
        // std::cout << sku << " " << item.hasSpecialPrice() << "\n";
    }

    std::vector<std::string> item_list = { "apple", "bannana", "apple", "bread", "oatmeal", "apple" };

    std::unordered_map<std::string, size_t> item_count;
    for (const auto& i: item_list) {
        item_count[i]++;
        // std::cout << "--> " << i << " " << item_count[i] << "\n";
    }
   
    unsigned int checkout_sum = 0; 

    for (const auto& [sku, quantity]: item_count) {
        std::cout << sku << " " << quantity << "\n";

        auto it = item_lookup.find(sku);
        // Fail if the item is not in the lookup table.
        if (it == item_lookup.end()) { std::cout << "Item not in lookup\n"; return EXIT_FAILURE; }

        auto& item = it->second; 

        // Check for special price and charge items at that price for the given quanity
        // Items remaining will be changed regular price
        if (item.hasSpecialPrice()) {
            std::cout << "Special Price\n";
            auto specialPrice = item.getSpecialPrice();
            auto multiple = quantity / specialPrice.getQuantity();
            if (multiple > 0) {
                checkout_sum += multiple * specialPrice.getCost();
                // remove the items that receive a special price
                item_count[sku] -= multiple * specialPrice.getQuantity();
            }
            
        }
        checkout_sum += quantity * item.getCost();
    }
    
    std::cout << "\nTotal : $ " << float(checkout_sum) / 100 << "\n";

    return EXIT_SUCCESS;
}

