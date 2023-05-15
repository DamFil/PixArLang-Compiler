.PHONY: all

all: a.out

a.out: Tests/test.cpp Parser/Parser.cpp Parser/Parser.h Scanner/Scanner.cpp Scanner/Scanner.h Scanner/FileStreamHandler.h Scanner/TokenStruct.h
	g++ -g Tests/test.cpp Parser/Parser.cpp Scanner/Scanner.cpp