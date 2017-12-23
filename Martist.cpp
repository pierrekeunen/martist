#include<cstddef>
#include<string>
#include<ctime>
#include<cstdlib> 
#include<vector> 
#include <cmath>
#include "martist.hpp"
#include "parser.hpp"
using namespace std;

Martist::Martist(unsigned char* buffer, size_t width, size_t height, int rdepth, int gdepth, int bdepth){
    redDepth(rdepth);
    greenDepth(gdepth);
    blueDepth(bdepth);
    changeBuffer(buffer, width, height);	
	seed(time(nullptr));
}

void Martist::redDepth(int depth){
    if(depth < 0)
        throw domain_error("The red depth can't be negative \n");
    r_depth = depth;
}
void Martist::greenDepth(int depth){
    if(depth < 0)
        throw domain_error("The green depth can't be negative \n");
    g_depth = depth;
}
void Martist::blueDepth(int depth){
    if(depth < 0)
        throw domain_error("The blue depth can't be negative \n");
    b_depth = depth;
}

int Martist::redDepth() const{
    return r_depth;
}
int Martist::greenDepth() const{
    return g_depth;
}
int Martist::blueDepth() const{
    return b_depth;
}

void Martist::seed(int seed){
	seed_mood = seed;
}

void Martist::changeBuffer(unsigned char* buffer, size_t width, size_t height){
	if(buffer == nullptr)
		throw domain_error("The buffer is a null pointer \n");
	if(width <= 0)
		throw domain_error("The width is not valid \n");
	if(height <= 0)
		throw domain_error("The height is not valid \n");

	im_width = width;
	im_height = height;
	pixels_array = buffer;
}

void Martist::paint(){
	double x, y;
	int position; //used for the one dimension array
	if(!expression_set){ //expression_set false by default
 		red = expressionGenerator(r_depth, seed_mood);
		green = expressionGenerator(g_depth, seed_mood * 4 ); // to avoid 50 shades of grey
		blue = expressionGenerator(b_depth, seed_mood / 8 );
	}

	Parser par; 
	Exp red_tok = par.parse(red);
	Exp green_tok = par.parse(green);
	Exp blue_tok = par.parse(blue);
	for (size_t i = 0; i < im_height; ++i){
		y = 2 * (i/((double)(im_height - 1))) - 1; // We need a x and y value between [-1,1] 
		for (size_t j = 0; j < im_width; ++j){
			x = 2 * ((double)j/((double)(im_width - 1))) - 1;
			position = (i * im_width + j) * 3; 

			pixels_array[position] = (pixelCalculation(x, y, red_tok) + 1) * 127.5; // red intensity for the (j,i) pixel
			pixels_array[position+1] = (pixelCalculation(x, y, green_tok) + 1) * 127.5; // green intensity for the (j,i) pixel
			pixels_array[position+2] = (pixelCalculation(x, y, blue_tok) + 1) * 127.5; // blue intensity for the (j,i) pixel
		}
	}
}

ostream& operator<<(ostream& output_stream, Martist& martist){
	output_stream << "red = " << martist.red << endl
				  << "green = " << martist.green << endl
				  << "blue = " << martist.blue << endl;
	return output_stream;	
}

