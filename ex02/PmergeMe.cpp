/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 00:49:51 by odakhch           #+#    #+#             */
/*   Updated: 2023/04/15 00:49:52 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe:: PmergeMe()
{
}

PmergeMe:: PmergeMe(const PmergeMe &copy): my_deque(copy.my_deque), my_list(copy.my_list)
{
}

PmergeMe &PmergeMe:: operator=(const PmergeMe &assign)
{
    (void) assign;
    return *this;
}

PmergeMe:: ~PmergeMe()
{
}

PmergeMe:: PmergeMe(int ac, char **av)
{
    long long check_num;
    int num;
    int i;
    std:: string value; 

    i = 1;
    while (i != ac)
    {
        if (strncmp(av[i], " ", 1) != 0)
        {
            value = av[i];
            if (!contains_only_number(value))
                throw std:: string("Error");
            check_num = std:: stoll(value);
            if (check_num > 2147483647)
                throw std:: string("Error");
            num = (int)check_num;
            this->my_deque.push_back(num);
            this->my_list.push_back(num);
        }
        i++;
    }
}

void PmergeMe:: display_list(void)
{
    clock_t start = clock();
    sort_numer_list(this->my_list);
    clock_t end = clock();
    double elapsed_time_list = double(end - start) / CLOCKS_PER_SEC * 1000000;
    std:: cout << "Time to process a range of   " << this->my_list.size() << " elements with std::list<int>  :  " << elapsed_time_list << " us" << std:: endl;
}

void PmergeMe:: sort_numer_list(std::list<int> &list)
{
    std:: list<int> left, right;
    std::list<int>::iterator it;

    if (list.size() <= 1)
        return ;
    std:: list<int> :: iterator middle = std::next(list.begin(), list.size() / 2);

    left.splice(left.begin(), list, list.begin(), middle);
    right.splice(right.begin(), list, middle, list.end());
    sort_numer_list(left);
    sort_numer_list(right);

    std::list<int>::iterator left_iter = left.begin();
    std::list<int>::iterator right_iter = right.begin();

    while (left_iter != left.end() && right_iter != right.end())
    {
        if (*left_iter < *right_iter)
        {
            list.push_back(*left_iter);
            ++left_iter;
        }
        else
        {
            list.push_back(*right_iter);
            ++right_iter;
        }
    }
    list.splice(list.end(), left, left_iter, left.end());
    list.splice(list.end(), right, right_iter, right.end());
}

void PmergeMe:: display_deque(void)
{
    std:: cout << "Before: ";
    for(size_t i = 0; i != this->my_deque.size(); i++)
        std:: cout << this->my_deque[i] << " ";
    clock_t start = clock();
    sort_numer_deque(this->my_deque);
    clock_t end = clock();
    double elapsed_time_deque = double(end - start) / CLOCKS_PER_SEC * 1000000;
    std:: cout << std:: endl << "After:  ";
    for(size_t i = 0; i != this->my_deque.size(); i++)
        std:: cout << this->my_deque[i] << " ";
    std:: cout << std:: endl << "Time to process a range of   " << this->my_deque.size() << " elements with std::deque<int> :  " << elapsed_time_deque << " us" << std:: endl;
}

void PmergeMe:: sort_numer_deque(std::deque<int> &deque)
{
    size_t middle;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    std:: deque<int> left, right;
    if (deque.size() <= 1)
        return ;
    middle = deque.size() / 2;
    for (size_t i = 0; i < middle; i++)
        left.push_back(deque[i]);
    for (size_t i = middle; i < deque.size(); i++)
        right.push_back(deque[i]);
    sort_numer_deque(left);
    sort_numer_deque(right);

    while (i < left.size() && j < right.size())
    {
        if (left[i] < right[j])
            deque[k++] = left[i++];
        else
            deque[k++] = right[j++];
    }
    while (i < left.size())
        deque[k++] = left[i++];
    while (j < right.size())
        deque[k++] = right[j++];
}

bool PmergeMe:: contains_only_number(std:: string &str)
{
    for (size_t i = 0; i != str.size(); i++)
    {
        if (!isdigit(str[i]))
            return (false);
    }
    return (true);
}
