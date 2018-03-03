//main.cpp
#include "common.h"
#include "operation.h"
#include <string>
#include <iostream>

using std::string;

void check(string) throw(string,const char*);	//检查函数
void Run(string);		//运行函数

int main(){
	using std::cout;
	using std::endl;
	using std::cin;
	using std::cerr;
	cout<<"输入“exit”来退出MATHF"<<endl;
	do{
		string command;
		cout<<"$$$ "; getline(cin,command);
		command = DeleteBlank(command);
		try{
			if(command == "exit") break;
			check(command);
			Run(command);
		}
		catch(string error){
			cerr<<error<<endl;
		}
		catch(const char* error){
			cerr<<error<<endl;
		}
	}while(1);
	return 0;
}

void Run(string str){
	if(str.empty()) return;
	using std::cout;
	using std::endl;
	string Statement_Type;	//语句类型
	for(decltype(str.length()) i{0};i < str.length();++i){
		unsigned int s{0};
		if(str[i] == '\''){
			for(auto j{i+1};j < str.length();++j)
				if(str[j] == '\''){i = j; break;}
			if(i == str.length()-1) Statement_Type = GetTypeOf(str);
			continue;
		}
		if(str[i] == '"'){
			for(auto j{i+1};j < str.length();++j)
				if(str[j] == '"'){i = j; break;}
			if(i == str.length()-1) Statement_Type = GetTypeOf(str);
			continue;
		}
		if(str[i] == '('){s = i; continue;}
		if(str[i] == ')'){Statement_Type = GetTypeOf(str.substr(s+1,i-s-1)); break;}
		if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'){
			if(s == 0 && str[s] != '(' && str[s] != '-' && str[s] != '+')
				Statement_Type = GetTypeOf(str.substr(0,i));
			else
				Statement_Type = GetTypeOf(str.substr(s+1,i-s-1));
			break;
		}
		if(i == str.length()-1) Statement_Type = GetTypeOf(str);
	}
	if(Statement_Type == "number"){
		string result = operation_number(str);
		cout<<">>> "<<result<<endl;
	}
	else if(Statement_Type == "string"){
		string result = operation_string(str);
		cout<<">>> "<<result<<endl;
	}
	else if(Statement_Type == "unknow")
		throw "错误（total）：语句类型未知！";	
}

void check(string str) throw(string,const char*){
	for(auto itr = str.begin();itr != str.end();++itr){
		if(*itr == '\''){
			for(auto p{itr+1};p != str.end();++p){
				if(*p != '\'' && p == str.end()-1) throw "错误（total）：单引号不匹配！";
				if(*p == '\''){itr = p; break;}
			}
			continue;
		}
		if(*itr == '"'){
			for(auto p{itr+1};p != str.end();++p){
				if(*p != '"' && p == str.end()-1) throw "错误（total）：双引号不匹配！";
				if(*p == '"'){itr = p; break;}
			}
			continue;
		}
	}
	unsigned int Num_L{0} , Num_R{0};
	for(auto e : str){
		if(e == '(') Num_L++;
		else if(e == ')') Num_R++;
	}
	if(Num_L != Num_R) throw "错误（total）：括号不匹配！";
}
