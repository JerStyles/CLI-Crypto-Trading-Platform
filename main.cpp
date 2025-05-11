#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "CSVReader.h"
#include "MerkelMain.h"
#include "OrderBookEntry.h"

int main() {
  CSVReader::readCSV("order_book.csv");
  return 0;
}