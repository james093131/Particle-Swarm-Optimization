#include "normal.hpp"

int main(int argc, const char *argv[])
{
    int Run = atoi(argv[1]);
    int MAX_NFE = atoi(argv[2]);
    int Dim = atoi(argv[3]);
    int Pop = atoi(argv[4]);
    int Fun_num = atoi(argv[5]);

    PSO pso;
    pso.run(Run, Dim, Pop, MAX_NFE, Fun_num);
}