#include <iostream>
#include <vector>
#include <string>

// 1. DEFINE THE TYPES
// Using an Enum is faster than comparing strings ("Buy" == "Buy")
enum class OrderType {
    Buy,
    Sell
};

// 2. THE ORDER OBJECT
// This is the atom of our universe.
class Order {
public:
    int id;
    double price;
    int quantity;
    OrderType type;

    // Constructor
    Order(int _id, double _price, int _qty, OrderType _type) 
        : id(_id), price(_price), quantity(_qty), type(_type) {}
};

// 3. THE BOOK
class OrderBook {
private:
    // We need two lists: one for Buys, one for Sells.
    // We use std::vector for now (simple dynamic array).
    std::vector<Order> buy_orders;
    std::vector<Order> sell_orders;

public:
    // Function to add an order to the book
    void addOrder(int id, double price, int qty, OrderType type) {
        // Create the order object
        Order newOrder(id, price, qty, type);

        // LOGIC TEST:
        // If it's a Buy, push to buy_orders.
        // If it's a Sell, push to sell_orders.
        if (type == OrderType::Buy) {
            buy_orders.push_back(newOrder);
        } else {
            // ??? (Fill this in)
            sell_orders.push_back(newOrder);
        }
        
        std::cout << "Order " << id << " added." << std::endl;
    }

    // Function to print the book (Debug)
    void printBook() {
        std::cout << "--- BUY ORDERS ---" << std::endl;
        for (const auto& order : buy_orders) {
            std::cout << "ID: " << order.id << " @ " << order.price << std::endl;
        }
        // ??? (Do the same for Sell orders)
        std::cout << "--- SELL ORDERS ---" << std::endl;
        for (const auto& order : sell_orders) {
            std::cout << "ID: " << order.id << " @ " << order.price << std::endl;
        }
    }
};

int main() {
    OrderBook book;
    
    // Test Case 1: Add a Buy Order
    book.addOrder(1, 100.50, 10, OrderType::Buy);
    
    // Test Case 2: Add a Sell Order
    book.addOrder(2, 101.00, 5, OrderType::Sell);

    book.printBook();
    return 0;
}