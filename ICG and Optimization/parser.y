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
void codegen_arraytemp();
void codegen_arrayassign();
void codegen_syns();
void codgen_un();
void showSt();
void codegen_call();
void codegen_param();
void codegen_return();
void yyerror(const char *s);


typedef struct quadruples{
    char op[100];
    char arg1[20];
    char arg2[20];
    char res[20];
    struct quadruples *next;
} quad;
quad *quad_head=NULL;
quad *quad_tail=NULL;

void insert_quad(char *op,char *arg1,char *arg2,char *res)
{
    quad *new=(quad *)malloc(sizeof(quad));
    strcpy(new->op,op);
    if(arg1!=NULL)
        strcpy(new->arg1,arg1);
    //new->arg2=NULL;
    if(arg2!=NULL)
        strcpy(new->arg2,arg2);
    if(res!=NULL)
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
    //printf("Quadruple table:\n");
    //printf("opeator arg1\targ2\tresult\n");
    while(temp1!=NULL)
    {
        printf("%s\t%s\t%s\t%s\n ",temp1->op,temp1->arg1,temp1->arg2,temp1->res);
        temp1=temp1->next;
    }
}


typedef struct node{
      int scope;
      char value[1000];
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
extern void update(char* name, char* value, int scope);
extern int insert(int* idx, int scope, char* dtype, char* val, int line_num);
extern void decrScope();
extern void incrScope();
extern char tdType[50];
extern char op[50];
char val[50];
int val1, val2;
int val1i, val2i;
float val1f, val2f;
char ddtype[50];
char set[4];
int flag = 0;
int top = 0;

%}
%token T_MAIN T_INT T_FLOAT T_DOUBLE T_CHAR T_VOID T_Terminator T_INC T_DEC T_EQ T_NE T_GT T_LT T_GTE T_LTE T_AND T_OR T_NOT T_BAND T_BOR T_BXOR T_ADDEQ T_MULEQ T_DIVEQ T_MODEQ T_LSEQ T_RSEQ T_ANDEQ T_XOREQ T_OREQ T_H
%token T_B T_OB T_SB T_CSB T_OSB T_CB T_OCB T_ID T_ENDL T_CIN T_COUT T_RETURN T_FOR T_IF T_ELSE T_OUT T_IN T_NUM T_SUBEQ T_COMMA T_BREAK T_CONTINUE T_OFB T_CFB T_VMAIN T_STR  T_STRING T_STRIN T_STROUT T_DEQ T_INCLUDE T_TRUE T_FALSE
%token T_CLASS T_PUBLIC T_PRIVATE T_PROTECTED T_ARRAY
%left T_ADD T_SUB
%left T_MUL T_DIV


%%
S: START { display_quad(); exit(0);}


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
|FUNC STMT
|FUNCALL STMT
|ARRAYASSGN STMT
|
;

/*
ARRAYASSGN STMT
|
;

ARRAYASSGN: T_ID {push($1); top++;} T_OSB VALUE T_CSB {codegen_arraytemp();} T_EQ VALUE {push($6); codegen_arrayassign();} T_Terminator {}
;

VALUE: T_ID {push($1);}
|T_NUM {push($1);}
;
*/

ARRAYASSGN: T_ID {push($1); top++;} T_OSB VALUE {codegen_arraytemp();} T_CSB T_EQ VALUE {codegen_arrayassign();} T_Terminator
;

VALUE: T_ID {push($1);}
|T_NUM {push($1);}
;


FUNC: TYPE T_ID T_OB PARAMLIST T_CB T_OFB STMT T_CFB {}
;

