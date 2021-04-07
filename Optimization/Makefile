all:
	lex lexer.l
	yacc -d newparser.y
	gcc y.tab.c lex.yy.c -ll

clean: 
	rm *.c *.out *.h