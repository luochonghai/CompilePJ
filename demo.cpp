#include <iostream>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<string>
#include "yacc.h"
#include <regex>
using namespace std;

//int yyparse();
int yylex();
extern "C" FILE* yyin;
extern "C" char* yytext;
int main(int argc, char* args[]) 
{
    if (argc > 1) 
    {
        FILE *file = fopen(args[1], "r");
        if (!file)
        {
            cerr << "Can not open file." << endl;
            return 1;
        } 
        else 
        {
            yyin = file;
        }
    }

    int row_index = 1,col_index = 1,
        pc_token = 0,pc_err = 0;
    
    cout<<setw(9)<<left<<"(行号"<<setw(8)<<right<<"列号)"<<setw(20)<<"种类"<<"    "<<"详情"<<endl;
    while(1)
    {
        //int token_input = yyparse();
        int token_input = yylex();
        string temp_type = "",temp_token = "";
	if(token_input == EOF)
	    break;        
        switch(token_input)
        {
            case COMMENT:
            {
                temp_type = "注释";
                break;
            }
	    case NCOMMENT:
	    {
		temp_type = "异常";
		temp_token = "A comment should be terminated with *) !";
		break;
	    }
            case REAL:
            {   
                temp_type = "实数";
                temp_token = string(yytext);
                break;
            }
	    case INTEGER:
	    {
		int len_int = strlen(yytext);
		if(len_int > 10)
		{
		    temp_type = "异常";
		    temp_token = "An integer should belong to [0,2147483647]!";
		    break;
		}
		else if(len_int < 10) 
		{
		    temp_type = "整数";
		    temp_token = yytext;
		    break;
		}
		string max_num = "2147483647";
		int signs = 1;
		for(int ni = 0;ni < 10;++ni)
		{
		    if(yytext[ni] > max_num[ni])
		    {
			signs = 0;
			break;
		    }
		}
		if(signs)
		{
		    temp_type = "整数";
		    temp_token = yytext;
		    break;
		}
		else
		{
		    temp_type = "异常";
		    temp_token = "An integer should belong to [0,2147483647]!";
		    break;
		}
	    }
	    case MINTEGER:
	    {
		temp_type = "异常";
		temp_token = "An integer should be non-negative!";
		break;
	    }
	    case MREAL:
	    {
		temp_type = "异常";
		temp_token = "A real should be non-negative!";
		break;
	    }
	    case RESERVE_W:
	    {
		temp_type = "保留字";
		temp_token = string(yytext);
		break;
	    }
	    case IDENTIFIER:
	    {
		if(strlen(yytext) > 255)
		{
		    temp_type = "异常";
		    temp_token = "The name of identifier should contain no more than 255 characters!";
		    break;
		}
		temp_type = "助记符";
		temp_token = string(yytext);
		break;
	    }
	    case WS:
	    {
		temp_type = "注释";
		break;
	    }	
	    case OPERATOR:
	    {
		temp_type = "终止符";
		temp_token = string(yytext);
		break;
	    }
	    case STRINGS:
	    {
		if(strlen(yytext) > 257)
		{
		    temp_type = "异常";
		    temp_token = "A string's length is no more than 255 characters!";
		    break;
		}
		temp_type = "字符串";
		temp_token = string(yytext);
		break;
	    }
	    case TL_STRINGS:
	    {
		temp_type = "异常";
		temp_token = "A string couldn't have any tabs or newlines!";
		break;
	    }
	    case NSTRINGS:
	    {
		temp_type = "异常";
		temp_token = "A string should both start and end with \"!";
		break;
	    }
	    case UNPRINTED:
	    {
		temp_type = "异常";
		temp_token = "Some Character(s) cannot be printed!";
		break;
	    }
	    case DELIMITER:
	    {
		temp_type = "终止符";
		temp_token = yytext;
		break;
	    }
            default:
                temp_type = "异常";
                temp_token = string(yytext);
        } 
        
        if(temp_type != "注释")
        {
    	    cout<<"("<<setw(5)<<right<<row_index<<","<<setw(5)<<col_index<<")"<<setw(20)<<temp_type<<"    "<<temp_token<<endl;
            if(temp_type != "异常")
		pc_token++;
	    else
	        pc_err++;	
        }

	for(int i = 0;i < strlen(yytext);++i)
	{
	    if(yytext[i] == '\n')
	    {
	        row_index++;
		col_index = 1;
	    }
	    else
		col_index++;
	}
    }
  
    cout<<endl<<"符号数: "<<pc_token<<endl<<"异常数: "<<pc_err<<endl;
    return 0;
}
