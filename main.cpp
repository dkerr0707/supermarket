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

class Checkout {

private:
    // The item lookup table for each item available in the store
    std::unordered_map<std::string, Item> m_item_lookup;

    // The current list of items being scanned
    std::vector<std::string> m_item_list;

public:

    Checkout (std::unordered_map<std::string, Item> item_lookup) : 
        m_item_lookup(item_lookup) {}

    void scan(std::string sku) { m_item_list.emplace_back(sku); }
    float getTotalPrice(); 

};

float Checkout::getTotalPrice() {
    
    std::unordered_map<std::string, size_t> item_count;
    for (const auto& i: m_item_list) {
        item_count[i]++;
        // std::cout << "--> " << i << " " << item_count[i] << "\n";
    }
   
    unsigned int checkout_sum = 0; 

    for (const auto& [sku, quantity]: item_count) {
        std::cout << sku << " " << quantity << "\n";

        auto it = m_item_lookup.find(sku);
        // Fail if the item is not in the lookup table.
        if (it == m_item_lookup.end()) { std::cout << "Item not in lookup\n"; return 0.0; }

        auto& item = it->second; 

        // Check for special price and charge items at that price for the given quantity
        // Items remaining will be changed regular price
        if (item.hasSpecialPrice()) {
            
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
    

    return float(checkout_sum) / 100;
}

int main() {

    // Pricing rules. A dictionary with the sku as the key and the item as a value.
    // Item includes quantity and special prices.
    // Special prices are quantity and price: eg 3 for 50 cents.
    // You could also do 2 for one: eg 2 for 25 cents.
    // Special price of 0 for 0 is no special price, empty.
    std::unordered_map<std::string, Item> pricing_rules = {
        { "apple", Item(25, SpecialPrice(3, 50) ) },
        { "bannana", Item(25, SpecialPrice(0, 0) ) },
        { "oatmeal", Item(50, SpecialPrice(0, 0) ) },
        { "bread", Item(75, SpecialPrice(0, 0) ) }
    };

    // The items being scanned at the register
    std::vector<std::string> item_list = { "apple", "apple", "bannana", "apple", "bread", "oatmeal", "apple" };

    // Create the Checkout
    Checkout co(pricing_rules);
    
    // Scan each item
    for(const auto& i: item_list) {
        co.scan(i);
    }

    // Get the price
    float price = co.getTotalPrice();
    std::cout << "Total : $ " << price << "\n";

    return EXIT_SUCCESS;
}