PARAMLIST: TYPE T_ID PARAMLIST{ 
    
    if(!insert(&count, scope + 1, $1, $2, yylineno)){
        yyerror("Variable redeclared");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
}
| TYPE T_ID T_EQ E PARAMLIST{
     
    if(!insert(&count, scope + 1, $1, $2, yylineno)){
        yyerror("Variable redeclared");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
    update($2, val, scope + 1);
}
| T_COMMA T_ID T_EQ E PARAMLIST
{
    
    if(!insert(&count, scope + 1, tdType, $2, yylineno)){
        yyerror("Variable redeclared");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
    update($2, val, scope);
}
| T_COMMA TYPE T_ID PARAMLIST{
    
    if(!insert(&count, scope+1, $2, $3, yylineno)){
        yyerror("Variable redeclared");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
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
|T_STR {strcpy(tdType,$1);}
;

/*done except arrays(?)*/
DECL: TYPE T_ID {push($2);} T_EQ E {codegen_assign();} VARLIST  T_Terminator {
    if(!insert(&count, scope, $1, $2, yylineno)){
        yyerror("Variable redeclared");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
    update($2, val, scope);    
}
| TYPE T_ID {push($2); push("0"); codegen_assign();} VARLIST T_Terminator {
    if(!insert(&count, scope, $1, $2, yylineno)){
        yyerror("Variable redeclared");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
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
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
    push($2);
    push("0");
    codegen_assign();
}
|T_ID {
    if(!insert(&count, scope, tdType, $1, yylineno)){
        yyerror("Variable redeclared");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
    
}
|T_COMMA T_ID {push($2);} T_EQ E {codegen_assign();} VARLIST {
    if(!insert(&count, scope, tdType, $2, yylineno)){
        yyerror("Variable redeclared");
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
    }
    update($2, val, scope);
}
|
;

/*done*/
ASSIGN_EXPR: T_ID {push($1);} ASSIGNOP E T_Terminator {
        if(find(scope, $1) == -1){
            yyerror("Variable not declared");
            printf("PROGRAM INVALID\n");
            display_quad(); displaySymTable(); exit(0);
        }
        int idx1 = find(scope, $1);
        char val2[100];
        
        char* id_type = symTable[idx1].dtype;

        if(!strcmp(op, "=")){
            update($1, $4, scope);
            codegen_assign();
        }
        else if(!strcmp(op, "+=")){
            if(!strcmp(id_type, "float")){
                float val1 = atof(symTable[idx1].value);
                if(!strcmp(ddtype, "float"))
                    val1 += atof($4);
                else
                    val1 += atoi($4);
                
                sprintf(val2, "%f", val1);
                update($1, val2, scope);
            }
            else{
                int val1 = atoi(symTable[idx1].value);
                val1 += atoi($4);
                
                sprintf(val2, "%d", val1);
                update($1, val2, scope);
            }
            codegen_syns();
        }
        else if(!strcmp(op, "-=")){
            if(!strcmp(id_type, "float")){
                float val1 = atof(symTable[idx1].value);
                if(!strcmp(ddtype, "float"))
                    val1 -= atof($4);
                else
                    val1 -= atoi($4);
                
                sprintf(val2, "%f", val1);
                update($1, val2, scope);
            }
            else{
                int val1 = atoi(symTable[idx1].value);
                val1 -= atoi($4);
                
                sprintf(val2, "%d", val1);
                update($1, val2, scope);
            }
            
            codegen_syns();
        }
        else if(!strcmp(op, "*=")){
            if(!strcmp(id_type, "float")){
                float val1 = atof(symTable[idx1].value);
                if(!strcmp(ddtype, "float"))
                    val1 *= atof($4);
                else
                    val1 *= atoi($4);
                
                sprintf(val2, "%f", val1);
                update($1, val2, scope);
            }
            else{
                int val1 = atoi(symTable[idx1].value);
                val1 *= atoi($4);
                
                sprintf(val2, "%d", val1);
                update($1, val2, scope);
            }

            codegen_syns();
        }
        else if(!strcmp(op, "/=")){
            if(!strcmp(id_type, "float")){
                float val1 = atof(symTable[idx1].value);
                if(!strcmp(ddtype, "float"))
                    val1 /= atof($4);
                else
                    val1 /= atoi($4);
                
                sprintf(val2, "%f", val1);
                update($1, val2, scope);
            }
            else{
                int val1 = atoi(symTable[idx1].value);
                val1 /= atoi($4);
                
                sprintf(val2, "%d", val1);
                update($1, val2, scope);
            }
            codegen_syns();
        }
        else if(!strcmp(op, "%=")){
            int val1 = atoi(symTable[idx1].value);
            val1 %= atoi($4);
            sprintf(val2, "%d", val1);
            update($1, val2, scope);
            codegen_syns();
        }
        else if(!strcmp(op, ">>=")){
            int val1 = atoi(symTable[idx1].value);
            val1 >>= atoi($4);
            sprintf(val2, "%d", val1);
            update($1, val2, scope);
            codegen_syns();
        }
        else if(!strcmp(op, "<<=")){
            int val1 = atoi(symTable[idx1].value);
            val1 <<= atoi($4);
            sprintf(val2, "%d", val1);
            update($1, val2, scope);
            codegen_syns();
        }
        else{
            yyerror("Invalid operation");
            printf("PROGRAM INVALID\n");
            display_quad(); displaySymTable(); exit(0);
        }
      }
;

E: E {if(!strcmp(ddtype, "float")){flag = 1; val1f = atof(val);} else{val1i = atoi(val);}} T_ADD {push("+");} T {
    if(flag){
        val2f = atof(val);
        float val1 = val1f+val2f;
        sprintf($$, "%f", val1);
        sprintf(val, "%f", val1);
        flag = 0;
        strcpy(ddtype, "float");
    }
    else{
        if(!strcmp(ddtype, "float")){
            val2f = atof(val);
            float val1 = val1f+val2f;
            sprintf($$, "%f", val1);
            sprintf(val, "%f", val1);
            strcpy(ddtype, "float");
        }
        else if(!strcmp(ddtype, "int")){
            val2i = atoi(val);
            int val1 = val1i+val2i;
            sprintf($$, "%d", val1);
            sprintf(val, "%d", val1);
            strcpy(ddtype, "int");
        }
    }

    
    codegen();
}
|E {if(!strcmp(ddtype, "float")){flag = 1; val1f = atof(val);} else{val1i = atoi(val);}} T_SUB {push("-");} T {
    if(flag){
        val2f = atof(val);
        float val1 = val1f-val2f;
        sprintf($$, "%f", val1);
        sprintf(val, "%f", val1);
        flag = 0;
        strcpy(ddtype, "float");
    }
    else{
        if(!strcmp(ddtype, "float")){
            val2f = atof(val);
            float val1 = val1f-val2f;
            sprintf($$, "%f", val1);
            sprintf(val, "%f", val1);
            strcpy(ddtype, "float");
        }
        else if(!strcmp(ddtype, "int")){
            val2i = atoi(val);
            int val1 = val1i-val2i;
            sprintf($$, "%d", val1);
            sprintf(val, "%d", val1);
            strcpy(ddtype, "int");
        }
    }

    codegen();
}
|T {$$ = $1;}
;

T: T {if(!strcmp(ddtype, "float")){flag = 1; val1f = atof(val);} else{val1i = atoi(val);}} T_MUL {push("*");} F {
    if(flag){
        val2f = atof(val);
        float val1 = val1f*val2f;
        sprintf($$, "%f", val1);
        sprintf(val, "%f", val1);
        flag = 0;
        strcpy(ddtype, "float");
    }
    else{
        if(!strcmp(ddtype, "float")){
            val2f = atof(val);
            float val1 = val1f*val2f;
            sprintf($$, "%f", val1);
            sprintf(val, "%f", val1);
            strcpy(ddtype, "float");
        }
        else if(!strcmp(ddtype, "int")){
            val2i = atoi(val);
            int val1 = val1i*val2i;
            sprintf($$, "%d", val1);
            sprintf(val, "%d", val1);
            strcpy(ddtype, "int");
        }
    }
    codegen();
}
|T {if(!strcmp(ddtype, "float")){flag = 1; val1f = atof(val);} else{val1i = atoi(val);}} T_DIV {push("/");} F {

    if(flag){
        val2f = atof(val);
        float val1 = val1f/val2f;
        sprintf($$, "%f", val1);
        sprintf(val, "%f", val1);
        flag = 0;
        strcpy(ddtype, "float");
    }
    else{
        if(!strcmp(ddtype, "float")){
            val2f = atof(val);
            float val1 = val1f/val2f;
            sprintf($$, "%f", val1);
            sprintf(val, "%f", val1);
            strcpy(ddtype, "float");
        }
        else if(!strcmp(ddtype, "int")){
            val2i = atoi(val);
            int val1 = val1i/val2i;
            sprintf($$, "%d", val1);
            sprintf(val, "%d", val1);
            strcpy(ddtype, "int");
        }
    }
    
    codegen();
}
|F {$$ = $1;}

F: T_ID {
        if(find(scope, $1) == -1){
            yyerror("Variable not declared");
            printf("PROGRAM INVALID\n");
            display_quad(); displaySymTable(); exit(0);
        }
        push($1);
        int idx = find(scope, $1);
        
        if(!strcmp(symTable[idx].dtype, "float")){
            sprintf($$, "%f", atof(symTable[idx].value));
            sprintf(val, "%f", atof(symTable[idx].value));
            strcpy(ddtype, "float");
        }
        else if(!strcmp(symTable[idx].dtype, "int")){
            sprintf($$, "%d", atoi(symTable[idx].value));
            sprintf(val, "%d", atoi(symTable[idx].value));
            strcpy(ddtype, "int");
        }
      }
|T_NUM {strcpy(val, $1); $$ = $1; push($1);
        char *position_ptr = strchr(val, '.');
        if(position_ptr != NULL){
            if(!(strcmp(tdType, "int")))
            {
                yyerror("Mismatched Datatype");
                printf("PROGRAM INVALID\n");
                display_quad(); displaySymTable(); exit(0);
            }
            strcpy(ddtype, "float");
        }
        else
            strcpy(ddtype, "int");
}
| T_OB E T_CB {$$ = $2;}
| BOOL {
        $$ = $1; push($1);
      }
| UNARYEXP
|T_STRING {push($1);}
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
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
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
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
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
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
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
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
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
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
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
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
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
        printf("PROGRAM INVALID\n");
        display_quad(); displaySymTable(); exit(0);
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

JUMPSTMT: T_RETURN T_ID {push($2); codegen_return();} T_Terminator
| T_RETURN T_NUM {push($2); codegen_return();} T_Terminator
| T_RETURN T_STRING {push($2); codegen_return();} T_Terminator
| T_RETURN T_Terminator
| T_CONTINUE T_Terminator
| T_BREAK T_Terminator
;




UNARYEXP: T_INC T_ID {
        if(find(scope, $2) == -1){
            yyerror("Variable not declared");
            printf("PROGRAM INVALID\n");
            display_quad(); displaySymTable(); exit(0);
        }
        push($1);
        push($2);
        codgen_un();
        int idx = find(scope, $2);
        
        if(!symTable[idx].dtype, "float"){
            float v = atof(symTable[idx].value);
            ++v;
            sprintf($$, "%f", v);
        }    
        else if(!strcmp(symTable[idx].dtype, "int")){
            int v = atoi(symTable[idx].value);
            ++v;
            sprintf($$, "%d", v);
        }

        update($2, $$, scope);
    }
| T_ID T_INC {
        if(find(scope, $1) == -1){
            yyerror("variable not declared");
            printf("PROGRAM INVALID\n");
            display_quad(); displaySymTable(); exit(0);
        }
        push($1);
        push($2);
        codgen_un();
        int idx = find(scope, $1);

        if(!strcmp(symTable[idx].dtype, "float")){
            float v = atof(symTable[idx].value);
            v++;
            sprintf($$, "%f", v);
        }
        else if(!strcmp(symTable[idx].dtype, "int")){
            int v = atoi(symTable[idx].value);
            v++;
            sprintf($$, "%d", v);
        }
        
        update($1, $$, scope);
    } 
| T_DEC T_ID {
        if(find(scope, $2) == -1){
            yyerror("variable not declared");
            printf("PROGRAM INVALID\n");
            display_quad(); displaySymTable(); exit(0);
        }
        push($1);
        push($2);
        codgen_un();
        int idx = find(scope, $2);

        if(!strcmp(symTable[idx].dtype, "float")){
            float v = atof(symTable[idx].value);
            --v;
            sprintf($$, "%f", v);
        }
        else if(!strcmp(symTable[idx].dtype, "int")){
            int v = atoi(symTable[idx].value);
            --v;
            sprintf($$, "%d", v);
        }

        update($2, $$, scope);
    }
| T_ID T_DEC {
        if(find(scope, $1) == -1){
            yyerror("variable not declared");
            printf("PROGRAM INVALID\n");
            display_quad(); displaySymTable(); exit(0);
        }
        push($1);
        push($2);
        codgen_un();
        int idx = find(scope, $1);
        
        if(!strcmp(symTable[idx].dtype, "float")){
            float v = atof(symTable[idx].value);
            v--;
            sprintf($$, "%f", v);
        }
        else if(!strcmp(symTable[idx].dtype, "int")){
            int v = atoi(symTable[idx].value);
            v--;
            sprintf($$, "%d", v);
        }

        update($1, $$, scope);
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

int lnum = 0;
int ltop = 0;
int label[25];
char i_[3]="00";
char temp[2]="t";
int paramCall = 0;
char call[5] = "call";
char param[6] = "param";




void push(char* val){
    strcpy(st[top++], val);
}

void codegen_arrayassign(){
    //printf("%s[%s] = %s \n",st[top-3],st[top-2],st[top-1]);
    insert_quad("[]=",st[top-3],st[top-2],st[top-1]);
    top-=2;
}

void codegen_arraytemp(){
    strcpy(temp,"t");
	strcat(temp,i_);
    // printf("%s = 4 * %s\n",temp,st[top-1]);
    insert_quad("*","4",st[top-1],temp);
    top-=1;
	strcpy(st[top-1],temp);
	if(i_[1]!='9')
		i_[1]++;
	else
	{
		i_[1] = '0';
		i_[0]++;
	}
}

void codegen_return(){
    // printf("return %s\n", st[top-1]);
    insert_quad("return",st[top-1],NULL,NULL);
    top-=1;
}

void codegen_call(){
    // printf("call(%s,%d)\n", st[top-1], paramCall);
    char temp[100];
    sprintf(temp, "%d", paramCall);
    insert_quad("call",st[top-1],temp,NULL);
    paramCall = 0;
    top-=1;
}

void codegen_param(){
    // printf("param %s\n", st[top-1]);
    insert_quad(param,st[top-1],NULL,NULL);
    top-=1;
    paramCall += 1;
}

void codegen()
{
	strcpy(temp,"t");
	strcat(temp,i_);
	// printf("%s = %s %s %s\n",temp,st[top-3],st[top-2],st[top-1]);
    insert_quad(st[top-2],st[top-3],st[top-1],temp);

	
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
    // printf(" %s = %s %c %d\n", temp, st[top-1], st[top-2][0], 1);

    char *ptr = malloc(2*sizeof(char));
    ptr[0] = st[top-2][0];
    ptr[1] = '\0';

    insert_quad(ptr,st[top-1],"1",temp);
    insert_quad("=",temp,NULL,st[top-1]);
    // printf("%s = %s\n", st[top - 1], temp);

    free(ptr);

    }
    else if((!strcmp(st[top - 1],"++")) || (!strcmp(st[top - 1],"--"))){
    // printf(" %s = %s %c %d\n", temp, st[top-2], st[top-1][0], 1);

    char *ptr = malloc(2*sizeof(char));
    ptr[0] = st[top-1][0];
    ptr[1] = '\0';

    insert_quad(ptr,st[top-2],"1",temp);
    insert_quad("=",temp,NULL,st[top-2]);
    // printf("%s = %s\n", st[top - 2], temp);

    free(ptr);
    }
    else
        // printf(" %s = %s%s\n", temp, st[top-2], st[top-1]);
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
//   printf("%s %c %s %c %s\n", st[top-3], st[top-2][1], st[top-3], st[top-2][0], st[top - 1]);

  char *ptr = malloc(2*sizeof(char));
  ptr[0] = st[top-2][0];
  ptr[1] = '\0';
  insert_quad(ptr,st[top-3],st[top-1],st[top-3]);

  free(ptr);
  
  top = top - 2;
}


void codegen_assign(){
//   printf("%s = %s\n", st[top-2], st[top-1]);
  insert_quad("=",st[top-1],NULL,st[top-2]);
  

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
    //   printf("L%d : \n",label[ltop - 1]);
      char lab[26] = "L";
      char temp1[100];
      sprintf(temp1, "%d", label[ltop - 1]);
      strcat(lab, temp1);

      insert_quad("Label",NULL,NULL,lab);
      label[ltop++] = ++lnum; //label for incrementing
      label[ltop++] = ++lnum; //label for body of for loop
      label[ltop++] = ++lnum; //label for statements outside for loop
}

void for2() //ICG for condition check
{
	strcpy(temp,"t");
	strcat(temp,i_);	
    // printf("%s = not %s %s %s\n",temp,st[top-3],st[top-2],st[top-1]);
    char temp1[50] = "not ";
    strcat(temp1, st[top-2]);
    insert_quad(temp1,st[top-3],st[top-1],temp);

    top -= 2;
	
    // printf("if %s goto L%d\n",temp,label[ltop - 1]);

    char lab2[26] = "L";
    char temp2[100];
    sprintf(temp2, "%d", label[ltop - 1]);
    strcat(lab2, temp2);
    insert_quad("if",temp,NULL,temp2);
	
    if(i_[1]!='9')
		i_[1]++;
	else
	{
		i_[1] = '0';
		i_[0]++;
	}
	// printf("goto L%d\n", label[ltop - 3]);
//   printf("L%d :\n", label[ltop - 2]);

}

void for3() //incrementing and executing loop again
{
//   printf("goto L%d\n", label[ltop - 4]);
  char lab[26] = "L";
  char temp1[100];
  sprintf(temp1, "%d", label[ltop - 4]);
  strcat(lab, temp1);
  insert_quad("goto",NULL,NULL,lab);
  
//   printf("L%d :\n", label[ltop - 3]);
  char lab2[26] = "L";
  char temp2[100];
  sprintf(temp2, "%d", label[ltop - 3]);
  strcat(lab2, temp2);
  insert_quad("Label",NULL,NULL,lab2);
}

void for4() //go to autoincrement and print label after loop
{
	// printf("goto L%d \n",label[ltop - 2]);
    char lab[26] = "L";
    char temp1[100];
    sprintf(temp1, "%d", label[ltop - 4]);
    strcat(lab, temp1);
    insert_quad("goto",NULL,NULL,lab);
	
    // printf("L%d : \n",label[ltop - 1]);
    char lab2[26] = "L";
    char temp2[100];
    sprintf(temp2, "%d", label[ltop - 3]);
    strcat(lab2, temp2);

    ltop = ltop - 4;
}

//if
void if1()
{
 lnum++;
 strcpy(temp,"t");
 strcat(temp,i_);
//  printf("%s = not %s %s %s\n",temp,st[top-3],st[top-2],st[top-1]);
 char temp1[50] = "not ";
 strcat(temp1, st[top-2]);
 insert_quad(temp1,st[top-3],st[top-1],temp);
 top -= 2;
 
//  printf("if %s goto L%d\n",temp,lnum);
 char lab2[26] = "L";
 char temp2[100];
 sprintf(temp2, "%d", lnum);
 strcat(lab2, temp2);
 insert_quad("if",temp,NULL,temp2);

 i_[0]++;
 label[++ltop]=lnum;
}

void if2()
{
int x;
lnum++;
x=label[ltop--];

char lab2[26] = "L";
char temp2[100];
sprintf(temp2, "%d", x);
insert_quad("goto",NULL,NULL,temp2);
// printf("goto L%d\n",lnum);

// printf("L%d: \n",x);
char lab[26] = "L";
char temp1[100];
sprintf(temp1, "%d", x);
strcat(lab, temp1);

insert_quad("Label",NULL,NULL,lab);
label[++ltop]=lnum;
}

//if-else
void if3()
{
int y;
y=label[ltop--];
printf("L%d: \n",y);
char lab[26] = "L";
char temp1[100];
sprintf(temp1, "%d", y);
strcat(lab, temp1);

insert_quad("Label",NULL,NULL,lab);

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
