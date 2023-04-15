/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 00:49:28 by odakhch           #+#    #+#             */
/*   Updated: 2023/04/15 00:49:30 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
