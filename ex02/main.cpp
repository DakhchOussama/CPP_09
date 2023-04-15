/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 00:50:03 by odakhch           #+#    #+#             */
/*   Updated: 2023/04/15 00:50:04 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    try
    {
        if (ac < 2)
            throw std:: string("No number");
        PmergeMe pre(ac, av);
        pre.display_deque();
        pre.display_list();
    }
    catch(std:: string &e)
    {
        std:: cout << e << std:: endl;
        return (-1);
    }
}
