/**************************************************************************************************
 *parser
 *Implementation transforming an infix notation to a RPN one.
 *************************************************************************************************/
#include <cstring>
#include <string>
#include <cctype>
#include <sstream>
#include "parser.hpp"

using namespace std;
//typedef std::vector<Lexer::token> Exp;
/* --------------------------------------------------------------------------------------------- *
Lexer: 

The two constructor of Lexer which initializes it's private variables if any

Input:
in		the input stream we work on
Ø     for the other one
*----------------------------------------------------------------------------------------------- */
Lexer::Lexer(){}
Lexer::Lexer(istream& in): input_stream(&in), counter(0), counter_bis(0){}

/* --------------------------------------------------------------------------------------------- *
next:

Gives the next token and removes it from the input.

Input:
Ø

Output:
next_token	next token removed from the input stream
*----------------------------------------------------------------------------------------------- */
Lexer::token Lexer::next(){
	    token next_token = peek();
      for(int i = 0; i < counter_bis; i++){
        input_stream->get();
      }
      counter += counter_bis;
      return next_token;  
}

/* --------------------------------------------------------------------------------------------- *
peek:

Gives the next token without removing it from the input. also throws error in
case of bad token.

Input:
Ø

Output:
next_token	next token of the input stream
*----------------------------------------------------------------------------------------------- */
Lexer::token Lexer::peek(){
	token next_token;
	char new_char;

	input_stream->get(new_char);
	int char_type = 0; 
	char word[6];
	string bad_token = "BAD TOKEN: ";
	string str;
	counter_bis = 1;

	if(input_stream->eof() || new_char == '\n')
		throw domain_error ("EOI");
	
  while(isspace(new_char)){
		input_stream->get(new_char);
    word[0] = new_char;	
		if(input_stream->eof() || new_char == '\n')
			throw domain_error("EOI");
		counter_bis++;
	}

	if(ispunct(new_char)){
		char_type = 1;
  }else if(isalpha(new_char)){
		char_type = 2;
  }else if(isalnum(new_char)){
    char_type = 3;
  }

	switch(char_type){
		case 0:
			    throw domain_error (bad_token.append(std::to_string(new_char)));
			    input_stream->putback(new_char);
			    break;
		case 1:
			    switch(new_char){
				        case '(':
                   	next_token = OPEN_PAR;
                    break;
                case ')':
                    next_token = CLOSE_PAR;
               	    break;
                case ',' :
               	    next_token = COMMA;
               	    break;	
                case '*':
               	    next_token = TIMES;	
               	    break;
                case '=':
                    next_token = EQUAL; 
                    break;    
                default:
               		   throw domain_error(bad_token.append(std::to_string(new_char)));   
           	}
           	input_stream->putback(new_char);
           	break;
    case 2:	
			    switch(new_char){
				        case 'x':
                   	next_token = X;
                   	break;
            	  case 'y':
                   	next_token = Y;
                   	break;
                case 's':
                   	word[0] = 's';
                   	input_stream->get(word + 1 , 3);
                   	if(input_stream->eof() || new_char == '\n')
                   		throw domain_error("EOI");
                   	counter_bis += 2;
                   	if(!strcmp(word,"sin")){
                        next_token = SIN;
                    }else{
                        throw domain_error (bad_token.append(word));
                    }
                  	break;	

                case 'c':
                   	word[0] = 'c';
                   	input_stream->get(word + 1 , 3);
                   	if(input_stream->eof() || new_char == '\n')
                   		throw domain_error("EOI");
                   	counter_bis += 2;
                   	if(!strcmp(word,"cos")){
                        next_token = COS;
                    }else{
                        throw domain_error (bad_token.append(word));
                    }
                    break;

                case 'a':
                   	word[0] = 'a';
                   	input_stream->get(word + 1 , 3);
                   	if(input_stream->eof() || new_char == '\n')
                   		throw domain_error("EOI");
                   	counter_bis += 2;
                   	if(!strcmp(word,"avg")){
                        next_token = AVG;
                    }else{
                        throw domain_error (bad_token.append(word));
                    }
                   	break;	

                case 'p':
                   	input_stream->get(new_char);
                   	if(input_stream->eof() || new_char == '\n')
                   		throw domain_error("EOI");
                   	counter_bis ++;
                   	if(new_char == 'i'){
                        next_token = PI;
                    }else{
                    	str = 'p';
                    	str += new_char;
                        throw domain_error (bad_token.append(str));
                    }
                   	break;
                case 'r':
                    word[0] = 'r';
                    input_stream->get(word + 1, 3);
                    if(input_stream->eof() || new_char == '\n')
                      throw domain_error("EOI");
                    counter_bis += 2;
                    if(!strcmp(word,"red")){
                        next_token = RED;
                    }else{
                        throw domain_error (bad_token.append(word));
                    }
                    break;

                case 'g':
                    word[0] = 'g';
                    input_stream->get(word + 1, 5);
                    if(input_stream->eof() || new_char == '\n')
                      throw domain_error("EOI");
                    counter_bis += 4;
                    if(!strcmp(word,"green")){
                        next_token = GREEN;
                    }else{
                        throw domain_error (bad_token.append(word));
                    }
                    break;

                case 'b':
                    word[0] = 'b';
                    input_stream->get(word + 1, 4);
                    if(input_stream->eof() || new_char == '\n')
                      throw domain_error("EOI");
                    counter_bis += 3;
                    if(!strcmp(word,"blue")){
                        next_token = BLUE;
                    }else{
                        throw domain_error (bad_token.append(word));
                    }
                    break;
                    	
               	default:
               		throw domain_error(bad_token.append(std::to_string(new_char)));   
           	}
        	for (int i = 0; i < counter_bis; i++)
    		{
    			input_stream->unget();
    		}
    		break;

    case 3:
       if(new_char != '0')
           throw domain_error(bad_token.append(std::to_string(new_char)));
       next_token = ZERO;
       break;   
    }
    return next_token;		
}

