#ifndef MARTIST_HPP_INCLUDED
#define MARTIST_HPP_INCLUDED

#include<istream>
#include<ostream>
#include<string>
#include<vector>
#include "parser.hpp"
typedef std::vector<Lexer::token> Exp;

class Martist{

    public:
        Martist(unsigned char* buffer, size_t width, size_t height, int rdepth, int gdepth, int bdepth);
        void redDepth(int depth);
        void greenDepth(int depth);
        void blueDepth(int depth);
        int redDepth() const;
        int greenDepth() const;
        int blueDepth() const;
        void seed(int seed);
        void changeBuffer(unsigned char* buffer, size_t width, size_t height);
        void paint();
        friend std::ostream& operator<<(std::ostream& output_stream, Martist& martist);
        friend std::istream& operator>>(std::istream& input_stream, Martist& martist);

    private:
    	int r_depth;
        int g_depth;
        int b_depth;
        size_t im_width;
        size_t im_height;        
        unsigned char* pixels_array;
        int seed_mood;
        std::string red;
        std::string green;
        std::string blue;
        bool expression_set;

        std::string expressionGenerator(int depth, int seed_mood);
        void recExpressionGenerator(int depth, std::string& expression);        
        double pixelCalculation(double x, double y, Exp expression);        
        double recPixelCalculation(double x, double y, Exp& expression);
        const double hardcoded_pi = 3.141592653589793238462643;        

};

#endif // MARTIST_HPP_INCLUDED
