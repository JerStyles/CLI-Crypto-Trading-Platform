#include "OrderBook.h"

#include <map>

#include "CSVReader.h"

OrderBook::OrderBook(std::string filename) {
  orders = CSVReader::readCSV(filename);
}
std::vector<std::string> OrderBook::getKnownProducts() {
  std::vector<std::string> products;
  std::map<std::string, bool> productsMap;

  for (OrderBookEntry& entry : orders) {
    productsMap[entry.product] = true;
  }

  for (auto const& entry : productsMap) {
    products.push_back(entry.first);
  }

  return products;
}
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                                 std::string product,
                                                 std::string timestamp) {
  std::vector<OrderBookEntry> orders_sub;
  for (OrderBookEntry& entry : orders) {
    if (entry.orderType == type && entry.product == product &&
        entry.timestamp == timestamp) {
      orders_sub.push_back(entry);
    }
  }
  return orders_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders) {
  double max = orders[0].price;
  for (OrderBookEntry& entry : orders) {
    if (entry.price > max) {
      max = entry.price;
    }
  }
  return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders) {
  double min = orders[0].price;
  for (OrderBookEntry& entry : orders) {
    if (entry.price < min) {
      min = entry.price;
    }
  }
  return min;
}

std::string OrderBook::getEarliestTime() {
  return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp) {
  std::string next_timestamp = "";
  for (OrderBookEntry& entry : orders) {
    if (entry.timestamp > timestamp) {
      next_timestamp = entry.timestamp;
      break;
    }
    if (next_timestamp == "") {
      next_timestamp = orders[0].timestamp;
    }
  }
  return next_timestamp;
}
