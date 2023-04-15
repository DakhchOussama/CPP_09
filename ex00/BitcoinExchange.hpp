/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 00:47:53 by odakhch           #+#    #+#             */
/*   Updated: 2023/04/15 00:47:55 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


class BitcoinExchange
{
private:
   std:: vector<std:: string> data;
   std:: multimap<std:: string, float, std:: greater<std:: string> > bitcoin_data;
   std:: vector<std:: pair<std:: string, std:: string> > input_data;
public:

    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &copy);
    BitcoinExchange & operator=(const BitcoinExchange &assign);
    ~BitcoinExchange();

    void parse_input(std:: string my_input);
    std:: string parse_date(std:: string line);
    std:: string check_year_month_day(std:: string date);
    bool isleapYear(int year);
    bool is_month_valid(int day, int year, int month);
    std:: string parse_value(std:: string line);
    void parse_data(std:: string input);
    float parse_exchange_rate(std:: string input);
    std:: string parse_date_map(std:: string input);
    void compare_return_input(void);
    bool check_all_space(std:: string line);
    bool contains_only_number(std:: string &str);

};
