#ifndef PARSER_HPP_INCLUDED
#define PARSER_HPP_INCLUDED

#include<iostream>
#include<vector>
#include<string>


class Lexer {
	public:
		enum token {X, Y, SIN, COS, PI, OPEN_PAR, CLOSE_PAR, TIMES, AVG, COMMA, ZERO, RED, BLUE, GREEN, EQUAL};
		Lexer();
		explicit Lexer(std::istream& in);
		token next();
		token peek();
		std::streamoff count() const;
		void reset();
        void print_token(Lexer::token tok);

	private:
		std::istream* input_stream;
		std::streamoff counter;
		std::streamoff counter_bis;
};
typedef std::vector<Lexer::token> Exp;

class Parser{
    public:
    	Parser();
        explicit Parser(std::istream& in);
        Exp parse(std::string exp);
        void print_token(Lexer::token tok);
		int depthParse(std::string exp, Exp& color_tokens);

    private:
        //std::istream* input_stream;
        Lexer lexer;
        void recursivParse(Exp& exp, Lexer::token tokens);
		int recursivParseDepth(Exp& exp, Lexer::token tokens);
		std::streamoff sizeOfToken(Lexer::token tokens);        

};

#endif