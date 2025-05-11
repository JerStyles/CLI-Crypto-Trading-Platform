#pragma once
#include <vector>

#include "OrderBook.h"
#include "OrderBookEntry.h"

class MerkelMain {
 public:
  MerkelMain();
  void init();

 private:
  void printMenu();
  int getUserOption();
  void processUserOption(int userOption);
  void printHelp();
  void printMarketStats();
  void enterAsk();
  void enterBid();
  void printWallet();
  void gotoNextTimeFrame();
  std::string currentTime;
  OrderBook orderBook{"order_book.csv"};
};