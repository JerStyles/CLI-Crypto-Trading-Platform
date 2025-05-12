#pragma once

#include <map>
#include <string>

#include "OrderBookEntry.h"

class Wallet {
 public:
  Wallet();
  void insertCurrency(std::string type, double amount);
  bool removeCurrency(std::string type, double amount);

  bool containsCurrency(std::string type, double amount);
  bool canFulfillOrder(OrderBookEntry order);
  std::string toString();

 private:
  std::map<std::string, double> currencies;  // Declare the map here
};