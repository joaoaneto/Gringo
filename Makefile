gringo:	lex_gringo.l bison_gringo.y
	bison -v -d -o bison_gringo.cpp bison_gringo.y
	flex -o lex_gringo.cpp lex_gringo.l
	g++ -o $@ main.cpp classes_gringo.cpp bison_gringo.cpp lex_gringo.cpp -lfl -lm

clean:
	$(RM) gringo bison_gringo.cpp lex_gringo.cpp bison_gringo.hpp
