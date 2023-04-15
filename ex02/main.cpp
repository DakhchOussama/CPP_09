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