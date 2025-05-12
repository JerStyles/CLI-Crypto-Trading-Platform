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

  wallet.insertCurrency("BTC", 10);

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
  std::cout << "3: Make an Ask" << std::endl;

  // 4 Make a bid
  std::cout << "4: Make a Bid" << std::endl;

  // 5 Print wallet
  std::cout << "5: Print wallet" << std::endl;

  // 6 Continue
  std::cout << "6: Continue" << std::endl;

  std::cout << "=========================" << std::endl;

  std::cout << "Current time is: " << currentTime << std::endl;
}

int MerkelMain::getUserOption() {
  int userOption;
  std::string line;
  std::cout << "Type in 1-6" << std::endl;
  std::getline(std::cin, line);
  try {
    userOption = std::stoi(line);
  } catch (const std::exception& e) {
    std::cout << "Invalid input!" << std::endl;
  }

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
    enterAsk();
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
    std::vector<OrderBookEntry> entries =
        orderBook.getOrders(OrderBookType::ask, product, currentTime);

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

void MerkelMain::enterAsk() {
  std::cout << "Make an offer - enter the amount: product, price, amount, eg: "
               "ETH/BTC, 2000, 0.5"
            << std::endl;
  std::string input;
  std::getline(std::cin, input);
  std::vector<std::string> tokens = CSVReader::tokenize(input, ',');
  if (tokens.size() != 3) {
    std::cout << "Bad input! " << input << std::endl;
  } else {
    try {
      OrderBookEntry obe = CSVReader::stringsToOBE(
          tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::ask);
      orderBook.insertOrder(obe);
    } catch (const std::exception& e) {
      std::cout << " MerkelMain::enterAsk Bad input! " << std::endl;
    }
  }
  std::cout << "You typed: " << input << std::endl;
}

void MerkelMain::enterBid() {
  std::cout << "Make a bid - enter the amout" << std::endl;
}

void MerkelMain::printWallet() {
  std::cout << "Your wallet is empty" << std::endl;
}

void MerkelMain::gotoNextTimeFrame() {
  std::cout << "Going to next time frame." << std::endl;
  std::vector<OrderBookEntry> sales =
      orderBook.matchAsksToBids("ETH/BTC", currentTime);
  std::cout << "Sales: " << sales.size() << std::endl;

  for (OrderBookEntry& sale : sales) {
    std::cout << "Sale amount: " << sale.price << "amount" << std::endl;
  }
  currentTime = orderBook.getNextTime(currentTime);
}

bool isValidInput(const std::string& input) {
  // Check if the input is a single character and is a digit
  if (input.length() == 1 && std::isdigit(input[0])) {
    int num = input[0] - '0';
    return num >= 0 && num <= 6;
  }
  return false;
}