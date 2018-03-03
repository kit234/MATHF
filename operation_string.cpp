//operation_string.cpp�����ַ������������йصĺ���
#include "operation.h"
#include "common.h"

using std::string;

typedef string String_Type; //����������ַ�������

static bool IsOperator(char); //�ж������ַ��Ƿ��������
static void check(string) throw(string,const char*);	//����ַ����Ƿ�Ϸ�

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
					throw "����string����δ֪�������ͣ�";
				but += str.substr(i+2,e-i-3);
				i = e-1;
			}
		}
	}while(!exit);
	return but;
}

void check(string str) throw(string,const char*){
	if(IsOperator(str[0]) || IsOperator(str[str.length()-1]))
		throw "����string�����������˫Ŀ�Դ���";
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
			throw "����string����������ظ����֣�";
	}
}
