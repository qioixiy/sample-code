#
SRC_LEX := *.l
SRC_YACC := *.y
all:
	flex ${SRC_LEX}
	yacc -d ${SRC_YACC}
	gcc lex.yy.c y.tab.c  -o main

clean:
	rm main y.tab.* lex.yy.c
