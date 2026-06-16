/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:52:44 by iel-ghou          #+#    #+#             */
/*   Updated: 2026/06/16 19:16:38 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
    : _vec(other._vec), _deq(other._deq) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

std::vector<size_t> PmergeMe::buildJacobsthalOrder(size_t size)
{
    std::vector<size_t> order;

    if (size == 0)
        return order;

    std::vector<bool> used(size, false);

    // First Jacobsthal numbers
    std::vector<size_t> jacob;
    jacob.push_back(1);

    size_t prev2 = 0;
    size_t prev1 = 1;

    while (true)
    {
        size_t next = prev1 + 2 * prev2;

        if (next >= size)
            break;

        jacob.push_back(next);

        prev2 = prev1;
        prev1 = next;
    }

    // Add Jacobsthal positions
    for (size_t i = 0; i < jacob.size(); i++)
    {
        if (!used[jacob[i]])
        {
            order.push_back(jacob[i]);
            used[jacob[i]] = true;
        }
    }

    // Add remaining positions
    for (size_t i = 0; i < size; i++)
    {
        if (!used[i])
            order.push_back(i);
    }

    return order;
}

void PmergeMe::insertionSortVector(std::vector<int> &arr, int val)
{
    int low = 0;
    int high = static_cast<int>(arr.size());

    while (low < high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] < val)
            low = mid + 1;
        else
            high = mid;
    }
    arr.insert(arr.begin() + low, val);
}

void PmergeMe::insertionSortDeque(std::deque<int> &arr, int val)
{
    int low = 0;
    int high = static_cast<int>(arr.size());

    while (low < high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] < val)
            low = mid + 1;
        else
            high = mid;
    }
    arr.insert(arr.begin() + low, val);
}

void PmergeMe::mergeInsertVector(std::vector<int> &arr)
{
    if (arr.size() <= 1)
        return;
    if (arr.size() == 2)
    {
        if (arr[0] > arr[1])
            std::swap(arr[0], arr[1]);
        return;
    }

    // 1. Pair up elements; keep track of the straggler
    bool hasStraggler = (arr.size() % 2 != 0);
    int  straggler    = hasStraggler ? arr.back() : 0;

    // 2. Sort each pair so the larger is first
    for (size_t i = 0; i + 1 < arr.size() - (hasStraggler ? 1 : 0); i += 2)
        if (arr[i] > arr[i + 1])
            std::swap(arr[i], arr[i + 1]);

    // 3. Recursively sort the sequence of larger elements
    std::vector<int> smaller;
    for (size_t i = 0; i + 1 < arr.size() - (hasStraggler ? 1 : 0); i += 2)
        smaller.push_back(arr[i]);

    std::vector<int> larger;
    for (size_t i = 1; i < arr.size() - (hasStraggler ? 1 : 0); i += 2)
        larger.push_back(arr[i]);

    mergeInsertVector(larger);

    // 4. Build sorted chain: start with first smaller (paired with smallest
    //    larger) then all larger elements, then insert rest via binary search
    std::vector<int> sorted = larger;
    std::vector<size_t> order = buildJacobsthalOrder(smaller.size());

    for (size_t i = 0; i < order.size(); ++i)
        insertionSortVector(sorted, smaller[order[i]]);

    if (hasStraggler)
        insertionSortVector(sorted, straggler);

    arr = sorted;
}

void PmergeMe::mergeInsertDeque(std::deque<int> &arr)
{
    if (arr.size() <= 1)
        return;
    if (arr.size() == 2)
    {
        if (arr[0] > arr[1])
            std::swap(arr[0], arr[1]);
        return;
    }

    bool hasStraggler = (arr.size() % 2 != 0);
    int  straggler    = hasStraggler ? arr.back() : 0;

    for (size_t i = 0; i + 1 < arr.size() - (hasStraggler ? 1 : 0); i += 2)
        if (arr[i] > arr[i + 1])
            std::swap(arr[i], arr[i + 1]);

    std::deque<int> smaller;
    for (size_t i = 0; i + 1 < arr.size() - (hasStraggler ? 1 : 0); i += 2)
        smaller.push_back(arr[i]);

    std::deque<int>  larger;
    for (size_t i = 1; i < arr.size() - (hasStraggler ? 1 : 0); i += 2)
        larger.push_back(arr[i]);

    mergeInsertDeque(larger);

    std::deque<int> sorted = larger;
    std::vector<size_t> order = buildJacobsthalOrder(smaller.size());

    for (size_t i = 0; i < order.size(); ++i)
        insertionSortDeque(sorted, smaller[order[i]]);

    if (hasStraggler)
        insertionSortDeque(sorted, straggler);

    arr = sorted;
}

void PmergeMe::sortVector()
{
    std::clock_t start = std::clock();
    mergeInsertVector(_vec);
    std::clock_t end = std::clock();

    double elapsed = static_cast<double>(end - start) /
                     CLOCKS_PER_SEC * 1000000.0;

    std::cout << "After:  ";
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : "
              << std::fixed << std::setprecision(5)
              << elapsed << " us" << std::endl;
}
#include <sys/time.h>
void PmergeMe::sortDeque()
{
    std::clock_t start = std::clock();
    mergeInsertDeque(_deq);
    std::clock_t end = std::clock();

    double elapsed = static_cast<double>(end - start) /
                     CLOCKS_PER_SEC * 1000000.0;

    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : "
              << std::fixed << std::setprecision(5)
              << elapsed << " us" << std::endl;
}

bool PmergeMe::verifyVector() const
{
    for (size_t i = 1; i < _vec.size(); ++i)
        if (_vec[i] < _vec[i - 1])
            return false;
    return true;
}

bool PmergeMe::verifyDeque() const
{
    for (size_t i = 1; i < _deq.size(); ++i)
        if (_deq[i] < _deq[i - 1])
            return false;
    return true;
}

void PmergeMe::parse(const std::string &input)
{
    std::istringstream ss(input);
    std::string        token;

    while (ss >> token)
    {
        for (size_t i = 0; i < token.size(); ++i)
            if (!std::isdigit(static_cast<unsigned char>(token[i])))
                throw std::invalid_argument("Error: non-numeric input: " + token);

        std::istringstream ns(token);
        long val;
        ns >> val;
        if (val < 0 || val > INT_MAX)
            throw std::invalid_argument("Error: negative number or large number bigger then int_max");

        _vec.push_back(val);
        _deq.push_back(val);
    }

    if (_vec.empty())
        throw std::invalid_argument("Error: empty input");

    std::cout << "Before: ";
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;

    sortVector();
    sortDeque();

    std::cout << "Vector sorted correctly: " << (verifyVector() ? "OK" : "KO") << std::endl;
    std::cout << "Deque  sorted correctly: " << (verifyDeque()  ? "OK" : "KO") << std::endl;
}