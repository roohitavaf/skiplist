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

#include "benchmark.h"
#include <math.h>

void effect_of_elements_num()
{
    std::cout << "effect_of_elements_num: \n";
    experiment_results_series ers;
    for (int n = 100; n <= 20000; n += 100)
    {
        experiment_params ep(n);
        auto er = do_experiment_skiplist(ep);
        ers.add(er);
    }
    std::cout << "skiplist: \n"
              << ers.to_string() << std::endl;
}

void skiplist_vs_linkedlist()
{
    std::cout << "skiplist_vs_linkedlist: \n";
    int start = 1000;
    int end = 20000;
    int step = 1000;

    experiment_results_series ers;
    for (int c = start; c <= end; c += step)
    {
        experiment_params ep(c);
        auto er = do_experiment_skiplist(ep);
        ers.add(er);
    }
    std::cout << "skiplist: \n"
              << ers.to_string() << std::endl;
    ers.clear();

    for (int c = start; c <= end; c += step)
    {
        experiment_params ep(c);
        ep.max_level = 1;
        auto er = do_experiment_skiplist(ep);
        ers.add(er);
    }
    std::cout << "linedlist: \n"
              << ers.to_string() << std::endl;
}

void effect_of_max_level()
{
    std::cout << "effect_of_max_level: \n";
    experiment_results_series ers;
    for (int l = 1; l <= 10; l += 1)
    {
        experiment_params ep(100000);
        ep.max_level = l;
        auto er = do_experiment_skiplist(ep);
        ers.add(er);
    }
    std::cout << "skiplist: \n"
              << ers.to_string() << std::endl;
}

void effect_of_p()
{
    std::cout << "effect_of_p: \n";
    experiment_results_series ers;
    for (double p = 0.05; p <= 0.8; p += 0.05)
    {
        experiment_params ep(100000, p);
        auto er = do_experiment_skiplist(ep);
        ers.add(er);
    }
    std::cout << "skiplist: \n"
              << ers.to_string() << std::endl;
}

void effect_of_locality()
{
    std::cout << "effect_of_locality: \n";
    int start = 1000;
    int end = 20000;
    int step = 1000;

    experiment_results_series ers;
    for (int n = start; n <= end; n += step)
    {
        experiment_params ep(n);
        auto er = do_experiment_skiplist(ep);
        ers.add(er);
    }
    std::cout << "skiplist (without locality): \n"
              << ers.to_string() << std::endl;

    ers.clear();
    for (int n = start; n <= end; n += step)
    {
        experiment_params ep(n);
        ep.locality = true;
        ep.k = 10;
        auto er = do_experiment_skiplist(ep);
        ers.add(er);
    }
    std::cout << "skiplist (with locality): \n"
              << ers.to_string() << std::endl;

    ers.clear();
    for (int n = start; n <= end; n += step)
    {
        experiment_params ep(n);
        ep.locality = true;
        ep.k = 10;
        ep.use_finger = true;
        auto er = do_experiment_skiplist(ep);
        ers.add(er);
    }
    std::cout << "skiplist (with locality & finger): \n"
              << ers.to_string() << std::endl;
}
void effect_of_finger()
{
    std::cout << "effect_of_finger: \n";
    int start = 1;
    int end = 10;
    int step = 1;
    int n = 500000;

    experiment_results_series ers;
    for (int k = start; k <= end; k += step)
    {
        experiment_params ep(n);
        ep.locality = true;
        ep.k = k;
        ep.use_finger = false;
        auto er = do_experiment_skiplist(ep);
        ers.add(er);
    }
    std::cout << "skiplist (without finger): \n"
              << ers.to_string() << std::endl;
    ers.clear();

    for (int k = start; k <= end; k += step)
    {
        experiment_params ep(n);
        ep.locality = true;
        ep.k = k;
        ep.use_finger = true;
        auto er = do_experiment_skiplist(ep);
        ers.add(er);
    }
    std::cout << "skiplist (with finger): \n"
              << ers.to_string() << std::endl;
}

void skip_list_vs_std_map()
{
    std::cout << "skip_list_vs_std_map: \n";
    experiment_results_series ers;
    for (int n = 100; n <= 20000; n += 100)
    {
        experiment_params ep(n);
        auto er = do_experiment_skiplist(ep);
        ers.add(er);
    }
    std::cout << "skiplist: \n"
              << ers.to_string() << std::endl;

    ers.clear();
    for (int n = 100; n <= 20000; n += 100)
    {
        experiment_params ep(n);
        auto er = do_experiment_map(ep);
        ers.add(er);
    }
    std::cout << "map: \n"
              << ers.to_string() << std::endl;
}
int main(int argc, char **argv)
{
    effect_of_elements_num();
    skiplist_vs_linkedlist();
    effect_of_max_level();
    effect_of_p();
    effect_of_locality();
    effect_of_finger();
    skip_list_vs_std_map();
    return 0;
}