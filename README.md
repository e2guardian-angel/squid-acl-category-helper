# squid-acl-category-helper
Squid external acl helper for categorizing IP addresses
This program utilizes the REST client library found here:

https://github.com/mrtazz/restclient-cpp.git

This program is part of the e2guardian-angel project and interfaces with the guardian-angel web service:

https://github.com/e2guardian-angel/guardian-angel

## Environment variables
Before running, you must define the following environment variables:
* GUARDIAN_HOST - hostname/ip of guardian-angel instance
* GUARDIAN_PORT - port that guardian-angel is running on
