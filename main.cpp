#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "CSVReader.h"
#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include "Wallet.h"

int main() {
  // CSVReader::readCSV("order_book.csv");
  // Wallet wallet;
  // wallet.insertCurrency("BTC", 5);
  // wallet.insertCurrency("USDT", 100005);

  // std::cout << "Wallet has BTC " << wallet.containsCurrency("BTC", 10)
  //           << std::endl;

  // std::cout << wallet.toString() << std::endl;
  // wallet.removeCurrency("USD", 1000);
  MerkelMain app{};
  app.init();

  return 0;
}