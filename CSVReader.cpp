#include "CSVReader.h"
#include <iostream>

CSVReader::CSVReader() {
}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFile) {
  std::vector<OrderBookEntry> entries;
  return entries;
}

std::vector<std::string> CSVReader::tokenize(std::string csvLine,
                                             char separator) {
  std::vector<std::string> tokens;
  return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens) {
  double price, amount;
  if (tokens.size() != 5) {
    std::cout << "Bad Line" << std::endl;
    throw std::exception{};
  }

  try {
    double price = std::stod(tokens[3]);
    double amount = std::stod(tokens[4]);
    std::cout << price << " : " << amount << std::endl;

  } catch (std::exception& e) {
    std::cout << "Bad float: " << tokens[3] << " " << tokens[4] << std::endl;
    throw;
  }

  OrderBookEntry obe{price, amount, tokens[0], tokens[1], OrderBookEntry::stringToOrderBookType(tokens[2])};

  return obe;
}
