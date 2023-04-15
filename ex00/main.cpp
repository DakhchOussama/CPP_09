#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std:: cout << "Error: could not open file." << std:: endl;
        return (-1);
    }
    try
    {
        BitcoinExchange bitcoin;
        bitcoin.parse_input(av[1]);
        bitcoin.parse_data("data.csv");
        bitcoin.compare_return_input();
    }
    catch(const std:: string& e)
    {
        std::cerr << "Error : " << e << std:: endl;
        return (-1);
    }
    return (0);
}