/* --------------------------------------------------------------------------------------------- *
count:

returns counter which is the number of characters read from the input stream

Input:
Ø

Output:
counter 	the number of characters
*----------------------------------------------------------------------------------------------- */
streamoff Lexer::count() const{
    return counter;
}


/* --------------------------------------------------------------------------------------------- *
reset:

sets the counter back to 0

Input:
Ø

Output:
Ø
*----------------------------------------------------------------------------------------------- */
void Lexer::reset(){
    counter = 0;
}

/* --------------------------------------------------------------------------------------------- *
Parser:

constructor of Parser which initializes it's private variable.
Input:
in    the input stream we work on
Ø     for the other consttructor

Output:
Ø
*----------------------------------------------------------------------------------------------- */
Parser::Parser(){}
Parser::Parser(std::istream& in): lexer(in){}

/* --------------------------------------------------------------------------------------------- *
parse:

returns whether recursivParse managed to parse the input stream or not and a vector of token
from the string given in input.

Input:
exp 	a string which we will transform into tokens.

Output:
expression  the vector of tokens
*----------------------------------------------------------------------------------------------- */
Exp Parser::parse(string exp){
    Exp expression;
    istringstream input(exp);
    lexer = Lexer(input);
		recursivParse(expression, lexer.next());
		return expression;
}

