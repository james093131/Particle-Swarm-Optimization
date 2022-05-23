#include "header.hpp"
void testing_function(double *x, double *f, int DIM, int N, int func_num);
void set_range(double &max, double &min, int func_num, int dim);

void search_algorithm ::run_all()
{
    for (cur_run = 0; cur_run < num_runs; cur_run++)
    {
        srand(time(NULL));
        seed = rand();

        run();
        run_result[cur_run] = final_fitness;
    }
    // cout << "dimensions: " << dim << " function number: " << func_num << " finish." << endl;
}
void search_algorithm::init(int num_runs, int func_num, int dim)
{

    this->num_runs = num_runs;
    this->func_num = func_num;
    this->dim = dim;
    set_range(max, min, func_num, dim);

    max_nfes = dim * 10000;
    run_result.resize(num_runs);
    run_eva.resize(num_runs);

    // cout << "dimension: " << dim << " function number: " << func_num << " transformation : " << ben_num << endl;
}
double search_algorithm::evaluation(v1d<double> sol)
{

    double f = 0.0;
    testing_function(&sol[0], &f, dim, 1, func_num);
    nfes++;
    return f;
}

void search_algorithm::output()
{
    double avg_fitness = 0.0;
    double best_fitness = DBL_MAX;
    for (size_t i = 0; i < run_result.size(); i++)
    {
        avg_fitness += run_result[i];
        if (best_fitness > run_result[i])
            best_fitness = run_result[i];
    }

    cout << "Function Number : " << func_num << " Average Fitness : " << avg_fitness / num_runs << ' ' << "Best Fitness : " << best_fitness << endl;
}
