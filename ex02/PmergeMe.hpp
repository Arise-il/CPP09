/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:48:18 by iel-ghou          #+#    #+#             */
/*   Updated: 2026/06/16 19:13:04 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>

# include <iostream>
# include <sstream>
# include <stdexcept>
# include <ctime>
# include <algorithm>
# include <climits>
# include <iomanip>

class PmergeMe
{
    private:
        std::vector<int> _vec;
        std::deque<int>  _deq;

        void            sortVector();
        void            sortDeque();

        // Ford-Johnson helpers for vector
        void            mergeInsertVector(std::vector<int> &arr);
        void            insertionSortVector(std::vector<int> &arr, int val);

        // Ford-Johnson helpers for deque
        void            mergeInsertDeque(std::deque<int> &arr);
        void            insertionSortDeque(std::deque<int> &arr, int val);

        std::vector<size_t> buildJacobsthalOrder(size_t size);
        

    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void    parse(const std::string &input);
        bool    verifyVector() const;
        bool    verifyDeque() const;
};

#endif