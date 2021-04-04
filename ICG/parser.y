%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYSTYPE char *
int yylex();
void if1();
void if2();
void if3();
void for1();
void for2();
void for3();
void for4();
void codegen();
void codegen_assign();
void codegen_syns();
void codgen_un();
void showSt();
void yyerror(const char *s);

typedef struct quadruples{
    char* operand1;
    char* operand2;
    char* operator;
    char* result;
} quad;
int len_quad = 0;
quad q[100];


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
// int count = 0;
extern node symTable[1000];

void push();
int sym[26];
extern int yylineno;
int valid=1;
extern int SymTable[100];


extern int scope;
extern int count;
extern void displaySymTable();
extern int find(int  scope, char *yytext);
extern void update(char* name, int value, int scope);
extern int insert(int* idx, int scope, char* dtype, char* val, int line_num);
extern void decrScope();
extern void incrScope();
extern char tdType[50];


%}
%token T_MAIN T_INT T_FLOAT T_DOUBLE T_CHAR T_VOID T_Terminator T_INC T_DEC T_EQ T_NE T_GT T_LT T_GTE T_LTE T_AND T_OR T_NOT T_BAND T_BOR T_BXOR T_ADDEQ T_MULEQ T_DIVEQ T_MODEQ T_LSEQ T_RSEQ T_ANDEQ T_XOREQ T_OREQ T_H
%token T_B T_OB T_SB T_CSB T_OSB T_CB T_OCB T_ID T_ENDL T_CIN T_COUT T_RETURN T_FOR T_IF T_ELSE T_OUT T_IN T_NUM T_SUBEQ T_COMMA T_BREAK T_CONTINUE T_OFB T_CFB T_VMAIN T_STRING T_STRIN T_STROUT T_DEQ T_STR T_INCLUDE T_TRUE T_FALSE
%token T_CLASS T_PUBLIC T_PRIVATE T_PROTECTED T_ARRAY
%left T_ADD T_SUB
%left T_MUL T_DIV


%%
S: START {printf("\n\nPROGRAM IS VALID\n\n"); exit(0);}


START: T_INCLUDE Prog
| Prog
;

Prog: DECL BODY 
| BODY
;

BODY: T_MAIN T_OFB STMT T_CFB 
| T_VMAIN T_OFB STMT T_CFB
| T_CLASS T_ID T_OFB CLASS_STMT T_CFB BODY
| FUNC BODY
|
;

CLASS_STMT: T_PUBLIC STMT CLASS_STMT
|T_PRIVATE STMT CLASS_STMT
|T_PROTECTED STMT CLASS_STMT
|
;

STMT: DECL STMT
|ASSIGN_EXPR STMT
|T_IN INOUT T_Terminator STMT
|T_OUT INOUT T_Terminator STMT
|FORSTMT STMT
|SELECTSTMT STMT
|JUMPSTMT STMT
|T_OFB STMT T_CFB STMT
|UNARYEXP T_Terminator STMT
| FUNC STMT
|
;

FUNC: TYPE T_ID T_OB PARAMLIST T_CB T_OFB STMT T_CFB { scope++;}
;

PARAMLIST: TYPE T_ID PARAMLIST{ 
    
    if(!insert(&count, scope + 1, $1, $2, yylineno)){
        yyerror("Variable redeclared");
    }
}
| TYPE T_ID T_EQ E PARAMLIST{
     
    if(!insert(&count, scope + 1, $1, $2, yylineno)){
        yyerror("Variable redeclared");
    }
    update($2, atoi($4), scope + 1);
}
| T_COMMA T_ID T_EQ E PARAMLIST
{
    
    if(!insert(&count, scope + 1, tdType, $2, yylineno)){
        yyerror("Variable redeclared");
    }
    update($2, atoi($4), scope);
}
| T_COMMA TYPE T_ID PARAMLIST{
    
    if(!insert(&count, scope+1, $2, $3, yylineno)){
        yyerror("Variable redeclared");
    }
}
|
;

