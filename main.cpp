#include <iostream>
#include <map>
#include <sstream>
#include <unordered_map>


struct Order {
    char side;
    double price;
    int quantity;
};


void printBestOrders(const std::map<double, int>& bids, const std::map<double, int>& asks) {
    auto bestBidIt = bids.rbegin();
    auto bestAskIt = asks.begin();

    if (bestBidIt != bids.rend()) {
	std::cout << bestBidIt->first << ' ';
    } else {
	std::cout << '-' << ' ';
    }

    if (bestAskIt != asks.end()) {
	std::cout << bestAskIt->first << '\n';
    } else {
	std::cout << '-' << '\n';
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
    std::string line;
    while (std::getline(std::cin, line)) {
	auto stream = std::istringstream(line);
	stream >> id;
	stream >> side;
	stream >> price;
	stream >> quantity;

	// get consistent ref to book without branching
	auto& book = side == 'B' ? bids : asks;
	if (quantity == 0) {
	    auto it = orders.find(id);
	    if (it == orders.end()) {
		continue;
	    }

	    book[price] -= it->second.quantity;
	    if (book[price] <= 0) {
		book.erase(price);
	    }
	    orders.erase(id);

	    printBestOrders(bids, asks);
	    continue;
	}

	auto it = orders.find(id);
	if (it != orders.end()) {
	    int oldQuantity = it->second.quantity;
	    book[price] -= (quantity - oldQuantity);
	} else {
	    orders.emplace(id, Order{side, price, quantity});
	    book[price] += quantity;
	}
	printBestOrders(bids, asks);
    }

    return 0;
}
