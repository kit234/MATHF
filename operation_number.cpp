//operation_number.cpp：和数字型运算有关的函数
#include "operation.h"
#include "common.h"
#include <string>
#include <cctype>

using std::string;
using std::isdigit;

//operation_number_without函数的一部分
#define part1 exit=false;
#define part2 auto e{i+1} , s{i-1}; //判断一个算术表达式的头尾
//因为unsigned与signed的相互转化，故使用s<str.length()作为条件
#define part3 for(;s < str.length();--s){if(IsOperator(str[s])) break;}
#define part4 for(;e < str.length();++e){if(e == i+1) continue; if(IsOperator(str[e])) break;}
#define part5 if(GetTypeOf(str.substr(s,i-s))!="number") throw "错误（number）：未知数据类型！";
#define part6 if(GetTypeOf(str.substr(i+1,e-i-1))!="number") throw "错误（number）：未知数据类型！";
#define part7 Number_Type but1{ StrToNum(str.substr(s,i-s)) };	//算术表达式中的第一个数
#define part8 Number_Type but2{ StrToNum(str.substr(i+1,e-i-1)) };	//算术表达式中的第二个数
#define part part1 part2 part3 part4 part5 part6 part7 part8
//-----------------------------------

typedef double Number_Type;	//文件中数字型运算中的数字类型

int CharToInt(char);	//将char类型转化成int型
static bool IsOperator(char);	//判断所给字符是否为运算符
string NumToStr(Number_Type);	//将Number_Type型转化成string型
Number_Type StrToNum(string);	//将string型转化成Number_Type型
string operation_number_without(string);	//完成不带括号的数字型运算

int CharToInt(char c){
	switch(c){
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
	}
}

bool IsOperator(char c){
	if(c == '+') return true;
	if(c == '-') return true;
	if(c == '*') return true;
	if(c == '/') return true;
	return false;
}

string NumToStr(Number_Type v){
	char but[100];
	sprintf(but,"%f",v);
	string str{but};
	//完成字符串的化简
	for(auto itr{ str.end()-1 };itr != str.begin();--itr){
		if(isdigit(*itr) && *itr != '0') break;
		if(*itr == '0'){*itr = ' '; continue;}
		if(*itr == '.'){*itr = ' '; break;}
	}
	str = DeleteBlank(str);
	if(!IsOperator(str[0])) str = "+" + str;
	return str;
}

Number_Type StrToNum(string str){
	Number_Type v{0};
	bool IsPoint{false};	//判断是否是小数
	bool IsNegative{false};	//判断是否是负数
	float location_point{0};	//小数位*10
	for(auto e : str){
		if(e == '-') IsNegative = true;
		else if(e == '.'){IsPoint = true; location_point = 10;}
		else if(isdigit(e)){
			if(IsNegative){
				if(IsPoint){
					if(e != '0') v = v - CharToInt(e) / location_point;
					location_point *= 10;
				}
				else{
					v = v * 10 - CharToInt(e);
				}
			}
			else{
				if(IsPoint){
					if(e != '0') v = v + CharToInt(e) / location_point;
					location_point *= 10;
				}
				else{
					v = v * 10 + CharToInt(e);
				}
			}
		}
	}
	return v;
}

string operation_number_without(string str){
	//检测部分
	if((IsOperator(str[0])&&str[0]!='-'&&str[0]!='+')||
			(IsOperator(str[str.length()-1])))
		throw "错误（number）：运算符单双目性错误！";
	//----------
	str = "+" + str; str = str + "+";
	do{			//乘除法级运算
		auto length{str.length()};
		bool exit{true};
		for(decltype(str.length()) i{0};i < length;++i){
			if(str[i] == '*'){
				part 
				str = str.substr(0,s) + NumToStr(but1 * but2) + str.substr(e,length-e);
				if(str[0] != '+') str = "+" + str;
				i = s + NumToStr(but1 * but2).length();
				length = str.length();
			}
			else if(str[i] == '/'){
				part
				if(but2 == 0) throw "错误（number）：被除数为零！";
				str = str.substr(0,s) + NumToStr(but1 / but2) + str.substr(e,length-e);
				if(str[0] != '+') str = "+" + str;
				i = s + NumToStr(but1 / but2).length();
				length = str.length();
			}
		}
	}while(!exit);
	do{			//加减法级运算
		auto length{(int)str.length()};
		bool exit{true};
		for(decltype(str.length()) i{0};i < length;++i){
			if(str[i] == '+'){
				if(IsOperator(str[i-1])) continue;
				if(i == 0 || i ==length - 1) continue;
				part
				str = str.substr(0,s) + NumToStr(but1 + but2) + str.substr(e,length-e);
				if(str[0] != '+'){str = "+" + str; ++i;}
				if(str[str.length()-1] != '+') str = str + "+";
				i = s + NumToStr(but1 + but2).length()-1;
				length = str.length();
			}
			else if(str[i] == '-'){
				if(IsOperator(str[i-1])) continue;
				part
				str = str.substr(0,s) + NumToStr(but1 - but2) + str.substr(e,length-e);
				if(str[0] != '+') str = "+" + str;
				i = s + NumToStr(but1 - but2).length();
				length = str.length();
			}
		}
	}while(!exit);
	for(auto itr{str.begin()};itr != str.end();++itr){
		if(*itr == '+') *itr = ' ';
	}
	str = DeleteBlank(str);
	return str;
}

string operation_number(string str){
	//检测部分
	for(auto itr{str.begin()};itr != str.end();++itr){
		if(IsOperator(*itr) && (IsOperator(*(itr-1)) || IsOperator(*(itr+1))))
			throw "错误（number）：运算符重复出现！";
	}
	//--------
	while(1){
		if(str.find_first_of('(') == string::npos) break;
		auto location_L{str.find_first_of('(')};		//左括号的位置
		decltype(location_L) location_R{ location_L + 1 };					//右括号的位置
		unsigned int Num_L{0},Num_R{0};		//括号中表达式拥有的左括号数与右括号数
		for(;location_R < str.length();++location_R){
			if(str[location_R] == '(') Num_L++;
			else if(str[location_R] == ')') Num_R++;
			if(Num_L < Num_R) break;
		}
	    //运用递归计算括号中表达式的值
		string but{ operation_number(str.substr(location_L+1,location_R-location_L-1)) };
		str = str.substr(0,location_L) + but + str.substr(location_R+1,str.length()-location_R-1);
	}
	return operation_number_without(str);
}
