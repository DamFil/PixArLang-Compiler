.PHONY: all

all: test2

test2: Tests/test.cpp Parser/Parser.cpp Parser/Parser.h Scanner/Scanner.cpp Scanner/Scanner.h Scanner/FileStreamHandler.h Scanner/TokenStruct.h
	g++ Tests/test.cpp Parser/Parser.cpp Scanner/Scanner.cpp -o test2