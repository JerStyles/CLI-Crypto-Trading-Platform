#include "MerkelMain.h"

#include <iostream>
#include <vector>

#include "CSVReader.h"
#include "OrderBookEntry.h"

MerkelMain::MerkelMain() {

};

void MerkelMain::init() {
  int input;
  currentTime = orderBook.getEarliestTime();
  while (true) {
    printMenu();
    input = getUserOption();
    processUserOption(input);
  }
};

void MerkelMain::printMenu() {
  // 1 Print help
  std::cout << "1: Help" << std::endl;

  // 2 Print exchange stat
  std::cout << "2: Print exchange stats" << std::endl;

  // 3 Make an offer
  std::cout << "3: Make an offer" << std::endl;

  // 4 Make a bid
  std::cout << "4: Make a bid" << std::endl;

  // 5 Print wallet
  std::cout << "5: Print wallet" << std::endl;

  // 6 Continue
  std::cout << "6: Continue" << std::endl;

  std::cout << "=========================" << std::endl;

  std::cout << "Current time is: " << currentTime << std::endl;
}

int MerkelMain::getUserOption() {
  int userOption;
  std::cout << "Type in 1-6" << std::endl;
  std::cin >> userOption;
  std::cout << "Your choice: " << userOption << "\n" << std::endl;

  return userOption;
}

void MerkelMain::processUserOption(int userOption) {
  if (userOption == 0) {
    std::cout << "Invalid choice. Choose 1-6" << std::endl;
  }

  if (userOption == 1) {
    printHelp();
  }

  if (userOption == 2) {
    printMarketStats();
  }

  if (userOption == 3) {
    enterOffer();
  }

  if (userOption == 4) {
    enterBid();
  }

  if (userOption == 5) {
    printWallet();
  }

  if (userOption == 6) {
    gotoNextTimeFrame();
  }
}

void MerkelMain::printHelp() {
  std::cout << "Help - your aim is to make money. Analyze the market and make "
               "bids and offers."
            << std::endl;
}

void MerkelMain::printMarketStats() {
  for (std::string const product : orderBook.getKnownProducts()) {
    std::cout << "Product: " << product << std::endl;
    std::vector<OrderBookEntry> entries = orderBook.getOrders(
        OrderBookType::ask, product, currentTime);

    if (entries.empty()) {
      std::cout << "No asks found for product: " << product << std::endl;
      continue;
    }

    std::cout << "Asks seen: " << entries.size() << std::endl;
    std::cout << "Max asks: " << OrderBook::getHighPrice(entries) << std::endl;
    std::cout << "Min asks: " << OrderBook::getLowPrice(entries) << std::endl;
  }
  unsigned int bids = 0;
  unsigned int asks = 0;
  // for (OrderBookEntry& entry : orders) {
  //   if (entry.orderType == OrderBookType::ask) {
  //     ++asks;
  //   }
  //   if (entry.orderType == OrderBookType::bid) {
  //     ++bids;
  //   }
  // }
  std::cout << "OrderBook asks: " << asks << " bids: " << bids << std::endl;
}

void MerkelMain::enterOffer() {
  std::cout << "Make an offer - enter the amout" << std::endl;
}

void MerkelMain::enterBid() {
  std::cout << "Make a bid - enter the amout" << std::endl;
}

void MerkelMain::printWallet() {
  std::cout << "Your wallet is empty" << std::endl;
}

void MerkelMain::gotoNextTimeFrame() {
  std::cout << "Going to next time frame." << std::endl;
  currentTime = orderBook.getNextTime(currentTime);
}