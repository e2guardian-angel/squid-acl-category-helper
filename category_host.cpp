/*
 * category.cpp
 *
 * This is the code that does the REST API calls to guardian-angel.
 * It sends an hostname to be checked, as well as the category name (which should be the name of the acl).
 */
#include <iostream>
#include <string>
#include <sstream>
#include "restclient-cpp/restclient.h"
#include "json/json.h"

using namespace std;

int main(int argc, char **argv) {

  /*
   * Get guardian-angel host and port from environment variables
   */
  const char* hostCstr = getenv("GUARDIAN_HOST");
  const char* portCstr = getenv("GUARDIAN_PORT");
  if (hostCstr == NULL || portCstr == NULL) {
    cerr << "ERROR: Must set GUARDIAN_HOST and GUARDIAN_PORT variables before running." << endl;
    return -1;
  }
  string host = string(hostCstr);
  string port = string(portCstr);
  try {
    stoi(portCstr);
  } catch (std::invalid_argument e) {
    cerr << "ERROR: GUARDIAN_PORT is in invalid format, expected integer" << endl;
    return -1;
  }

  const string CATEGORY_POST_URL = "http://" + host + ":" + port + "/lookuphost";

  /*
   * Main logic
   */
  while(1) {
    string category, hostname;
    cin >> category >> hostname;
    
    // Perform REST API
    RestClient::Response r = RestClient::post(CATEGORY_POST_URL, "application/json", "{\"hostname\":\"" + hostname + "\",\"category\":\"" + category +"\"}");

    if (r.code != 200) {
      cout << "ERR" << endl;
    } else {
      JSONCPP_STRING err;
      Json::Value root;
      std::istringstream jsonStream(r.body);
      jsonStream >> root;
      bool match = root["match"].asBool();

      if (match) {
	cout << "OK" << endl;
      } else {
	cout << "ERR" << endl;
      }
    }
  }

  return 0;
  
}
