/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:52:46 by iel-ghou          #+#    #+#             */
/*   Updated: 2026/06/13 16:44:36 by iel-ghou         ###   ########.fr       */
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

// void RPN::parse_and_fill(const std::string &string){
//     std::string::size_type pos = string.find("(){},.");
//     if (pos != std::string::npos){
//         std::cerr << "found an invalid character !!" << std::endl;
//         return ;
//     }
//     for (int i = 0; string[i] != '\0' ; i++)
//     {
//         if (string[i] == ' ')
//             continue;
        
//         _nums.push_back(string[i]);
//     }
//     std::list<char> pure_numbers;
//     std::list<char> pure_operators;
//     for (std::list<char>::const_iterator it = _nums.begin(); it != _nums.end(); ++it) {
//         if (isdigit(*it))
//             pure_numbers.push_back(*it);
//         else
//             pure_operators.push_back(*it);
//     }
//     _nums.clear();
//     if (pure_numbers.empty() || pure_operators.size() != pure_numbers.size() - 1)
//     {
//         std::cerr << "either not enough number or operators." << std::endl;
//         return;
//     }
    
//     std::list<char>::iterator num_it = pure_numbers.begin();
//     std::list<char>::iterator op_it = pure_operators.begin();

//     while (num_it != pure_numbers.end())
//     {
//         _nums.push_back(*num_it);
//         num_it++;
//         if (op_it != pure_operators.end()) {
//             _nums.push_back(*op_it);
//             op_it++;
//         }   
//     }
// }
// void RPN::prossess(){
//     if (_nums.empty())
//     {
//         std::cerr << "Error: No expression to evaluate." << std::endl;
//         return ;
//     }
    
//     std::list<char>::iterator it = _nums.begin();
//     if (it == _nums.end())
//         return;
//     int result = *it - '0';
//     ++it;

//     while (it != _nums.end())
//     {
//         char op = *it;
//         ++it;

//         int next_num = *it - '0';
//         ++it;

//         switch (op)
//         {
//             case '+':
//                 result += next_num;
//                 break;
//             case '-':
//                 result -= next_num;
//                 break;
//             case '*':
//                 result *= next_num;
//                 break;
//             case '/':
//                 if (next_num == 0)
//                 {
//                     std::cerr << "Error: Division by zero!" << std::endl;
//                     return ;
//                 }
//                 result /= next_num;
//                 break;
//             default:
//                 std::cerr << "Invalid operator" << std::endl;
//                 return;
//         }
//     }
//     std::cout << result << std::endl;
// }