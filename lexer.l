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
int flag = 0;
int dflag = 0;
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


"int main()" { printf("%d|\tMAIN FUNCTION - int main() \n",yylineno); return T_MAIN; }
"void main()" { printf("%d|\tMAIN FUNCTION - void main() \n", yylineno); return T_VMAIN; }

"int" { strcpy(tdType, yytext); printf("%d|\tKEYWORD - INT\n", yylineno); dflag = 1; yylval = strdup(yytext); return T_INT; }
"float" { strcpy(tdType, yytext); printf("%d|\tKEYWORD - FLOAT\n", yylineno); dflag = 1; yylval = strdup(yytext); return T_FLOAT; }
"double" { strcpy(tdType, yytext); printf("%d|\tKEYWORD - DOUBLE\n", yylineno); dflag = 1; yylval = strdup(yytext); return T_DOUBLE; }
"char" { strcpy(tdType, yytext); printf("%d|\tKEYWORD - CHAR\n", yylineno); dflag = 1; yylval = strdup(yytext); return T_CHAR;}
"string" { strcpy(tdType, yytext); printf("%d|\tKEYWORD - STRING\n", yylineno); dflag = 1; yylval = strdup(yytext); return T_STR; }
"void" { strcpy(tdType, yytext); printf("%d|\tKEYWORD - VOID\n", yylineno);  dflag = 1; yylval = strdup(yytext); return T_VOID; }
"public:" { printf("%d|\tKEYWORD - PUBLIC\n", yylineno); yylval = strdup(yytext); return T_PUBLIC; }
"private:" {printf("%d|\tKEYWORD - PRIVATE\n", yylineno); yylval = strdup(yytext); return T_PRIVATE; }
"protected:" { printf("%d|\tKEYWORD - PROTECTED\n", yylineno); yylval = strdup(yytext); return T_PROTECTED; }
"class" { printf("%d|\tKEYWORD - CLASS\n", yylineno);  yylval = strdup(yytext); return T_CLASS; }

"," { printf("%d|\tCOMMA - ,\n", yylineno); return T_COMMA; }
";" { printf("%d|\tTerminator - ;\n", yylineno); return T_Terminator; }

"break" { printf("%d|\tKEYWORD - BREAK\n", yylineno); return T_BREAK; }
"continue" { printf("%d|\tKEYWORD - CONTINUE\n", yylineno); return T_CONTINUE; }

"if"	{ printf("%d|\tKEYWORD - IF \n",yylineno); return T_IF; }
"else" { printf("%d|\tKEYWORD - ELSE \n",yylineno); return T_ELSE; }
"for" {scope++; printf("%d|\tKEYWORD - FOR \n",yylineno); return T_FOR; }
"return" { printf("%d|\tKEYWORD - RETURN \n",yylineno); return T_RETURN; }
"endl" { printf("%d|\tKEYWORD - ENDL \n",yylineno); return T_ENDL; }
"cin" { printf("%d|\tKEYWORD - CIN \n",yylineno); return T_IN; }
"cout" { printf("%d|\tKEYWORD - COUT \n",yylineno); return T_OUT; }

