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
void codegen_call();
void codegen_param();
void yyerror(const char *s);


typedef struct quadruples{
    char op;
    char arg1[20];
    char arg2[20];
    char res[20];
    struct quadruples *next;
} quad;
quad *quad_head=NULL;
quad *quad_tail=NULL;

void insert_quad(char op,char *arg1,char *arg2,char *res)
{
    quad *new=(quad *)malloc(sizeof(quad));
    new->op=op;
    strcpy(new->arg1,arg1);
    //new->arg2=NULL;
    if(arg2!=NULL)
        strcpy(new->arg2,arg2);
    strcpy(new->res,res);
    new->next=NULL;
    if(quad_head==NULL)
    {
        quad_head=new;
        quad_tail=quad_head;
    }
    else
    {
        quad_tail->next=new;
        quad_tail=quad_tail->next;
    }
}

void display_quad()
{
    quad *temp1;
    temp1=quad_head;
    printf("quadruple table:\n");
    while(temp1!=NULL)
    {
        printf("%c\t%s\t%s\t%s\n ",temp1->op,temp1->arg1,temp1->arg2,temp1->res);
        temp1=temp1->next;
    }
}


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
extern char op[50];
char val[50];
int val1, val2;

%}
%token T_MAIN T_INT T_FLOAT T_DOUBLE T_CHAR T_VOID T_Terminator T_INC T_DEC T_EQ T_NE T_GT T_LT T_GTE T_LTE T_AND T_OR T_NOT T_BAND T_BOR T_BXOR T_ADDEQ T_MULEQ T_DIVEQ T_MODEQ T_LSEQ T_RSEQ T_ANDEQ T_XOREQ T_OREQ T_H
%token T_B T_OB T_SB T_CSB T_OSB T_CB T_OCB T_ID T_ENDL T_CIN T_COUT T_RETURN T_FOR T_IF T_ELSE T_OUT T_IN T_NUM T_SUBEQ T_COMMA T_BREAK T_CONTINUE T_OFB T_CFB T_VMAIN T_STRING T_STRIN T_STROUT T_DEQ T_STR T_INCLUDE T_TRUE T_FALSE
%token T_CLASS T_PUBLIC T_PRIVATE T_PROTECTED T_ARRAY
%left T_ADD T_SUB
%left T_MUL T_DIV


%%
S: START {printf("\n\nPROGRAM IS VALID\n\n"); display_quad(); exit(0);}


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
| FUNCALL STMT
|
;

FUNC: TYPE T_ID T_OB PARAMLIST T_CB T_OFB STMT T_CFB {}
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

FUNCALL: T_ID {push($1);} T_OB F_PARAMLIST T_CB  T_Terminator {codegen_call();}
;

F_PARAMLIST: T_COMMA T_ID { push($2); codegen_param(); } F_PARAMLIST 
|T_ID { push($1); codegen_param(); } F_PARAMLIST
|T_COMMA T_ID {push($2);} T_EQ E {codegen_assign(); codegen_param();} F_PARAMLIST
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

