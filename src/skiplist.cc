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
#include "skiplist.h"

#include <cstdlib>

skiplist::skiplist (int cap, double p) : level_(1), cap_(cap), p_(p), size_(0), header_(INT_MIN,0), nil_(INT_MAX,0) {
    max_level_ = 5; //TODO set max_level_ according to cap_
    for (int l=0; l < max_level_; l++){
        header_.forward_ptrs_.push_back(&nil_); 
    }
}

skiplist::~skiplist(){
    auto node = header_.forward_ptrs_[0]; 
    while (node != &nil_) {
        auto next = node->forward_ptrs_[0]; 
        delete node; 
        node = next; 
    }
}

std::pair<bool, int> skiplist::search (int key) {
    auto node = &header_; 
    for (int l = level_-1; l >= 0; l--){
        while (node->forward_ptrs_[l]->key_ < key) 
            node = node->forward_ptrs_[l]; 
    }
    node = node->forward_ptrs_[0]; 
    if (node->key_ == key)
        return {true, node->value_}; 
    return {false, 0}; 
}

bool skiplist::insert(int key, int value) {
    if (size_ == cap_)
        return false;
    auto node = &header_; 
    std::vector<skiplist_element*> to_be_updated (max_level_, nullptr);
    for (int l = level_-1; l >= 0; l--){
        while (node->forward_ptrs_[l]->key_ < key) 
            node = node->forward_ptrs_[l]; 
        to_be_updated[l] = node;
    }
    node = node->forward_ptrs_[0]; 
    if (node->key_ == key) {
        node->value_ = value; 
        return false;
    } else {
        int new_level = get_random_level();
        if (new_level > level_){
            for (int l = level_; l < new_level; l++){
                to_be_updated[l] = &header_;
            }
            level_ = new_level;
        }
        auto new_node = new skiplist_element(key, value); 
        for (int l=0; l < new_level; l++){
            new_node->forward_ptrs_.push_back(to_be_updated[l]->forward_ptrs_[l]); 
            to_be_updated[l]->forward_ptrs_[l] = new_node;
        }
        size_++;
        return true;
    }
}

bool skiplist::erase(int key) {
    auto node = &header_; 
    std::vector<skiplist_element*> to_be_updated (max_level_, nullptr);
    for (int l = level_-1; l >= 0; l--){
        while (node->forward_ptrs_[l]->key_ < key) 
            node = node->forward_ptrs_[l]; 
        to_be_updated[l] = node;
    }
    node = node->forward_ptrs_[0]; 
    if (node->key_ == key) {
        for (int l=0; l < level_; l++) {
            if (to_be_updated[l]->forward_ptrs_[l] != node) 
                break;
            to_be_updated[l]->forward_ptrs_[l] = node->forward_ptrs_[l];
        }
        delete node; 
        while (level_ > 1 && header_.forward_ptrs_[level_] == &nil_) 
            level_--; 
        size_--; 
        return true;
    }
    return false;
}

int skiplist::get_random_level(){
    int level = 1; 
    double random = ((double)rand()/RAND_MAX); 
    while (random < p_  && level < max_level_) {
        level++; 
        random = ((double)rand()/RAND_MAX); 
    }
    return level;
}