#pragma once
#include <string>
#include <vector>

#include "CSVReader.h"
#include "OrderBookEntry.h"

class OrderBook {
 public:
  OrderBook(std::string filename);
  std::vector<std::string> getKnownProducts();
  std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product,
                                        std::string timestamp);
  void insertOrder(OrderBookEntry& order);
  std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);
  std::string getEarliestTime();
  std::string getNextTime(std::string timestamp);
  static double getHighPrice(std::vector<OrderBookEntry>& orders);
  static double getLowPrice(std::vector<OrderBookEntry>& orders);

 private:
  std::vector<OrderBookEntry> orders;
};