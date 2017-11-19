#include<iostream>
#include<stdio.h>
#include<string>
#include<stack>

using namespace std;

bool IsValid(string s)
{
    stack<char> st;
    size_t i = 0;
    while(s[i]){
        switch(s[i]){
        case '(':
        case '[':
        case '{':st.push(s[i]); break;
        case ')':if(st.empty() || st.top() != '(') return false;
                    else st.pop();break;
        case ']':if(st.empty() || st.top() != '[') return false;
                    else st.pop();break;
        case '}':if(st.empty() || st.top() != '{') return false;
                    else st.pop(); break;
        default:  ;
        }
        ++i;
    }
    return st.empty();
}

int Myatoi(string str)
{
    int num = 0;
    int indictaor = 1;
    for(size_t i =0 ; i < str.size();){
        i = str.find_first_not_of(' ');//
        if(str[i] == '-' || str[i] == '+')
            (str[i++] == '-') ? indictaor = -1 : indictaor = 1;
        while(str[i] <= '9' && str[i] >= '0'){
            num = num*10 + (str[i++] - '0' );
            if(num*indictaor > 0x7fffffff) return  -1;
            if(num*indictaor < (signed int)0x80000000) return  -1;
        }
    }
        
    return num*indictaor;
}

enum Status {KValid = 0, KInValid};
int g_nValid = KValid;

int my_atoi(const char* str)
{
    int num = 0;
    if(str == NULL || *str == '\0'){
        g_nValid = KInValid;
        return 0;    
    }
    int symbol = 1;
    if(*str == '+' || *str == '-')
        (*str++ == '+') ? symbol = 1 : symbol = -1;
    if(*str == '\0'){
        g_nValid = KInValid;
        return 0;
    }
    while(*str != '\0'){
        if(*str >= '0' && *str <= '9'){
            num = num*10 + (*str - '0');
            if(num*symbol > 0x7fffffff || num*symbol < (signed int)0x80000000){
                g_nValid = KInValid;
                return 0;
            }
        }
        ++str;
    }
    
    return num * symbol;
}



int main()
{
    printf("g--");
    cout<<"yimign"<<endl;
    cout<<IsValid("{[()]}")<<endl;
    cout<<Myatoi("2234")<<endl;
    cout<<g_nValid<<" "<<my_atoi("+99812")<<endl;
    return 0;
}