/*done except arrays(?)*/
DECL: TYPE T_ID {push($2);} T_EQ E {codegen_assign();} VARLIST  T_Terminator {
    if(!insert(&count, scope, $1, $2, yylineno)){
        yyerror("Variable redeclared");
    }
    update($2, atoi(val), scope);    
}
| TYPE T_ID {push($2); push("0"); codegen_assign();} VARLIST T_Terminator {
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

/*done*/
VARLIST: T_COMMA T_ID VARLIST {
    if(!insert(&count, scope, tdType, $2, yylineno)){
        yyerror("Variable redeclared");
    }
    push($2);
    push("0");
    codegen_assign();
}
|T_ID {
    if(!insert(&count, scope, tdType, $1, yylineno)){
        yyerror("Variable redeclared");
    }
    
}
|T_COMMA T_ID {push($2);} T_EQ E {codegen_assign();} VARLIST {
    if(!insert(&count, scope, tdType, $2, yylineno)){
        yyerror("Variable redeclared");
    }
    update($2, atoi(val), scope);
}
|
;

/*done*/
ASSIGN_EXPR: T_ID {push($1);} ASSIGNOP E T_Terminator {
        if(find(scope, $1) == -1){
            yyerror("Variable not declared");
        }
        int idx1 = find(scope, $1);
        int val1 = symTable[idx1].value;

        if(!strcmp(op, "=")){
            update($1, atoi($4), scope);
            codegen_assign();
        }
        else if(!strcmp(op, "+=")){
            val1 += atoi($4);
            update($1, val1, scope);
            codegen_syns();
        }
        else if(!strcmp(op, "-=")){
            val1 -= atoi($4);
            update($1, val1, scope);
            codegen_syns();
        }
        else if(!strcmp(op, "*=")){
            val1 *= atoi($4);
            update($1, val1, scope);
            codegen_syns();
        }
        else if(!strcmp(op, "/=")){
            val1 /= atoi($4);
            update($1, val1, scope);
            codegen_syns();
        }
        else if(!strcmp(op, "%=")){
            val1 %= atoi($4);
            update($1, val1, scope);
            codegen_syns();
        }
        else if(!strcmp(op, ">>=")){
            val1 >>= atoi($4);
            update($1, val1, scope);
            codegen_syns();
        }
        else if(!strcmp(op, "<<=")){
            val1 <<= atoi($4);
            update($1, val1, scope);
            codegen_syns();
        }
        else{
            yyerror("Invalid operation");
        }
      }
;

E: E {} T_ADD {push("+");} T {
    int val = atoi($1) + atoi($3);
    sprintf($$, "%d", val);
    
    codegen();
}
|E {} T_SUB {push("-");} T {
    int val = atoi($1) - atoi($3);
    sprintf($$, "%d", val);
    codegen();
}
|T {$$ = $1;}
;

T: T {} T_MUL {push("*");} F {
    int val = atoi($1) * atoi($3);
    sprintf($$, "%d", val);
    codegen();
}
|T {} T_DIV {push("/");} F {
    int val = atoi($1) / atoi($3);
    sprintf($$, "%d", val);
    codegen();
}
|F {$$ = $1;}

F: T_ID {
        if(find(scope, $1) == -1){
            yyerror("Variable not declared");
        }
        push($1);
        int idx = find(scope, $1);
        sprintf($$, "%d", symTable[idx].value);
      }
|T_NUM {strcpy(val, $1); $$ = $1;push($1);}
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

OPERATION: E LOGICOP E {
    if(!strcmp($2, "&&")){
        if($1 && $3)
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else if(!strcmp($2, "||")){
        if($1 || $3)
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else{
        yyerror("Invalid operation");
    }
}
|E RELOP E  {
    if(!strcmp($2, "==")){
        if($1 == $3)
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else if(!strcmp($2, ">=")){
        if($1 >= $3)
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else if(!strcmp($2, "<")){
        if($1 < $3)
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else if(!strcmp($2, ">")){
        if($1 > $3)
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else if(!strcmp($2, "<=")){
        if($1 <= $3)
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else if(!strcmp($2, "!=")){
        if($1 != $3)
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else{
        yyerror("Invalid operation");
    }
    
}
|E BITOP E
|E RELOP E {
    if(!strcmp($2, "==")){
        if($1 == $3)
            val1 = 1;
        else
            val1 = 0;
    }
    else if(!strcmp($2, ">=")){
        if($1 >= $3)
            val1 = 1;
        else
            val1 = 0;
    }
    else if(!strcmp($2, "<")){
        if($1 < $3)
            val1 = 1;
        else
            val1 = 0;
    }
    else if(!strcmp($2, ">")){
        if($1 > $3)
            val1 = 1;
        else
            val1 = 0;
    }
    else if(!strcmp($2, "<=")){
        if($1 <= $3)
            val1 = 1;
        else
            val1 = 0;
    }
    else if(!strcmp($2, "!=")){
        if($1 != $3)
            val1 = 1;
        else
            val1 = 0;
    }
    else{
        yyerror("Invalid operation");
    }
} LOGICOP E RELOP E {
    if(!strcmp($6, "==")){
        if($5 == $7)
            val2 = 1;
        else
            val2 = 0;
    }
    else if(!strcmp($6, ">=")){
        if($5 >= $7)
            val2 = 1;
        else
            val2 = 0;
    }
    else if(!strcmp($6, "<")){
        if($5 < $7)
            val2 = 1;
        else
            val2 = 0;
    }
    else if(!strcmp($6, ">")){
        if($5 > $7)
            val2 = 1;
        else
            val2 = 0;
    }
    else if(!strcmp($6, "<=")){
        if($5 <= $7)
            val2 = 1;
        else
            val2 = 0;
    }
    else if(!strcmp($6, "!=")){
        if($5 != $7)
            val2 = 1;
        else
            val2 = 0;
    }
    else{
        yyerror("Invalid operation");
    }

    if(!strcmp($4, "&&")){
        if(val1 && val2)
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else if(!strcmp($4, "||")){
        if(val1 || val2)
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
    }
    else{
        yyerror("Invalid operation");
    }

}
|T_NOT T_OB E RELOP E T_CB {
        if(!strcmp($4, "==")){
        if($3 == $5)
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp($4, ">=")){
        if($3 >= $5)
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp($4, "<")){
        if($3 < $5)
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp($4, ">")){
        if($3 > $5)
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp($4, "<=")){
        if($3 <= $5)
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp($4, "!=")){
        if($3 != $5)
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else{
        yyerror("Invalid operation");
    }
}
|T_NOT E RELOP E {
    if(!strcmp($3, "==")){
        if($2 == $4)
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp($3, ">=")){
        if($2 >= $4)
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp($3, "<")){
        if($2 < $4)
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp($3, ">")){
        if($2 > $4)
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp($3, "<=")){
        if($2 <= $4)
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else if(!strcmp($3, "!=")){
        if($2 != $4)
            printf("Expression evaluated to 0\n");
        else
            printf("Expression evaluated to 1\n");
    }
    else{
        yyerror("Invalid operation");
    }
}
|T_NOT E
    {
    if(!$2)
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
}
|E {
    if($1)
            printf("Expression evaluated to 1\n");
        else
            printf("Expression evaluated to 0\n");
}
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
        push($1);
        push($2);
        codgen_un();
        int idx = find(scope, $2);
        sprintf($$, "%d", ++symTable[idx].value);
        update($2, atoi($$), scope);
    }
| T_ID T_INC {
        if(find(scope, $1) == -1){
            yyerror("variable not declared");
        }
        push($1);
        push($2);
        codgen_un();
        int idx = find(scope, $1);
        sprintf($$, "%d", symTable[idx].value++);
        update($1, atoi($$), scope);
    } 
| T_DEC T_ID {
        if(find(scope, $2) == -1){
            yyerror("variable not declared");
        }
        push($1);
        push($2);
        codgen_un();
        int idx = find(scope, $2);
        sprintf($$, "%d", --symTable[idx].value);
        update($2, atoi($$), scope);
    }
| T_ID T_DEC {
        if(find(scope, $1) == -1){
            yyerror("variable not declared");
        }
        push($1);
        push($2);
        codgen_un();
        int idx = find(scope, $1);
        sprintf($$, "%d", symTable[idx].value--);
        update($1, atoi($$), scope);
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

ASSIGNOP: T_EQ {strcpy(op,$1); $$ = $1;}
| T_ADDEQ { strcpy(op,$1); push("+="); $$ = $1;}
| T_MULEQ {strcpy(op,$1); push("*="); $$ = $1;}
| T_DIVEQ {strcpy(op,$1); push("/="); $$ = $1;}
| T_MODEQ {strcpy(op,$1); push("%="); $$ = $1;}
| T_LSEQ {strcpy(op,$1); push("<<="); $$ = $1;}
| T_RSEQ {strcpy(op,$1); push(">>="); $$ = $1;}
| T_SUBEQ {strcpy(op,$1); push("-="); $$ = $1;}
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
int paramCall = 0;



void push(char* val){
    strcpy(st[top++], val);
}


void codegen_call(){
    printf("call(%s, %d)\n", st[top-1], paramCall);
    paramCall = 0;
    top-=1;
}

void codegen_param(){
    printf("param %s\n", st[top-1]);
    top-=1;
    paramCall += 1;
}

void codegen()
{
	strcpy(temp,"t");
	strcat(temp,i_);
	printf("%s = %s %s %s\n",temp,st[top-3],st[top-2],st[top-1]);
    insert_quad(st[top-2][0],st[top-3],st[top-1],temp);

	
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
    insert_quad(st[top-2][0],st[top-1],"1",temp);
    insert_quad('=',temp,NULL,st[top-1]);
    printf("%s = %s\n", st[top - 1], temp);


    }
    else if((!strcmp(st[top - 1],"++")) || (!strcmp(st[top - 1],"--"))){
    printf(" %s = %s %c %d\n", temp, st[top-2], st[top-1][0], 1);
    insert_quad(st[top-1][0],st[top-2],"1",temp);
    insert_quad('=',temp,NULL,st[top-2]);
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

//done
void codegen_syns(){
  printf("%s %c %s %c %s\n", st[top-3], st[top-2][1], st[top-3], st[top-2][0], st[top - 1]);
  insert_quad(st[top-2][0],st[top-3],st[top-1],st[top-3]);
    
  
  top = top - 2;
}


void codegen_assign(){
  printf("%s = %s\n", st[top-2], st[top-1]);
  insert_quad('=',st[top-1],NULL,st[top-2]);
  

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
    printf("%s = not %s %s %s\n",temp,st[top-3],st[top-2],st[top-1]);
    top -= 2;
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
 printf("%s = not %s %s %s\n",temp,st[top-3],st[top-2],st[top-1]);
 top -= 2;
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
    
    /*quad *current=quad_head;
    quad *next=NULL;
    while(current!=NULL)
    {
        next=current->next;
        free(current);
        current=next;
    }
    quad_head=NULL;*/
    return 0;

}
