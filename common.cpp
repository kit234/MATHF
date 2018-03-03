//common.cpp：多个文件需要用到的公共函数的定义
#include "common.h"
#include <string>
#include <cctype>

using std::string;
using std::isdigit;

string DeleteBlank(string str){
	string but;
	for(unsigned int i{0};i < str.length();++i){
		if(str[i] == '\''){
			for(unsigned int location{i+1};location<str.length();++location){
				if(str[location] == '\''){
					but += str.substr(i,location-i+1);
					i = location;
					break;
				}
			}
		}
		else if(str[i] == '"'){
			for(unsigned int location{i+1};location<str.length();++location){
				if(str[location] == '"'){
					but += str.substr(i,location-i+1);
					i = location;
					break;
				}
			}
		}
		else if(str[i] != ' ') but += str[i];
	}
	return but;
}

string GetTypeOf(string str){
	if(str.empty()) return "unknow";
	if(str[0] == '\'' && str[str.length()-1] == '\'') return "string";
	if(str[0] == '"' && str[str.length()-1] == '"') return "string";
	{
		bool IsDigit{true};
		for(decltype(str.length()) i{0};i < str.length();++i){
			if(i == 0 && (str[0] == '-' || str[0] == '+')) continue;
			if(!isdigit(str[i])){IsDigit = false; break;}
		}
		if(IsDigit) return "number";
	}
	return "unknow";
}
