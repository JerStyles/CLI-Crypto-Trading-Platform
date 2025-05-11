#include "CSVReader.h"

#include <fstream>
#include <iostream>

CSVReader::CSVReader() {
}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename) {
  std::vector<OrderBookEntry> entries;

  std::ifstream csvFile{csvFilename};
  std::string line;
  if (csvFile.is_open()) {
    while (std::getline(csvFile, line)) {
      try {
        OrderBookEntry obe = stringsToOBE(tokenize(line, ','));
        entries.push_back(obe);
      } catch (const std::exception& e) {
        std::cout << "Bad data" << std::endl;
      }

    }  // end of while
  }
  std::cout << "CSVReader::readCSV read " << entries.size() << " entries"
            << std::endl;
  return entries;
}

std::vector<std::string> CSVReader::tokenize(std::string csvLine,
                                             char separator) {
  std::vector<std::string> tokens;
  signed int start, end;
  std::string token;
  start = csvLine.find_first_not_of(separator, 0);
  do {
    end = csvLine.find_first_of(separator, start);
    if (start == csvLine.length() || start == end) {
      break;
    }
    if (end > 0) {
      token = csvLine.substr(start, end - start);
    } else {
      token = csvLine.substr(start, csvLine.length() - start);
    }
    tokens.push_back(token);
    start = end + 1;

  } while (end > 0);

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

  OrderBookEntry obe{price, amount, tokens[0], tokens[1],
                     OrderBookEntry::stringToOrderBookType(tokens[2])};

  return obe;
}

OrderBookEntry CSVReader::stringsToOBE(std::string priceString,
                                       std::string amountString,
                                       std::string timestamp,
                                       std::string product,
                                       OrderBookType orderType) {
  double price, amount;
  try {
    double price = std::stod(priceString);
    double amount = std::stod(amountString);

  } catch (std::exception& e) {
    std::cout << "Bad float: " << priceString << " " << amountString
              << std::endl;
    throw;
  }

  OrderBookEntry obe{price, amount, timestamp, product, orderType};
  return obe;
}