INOUT: T_STRIN T_ID 
|T_STROUT T_ID INOUT
|T_STROUT T_ENDL INOUT
|T_STROUT T_STRING INOUT
|
;


TYPE: T_INT {strcpy(tdType,$1);} 
|T_FLOAT {strcpy(tdType,$1);}
|T_CHAR {strcpy(tdType,$1);}
|T_DOUBLE {strcpy(tdType,$1);}
|T_VOID {strcpy(tdType,$1);}
;

DECL: TYPE T_ID {push($2);} T_EQ E VARLIST T_Terminator {
    codegen_assign();
    if(!insert(&count, scope, $1, $2, yylineno)){
        yyerror("Variable redeclared");
    }
    update($2, atoi($4), scope);
}
| TYPE T_ID VARLIST T_Terminator {
    if(!insert(&count, scope, $1, $2, yylineno)){
        yyerror("Variable redeclared");
    }
}
| TYPE T_ARRAY T_Terminator
| TYPE T_ARRAY T_EQ T_OFB ARRELE T_CFB T_Terminator
;

ARRELE: T_NUM T_COMMA ARRELE
| T_STRING T_COMMA ARRELE
| T_NUM
| T_STRING
|
;

VARLIST: T_COMMA T_ID VARLIST {
    if(!insert(&count, scope, tdType, $2, yylineno)){
        yyerror("Variable redeclared");
    }
}
|T_ID {
    if(!insert(&count, scope, tdType, $1, yylineno)){
        yyerror("Variable redeclared");
    }
}
|T_COMMA T_ID T_EQ E VARLIST {
    if(!insert(&count, scope, tdType, $2, yylineno)){
        yyerror("Variable redeclared");
    }
    update($2, atoi($4), scope);
}
|
;

ASSIGN_EXPR: T_ID ASSIGNOP E T_Terminator {
        codegen();
        if(find(scope, $1) == -1){
            yyerror("Variable not declared");
        }
        int idx1 = find(scope, $1);
        int val1 = symTable[idx1].value;

        if(strcmp($2, "=")){
            update($1, atoi($4), scope);
        }
        else if(strcmp($2, "+=")){
            val1 += atoi($4);
            update($1, val1, scope);
        }
        else if(strcmp($2, "-=")){
            val1 -= atoi($4);
            update($1, val1, scope);
        }
        else if(strcmp($2, "*=")){
            val1 *= atoi($4);
            update($1, val1, scope);
        }
        else if(strcmp($2, "/=")){
            val1 /= atoi($4);
            update($1, val1, scope);
        }
        else if(strcmp($2, "%=")){
            val1 %= atoi($4);
            update($1, val1, scope);
        }
        else if(strcmp($2, ">>=")){
            val1 >>= atoi($4);
            update($1, val1, scope);
        }
        else if(strcmp($2, "<<=")){
            val1 <<= atoi($4);
            update($1, val1, scope);
        }
        else{
            yyerror("Invalid operation");
        }
      }
;

E: E T_ADD T {
    push($2);
    int val = atoi($1) + atoi($3);
    sprintf($$, "%d", val);
}
|E T_SUB T {
    push($2);
    int val = atoi($1) - atoi($3);
    sprintf($$, "%d", val);
}
|T {$$ = $1;}
;

T: T T_MUL F {
    push($2);
    int val = atoi($1) * atoi($3);
    sprintf($$, "%d", val);
}
|T T_DIV F {
    push($2);
    int val = atoi($1) / atoi($3);
    sprintf($$, "%d", val);
}
|F {$$ = $1;}

F: T_ID {
        if(find(scope, $1) == -1){
            yyerror("Variable not declared");
        }
        int idx = find(scope, $1);
        sprintf($$, "%d", symTable[idx].value);
        push($1);
        showSt();
      }
