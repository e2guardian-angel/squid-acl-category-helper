/*
 * category.cpp
 *
 * This is the code that does the REST API calls to guardian-angel.
 * It sends an hostname to be checked, as well as the category name (which should be the name of the acl).
 */
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <arpa/inet.h>
#include "restclient-cpp/restclient.h"
#include "json/json.h"

using namespace std;
const string CONFIG_PATH = "/opt/guardian/helper.conf";
const int READ_BUFFER_SIZE = 1024;


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


int main(int argc, char **argv) {

  /*
   * Get guardian-angel host and port from environment variables
   */
  string configStr = readAllText(CONFIG_PATH);
  if (configStr == "") {
    cerr << "Must provide a valid config file in " + CONFIG_PATH << endl;
    return -1;
  }

  string host, port;
  try {
    Json::Value config = stringToJson(configStr);
    host = config["host"].asString();
    port = config["port"].asString();
    stoi(port.c_str());
  } catch (std::exception e) {
    cerr << "ERROR: host and/or port are missing or invalid" << endl;
    return -1;
  }

  const string HOST_CATEGORY_POST_URL = "http://" + host + ":" + port + "/lookuphost";
  const string IP_CATEGORY_POST_URL = "http://" + host + ":" + port + "/lookupip";

  /*
   * Main logic
   */
  while(1) {
    char buffer[READ_BUFFER_SIZE];
    string dst, hostname;
    cin.getline(buffer, 1024, '\n');
    stringstream ss(buffer);
    ss >> category;
    ss >> dst;

    struct sockaddr_in sa;
    if (inet_pton(AF_INET, dst.c_str(), &(sa.sin_addr))) {
      // dst is an IP address
      RestClient::Response r = RestClient::post(IP_CATEGORY_POST_URL, "application/json", "{\"ip\":\"" + ip + "\",\"category\":\"" + category +"\"}");
    } else {
      // dst is a hostname
      RestClient::Response r = RestClient::post(HOST_CATEGORY_POST_URL, "application/json", "{\"hostname\":\"" + hostname + "\",\"category\":\"" + category +"\"}");
    }

    if (r.code != 200) {
      cout << "ERR" << endl;
    } else {
      Json::Value responseJson = stringToJson(r.body);
      bool match = responseJson["match"].asBool();

      if (match) {
	cout << "OK" << endl;
      } else {
	cout << "ERR" << endl;
      }
    }
  }

  return 0;
  
}
