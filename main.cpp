#include <iostream>
#include <string>
#include "scheme_calculator.hpp"


int main(int argc, char* argv[])
{
    std::cout << "Welcome to scheme-calculator" << std::endl;
    std::string s;
    while (true)
    {
        std::cout << "> ";
        getline(std::cin, s);
        scheme::SchemeValue* exp = scheme::read(s);
        scheme::SchemeValue* result = scheme::calculator::eval(exp);
        if (result)
        {
            std::cout << scheme::calculator::get_eval_value(result) << std::endl;
            scheme::free_single_obj(result);
        }
        scheme::free_obj(exp);
        // std::cout << "new count: " << scheme::get_new_count() << std::endl;
        // std::cout << "free count: " << scheme::get_free_count() << std::endl;
    }
    return 0;
}
