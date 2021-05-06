# compiler flags:
# -lcurl
CFLAGS  = -lcurl

all: ip_category_helper

ip_category_helper: category.cpp
	g++ $(CFLAGS) -o ip_category_helper /usr/lib/libjsoncpp.a /usr/local/lib/librestclient-cpp.a

clean:
	rm ip_category_helper
