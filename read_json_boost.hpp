#ifndef __READ_JSON_BOOST__
#define __READ_JSON_BOOST__

#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\json_parser.hpp>
#include <iostream>
#include <string>

namespace READ_JSON_BOOST {
	template<class T>
	T read_json_child(std::string str,std::string child_name) {
		std::stringstream ss(str);
		boost::property_tree::ptree pt;

		try {
			read_json(ss, pt);
		}
		catch (boost::property_tree::ptree_error &e) {
			return -1;
		}

		try {
			T value = pt.get<T>(child_name);	// 得到"code"的value   
			return value;
		}
		catch (boost::property_tree::ptree_error &e)
		{
			return -1;
		}
	}
}

#endif // !__READ_JSON_BOOST__
