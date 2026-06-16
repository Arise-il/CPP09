/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 16:28:23 by iel-ghou          #+#    #+#             */
/*   Updated: 2026/06/11 18:00:54 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    fill_data_base("data.csv");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
: _data_base(other._data_base){}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        _data_base = other._data_base;
    return *this;
}

BitcoinExchange::~BitcoinExchange(){}

std::string BitcoinExchange::trim(const std::string &s)
{
    size_t start = s.find_first_not_of(" \t");
    if (start == std::string::npos)
        return "";

    size_t end = s.find_last_not_of(" \t");
    return s.substr(start, end - start + 1);
}

bool BitcoinExchange::isValidNumber(const std::string &s, double &out)
{
    char *end;
    out = std::strtod(s.c_str(), &end);

    if (*end != '\0')
        return false;

    return true;
}

void BitcoinExchange::fill_data_base(const std::string &file_name)
{
    std::ifstream file(file_name.c_str());
    if (!file.is_open())
    {
        std::cout << "Error: could not open database file" << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty() || line == "date,exchange_rate")
            continue;

        size_t pos = line.find(',');
        if (pos == std::string::npos)
            continue;

        std::string date = trim(line.substr(0, pos));
        std::string value_str = trim(line.substr(pos + 1));

        if (date.empty() || value_str.empty())
            continue;

        double value;
        if (!isValidNumber(value_str, value))
            continue;

        _data_base[date] = value;
    }
}

void BitcoinExchange::process_file(const std::string &file_name)
{
    std::ifstream file(file_name.c_str());
    if (!file.is_open())
    {
        std::cout << "Error: could not open file" << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty() || line == "date | value")
            continue;

        size_t pos = line.find('|');
        if (pos == std::string::npos)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = trim(line.substr(0, pos));
        std::string value_str = trim(line.substr(pos + 1));

        if (date.empty() || value_str.empty())
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        double value;
        if (!isValidNumber(value_str, value))
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        if (value < 0)
        {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }

        if (value > 1000)
        {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }

        /* ===== Find closest lower date ===== */

        std::map<std::string, double>::iterator it = _data_base.lower_bound(date);

        if (it == _data_base.begin() && it->first != date)
        {
            std::cout << "Error: no valid date for " << date << std::endl;
            continue;
        }

        if (it == _data_base.end() || it->first != date)
            --it;

        double result = it->second * value;

        std::cout << date << " => " << value
                  << " = " << result << std::endl;
    }
}