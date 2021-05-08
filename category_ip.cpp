/*
 * category.cpp
 *
 * This is the code that does the REST API calls to guardian-angel.
 * It sends an IP to be checked, as well as the category name (which should be the name of the acl).
 */
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "restclient-cpp/restclient.h"
#include "json/json.h"
#include "category.h"

using namespace std;
const string CONFIG_PATH = "/opt/guardian/helper.conf";
const int READ_BUFFER_SIZE = 1024;

int main(int argc, char **argv) {

  /*
   * Get guardian-angel host and port from config file
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

  const string CATEGORY_POST_URL = "http://" + host + ":" + port + "/lookupip";

  /*
   * Main logic
   */
  while(1) {
        char buffer[READ_BUFFER_SIZE];
    string category, ip;
    cin.getline(buffer, 1024, '\n');
    stringstream ss(buffer);
    ss >> category;
    ss >> ip;
    
    // Perform REST API
    RestClient::Response r = RestClient::post(CATEGORY_POST_URL, "application/json", "{\"ip\":\"" + ip + "\",\"category\":\"" + category +"\"}");

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
