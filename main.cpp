#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <optional>

// This class holds the logic for special prices
// Must be in the for of quantity and cost
// eg 3 for 75 cents
// eg 2 for one is an quantity of 2 for the cost of a single item
// eg 20 % off is quantity of 1 and cost of 80 % of the price
class SpecialPrice {

private:
    unsigned int m_quantity;
    unsigned int m_cost;

public:

    SpecialPrice(unsigned int quantity, unsigned int cost) :
        m_quantity(quantity), m_cost(cost) {}

    unsigned int getQuantity() const { return m_quantity; }
    unsigned int getCost() const { return m_cost; }

};

// Item class holds the cost of each item in pennies and an optional the special price class.
// Not all items have a special price.
// The sku was not necessary in the class because it is kept as
// the dictionary key. See pricing rules in the main function.
class Item {

private:
    unsigned int m_cost; // in pennies
    std::optional<SpecialPrice> m_special_price;

public:
    Item(unsigned int cost) : m_cost(cost) {}

    Item(unsigned int cost, SpecialPrice special_price) : 
        m_cost(cost), m_special_price(special_price) {}

    unsigned int getCost() const { return m_cost; }
    std::optional<SpecialPrice> getSpecialPrice() const { return m_special_price; }

};

// The checkout class that holds the pricing rules and the current list of items
// getTotalPrice calculates the current total price of the item list.
class Checkout {

private:
    // The pricing rules for each item in the store
    std::unordered_map<std::string, Item> m_pricing_rules;

    // The current list of items being scanned
    std::vector<std::string> m_item_list;

public:

    Checkout (std::unordered_map<std::string, Item> pricing_rules) : 
        m_pricing_rules(std::move(pricing_rules)) {}

    void scan(std::string sku) { m_item_list.emplace_back(sku); }
    float getTotalPrice() const; 

};

// Main price logic. Calculate the current price for items in the list.
// If new items are added this function must be called to get the total price.
float Checkout::getTotalPrice() const {
   
    // We need a count for each item to see if any special price rules apply 
    std::unordered_map<std::string, size_t> item_count;
    for (const auto& i: m_item_list) {
        item_count[i]++;
    }
   
    unsigned int total_price = 0; 

    for (auto& [sku, quantity]: item_count) {
        std::cout << sku << " " << quantity << "\n";

        auto it = m_pricing_rules.find(sku);

        // Fail if the item is not in the pricing rules.
        assert(("Item not in pricing rules", it != m_pricing_rules.end())); 

        auto& item = it->second; 

        // Check for special price and charge items at that price for the given quantity
        // Items remaining will be changed regular price
        auto specialPrice = item.getSpecialPrice();
        if (specialPrice.has_value()) {
            
            auto multiple = quantity / specialPrice->getQuantity();
            if (multiple > 0) {
                total_price += multiple * specialPrice->getCost();
                // remove the items that receive a special price
                quantity -= multiple * specialPrice->getQuantity();
            }
            
        }

        // All non special price items
        total_price += quantity * item.getCost();
    }
    

    return float(total_price) / 100.0f;
}

int main() {

    // Pricing rules. A dictionary with the sku as the key and the item as a value.
    // Items include price in cents and/or special prices.
    // Special prices have quantity and price: eg 3 for 50 cents.
    // Not all items have special prices.
    std::unordered_map<std::string, Item> pricing_rules = {
        { "apple", Item(25, SpecialPrice(3, 50) ) },
        { "banana", Item(25) },
        { "oatmeal", Item(50) },
        { "bread", Item(75) }
    };

    // The items being scanned at the register
    std::vector<std::string> item_list = {
        "apple", "apple", "banana", "apple", "bread", "oatmeal", "apple" };

    // Create the Checkout
    Checkout co(pricing_rules);
    
    // Scan each item
    for(const auto& i: item_list) {
        co.scan(i);
    }

    // Get the price
    float price = co.getTotalPrice();
    std::cout << "\nTotal : $ " << price << "\n";

    return EXIT_SUCCESS;
}

