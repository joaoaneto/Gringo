gringo:	lex_gringo.l bison_gringo.y
	bison -v -d -o bison_gringo.cpp bison_gringo.y
	flex -o lex_gringo.cpp lex_gringo.l
	g++ -o $@ -g main.cpp classes_gringo.cpp visitor.cpp bison_gringo.cpp lex_gringo.cpp

clean:
	$(RM) gringo gringo.exe bison_gringo.cpp lex_gringo.cpp bison_gringo.hpp