|T_NUM {$$ = $1;push($1);showSt();}
| T_OB E T_CB {$$ = $2;}
| BOOL {
        $$ = $1; push($1);
      }
| UNARYEXP
;

FORSTMT: T_FOR T_OB INITFOR {for1();} COND T_Terminator {for2();} ITRCHANGE {for3();} T_CB T_OFB STMT T_CFB {for4(); scope--;} 
;

INITFOR: T_ID T_Terminator
|ASSIGN_EXPR
|DECL
|T_Terminator
;

COND: OPERATION
;

OPERATION: E LOGICOP E
|E RELOP E 
|E BITOP E
|E RELOP E LOGICOP E RELOP E
|T_NOT T_OB E RELOP E T_CB
|T_NOT E RELOP E
|T_NOT E
|E
|
;

ITRCHANGE: UNARYEXP
| ASSIGN_EXPR
|
;

SELECTSTMT: T_IF T_OB COND T_CB {if1();} T_OFB STMT T_CFB {if2();} ELSEBODY {if3();}
;

ELSEBODY: T_ELSE T_OFB STMT T_CFB
|
;

JUMPSTMT: T_RETURN T_ID T_Terminator
| T_RETURN T_NUM T_Terminator
| T_RETURN T_STRING T_Terminator
| T_RETURN T_Terminator
| T_CONTINUE T_Terminator
| T_BREAK T_Terminator
;




UNARYEXP: T_INC T_ID {
        if(find(scope, $2) == -1){
            yyerror("Variable not declared");
        }
        int idx = find(scope, $2);
        sprintf($$, "%d", ++symTable[idx].value);
        update($2, atoi($$), scope);
        push($1);
        push($2);
      }
| T_ID T_INC {
        if(find(scope, $1) == -1){
            yyerror("variable not declared");
        }
        int idx = find(scope, $1);
        sprintf($$, "%d", symTable[idx].value++);
        update($1, atoi($$), scope);
        push($1);
        push($2);
      } 
| T_DEC T_ID {
        if(find(scope, $2) == -1){
            yyerror("variable not declared");
        }
        int idx = find(scope, $2);
        sprintf($$, "%d", --symTable[idx].value);
        update($2, atoi($$), scope);
        push($1);
        push($2);
      }
| T_ID T_DEC {
        if(find(scope, $1) == -1){
            yyerror("variable not declared");
        }
        int idx = find(scope, $1);
        sprintf($$, "%d", symTable[idx].value--);
        update($1, atoi($$), scope);
        push($1);
        push($2);
      }
;

LOGICOP: T_OR {$$ = $1; push($1);}
| T_AND {$$ = $1; push($1);}
;

BITOP: T_BAND {$$ = $1; push($1);}
| T_BOR {$$ = $1; push($1);}
| T_BXOR {$$ = $1; push($1);}
;

RELOP: T_DEQ {$$ = $1; push($1);}
| T_LT {$$ = $1; push($1);}
| T_GT {$$ = $1; push($1);}
| T_GTE {$$ = $1; push($1);}
| T_LTE {$$ = $1; push($1);}
| T_NE {$$ = $1; push($1);}
;

ASSIGNOP: T_EQ {$$ = $1; push($1);}
| T_ADDEQ {$$ = $1; push($1);}
| T_MULEQ {$$ = $1; push($1);}
| T_DIVEQ {$$ = $1; push($1);}
| T_MODEQ {$$ = $1; push($1);}
| T_LSEQ {$$ = $1; push($1);}
| T_RSEQ {$$ = $1; push($1);}
| T_SUBEQ {$$ = $1; push($1);}
;

BOOL: T_TRUE {$$ = "1"; push($1);}
| T_FALSE {$$ = "0"; push($1);}
;

%%
#include <ctype.h>


void yyerror(const char *s) {
    printf("\nERROR: %s on line %d\n",s, yylineno);
}

char st[100][20];
int top = 0;
int lnum = 0;
int ltop = 0;
int label[25];
char i_[3]="00";
char temp[2]="t";

