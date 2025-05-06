#pragma once
#include <vector>
#include "OrderBookEntry.h"

class MerkelMain {
 public:
  MerkelMain();
  // call this to start the sim
  void init();

 private:
  void loadOrderBook();
  void printMenu();
  int getUserOption();
  void processUserOption(int userOption);
  void printHelp();
  void printMarketStats();
  void enterOffer();
  void enterBid();
  void printWallet();
  void gotoNextTimeFrame();
  std::vector<OrderBookEntry> orders;
};