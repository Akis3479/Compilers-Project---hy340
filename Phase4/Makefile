all:
	@echo "\nGenerating Syntax Analyzer...\n"
	yacc -v -d parser.y
	flex al.l
	gcc -g lex.yy.c y.tab.c -o fasi4

clean:
	rm -rf fasi4
	rm -rf lex.yy.c
	rm -rf y.tab.c
	rm -rf y.tab.h
	rm -rf y.output
	rm -rf quads.txt
	rm -rf binary.bin
	rm -rf t_code.txt
