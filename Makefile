CXX = g++
LEX = flex
YACC = bison -d
CXXFLAGS = -Wall -Wextra -pedantic
LEXFLAGS = -Wno-unused -Wno-sign-compare -x c++
YACCFLAGS = -x c++

PROGRAM = mypython

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o) parse.tab.o lex.yy.o

all:	.depend $(PROGRAM)

mypython:	$(OBJ)
	$(CXX) -o $(PROGRAM) $(OBJ)

parse.tab.c:	.depend parse.y
	$(YACC) parse.y

parse.tab.o:	parse.tab.c
	$(CXX) $(CFLAGS) $(YACCFLAGS) -c parse.tab.c

lex.yy.c:	scan.l parse.tab.o
	$(LEX) scan.l

lex.yy.o:	lex.yy.c
	$(CXX) $(CFLAGS) $(LEXFLAGS) -c lex.yy.c

clean:
	rm -f $(OBJ) $(PROGRAM) .depend parse.tab.c lex.yy.c parse.tab.h
	rm -rf doc

doc:	doxygen
	xdg-open doc/html/inherits.html &

doxygen:
	doxygen Doxyfile

depend:
	rm -f .depend
	$(MAKE) .depend

.depend:	$(SRC)
	rm -f .depend
	for src in $(SRC) ; do \
		$(CXX) -M -MM $$src | tee -a .depend ; \
	done

statement.o:	CXXFLAGS+=-Wno-unused-parameter
expression.o:	CXXFLAGS+=-Wno-unused-parameter

ifneq ($(wildcard .depend),'')
include .depend
endif

.PHONY:	all clean depend doc
