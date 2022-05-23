#include "header.hpp"

int main(int argc, const char *argv[])
{
    int run = atoi(argv[1]);
    int dim = atoi(argv[2]);
    int fun_num = atoi(argv[3]);
    int pop_size = atoi(argv[4]);

    search_algorithm *search_alg;

    search_alg = new pso(pop_size);

    search_alg->init(run,
                     fun_num,
                     dim);
    search_alg->run_all();
    search_alg->output();
    return 0;
}