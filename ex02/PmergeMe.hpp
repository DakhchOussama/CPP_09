#include <iostream>
#include <deque>
#include <list>

class PmergeMe
{
private:
    std::deque<int> my_deque;
    std:: list<int> my_list; 
public:
    PmergeMe();
    PmergeMe(int ac, char **av);
    PmergeMe(const PmergeMe &copy);
    PmergeMe & operator=(const PmergeMe &assign);
    ~PmergeMe();
    void display_deque(void);
    void display_list(void);
    void sort_numer_deque(std::deque<int> &deque);
    void sort_numer_list(std::list<int> &list);
    bool contains_only_number(std:: string &str);
};