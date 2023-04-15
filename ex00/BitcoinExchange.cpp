#include "BitcoinExchange.hpp"

BitcoinExchange:: BitcoinExchange()
{
}

BitcoinExchange:: ~BitcoinExchange()
{
}

BitcoinExchange:: BitcoinExchange(const BitcoinExchange &copy): data(copy.data), bitcoin_data(copy.bitcoin_data), input_data(copy.input_data)
{
}

BitcoinExchange &BitcoinExchange:: operator=(const BitcoinExchange &assign)
{
    if (this != &assign)
    {
        this->data = assign.data;
        this->bitcoin_data = assign.bitcoin_data;
        this->input_data = assign.input_data;
    }
    return *this;
}

void BitcoinExchange:: parse_input(std:: string my_input)
{
    std:: ifstream input_file;
    std:: string line;
    

    if (my_input == "data.csv")
        throw std:: string("Another file other than data.csv");
    input_file.open(my_input);
    if (input_file.is_open()) 
    {
        std:: string line;
        while (std:: getline(input_file, line, '\n'))
        {
            if (check_all_space(line))
                this->data.push_back(line);
        }
        input_file.close();
    }
    else
        throw std:: string("No file to read");
    input_file.close();
    if (this->data.size() == 0)
        throw std:: string("No data to read");
    if (this->data[0].find("date") != std:: string:: npos && this->data[0].find("|") != std:: string:: npos && this->data[0].find("value") != std:: string:: npos)
    {
        for (size_t i = 0; i != this->data.size(); i++)
            this->input_data.push_back(std:: make_pair(parse_date(this->data[i]), parse_value(this->data[i])));
    }
    else
        throw std:: string("No data found");
}

bool BitcoinExchange:: check_all_space(std:: string line)
{
    bool all_spaces = true;
    for (size_t i = 0; i != line.size(); i++)
    {
        if (!std:: isspace(line[i]))
        {
            all_spaces = false;
            break;
        }
    }
    if (all_spaces)
        return false;
    else
        return true;
}

std:: string BitcoinExchange:: parse_value(std:: string line)
{
    std:: string pipe;
    std:: string value;
    int found_pipe;
    std:: string error_message; 

    found_pipe = 0;
    for (size_t i = 0; i != line.size(); i++)
    {
        if (line[i] == '|')
            found_pipe = i;
    }
    for (size_t i = found_pipe + 1; i != line.size(); i++)
    {
        if (line[i] != ' ')
            value += line[i];
    }
    if (value.size() == 0)
    {
        error_message = "Error: bad input => ";
        return (error_message);
    }
    return (value);
}

std:: string BitcoinExchange:: parse_date(std:: string line)
{
    std:: string pipe;
    std:: string date;
    std:: string error_message; 
    int found_pipe;
    int count;

    found_pipe = 0;
    count = 0;
    for (size_t i = 0; i != line.size(); i++)
    {
        if (line[i] == '|')
        {
            found_pipe = i;
            ++count;
        }
    }
    if (count != 1)
    {
        error_message = "Error: bad input => " + line;
        return (error_message);
    }
    for (int i = 0; i != found_pipe - 1; i++)
        date += line[i];
    if (date.find(" ") != std:: string:: npos)
    {
        size_t first = date.find_first_not_of(" ");
        size_t last = date.find_last_not_of(" ");
        date = date.substr(first, last - first + 1);
        if (date.find(" ") != std:: string:: npos)
        {
            error_message = "Error: bad input => " + date;
            return (error_message);
        }
    }
    if (date != "date")
       date = check_year_month_day(date);
    return (date);
}

std:: string BitcoinExchange:: check_year_month_day(std:: string date)
{
    int found_hyphen;
    std:: string year;
    std:: string month;
    std:: string day;
    int conver_day;
    int conver_month;
    int conver_year;
    size_t j;

    found_hyphen = 0;
    j = 0;
    for (size_t i = 0; i != date.size(); i++)
    {
        if (date[i] == '-')
        {
            ++found_hyphen;
            if (found_hyphen == 1)
            {
                for (; j != i; j++)
                    year += date[j];
            }
            else if (found_hyphen == 2)
            {
                j++;
                for (; j != i; j++)
                    month += date[j];
            }
        }
    }
    j++;
    for (; j != date.size(); j++)
        day += date[j];
    if (found_hyphen != 2)
        return std::string("Error: bad input => " + date);
    if (day.size() != 2 || year.size() != 4 || month.size() != 2)
        return std::string("Error: bad input => " + date);
    try
    {
        conver_day = std:: stoi(day);
        conver_month = std:: stoi(month);
        conver_year = std:: stoi(year);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std:: exit(1);
    }
    if (conver_day <= 0 || conver_month <= 0 || conver_year <= 0 || conver_day > 31)
        return std::string("Error: bad input => " + date);
    if (!is_month_valid(conver_day, conver_year, conver_month))
        return std::string("Error: bad input => " + date);
    return date;
}

