/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:52:43 by iel-ghou          #+#    #+#             */
/*   Updated: 2026/06/13 16:33:37 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

# include <iostream>
# include <stack>
# include <cstdlib>
# include <cctype>

class RPN{
    private:
        std::stack<int> _stack;
    public:
        RPN();
        RPN(const RPN &other);
        RPN	&operator=(const RPN &other);
        ~RPN();

        void evaluate(const std::string &expression);
         
};

#endif