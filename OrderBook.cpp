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

void OrderBook::insertOrder(OrderBookEntry& order) {
  orders.push_back(order);
  std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product,
                                                       std::string timestamp) {
  std::vector<OrderBookEntry> asks =
      getOrders(OrderBookType::ask, product, timestamp);
  std::vector<OrderBookEntry> bids =
      getOrders(OrderBookType::bid, product, timestamp);
  std::vector<OrderBookEntry> sales;

  std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
  std::sort(bids.begin(), asks.end(), OrderBookEntry::compareByPriceDesc);

  for (OrderBookEntry& ask : asks) {
    for (OrderBookEntry& bid : bids) {
      if (bid.price >= ask.price) {
        OrderBookEntry sale{ask.price, 0, timestamp, product,
                            OrderBookType::sale};
        if (bid.amount == ask.amount) {
          sale.amount = ask.amount;
          sales.push_back(sale);
          bid.amount = 0;
          break;
        }

        if (bid.amount > ask.amount) {
          sale.amount = ask.amount;
          sales.push_back(sale);
          bid.amount = bid.amount - ask.amount;
        }

        if (bid.amount < ask.amount) {
          sale.amount = bid.amount;
          sales.push_back(sale);
          ask.amount = ask.amount - bid.amount;
          bid.amount = 0;
          continue;
        }
      }
    }
  }
  return sales;
}