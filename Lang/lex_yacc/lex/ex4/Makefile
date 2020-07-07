#
SRC_LEX := *.l
all:
	flex ${SRC_LEX}
	gcc lex.yy.c -o main -lfl

test: all
	cat testfile.txt | ./main

clean:
	-@rm main lex.yy.c
