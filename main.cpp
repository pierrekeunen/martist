#include <iostream>
#include <sstream>
#include <utility>
#include <memory>
#include <cstdio>
#include "CImg.h"
#include "martist.hpp"
#include "parser.hpp"

using namespace cimg_library;


/*static string to_string(streamoff stroff)
{
    stringstream ss;
    ss << stroff;
    return ss.str();
}*/

int main(int argc, char** argv)
{
    size_t width = 1000;
    size_t height = 1000;
    int rdepth = 15;
    int gdepth = 15;
    int bdepth = 15;
    unsigned char buffer[width * height * 3];
    //std::shared_ptr<MathExpressions> math = std::make_shared<MathExpressions>();
    //MathExpressions math = MartistathExpressions();

    Martist m_artist(buffer, width, height, rdepth, gdepth, bdepth);
        
    std::string test_str = "red = (cos(pi * (x * y)) * avg(y, sin(pi * cos(pi * cos(pi * sin(pi * (x * avg(y, y)))))))) \n  green = (y * cos(pi * cos(pi * cos(pi * cos(pi * cos(pi * (sin(pi * x) * cos(pi * y)))))))) \n blue = sin(pi * ((y * y) * cos(pi * cos(pi * cos(pi * sin(pi * sin(pi * avg(x, y))))))))";

    //std::string test_str = "red = (cos(pi *(x * y)) * avg(y, sin(pi * cos(pi * cos(pi * sin(pi * (x * avg(y, y)))))))) \n green = (y * cos(pi * cos(pi * cos(pi * cos(pi * cos(pi * (sin(pi * x) * cos(pi * y)))))))) \n blue = sin(pi * ((y * y) * cos(pi * cos(pi * cos(pi * sin(pi * sin(pi * avg(x, y))))))))";
    std::istringstream test(test_str);
    std::cout << test_str << std::endl; 
    test >> m_artist;

    //m_artist.paint();
    //std::cout << m_artist;

    unsigned char new_buffer[width * height * 3];
    for(size_t i = 0; i < height; i++)
        for(size_t j = 0; j < width; j++)
    {
        new_buffer[i*width + j] = buffer[3*(i*width + j)];
        new_buffer[width*height + i*width + j] = buffer[3*(i*width + j) + 1];
        new_buffer[2*width*height + i*width + j] = buffer[3*(i*width + j) + 2];
    }

    CImg<unsigned char> img(new_buffer, width, height, 1, 3, false);
    CImgDisplay main_disp(img, "Martist");

    while(!main_disp.is_closed())
        main_disp.wait();

    return 0;
}







