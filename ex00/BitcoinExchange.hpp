/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 16:10:46 by iel-ghou          #+#    #+#             */
/*   Updated: 2026/06/11 17:58:09 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <map>
# include <string>
# include <cstdlib>

class BitcoinExchange{
    private:
        std::map<std::string, double> _data_base;
        std::string trim(const std::string &s);
        bool isValidNumber(const std::string &s, double &out);
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange	&operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        void fill_data_base(const std::string &file_name);
        void process_file(const std::string &file_name);
         
};

#endif