istream& operator>>(istream& input_stream, Martist& martist){
	Lexer lexer(input_stream);
	Parser par;
	Lexer::token next_token;
	Exp red_tok;
	Exp green_tok;
	Exp blue_tok;
	while(!input_stream.eof()){
		next_token = lexer.next();
  		switch(next_token){
  			case Lexer::RED:
  				next_token = lexer.next();
  				if(next_token != Lexer::EQUAL)
 					throw domain_error("Red: input not allowed");
				next_token = lexer.peek();
				if(next_token == Lexer::ZERO){
					martist.r_depth = 0;
					getline(input_stream, martist.red);
					martist.red = "0";
				}else{
					getline(input_stream, martist.red);
					martist.r_depth = par.depthParse(martist.red, red_tok);
				}
				break;
			case Lexer::GREEN:
  				next_token = lexer.next();
  				if(next_token != Lexer::EQUAL)
 					throw domain_error("Green: input not allowed");
				next_token = lexer.peek();
				if(next_token == Lexer::ZERO){
					martist.g_depth = 0;
					getline(input_stream, martist.green);
					martist.green = "0";
				}else{
					getline(input_stream, martist.green);					
					martist.g_depth = par.depthParse(martist.green, green_tok);			
				}
				break;
			case Lexer::BLUE:
  				next_token = lexer.next();
  				if(next_token != Lexer::EQUAL)
 					throw domain_error("Blue: input not allowed");
				next_token = lexer.peek();
				if(next_token == Lexer::ZERO){
					martist.b_depth = 0;
					getline(input_stream, martist.blue);
					martist.blue = "0";
				}else{
					getline(input_stream, martist.blue);										
					martist.b_depth = par.depthParse(martist.blue, blue_tok);				
				}
				break;
			default:
				throw domain_error(" Input not allowed");
		}					
	}
	martist.expression_set = true;
	martist.paint();
	return input_stream;
}

string Martist::expressionGenerator(int depth, int seed_mood){
	string expression;
	if (depth < 1)
		throw domain_error("depth must be greater than 0");
	int depth_bis = depth;
	srand((unsigned int) seed_mood);
	recExpressionGenerator(depth_bis, expression);
	return expression;
}

void Martist::recExpressionGenerator(int depth, string& expression){
	int random_choice;
	if(depth == 1){ // I chose to have the maximum depth possible
		random_choice = rand() %2;
		if(random_choice == 0)
			expression += "x";
		else
			expression += "y";
	}else{
		random_choice = rand() %4;
		switch(random_choice){
			case 0:
				expression += "sin(pi*";
				recExpressionGenerator(depth - 1, expression);
				expression += ")";
				break;
			case 1:
				expression += "cos(pi*";
				recExpressionGenerator(depth - 1, expression);
				expression += ")";
				break;
			case 2:
				expression += "(";
				recExpressionGenerator(depth - 1, expression);
				expression += "*";
				recExpressionGenerator(depth - 1, expression);
				expression += ")";
				break;
			case 3:
				expression += "avg(";
				recExpressionGenerator(depth - 1, expression);
				expression += ",";
				recExpressionGenerator(depth - 1, expression);
				expression += ")";
				break;

		}
	}
}

double Martist::pixelCalculation(double x, double y, Exp expression){
	if(expression.empty())
		throw domain_error("The expression is empty \n");
	if( x > 1 || x < -1)
		throw domain_error("x is out of bound \n");
	if( y > 1 || y < -1)
		throw domain_error("y is out of bound \n");
	Exp expression_bis = expression;
	double result = recPixelCalculation(x, y, expression_bis);
	return result;
}

double Martist::recPixelCalculation(double x, double y, Exp& expression){
	
	Lexer::token first_token = expression.front();
	expression.erase(expression.begin());
	double exp1, exp2;
	switch(first_token){
		case Lexer::ZERO:
			return 0.0;
		case Lexer::X:
			return x;
		case Lexer::Y:
			return y;
		case Lexer::SIN:
			return std::sin(hardcoded_pi * recPixelCalculation(x, y, expression));
		case Lexer::COS:
			return std::cos(hardcoded_pi * recPixelCalculation(x, y, expression));
		case Lexer::OPEN_PAR:
			exp1 = recPixelCalculation(x, y, expression);
			exp2 = recPixelCalculation(x, y, expression);
			return exp1 * exp2;
		case Lexer::AVG:
			exp1 = recPixelCalculation(x, y, expression);
			exp2 = recPixelCalculation(x, y, expression);
			return (exp1 + exp2)/2;
		default:
			throw domain_error("wrong token in expression");	
	}
}


