/**
MIT License

Copyright (c) 2021 Mohammad Roohitavaf

www.mydistributed.systems
https://github.com/roohitavaf

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _SKIPLIST_SRC_SKIPLIST_H_
#define _SKIPLIST_SRC_SKIPLIST_H_

#include <vector>

struct skiplist_element
{ //TODO: make it template class
    int key_;
    int value_;
    std::vector<skiplist_element *> forward_ptrs_; //TODO: change it to use array and std::unique_ptr
    skiplist_element (int key, int value) : key_(key), value_(value) {}
};

class skiplist
{ //TODO: make it template class
private:
    int level_;
    int cap_;
    int max_level_;
    double p_;
    int size_;
    skiplist_element header_;
    skiplist_element nil_;

    int get_random_level();

public:
    skiplist(int cap, double p = 0.25);
    ~skiplist();
    std::pair<bool, int> search(int key); //TODO: change it to use std::optional.
    
    /**
     * @return true if it adds a new element. 
     * If it does not add a new element due to either capacity or existence of the element, it return false.
    */
    bool insert(int key, int value);
    bool erase(int key);
};
#endif //_SKIPLIST_SRC_SKIPLIST_H_