/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 00:49:16 by odakhch           #+#    #+#             */
/*   Updated: 2023/04/15 00:49:20 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN:: RPN()
{
}

RPN:: ~RPN()
{
}

RPN:: RPN(const RPN &copy): my_stack(copy.my_stack)
{
}

RPN &RPN:: operator=(const RPN &assign)
{
    if (this != &assign)
    {
        this->my_stack = assign.my_stack;
    }
    return (*this);
}

float RPN:: calculate_rpn(std:: string input)
{
    float num = 0;
    int value = 0;
    float fvalue = 0;
    std:: string:: iterator it;

    for (it = input.begin(); it != input.end(); it++)
    {
        if (is_operator(*it) && this->my_stack.size() >= 2)
        {
            int operation_2 = this->my_stack.top();
            this->my_stack.pop();
            int operation_1 = this->my_stack.top();
            this->my_stack.pop();
            if (*it == '+')
                num = operation_1 + operation_2;
            else if (*it == '-')
                num = operation_1 - operation_2;
            else if (*it == '*')
                num = operation_1 * operation_2;
            else if (*it == '/')
            {
                if (operation_2 == 0)
                    throw std:: string("Error");
                num = operation_1 / operation_2;
            }
            this->my_stack.push(num);
        }
        else if (is_number(*it))
        {
            value = *it - '0';
            fvalue = (float)value;
            this->my_stack.push(fvalue);
        }
        else if (*it != ' ')
            throw std:: string("Error");
    }
    if (this->my_stack.size() != 1)
        throw std:: string("Error");
    return this->my_stack.top();
}

bool RPN:: is_number(char c)
{
    if (c >= '0' && c <= '9')
        return true;
    else
        return false;
}

bool RPN:: is_operator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return true;
    else
        return false;
}
