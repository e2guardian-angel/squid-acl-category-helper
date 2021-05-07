# compiler flags:
# -lcurl

host_category_helper: category_host.cpp
	g++ -o ip_category_helper category_host.cpp /usr/lib/libjsoncpp.a /usr/local/lib/librestclient-cpp.a -lcurl

ip_category_helper: category_ip.cpp
	g++ -o ip_category_helper category_ip.cpp /usr/lib/libjsoncpp.a /usr/local/lib/librestclient-cpp.a -lcurl

clean:
	rm ip_category_helper
