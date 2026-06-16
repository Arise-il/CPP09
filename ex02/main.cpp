/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:33:52 by iel-ghou          #+#    #+#             */
/*   Updated: 2026/06/16 19:08:07 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PmergeMe.hpp"
#include <fstream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error: Please provide at least one argument!" << std::endl;
        return (1);
    }

    try
    {
        std::string combined_arg = argv[1];
        for (int i = 2; i < argc; ++i)
        {
            combined_arg += " ";
            combined_arg += argv[i];
        }
        PmergeMe vec;
        vec.parse(combined_arg);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }

    return 0;
}