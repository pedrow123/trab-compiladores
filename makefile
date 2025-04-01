compilador: parser.y compilador.l 
	bison -d parser.y
	flex compilador.l
	clang -o compilador parser.tab.c lex.yy.c -lfl

clean:
	rm -f lex.yy.c compilador parser.tab.c parser.tab.h