void push(char* val){
  strcpy(st[top++], val);
}

void codegen()
{
	strcpy(temp,"t");
	strcat(temp,i_);
	printf("%s = %s %s %s\n",temp,st[top-3],st[top-2],st[top-1]);
	top-=2;
	strcpy(st[top-1],temp);
	if(i_[1]!='9')
		i_[1]++;
	else
	{
		i_[1] = '0';
		i_[0]++;
	}
}

void codgen_un()
{
	strcpy(temp,"t");
	strcat(temp,i_);
      
    if((!strcmp(st[top - 2],"++")) || (!strcmp(st[top - 2],"--"))){
    printf(" %s = %s %c %d\n", temp, st[top-1], st[top-2][0], 1);

    printf("%s = %s\n", st[top - 1], temp);

    }
    else if((!strcmp(st[top - 1],"++")) || (!strcmp(st[top - 1],"--"))){
    printf(" %s = %s %c %d\n", temp, st[top-2], st[top-1][0], 1);

    printf("%s = %s\n", st[top - 2], temp);

    }
    else
        printf(" %s = %s%s\n", temp, st[top-2], st[top-1]);
    top = top - 1;
    strcpy(st[top - 1], temp);
    if(i_[1]!='9')
        i_[1]++;
    else
    {
        i_[1] = '0';
        i_[0]++;
    }
}

void codegen_syns(){
  printf("%s %c %s %c %s\n", st[top-3], st[top-2][1], st[top-3], st[top-2][0], st[top - 1]);
  top = top - 2;
}


void codegen_assign(){
  printf("%s = %s\n", st[top-2], st[top-1]);
  top = top - 2;
}

void showSt(){
  printf("\nprinting the stack contents\n");
  int temp = top;
  while(temp != -1){
    printf("%s ", st[temp--]);

  }
  printf("\nstack over \n---------------------------\n");
}

//for
void for1() //mainly for getting labels ready
{
      label[ltop++] = ++lnum; // label after (for(int i = 0;)) i.e. after declaring i = 0; => i = 0; label1: .... [Most important: label for checking condition]
      printf("L%d : \n",label[ltop - 1]);
      label[ltop++] = ++lnum; //label for incrementing
      label[ltop++] = ++lnum; //label for body of for loop
      label[ltop++] = ++lnum; //label for statements outside for loop
}

void for2() //ICG for condition check
{
	strcpy(temp,"t");
	strcat(temp,i_);	
    printf("%s = not %s\n",temp,st[top -1]);
	printf("if %s goto L%d\n",temp,label[ltop - 1]);
	if(i_[1]!='9')
		i_[1]++;
	else
	{
		i_[1] = '0';
		i_[0]++;
	}
	printf("goto L%d\n", label[ltop - 3]);
  printf("L%d :\n", label[ltop - 2]);

}

void for3() //incrementing and executing loop again
{
  printf("goto L%d\n", label[ltop - 4]);
  printf("L%d :\n", label[ltop - 3]);
}

void for4() //go to autoincrement and print label after loop
{
	printf("goto L%d \n",label[ltop - 2]);
	printf("L%d : \n",label[ltop - 1]);
      ltop = ltop - 4;
}

//if
void if1()
{
 lnum++;
 strcpy(temp,"t");
 strcat(temp,i_);
 printf("%s = not %s\n",temp,st[top - 1]);
 printf("if %s goto L%d\n",temp,lnum);
 i_[0]++;
 label[++ltop]=lnum;
}

void if2()
{
int x;
lnum++;
x=label[ltop--];
printf("goto L%d\n",lnum);
printf("L%d: \n",x);
label[++ltop]=lnum;
}

//if-else
void if3()
{
int y;
y=label[ltop--];
printf("L%d: \n",y);
}


int main()
{
    //printf("LINE\tTOKENS\n");
    yyparse();
    return 0;

}