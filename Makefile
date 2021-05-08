# Makefile for category helper

all: category_helper

SQUID_HELPER_DIR=/usr/local/bin/squidhelpers

category_helper: category.cpp
	g++ -o category_helper category.cpp /usr/lib/libjsoncpp.a /usr/local/lib/librestclient-cpp.a -lcurl

install:
	mkdir -p $(SQUID_HELPER_DIR) && cp category_helper $(SQUID_HELPER_DIR)

clean:
	rm category_helper
