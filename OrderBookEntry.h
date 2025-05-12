#pragma once
#include <string>

enum class OrderBookType { bid, ask, unknown, sale };

class OrderBookEntry {
 public:
  OrderBookEntry(double _price, double _amount, std::string _timestamp,
                 std::string _product, OrderBookType _orderType);

  static OrderBookType stringToOrderBookType(std::string s);

  static bool compareByTimestamp(OrderBookEntry& entry_1,
                                 OrderBookEntry& entry_2) {
    return entry_1.timestamp < entry_2.timestamp;
  }

  static bool compareByPriceAsc(OrderBookEntry& entry_1,
                              OrderBookEntry& entry_2) {
    return entry_1.price < entry_2.price;
  }

  static bool compareByPriceDesc(OrderBookEntry& entry_1,
                               OrderBookEntry& entry_2) {
    return entry_1.price > entry_2.price;
  }
  double price;
  double amount;
  std::string timestamp;
  std::string product;
  OrderBookType orderType;
};

// OrderBookTypeOrderBookEntry(double _price, double _amount, std::string
// _timestamp, std::string _product, OrderBookType _orderType);
