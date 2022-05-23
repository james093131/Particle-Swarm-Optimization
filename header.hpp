#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include <random>
#include <iomanip>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
using v1d = vector<T>;
template <typename T>
using v2d = vector<vector<T>>;
template <typename T>
using v3d = vector<vector<vector<T>>>;

struct Solution
{
    v1d<double> position;
    double fitness;
};
class search_algorithm
{
public:
    virtual void run() = 0;

    double max;
    double min;
    double final_fitness;
    int dim;
    int nfes;     // evaluations
    int max_nfes; // max evaluations
    int num_runs;
    int func_num;
    int cur_run;
    v1d<double> run_result;
    v1d<int> run_eva;

    unsigned seed;
    std::mt19937_64 generator;
    std::uniform_real_distribution<double> uniform;

    // function
    void init(int num_runs, int func_num, int dim);
    double evaluation(v1d<double> sol);
    void run_all();
    void output();
};

class pso : public search_algorithm
{
public:
    virtual void run();
    pso(int pop_size);

private:
    int pop_size;

    struct Particle
    {
        Solution sol;
        Solution p_best;
        v1d<double> velocity;
    };
    struct Global_best
    {
        Solution sol;
    };
    struct Parameter
    {
        double w, c1, c2;
    };
    v1d<Particle> particle;
    Parameter parameter;
    Global_best global_best;
    void init();
    void transition();
};

#endif