/* --------------------------------------------------------------------------------------------- *
recursivParse:

parse our input stream and puts it into the vector exp if no error were thrown. In
this case returns the place of the parse error of the input stream.
Input:
exp 	the vector being completed with the new expression
tokens	a token to determine what we do next (
Øthrow an error if misplaced, fill exp if not)

Output:
*----------------------------------------------------------------------------------------------- */
void Parser::recursivParse(Exp& exp, Lexer::token tokens){
	string parse_error_at = "PARSE ERROR AT CHARACTER:  ";
	Lexer::token next_token = tokens;
  switch(tokens){
    case Lexer::ZERO:
      exp.emplace_back(Lexer::ZERO);
      break; 

		case Lexer::X:	
			exp.emplace_back(Lexer::X);
			break;

		case Lexer::Y:
			exp.emplace_back(Lexer::Y);  // return Y()
			break;

		case Lexer::SIN:
      exp.emplace_back(Lexer::SIN); // no need to put PI and TIMES as long as we know they are there
			next_token = lexer.next();
			if(next_token != Lexer::OPEN_PAR)
				throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
			next_token = lexer.next();
			if(next_token != Lexer::PI)
				throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
			next_token = lexer.next();
			if(next_token != Lexer::TIMES)
				throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
			
      recursivParse(exp, lexer.next());
			next_token = lexer.next();
			if(next_token != Lexer::CLOSE_PAR)
				throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
			break;	

		case Lexer::COS:
      exp.emplace_back(Lexer::COS); // no need to put PI and TIMES as long as we know they were there   
			next_token = lexer.next();
			if(next_token != Lexer::OPEN_PAR)
				throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
			next_token = lexer.next();
			if(next_token != Lexer::PI)
				throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
			next_token = lexer.next();
			if(next_token != Lexer::TIMES)
				throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));      
			
      recursivParse(exp, lexer.next());
			next_token = lexer.next();
			if(next_token != Lexer::CLOSE_PAR)
				throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
			break;
		
		case Lexer::OPEN_PAR:
      exp.emplace_back(Lexer::OPEN_PAR);
			
      recursivParse(exp, lexer.next());
			next_token = lexer.next();
			if(next_token != Lexer::TIMES)
				throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
      
      recursivParse(exp, lexer.next());
			next_token = lexer.next();
			if(next_token != Lexer::CLOSE_PAR)
				throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
			break;	

		case Lexer::AVG: 
      exp.emplace_back(Lexer::AVG);
			next_token = lexer.next();  
			if(next_token != Lexer::OPEN_PAR)	
				throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
			
      recursivParse(exp, lexer.next());
			next_token = lexer.next();
			if(next_token != Lexer::COMMA)	
				throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));			
			
      recursivParse(exp, lexer.next());
			next_token = lexer.next();
			if(next_token != Lexer::CLOSE_PAR)	
				throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
			break;

		default:
			throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
	}
}

int Parser::depthParse(string exp, Exp& color_tokens){
    std::cout << exp << endl;
    istringstream input(exp);
    lexer = Lexer(input);
    return recursivParseDepth(color_tokens, lexer.next());;
}
/* --------------------------------------------------------------------------------------------- *
recursivParseDepth:

parse our input stream and puts it into the vector exp if no error were thrown. In
this case returns the place of the parse error of the input stream.
Input:
exp   the vector being completed with the new expression
tokens  a token to determine what we do next (
Øthrow an error if misplaced, fill exp if not)

Output:
*----------------------------------------------------------------------------------------------- */
int Parser::recursivParseDepth(Exp& exp, Lexer::token tokens){
  string parse_error_at = "PARSE ERROR AT CHARACTER:  ";
  int depth1, depth2;
  Lexer::token next_token = tokens;
  switch(tokens){
    case Lexer::X:  
      exp.emplace_back(Lexer::X);
      return 1;

    case Lexer::Y:
      exp.emplace_back(Lexer::Y);
      return 1;

    case Lexer::SIN:
      exp.emplace_back(Lexer::SIN);
      next_token = lexer.next();
      if(next_token != Lexer::OPEN_PAR)
        throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
      next_token = lexer.next();
      if(next_token != Lexer::PI)
        throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
      next_token = lexer.next();
      if(next_token != Lexer::TIMES)
        throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
      // no need to put PI and TIMES as long as we know they were there.
      depth1 = recursivParseDepth(exp, lexer.next());
      next_token = lexer.next();

      if(next_token != Lexer::CLOSE_PAR)
        throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
      return depth1++;   
    case Lexer::COS:
      exp.emplace_back(Lexer::COS); // no need to put PI and TIMES as long as we know they were there   
      next_token = lexer.next();
      if(next_token != Lexer::OPEN_PAR)
        throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
      next_token = lexer.next();
      if(next_token != Lexer::PI)
        throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
      next_token = lexer.next();
      if(next_token != Lexer::TIMES)
        throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));      
      depth1 = recursivParseDepth(exp, lexer.next());
      next_token = lexer.next();
      if(next_token != Lexer::CLOSE_PAR)
        throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
      return depth1++;
    
    case Lexer::OPEN_PAR:
      exp.emplace_back(Lexer::OPEN_PAR);
      depth1 = recursivParseDepth(exp, lexer.next());
      next_token = lexer.next();
      if(next_token != Lexer::TIMES)
        throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
      depth2 = recursivParseDepth(exp, lexer.next());
      next_token = lexer.next();
      if(next_token != Lexer::CLOSE_PAR)
        throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
  
      if(depth1 > depth2)
        return depth1++;
      return depth2++;

    case Lexer::AVG: 
      exp.emplace_back(Lexer::AVG);
      next_token = lexer.next();  
      if(next_token != Lexer::OPEN_PAR) 
        throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
      depth1 = recursivParseDepth(exp, lexer.next());

      next_token = lexer.next();
      if(next_token != Lexer::COMMA)  
        throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));     
      depth2 = recursivParseDepth(exp, lexer.next());
      next_token = lexer.next();
      if(next_token != Lexer::CLOSE_PAR)  
        throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
      if(depth1 > depth2)
        return depth1++;
      return depth2++;

    default:
      throw domain_error(parse_error_at.append(std::to_string(lexer.count() - sizeOfToken(next_token) + 1)));
  }
}	