"#include"" "?("<"|\"){letter}({letter}|{digit})*"\.h"?(\"|">")  {printf("%d|\tPREPROCESSOR - %s\n", yylineno, yytext); return T_INCLUDE;}
{letter}({letter}|{digit})*"["{digit}"]" { printf("%d|\tID - %s\n",yylineno, yytext); yylval = strdup(yytext); return T_ARRAY; } 

{letter}({letter}|{digit})* { printf("%d|\tID - %s\n",yylineno, yytext); yylval = strdup(yytext); return T_ID; }
[+-]?{digit}+(\.{digit}+)?(E[+-]?{digit}+)? { printf("%d|\tDIGIT - %s\n",yylineno, yytext); yylval = strdup(yytext); return T_NUM; }
\".*\" {strcpy(tdType,yytext);printf("%d|\tSTRING - %s\n",yylineno,yytext);return T_STRING;}

"+" { printf("%d|\tARITHMETIC OPERATOR - %s\n",yylineno, yytext); return T_ADD; }
"-" { printf("%d|\tARITHMETIC OPERATOR - %s\n",yylineno, yytext); return T_SUB; }
"*" { printf("%d|\tARITHMETIC OPERATOR - %s\n",yylineno, yytext); return T_MUL; }
"/" { printf("%d|\tARITHMETIC OPERATOR - %s\n",yylineno, yytext); return T_DIV; }

"++" { printf("%d|\tARITHMETIC OPERATOR - %s\n",yylineno, yytext); return T_INC; }
"--" { printf("%d|\tARITHMETIC OPERATOR - %s\n",yylineno, yytext); return T_DEC; }

"==" { printf("%d|\tRELATIONAL OPERATOR - %s\n",yylineno, yytext); return T_DEQ; }
"!=" { printf("%d|\tRELATIONAL OPERATOR - %s\n",yylineno, yytext); return T_NE; }
">" { printf("%d|\tRELATIONAL OPERATOR - %s\n",yylineno, yytext); return T_GT; }
"<" { printf("%d|\tRELATIONAL OPERATOR - %s\n",yylineno, yytext); return T_LT; }
">=" { printf("%d|\tRELATIONAL OPERATOR - %s\n",yylineno, yytext); return T_GTE; }
"<=" { printf("%d|\tRELATIONAL OPERATOR - %s\n",yylineno, yytext); return T_LTE; }

"&&" { printf("%d|\tLOGICAL OPERATOR - %s\n",yylineno, yytext); return T_AND; }
"||" { printf("%d|\tLOGICAL OPERATOR - %s\n",yylineno, yytext); return T_OR; }
"!" { printf("%d|\tLOGICAL OPERATOR - %s\n",yylineno, yytext); return T_NOT; }

"&" { printf("%d|\tBITWISE OPERATOR - %s\n",yylineno, yytext); return T_BAND; }
"|" { printf("%d|\tBITWISE OPERATOR - %s\n",yylineno, yytext); return T_BOR; }
"^" { printf("%d|\tBITWISE OPERATOR - %s\n",yylineno, yytext); return T_BXOR; }

"=" { printf("%d|\tASSIGNMENT OPERATOR - %s\n",yylineno, yytext); return T_EQ; }
"+=" { printf("%d|\tASSIGNMENT OPERATOR - %s\n",yylineno, yytext); return T_ADDEQ; }
"-=" { printf("%d|\tASSIGNMENT OPERATOR - %s\n",yylineno, yytext); return T_SUBEQ; }
"*=" { printf("%d|\tASSIGNMENT OPERATOR - %s\n",yylineno, yytext); return T_MULEQ; }
"/=" { printf("%d|\tASSIGNMENT OPERATOR - %s\n",yylineno, yytext); return T_DIVEQ; }
"%=" { printf("%d|\tASSIGNMENT OPERATOR - %s\n",yylineno, yytext); return T_MODEQ; }
"<<=" { printf("%d|\tASSIGNMENT OPERATOR - %s\n",yylineno, yytext); return T_LSEQ; }
">>=" { printf("%d|\tASSIGNMENT OPERATOR - %s\n",yylineno, yytext); return T_RSEQ; }

">>" { printf("%d|\tSTREAM OPERATOR - %s\n",yylineno, yytext); return T_STRIN; }
"<<" { printf("%d|\tSTREAM OPERATOR - %s\n",yylineno, yytext); return T_STROUT; }

"{}" { printf("%d|\tCURLY BRACES - %s\n", yylineno, yytext); return T_CB; }
"{"  { scope++; printf("%d|\tOPEN CURLY BRACES - %s\n", yylineno, yytext); return T_OFB; }
"}"  { scope--; printf("%d|\tCLOSE CURLY BRACES - %s\n", yylineno, yytext); return T_CFB; }

"[" { printf("%d|\tOPEN SQAURE BRACES - %s\n", yylineno, yytext); return T_OSB; }
"]" { printf("%d|\tCLOSE SQAURE BRACES - %s\n", yylineno, yytext); return T_CSB; }
"[]" { printf("%d|\tSQAURE BRACES - %s\n", yylineno, yytext); return T_SB; }

"(" { printf("%d|\tOPEN BRACES - %s\n", yylineno, yytext); return T_OB; }
")" { printf("%d|\tCLOSE BRACES - %s\n", yylineno, yytext);return T_CB; }
"()" { printf("%d|\tBRACES - %s\n", yylineno, yytext); return T_B; }

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