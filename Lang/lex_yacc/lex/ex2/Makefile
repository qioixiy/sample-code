#
SRC_LEX := *.l
all:
	flex ${SRC_LEX}
	gcc lex.yy.c -o main -lfl

clean:
	-@rm main lex.yy.c