void Parser::print_token(Lexer::token tok){
    switch(tok){
        case Lexer::X:
            printf(" x \n ");
            break;
        case Lexer::Y:
            printf(" y \n ");
            break;
        case Lexer::PI:
            printf(" pi ");
            break;
        case Lexer::SIN:
            printf(" sin \n");
            break;
        case Lexer::COS:
            printf(" cos \n");
            break;
        case Lexer::OPEN_PAR:
            printf(" ( \n ");
            break;
        case Lexer::CLOSE_PAR:
            printf(" ) \n");
            break;
        case Lexer::TIMES:
            printf(" * \n");
            break;
        case Lexer::AVG:
            printf(" avg \n");
            break;
        case Lexer::COMMA:
            printf(" , \n ");
            break;
        case Lexer::ZERO:
            printf(" zero \n ");    
            break;
        case Lexer::RED:
            printf(" red ");
            break;
        case Lexer::BLUE:
            printf(" blue ");
            break;
        case Lexer::GREEN:
            printf(" green ");
            break;
        case Lexer::EQUAL:
            printf(" = ");
            break;
    }

}
void Lexer::print_token(Lexer::token tok){
    switch(tok){
        case Lexer::X:
            printf(" x \n ");
            break;
        case Lexer::Y:
            printf(" y \n ");
            break;
        case Lexer::PI:
            printf(" pi ");
            break;
        case Lexer::SIN:
            printf(" sin \n");
            break;
        case Lexer::COS:
            printf(" cos \n");
            break;
        case Lexer::OPEN_PAR:
            printf(" ( \n ");
            break;
        case Lexer::CLOSE_PAR:
            printf(" ) \n");
            break;
        case Lexer::TIMES:
            printf(" * \n");
            break;
        case Lexer::AVG:
            printf(" avg \n");
            break;
        case Lexer::COMMA:
            printf(" , \n ");
            break;
        case Lexer::ZERO:
            printf(" zero \n ");    
            break;
        case Lexer::RED:
            printf(" red ");
            break;
        case Lexer::BLUE:
            printf(" blue ");
            break;
        case Lexer::GREEN:
            printf(" green ");
            break;
        case Lexer::EQUAL:
            printf(" = ");
            break;

    }

}
/* --------------------------------------------------------------------------------------------- *
sizeOfToken:

returns de size of the tokens that throwed a parse error to get the right position for
the error message 

Input:
tokens 		the token that was misplaced

Output:
size_token  	the size of that token
*----------------------------------------------------------------------------------------------- */
std::streamoff Parser::sizeOfToken(Lexer::token tokens)
{	std::streamoff size_tokens;
    switch(tokens){
        case Lexer::X:
            size_tokens = 1;
            break;
        case Lexer::Y:
            size_tokens = 1;
            break;
        case Lexer::SIN:
            size_tokens = 3;
            break;
        case Lexer::COS:
            size_tokens = 3;
            break;
        case Lexer::PI:
            size_tokens = 2;
            break;
        case Lexer::OPEN_PAR:
            size_tokens = 1;
            break;
        case Lexer::CLOSE_PAR:
            size_tokens = 1;
            break;
        case Lexer::TIMES:
            size_tokens = 1;
            break;
        case Lexer::AVG:
            size_tokens = 3;
            break;
        case Lexer::COMMA:
            size_tokens = 1;
            break;
        default:    
            throw domain_error("wrong token evaluation");  
    
    }
    return size_tokens;
}



