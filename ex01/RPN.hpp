#include <iostream>
#include <stack>
#include <sstream>

class RPN
{
private:
    std:: stack<float> my_stack;
public:
    RPN();
    RPN(const RPN &copy);
    RPN & operator=(const RPN &assign);
    ~RPN();
    float calculate_rpn(std:: string input);
    bool is_operator(char c);
    bool is_number(char c);
}; 