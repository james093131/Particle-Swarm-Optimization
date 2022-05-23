#include "header.hpp"
pso ::pso(int pop_size)
{

    this->pop_size = pop_size;
};
void pso::run()
{
    std::cout << scientific << setprecision(8);
    std::random_device rd;
    generator.seed(seed);

    for (int i = 0; i < num_runs; i++)
    {
        init();
        while (nfes < max_nfes)
        {
            transition();

            // evaluation
            for (size_t i = 0; i < particle.size(); i++)
            {
                particle[i].sol.fitness = search_algorithm::evaluation(particle[i].sol.position);

                if (particle[i].sol.fitness < particle[i].p_best.fitness)
                {
                    particle[i].p_best = particle[i].sol;

                    if (particle[i].sol.fitness < global_best.sol.fitness)
                        global_best.sol = particle[i].sol;
                }
            }
            cout << nfes << ' ' << global_best.sol.fitness << endl;
        }
        final_fitness = global_best.sol.fitness;
    }
}

void pso::init()
{
    nfes = 0;
    // structure
    particle.assign(pop_size, Particle{
                                  .sol = Solution{.position = v1d<double>(dim, 0), .fitness = 0.0},
                                  .p_best = Solution{.position = v1d<double>(dim, 0), .fitness = 0.0},
                                  .velocity = v1d<double>(dim, 0)});

    parameter.w = 0.729844;
    parameter.c1 = 1.496180;
    parameter.c2 = 1.496180;
    global_best.sol = Solution{.position = v1d<double>(dim, 0), .fitness = DBL_MAX};
    for (int i = 0; i < pop_size; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            particle[i].sol.position[j] = uniform(generator) * (max - min) + min;
        }
        particle[i].sol.fitness = search_algorithm::evaluation(particle[i].sol.position);
        particle[i].p_best = particle[i].sol;

        if (particle[i].sol.fitness < global_best.sol.fitness)
            global_best.sol = particle[i].sol;
    }
}

void pso::transition()
{
    for (size_t i = 0; i < particle.size(); i++)
    {
        for (int j = 0; j < dim; j++)
        {
            double r1 = uniform(generator);
            double r2 = uniform(generator);
            particle[i].velocity[j] = parameter.w * particle[i].velocity[j] +
                                      parameter.c1 * r1 * (particle[i].p_best.position[j] - particle[i].sol.position[j]) +
                                      parameter.c2 * r2 * (global_best.sol.position[j] - particle[i].sol.position[j]);

            particle[i].sol.position[j] += particle[i].velocity[j];
            if (particle[i].sol.position[j] > max)
                particle[i].sol.position[j] = max;
            if (particle[i].sol.position[j] < min)
                particle[i].sol.position[j] = min;
        }
    }
}
