#pragma once
#include <string>
#include "List.h"
using namespace std;
string listToStringCommas(List<string> list) { 
	string res;
	List<string>::Iterator it = list.cbegin();
	if (it != list.cend()) {
		res += it.elem();
		it.next();
	}
	while (it != list.cend()) {
		res += "," + it.elem();
		it.next();
	}
	return res;
}