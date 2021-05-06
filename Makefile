# compiler flags:
# -lcurl

all: ip_category_helper

ip_category_helper: category.cpp
	g++ -o ip_category_helper category.cpp /usr/lib/libjsoncpp.a /usr/local/lib/librestclient-cpp.a -lcurl

clean:
	rm ip_category_helper
