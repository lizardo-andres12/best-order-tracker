#include <iostream>
#include <map>
#include <unordered_map>


struct Order {
    char side;
    double price;
    int quantity;
};


void printBestOrders(const std::map<double, int>& bids, const std::map<double, int>& asks) {
    if (!bids.empty()) {
	std::cout << bids.rbegin()->first << ' ';
    } else {
	std::cout << "- ";
    }

    if (!asks.empty()) {
	std::cout << asks.begin()->first << '\n';
    } else {
	std::cout << "-\n";
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::map<double, int> bids;
    std::map<double, int> asks;
    std::unordered_map<int, Order> orders;

    int id, quantity;
    double price;
    char side;

    while (std::cin >> id >> side >> price >> quantity) {
	if (quantity == 0) {
	    auto it = orders.find(id);
	    if (it != orders.end()) {
		const Order& order = it->second;
		auto& book = order.side == 'B' ? bids : asks;
		
		book[order.price] -= order.quantity;
		if (book[order.price] <= 0) {
		    book.erase(order.price);
		}
		orders.erase(it);
	    }
	} else {
	    auto it = orders.find(id);
	    if (it != orders.end()) {
		const Order& oldOrder = it->second;
		auto& oldBook = oldOrder.side == 'B' ? bids : asks;

		oldBook[oldOrder.price] -= oldOrder.quantity;
		if (oldBook[oldOrder.price] <= 0) {
		    oldBook.erase(oldOrder.price);
		}
	    }

	    orders[id] = {side, price, quantity};
	    auto& book = side == 'B' ? bids : asks;
	    book[price] += quantity;
	}

	printBestOrders(bids, asks);
    }

    return 0;
}
