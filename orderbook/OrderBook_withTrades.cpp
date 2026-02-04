#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Required for std::sort

// 1. DEFINE THE TYPES
enum class OrderType {
    Buy,
    Sell
};

// 2. THE ORDER OBJECT
class Order {
public:
    int id;
    double price;
    int quantity;
    OrderType type;

    Order(int _id, double _price, int _qty, OrderType _type) 
        : id(_id), price(_price), quantity(_qty), type(_type) {}
};

// 3. THE BOOK
class OrderBook {
private:
    std::vector<Order> buy_orders;
    std::vector<Order> sell_orders;

    // Sorting Rules (Comparators)
    // Buys: Highest Price is top priority
    static bool compareBuys(const Order& a, const Order& b) {
        return a.price > b.price; 
    }
    // Sells: Lowest Price is top priority
    static bool compareSells(const Order& a, const Order& b) {
        return a.price < b.price; 
    }

public:
    // The Matching Engine
    void match() {
        // Sort both sides to get Best Bid and Best Ask at the front
        std::sort(buy_orders.begin(), buy_orders.end(), compareBuys);
        std::sort(sell_orders.begin(), sell_orders.end(), compareSells);

        // While both sides have orders, check for matches
        while (!buy_orders.empty() && !sell_orders.empty()) {
            
            Order& bestBuy = buy_orders.front();
            Order& bestSell = sell_orders.front();

            // Do prices cross? (Bid >= Ask)
            if (bestBuy.price >= bestSell.price) {
                
                // Determine Quantity: The minimum of the two
                int tradeQty = std::min(bestBuy.quantity, bestSell.quantity);
                
                // Determine Price: Maker-Taker rule
                // In a real engine, we check timestamps. 
                // Here, we simplify: The execution price is usually the resting order's price.
                // Since we re-sort every time, let's just use the Bid price for this visual test.
                double tradePrice = bestBuy.price; 
                
                std::cout << ">> TRADE EXECUTION: " << tradeQty << " units @ $" 
                          << tradePrice << " (Buyer: " << bestBuy.id 
                          << ", Seller: " << bestSell.id << ")" << std::endl;

                // Update Quantities
                bestBuy.quantity -= tradeQty;
                bestSell.quantity -= tradeQty;

                // Remove filled orders
                if (bestBuy.quantity == 0) buy_orders.erase(buy_orders.begin());
                if (bestSell.quantity == 0) sell_orders.erase(sell_orders.begin());
                
            } else {
                // No cross? Stop matching.
                break;
            }
        }
    }

    void addOrder(int id, double price, int qty, OrderType type) {
        Order newOrder(id, price, qty, type);
        
        if (type == OrderType::Buy) {
            buy_orders.push_back(newOrder);
            std::cout << "[+] Added BUY: Order " << id << " @ $" << price << std::endl;
        } else {
            sell_orders.push_back(newOrder);
            std::cout << "[+] Added SELL: Order " << id << " @ $" << price << std::endl;
        }
        
        // Run the engine immediately after every new order
        match();
    }
};

int main() {
    OrderBook book;
    
    std::cout << "--- MARKET OPEN ---" << std::endl;
    
    // 1. Add a BUY order (Maker)
    // Buyer #1 wants 10 units at $100.
    book.addOrder(1, 100.00, 10, OrderType::Buy);
    
    // 2. Add a SELL order (Taker)
    // Seller #2 is willing to sell 5 units at $99.
    // Logic: Since Buyer #1 is already there at $100, this should trade instantly.
    book.addOrder(2, 99.00, 5, OrderType::Sell);

    // 3. Add another SELL order (Taker)
    // Seller #3 sells 5 units at $100.
    // Logic: Should fill the remaining 5 units of Buyer #1.
    book.addOrder(3, 100.00, 5, OrderType::Sell);

    return 0;
}