//operation_string.cpp：和字符串类型运算有关的函数
#include "operation.h"
#include "common.h"

using std::string;

typedef string String_Type; //用于运算的字符串类型

static bool IsOperator(char); //判断所给字符是否是运算符
static void check(string) throw(string,const char*);	//检查字符串是否合法

bool IsOperator(char c){
	if(c == '+') return true;
	return false;
}

string operation_string(string str){
	check(str);
	String_Type but;
	str = "+" + str;
	str = str + "+";
	do{
		bool exit{true};
		for(decltype(str.length()) i{0};i < str.length();++i){
			if(str[i] == '+'){
				if(i == str.length()-1) break;
				exit = false;
				auto e{i+1};
				for(;e < str.length();++e){
					if(str[e] == '\''){
						for(auto j{e+1};j < str.length();++j)
							if(str[j] == '\''){e = j; break;}
					}
					else if(str[e] == '"'){
						for(auto j{e+1};j < str.length();++j)
							if(str[j] == '"'){e = j;break;}
					}
					else if(IsOperator(str[e])) break;
				}
				if(GetTypeOf(str.substr(i+1,e-i-1))!="string")
					throw "错误（string）：未知数据类型！";
				but += str.substr(i+2,e-i-3);
				i = e-1;
			}
		}
	}while(!exit);
	return but;
}

void check(string str) throw(string,const char*){
	if(IsOperator(str[0]) || IsOperator(str[str.length()-1]))
		throw "错误（string）：运算符单双目性错误！";
	for(auto itr = str.begin();itr != str.end();++itr){
		if(*itr == '\''){
			for(auto p = itr + 1;p != str.end();++p)
				if(*p == '\''){itr = p; break;}
			continue;
		}
		if(*itr == '"'){
			for(auto p = itr + 1;p != str.end();++p)
				if(*p == '"'){itr = p; break;}
			continue;
		}
		if(IsOperator(*itr) && (IsOperator(*(itr-1)) || IsOperator(*(itr+1))))
			throw "错误（string）：运算符重复出现！";
	}
}
