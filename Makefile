gringo:	lex_gringo.l bison_gringo.y
	bison -d -o bison_gringo.cpp bison_gringo.y
	flex -o lex_gringo.cpp lex_gringo.l
	g++ -o $@ bison_gringo.cpp lex_gringo.cpp -lfl -lm

clean:
	$(RM) gringo
