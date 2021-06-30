all:
	@echo "\nGenerating Syntax Analyzer...\n"
	yacc -v -d parser.y
	flex al.l
	gcc lex.yy.c y.tab.c -o fasi2

clean:
	rm -rf fasi2
	rm -rf lex.yy.c
	rm -rf y.tab.c
	rm -rf y.tab.h 
	rm -rf y.output