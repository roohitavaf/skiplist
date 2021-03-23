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
LIABILITY
*/
#include "skiplist.h"
#include <map>
#include<iostream>
#include<math.h>
#include<chrono>
#include<vector>
#include<string>

struct experiment_params
{
    int insert_num;
    int search_num;
    int erase_num;
    int max_level;
    double p;
    bool use_finger;
    bool locality; 
    int k; 

    experiment_params(int insert_num_, double p_ = 0.25) : insert_num(insert_num_), p(p_)
    {
        search_num = std::max(1,insert_num / 100);
        erase_num = std::max(1,insert_num / 100);
        max_level = std::max(1.0, ceil((double)log(insert_num) / log(1 / p)));
        use_finger = false;
        locality = false;
    }
};

struct experiment_results
{
    double avg_insert_us;
    double avg_search_us;
    double avg_erase_us;
    int max_ptrs_num;

    void print () {
        std::cout << "avg_insert_us: " << avg_insert_us << " avg_search_us: " \
         << avg_search_us << " avg_erase_us: " << avg_erase_us << " max_ptrs_num: " << max_ptrs_num << std::endl;
    }
};

struct experiment_results_series {
    std::vector<experiment_results> instances; 
    void add (experiment_results er) {
        instances.push_back(er);
    }
    void clear(){
        instances.clear();
    }

    std::string to_string() {
        std::string result = "avg_insert_us,avg_search_us,avg_erase_us,max_ptrs_num\n"; 
        for (auto& instance : instances) {
            result += std::to_string(instance.avg_insert_us) + "," + std::to_string(instance.avg_search_us) + \
            "," + std::to_string(instance.avg_erase_us) + "," + std::to_string(instance.max_ptrs_num) + "\n"; 
        }
        return result;
    }
};

experiment_results do_experiment_skiplist(experiment_params params)
{
    experiment_results er; 
    skiplist sk(params.insert_num, params.p, params.max_level);
    if (params.use_finger)
        sk.enable_finger();

    //insert
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i = 0; i < params.insert_num; i++)
    {
        sk.insert(i, i);
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count(); 
    er.avg_insert_us = (double)total/params.insert_num;
    er.max_ptrs_num = sk.get_max_ptrs_nums();

    //search
    begin = std::chrono::steady_clock::now();
    int key; 
    for (int i = 0; i < params.search_num; i++)
    {
        if (i==0 || !params.locality){
            double random = ((double)rand() / RAND_MAX);
            key = (int)(random * params.insert_num);
        }else {
            double random = ((double)rand() / RAND_MAX);
            int sign = (((double)rand() / RAND_MAX) < 0.5) ? 1 : -1 ;
            key = sign*((int)(random * params.k) + 1) +  key;
        }
        sk.search(key);
    }
    end = std::chrono::steady_clock::now();
    total = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count(); 
    er.avg_search_us = (double)total/params.search_num; 

    //erase
     begin = std::chrono::steady_clock::now();
    for (int i = 0; i < params.erase_num; i++)
    {
        double random = ((double)rand() / RAND_MAX);
        int key = (int)(random * params.insert_num);
        sk.erase(key);
    }
    end = std::chrono::steady_clock::now();
    total = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count(); 
    er.avg_erase_us = (double)total/params.erase_num; 
    return er;
}

// experiment_results do_experiment_map(experiment_params params)
// {
//     std::map<int, int> m;

//     //insert
//     for (int i = 0; i < params.insert_num; i++)
//     {
//         double random = ((double)rand() / RAND_MAX);
//         int key = (int)(random * params.insert_num);
//         m.insert(key, i);
//     }

//     //search
//     for (int i = 0; i < params.search_num; i++)
//     {
//         double random = ((double)rand() / RAND_MAX);
//         int key = (int)(random * params.insert_num);
//         m.find(key);
//     }

//     //erase
//     for (int i = 0; i < params.erase_num; i++)
//     {
//         double random = ((double)rand() / RAND_MAX);
//         int key = (int)(random * params.insert_num);
//         m.erase(key);
//     }

//     return {0, 0, 0};
// }