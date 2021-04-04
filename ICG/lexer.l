%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #define YYSTYPE char *
  #include "y.tab.h"
  extern YYSTYPE yylval;

typedef struct node{
    int scope;
    int value;
    char name[100];
    char dtype[50];
    int line_num;
    int valid;
}node;

typedef struct table{
    node* head;
}table;
int count = 0;
node symTable[1000];
char tdType[50];
int insert(int* idx, int scope, char* dtype, char* val, int line_num);
void displaySymTable();
int find(int  scope, char *name);
void update(char* name, int value, int scope);
void incrScope();
void decrScope();

int scope = 0;
char tdType[50];

%}

%option yylineno
digit [0-9]
letter [a-zA-Z]

%%

[ \n\t\s]+ ;		// whitespaces
\/\/.*	;		//remove comments
\/\*(.*\n)*.*\*\/ ;		//remove comments


"int main()" {  return T_MAIN; }
"void main()" {  return T_VMAIN; }

"int" { strcpy(tdType, yytext); yylval = strdup(yytext); return T_INT; }
"float" { strcpy(tdType, yytext);  yylval = strdup(yytext); return T_FLOAT; }
"double" { strcpy(tdType, yytext); yylval = strdup(yytext); return T_DOUBLE; }
"char" { strcpy(tdType, yytext); yylval = strdup(yytext); return T_CHAR;}
"string" { strcpy(tdType, yytext); yylval = strdup(yytext); return T_STR; }
"void" { strcpy(tdType, yytext); yylval = strdup(yytext); return T_VOID; }
"public:" { yylval = strdup(yytext); return T_PUBLIC; }
"private:" {yylval = strdup(yytext); return T_PRIVATE; }
"protected:" {  yylval = strdup(yytext); return T_PROTECTED; }
"class" { yylval = strdup(yytext); return T_CLASS; }

"," { return T_COMMA; }
";" {return T_Terminator; }

"break" { return T_BREAK; }
"continue" { return T_CONTINUE; }

"if"	{ return T_IF; }
"else" {  return T_ELSE; }
"for" {scope++;  return T_FOR; }
"return" { return T_RETURN; }
"endl" {  return T_ENDL; }
"cin" {  return T_IN; }
"cout" { return T_OUT; }

"#include"" "?("<"|\"){letter}({letter}|{digit})*"\.h"?(\"|">")  {return T_INCLUDE;}
{letter}({letter}|{digit})*"["{digit}"]" { yylval = strdup(yytext); return T_ARRAY; } 

{letter}({letter}|{digit})* { yylval = strdup(yytext); return T_ID; }
[+-]?{digit}+(\.{digit}+)?(E[+-]?{digit}+)? { yylval = strdup(yytext); return T_NUM; }
\".*\" {strcpy(tdType,yytext); return T_STRING;}

"+" {  return T_ADD; }
"-" {  return T_SUB; }
"*" {  return T_MUL; }
"/" {  return T_DIV; }

"++" { return T_INC; }
"--" { return T_DEC; }

"==" { return T_DEQ; }
"!=" { return T_NE; }
">" {  return T_GT; }
"<" {  return T_LT; }
">=" { return T_GTE; }
"<=" { return T_LTE; }

"&&" {  return T_AND; }
"||" {  return T_OR; }
"!" {   return T_NOT; }

"&" { return T_BAND; }
"|" { return T_BOR; }
"^" { return T_BXOR; }

"=" { return T_EQ; }
"+=" { return T_ADDEQ; }
"-=" { return T_SUBEQ; }
"*=" { return T_MULEQ; }
"/=" { return T_DIVEQ; }
"%=" { return T_MODEQ; }
"<<=" { return T_LSEQ; }
">>=" { return T_RSEQ; }

">>" { return T_STRIN; }
"<<" { return T_STROUT; }

"{}" { return T_CB; }
"{"  { scope++; return T_OFB; }
"}"  { scope--; return T_CFB; }

"[" { return T_OSB; }
"]" { return T_CSB; }
"[]" {  return T_SB; }

"(" { return T_OB; }
")" { return T_CB; }
"()" { return T_B; }

. ;

%%

int insert(int* idx, int scope, char* dtype, char* name, int line_num){
    int present = 0;
  
    for(int i = 0; i < *idx; i++){
            if(!strcmp(symTable[i].name, name) && symTable[i].scope == scope && !symTable[0].valid){
                present = 1;
                break;
            }
    }

    if(!present){
        symTable[*idx].scope = scope;
        symTable[*idx].line_num = line_num;
        symTable[*idx].value = 0;
        strcpy(symTable[*idx].name, name);
        strcpy(symTable[*idx].dtype, dtype);
        symTable[*idx].valid = scope;
        *idx = *idx + 1;

        return 1;
    }
    return 0;
}

void displaySymTable()
{
        printf("\nSYMBOL TABLE: \n");
        printf("Token\t\tData type\tScope\t\tValue\t\tLine number\n");
        for(int i = 0; i < count; i++)
        {
                printf("%s\t\t%s\t\t%d\t\t%d\t\t%d\n", symTable[i].name, symTable[i].dtype, symTable[i].scope, symTable[i].value, symTable[i].line_num);
        }
        printf("\n");
}

void update(char* name, int value, int scope){
  for(int i = 0; i < count; i++)
  {
    if(!strcmp(symTable[i].name, name) && symTable[i].scope == scope && symTable[i].valid){
        symTable[i].value = value;
    }
  }
}

int find(int  scope, char *name){
  int present = 0;
  for(int i = 0; i < count; i++)
  {
    if(!strcmp(symTable[i].name, name) && symTable[i].scope <= scope && symTable[i].valid){
        return i;
    }
  }
    return -1;
  }

void incrScope(){
    for(int i = 0; i < count; i++)
    {
      if(symTable[i].valid) symTable[i].valid += 1;
    }
}

void decrScope(){
  for(int i = 0; i < count; i++)
  {
    if(symTable[i].valid != 0)
    {
      symTable[i].valid -= 1;
      if(symTable[i].valid < symTable[i].scope){
          symTable[i].valid = 0;
        }
    }
  }
}