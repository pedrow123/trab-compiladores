compilador: parser.y compilador.l tabela_simbolos.c llvm_lib.c
	bison -d parser.y
	flex compilador.l
	clang -o compilador tabela_simbolos.c llvm_lib.c parser.tab.c lex.yy.c -lfl

clean:
	rm -f lex.yy.c compilador parser.tab.c parser.tab.h