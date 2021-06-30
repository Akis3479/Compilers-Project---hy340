all:	newbin
	gcc -g avm.c -o avm

newbin:
	(cd ../PhaseD/ && make && fasi4 < mytest)
	\cp ../PhaseD/binary.bin .

clean:
	rm -rf avm
	rm -rf binary.bin
