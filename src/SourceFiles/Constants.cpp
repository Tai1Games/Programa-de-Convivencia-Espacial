#include "Constants.h"
#include <fstream>

Constants::Constants(const std::string& path) {
	std::ifstream read(path);
	assert(read.is_open());  //hehe
	read >> data;
	initialized_ = true;
}

//La plantilla genérica no hace comprobaciones de tipo
template<typename T>
T Constants::getConstant(const std::string& key) const {
	T d;
	if (!data[key].is_null())
		d = data[key].get<T>();
	return d;
}
template<>
int Constants::getConstant<int>(const std::string& key) const {
	int pt = 0;
	if (!data[key].is_null() && data[key].is_number_integer())
		pt = data[key].get<int>();
	return pt;
}
template<>
bool Constants::getConstant<bool>(const std::string& key) const {
	bool r;
	if (!data[key].is_null() && data[key].is_boolean())
		r = data[key].get<bool>();
	return r;
}
template<>
double Constants::getConstant<double>(const std::string& key) const {
	double pt = 0;
	if (!data[key].is_null() && data[key].is_number())
		pt = data[key].get<double>();
	return pt;
}
template<>
std::string Constants::getConstant<std::string>(const std::string& key) const {
	std::string pt = "";
	if (!data[key].is_null() && data[key].is_string())
		pt = data[key].get<std::string>();
	return pt;
}
template<>
float Constants::getConstant<float>(const std::string& key) const {
	float pt = 0.0;
	if (!data[key].is_null() && data[key].is_number())
		pt = data[key].get<float>();
	return pt;
}