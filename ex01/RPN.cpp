/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:52:46 by iel-ghou          #+#    #+#             */
/*   Updated: 2026/06/16 19:00:26 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(){}
RPN::RPN(const RPN &other): _stack(other._stack){}
RPN	&RPN::operator=(const RPN &other){
    if(this != &other)
        _stack = other._stack;
    return (* this);
}
RPN::~RPN(){}

void RPN::evaluate(const std::string &expression)
{
    for (size_t i = 0; i < expression.length(); i++)
    {
        char c = expression[i];

        if (c == ' ')
            continue;

        if (std::isdigit(c))
            _stack.push(c - '0');
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            if (_stack.size() < 2)
            {
                std::cerr << "Error" << std::endl;
                return;
            }

            int b = _stack.top();
            _stack.pop();
            int a = _stack.top();
            _stack.pop();

            int result;
            switch (c)
            {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    if (b == 0)
                    {
                        std::cerr << "Error: division by zero" << std::endl;
                        return;
                    }
                    result = a / b;
                    break;
                default:
                    return;
            }
            _stack.push(result);
        }
        else
        {
            std::cerr << "Error" << std::endl;
            return;
        }
    }
    if (_stack.size() != 1)
    {
        std::cerr << "Error" << std::endl;
        return;
    }
    std::cout << _stack.top() << std::endl;
}