bool BitcoinExchange:: is_month_valid(int day, int year, int month)
{
    if (month < 1 || month > 12)
        return false;
    else if (month == 2)
    {
        if (isleapYear(year))
        {
            if (day <= 29)
                return true;
            return false;
        }
        else
        {
            if (day <= 28)
                return true; 
            return false;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
            return false;
        return true;
    }
    else
    {
        if (day > 31)
            return false;
        return true;
    }
}

bool BitcoinExchange:: isleapYear(int year)
{
    // Gregorian calendar
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else
        return false;
}

void BitcoinExchange:: parse_data(std:: string input)
{
    std:: ifstream input_file;
    std:: string line;
    std:: string date;
    std:: vector<std:: string> v_input;

    input_file.open(input);
    if (input_file.is_open()) 
    {
        std:: string line;
        while (std:: getline(input_file, line, '\n'))
            v_input.push_back(line);
        input_file.close();
    }
    else
        throw std:: string("No data to read");
    for (size_t i = 1; i != v_input.size(); i++)
        this->bitcoin_data.insert(std:: make_pair(parse_date_map(v_input[i]), parse_exchange_rate(v_input[i])));
}

float BitcoinExchange:: parse_exchange_rate(std:: string input)
{
    size_t position;
    std:: string num;
    float convert_int;

    position = 0;
    for (size_t i = 0; i != input.size(); i++)
    {
        if (input[i] == ',')
            position = i;
    }
    for (size_t i = position + 1; i != input.size(); i++)
            num += input[i];
    convert_int = std:: atof(num.c_str());
    return (convert_int);
}

std:: string BitcoinExchange:: parse_date_map(std:: string input)
{
    int position;
    std:: string date;
     for (size_t i = 0; i != input.size(); i++)
    {
        if (input[i] == ',')
            position = i;
    }
    for (int i = 0; i != position; i++)
            date += input[i];
    return (date);
}

void BitcoinExchange:: compare_return_input(void)
{
    float key;
    float value;
    std:: string str;
    std:: string date;
    std:: string date_dbs;
    float new_value;
    std:: multimap<std:: string, float>:: iterator it2;

    
    for (size_t i = 1; i < this->input_data.size(); i++)
    {
        date = this->input_data[i].first;
        str = this->input_data[i].second;
        if (str.find("Error") != std:: string:: npos)
        {
            std:: cout << str << date << std:: endl;
            continue;
        }
        if (!contains_only_number(str))
        {
            std:: cout << "Error: bad input => " << str << std:: endl;
            continue;
        }
        if (date.find("Error") != std:: string:: npos)
        {
            std:: cout << date << std:: endl;
            continue;
        }
        key = std::stof(str);
        if (key < 0 || key > 100)
        {
            if (key < 0)
            {
                std:: cout << "Error: not a positive number." << std:: endl;
                continue;
            }
            if (key > 100)
            {
                std:: cout << "Error: too large a number." << std:: endl; //? when you check espace between dat
                continue;
            }
        }
        else
        {
            for (it2 = this->bitcoin_data.begin(); it2 != this->bitcoin_data.end(); it2++)
            {
                date_dbs = it2->first;
                value = it2->second;
                if (date_dbs == date)
                {
                    new_value = value * key;
                    std:: cout << date << " => " << key << " = " << new_value << std:: endl;
                    break;
                }
                else if (date_dbs > date)
                {
                    std::map<std::string, float>::iterator it_lb = this->bitcoin_data.lower_bound(date);
                    if (it_lb != this->bitcoin_data.end())
                    {
                       date_dbs = it_lb->first;
                       value = it_lb->second;
                       new_value = value * key;
                       std:: cout << date << " => " << key << " = " << new_value << std:: endl;
                       break;
                    }
                }
            }
        }
    }
}

bool BitcoinExchange:: contains_only_number(std:: string &str)
{
    for (size_t i = 0; i != str.size(); i++)
    {
        if (!isdigit(str[i]))
        {
            if (str[i] == '.' || str[i] == '-')
                continue;
            return (false);
        }
    }
    return (true);
}