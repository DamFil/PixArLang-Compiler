.PHONY: all

all: a.out test

#test: Tests/test.cpp Parser/Parser.cpp Parser/Parser.h Scanner/Scanner.cpp Scanner/Scanner.h Scanner/FileStreamHandler.h Scanner/TokenStruct.h
#	g++ Tests/test.cpp Parser/Parser.cpp Scanner/Scanner.cpp -o test

a.out: Tests/test.cpp Parser/Parser.cpp Parser/Parser.h Parser/AST.h Scanner/Scanner.cpp Scanner/Scanner.h Scanner/FileStreamHandler.h Scanner/TokenStruct.h XMLVisitor/XMLVisitor.h XMLVisitor/XMLVisitor.cpp SemanticAnalysis/SymbolTable.h SemanticAnalysis/SemVisitor.h SemanticAnalysis/SemVisitor.cpp
	g++ -g Tests/test.cpp Parser/Parser.cpp Scanner/Scanner.cpp XMLVisitor/XMLVisitor.cpp SemanticAnalysis/SemVisitor.cpp