#ifndef UTILS_H
#define UTILS_H

#include <sstream>

template <class N>
std::string NumberToString(N n)
{
	std::stringstream ss;
	ss << n;
	return ss.str();
}

#endif