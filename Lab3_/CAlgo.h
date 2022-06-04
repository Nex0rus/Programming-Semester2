#pragma once
#include <functional>
#include <iterator>
#include <concepts>


template<std::input_iterator InputIterator, class UnaryPredicate>
bool all_of(InputIterator first, InputIterator last, UnaryPredicate p)
{
    if (first == last)
    {
        return false;
    }
    for (; first != last; ++first)
    {
        if (!p(*first))
        {
            return false;
        }
    }

    return true;
}


template<std::input_iterator InputIterator, class UnaryPredicate>
bool any_of(InputIterator first, InputIterator last, UnaryPredicate p)
{
    for (; first != last; ++first)
    {
        if (p(*first))
        {
            return true;
        }
    }

    return false;
}


template<std::input_iterator InputIterator, class UnaryPredicate>
bool none_of(InputIterator first, InputIterator last, UnaryPredicate p)
{
    for (; first != last; ++first)
    {
        if (p(*first))
        {
            return false;
        }
    }

    return true;
}

template<std::input_iterator InputIterator, class UnaryPredicate>
bool one_of(InputIterator first, InputIterator last, UnaryPredicate p)
{
    if (first == last)
    {
        return false;
    }
    bool flag = false;
    for (; first != last; ++first)
    {
        if (p(*first))
        {
            if (!flag)
            {
                flag = true;
            }

            else
            {
                return false;
            }
        }
    }

    return true;
}

template<std::forward_iterator ForwardIterator, class Compare=std::less<>>
bool is_sorted(ForwardIterator first, ForwardIterator last, Compare comp = Compare{})
{
    ForwardIterator next = first++;
    while(first != last)
    {
        if (!comp(*next, *first))
        {
            return false;
        }
        ++next;
        ++first;
    }
    return true;

}


template<std::input_iterator InputIterator, class UnaryPredicate>
InputIterator find_not(InputIterator first, InputIterator last, UnaryPredicate p)
{
    for (; first != last; ++first)
    {
        if (!p(*first))
        {
            return first;
        }
    }

    return last;
}


template<std::forward_iterator ForwardIterator, class UnaryPredicate>
bool is_partitioned(ForwardIterator first, ForwardIterator last, UnaryPredicate p)
{
    ForwardIterator partitioner = find_not(first, last, p);
    if (partitioner == last)
    {
        return true;
    }
    ++partitioner;
    for (; partitioner != last; ++partitioner)
    {
        if (p(*partitioner))
        {
            return false;
        }
    }

    return true;
}

template<std::bidirectional_iterator BidirectionalIterator, class UnaryPredicate>
BidirectionalIterator find_backward(BidirectionalIterator first, BidirectionalIterator last, UnaryPredicate p)
{
    BidirectionalIterator res = last;
    --last;
    while (last != first)
    {
        if (p(*last)) 
        {
            return last;
        }
        --last;
    }

    return res;
}

template<std::bidirectional_iterator BidirectionalIterator, class UnaryPredicate>
bool is_palindrome(BidirectionalIterator first, BidirectionalIterator last, UnaryPredicate p)
{
    --last;
    while (first != last && last - first != 1)
    {
        if (p(*first) != p(*last))
        {
            return false;
        }
        ++first;
        --last;
    }

    if (p(*first) != p(*last)) 
    {
        return false;
    }

    return true;
}
