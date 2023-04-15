/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 00:49:34 by odakhch           #+#    #+#             */
/*   Updated: 2023/04/15 00:49:35 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std:: cout << "Error" << std:: endl;
        return (-1);
    }
    try
    {
        float num;
        RPN RPL;

        num = RPL.calculate_rpn(av[1]);
        std:: cout << num << std:: endl;
    }
    catch(const std:: string& e)
    {
        std::cerr << e << std:: endl;
        return (-1);
    }
    return (0);
}
