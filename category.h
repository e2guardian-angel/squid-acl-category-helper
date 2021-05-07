#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "json/json.h"

std::string readAllText(const std::string& path) {
  std::ifstream infile;
  infile.open(path);
  if (infile.fail()) {
    return "";
  }
  infile.seekg(0, std::ios::end);
  auto size = infile.tellg();
  std::string contents((std::size_t)size, ' ');
  infile.seekg(0);
  infile.read(&contents[0], size);
  return contents;
}

Json::Value stringToJson(std::string arg) {
  Json::Value root;
  std::istringstream jsonStream(arg);
  jsonStream >> root;
  return root;
}
