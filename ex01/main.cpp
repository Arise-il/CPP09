/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:52:41 by iel-ghou          #+#    #+#             */
/*   Updated: 2026/06/13 16:32:46 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RPN.hpp"
#include <fstream>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "ONE ARGUMENT PLS !!!!!" << std::endl;
        return (1);
    }

    RPN rpn;
    rpn.evaluate(argv[1]);
    return 0;
    
}