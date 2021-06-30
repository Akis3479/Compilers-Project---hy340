WORKINGPATH = Working
ERRORATH = Errors
TESTSPHASE3 = tests_phase_3

all:
	@echo "\nGenerating Syntax Analyzer...\n"
	yacc -v -d parser.y
	flex al.l
	gcc -g lex.yy.c y.tab.c -o fasi3

clean:
	rm -rf fasi3
	rm -rf lex.yy.c
	rm -rf y.tab.c
	rm -rf y.tab.h
	rm -rf y.output

working: 
	fasi3 < $(WORKINGPATH)/Anonymous.asc
	fasi3 < $(WORKINGPATH)/Block.asc
	fasi3 < $(WORKINGPATH)/Circle.asc
	fasi3 < $(WORKINGPATH)/GlobalAndLocal.asc
	fasi3 < $(WORKINGPATH)/Grammar.asc
	fasi3 < $(WORKINGPATH)/Random.asc
	fasi3 < $(WORKINGPATH)/ShadowedNameOffunctions.asc
	fasi3 < $(WORKINGPATH)/Simple.asc
	fasi3 < $(WORKINGPATH)/Tree.asc

tests:
	fasi3 < $(TESTSPHASE3)/backpatch.asc
	fasi3 < $(TESTSPHASE3)/p3t_assignments_complex.asc
	fasi3 < $(TESTSPHASE3)/p3t_assignments_objects.asc
	fasi3 < $(TESTSPHASE3)/p3t_assignments_simple.asc
	fasi3 < $(TESTSPHASE3)/p3t_basic_expr.asc
	fasi3 < $(TESTSPHASE3)/p3t_calls.asc
	fasi3 < $(TESTSPHASE3)/p3t_const_maths.asc
	fasi3 < $(TESTSPHASE3)/p3t_flow_control.asc
	fasi3 < $(TESTSPHASE3)/p3t_funcdecl.asc
	fasi3 < $(TESTSPHASE3)/p3t_if_else.asc
#	fasi3 < $(TESTSPHASE3)/p3t_object_creation_expr.asc
	fasi3 < $(TESTSPHASE3)/p3t_relational.asc
	fasi3 < $(TESTSPHASE3)/p3t_var_maths.asc
	fasi3 < $(TESTSPHASE3)/t.asc

errors:
#	fasi3 < $(ERRORATH)/Error0.asc
#	fasi3 < $(ERRORATH)/Error1.asc
#	fasi3 < $(ERRORATH)/Error2.asc
#	fasi3 < $(ERRORATH)/Error3.asc
#	fasi3 < $(ERRORATH)/Error4.asc
#	fasi3 < $(ERRORATH)/Error5.asc
#	fasi3 < $(ERRORATH)/Error6.asc
#	fasi3 < $(ERRORATH)/Error7.asc
#	fasi3 < $(ERRORATH)/Error8.asc
#	fasi3 < $(ERRORATH)/Error9.asc
#	fasi3 < $(ERRORATH)/Error10.asc
#	fasi3 < $(ERRORATH)/Error11.asc
#	fasi3 < $(ERRORATH)/Error12.asc
