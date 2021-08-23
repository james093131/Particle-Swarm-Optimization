#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <float.h>
#include <sys/stat.h>
#include <iomanip>
#include <random> /* 亂數函式庫 */
#include <ctime>
#include <functional>
#include "TestingFunction.cpp"

using namespace std;
typedef vector<char> c1d;
typedef vector<c1d> c2d;
typedef vector<c2d> c3d;
typedef vector<c3d> c4d;
typedef vector<int> i1d;
typedef vector<i1d> i2d;
typedef vector<i2d> i3d;
typedef vector<i3d> i4d;
typedef vector<double> d1d;
typedef vector<d1d> d2d;
typedef vector<d2d> d3d;
typedef vector<d3d> d4d;

class PSO
{
public:
    d1d Run_result;
    d1d Run_evaluation;

public:
    void run(int run, int dim, int pop, int MAX_NFE, int fun_num)
    {
        srand((unsigned)time(NULL));
        Run_set(MAX_NFE / pop, run);
        double START, END;
        START = clock();
        for (int i = 0; i < run; i++)
        {
            Set(pop, dim, fun_num);
            Initial(pop, dim, MAX_NFE, fun_num); //random initial
            // record_point(pop, dim);
            while (NFE < MAX_NFE)
            {
                Transition(pop, dim);
                Evaluation(pop, dim, fun_num, MAX_NFE);
                // record_point(pop, dim);
            }
            Run_result[i] = Current_best_obj;
        }
        END = clock();
        Output(run, MAX_NFE, dim, pop, START, END, fun_num);
    }

private:
    d2d Particle;
    d1d Objective;
    d2d Velocity;
    d2d P_best_pos;
    d1d P_best_obj;
    d1d G_best_pos;
    double Current_best_obj;
    d1d Current_best_Particle;
    double w, c1, c2;
    double max, min;
    int NFE;

private:
    inline double randomDouble() //uniform distribution [0, 1)
    {
        return (double)rand() / (double)RAND_MAX;
    }
    inline int randomInt(int min, int max)
    {
        return (rand() % (max - min + 1) + min);
    }
    void Run_set(int Iter, int Run)
    {
        Run_evaluation.resize(Iter, 0);
        Run_result.resize(Run, 0);
    }
    void Set(int pop, int dim, int fun_num)
    {
        cout << scientific << setprecision(8);

        Particle.clear();
        Particle.swap(Particle);
        Particle.assign(pop, d1d(dim, 0));

        Objective.clear();
        Objective.swap(Objective);
        Objective.resize(pop, 0);

        Velocity.clear();
        Velocity.swap(Velocity);
        Velocity.assign(pop, d1d(dim, 0));

        Current_best_Particle.clear();
        Current_best_Particle.swap(Current_best_Particle);
        Current_best_Particle.resize(dim, 0);

        Current_best_obj = DBL_MAX;

        P_best_pos.clear();
        P_best_pos.swap(P_best_pos);
        P_best_pos.assign(pop, d1d(dim, DBL_MAX));

        P_best_obj.clear();
        P_best_obj.swap(P_best_obj);
        P_best_obj.resize(pop, DBL_MAX);

        G_best_pos.clear();
        G_best_pos.swap(G_best_pos);
        G_best_pos.resize(dim, 0);

        w = 0.729844;
        c1 = 1.496180;
        c2 = 1.496180;
        NFE = 0;
        Set_Range(max, min, fun_num, dim);
    }
    void Initial(int pop, int dim, int MAX_NFE, int fun_num) //random initial
    {
        for (int i = 0; i < pop; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                Particle[i][j] = randomDouble() * (max - min) + min;
            }
        }

        Evaluation(pop, dim, fun_num, MAX_NFE);
    }
    void Evaluation(int pop, int dim, int fun_num, int MAX_NFE)
    {
        int chc = 1; //record evaluation or not
        for (int i = 0; i < pop; i++)
        {
            Testing_Function(&Particle[i][0], &Objective[i], dim, 1, fun_num);
            if (Objective[i] < P_best_obj[i]) //find pbest
            {
                P_best_obj[i] = Objective[i];
                P_best_pos[i] = Particle[i];

                if (Objective[i] < Current_best_obj) //find gbest
                {
                    Current_best_obj = Objective[i];
                    G_best_pos = Particle[i];
                }
            }

            NFE++;
            if (NFE > MAX_NFE)
            {
                chc = 0;
                break;
            }
        }

        if (chc)
        {
            Run_evaluation[NFE / pop - 1] += Current_best_obj;
        }
    }
    void Transition(int pop, int dim)
    {
        for (int i = 0; i < pop; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                double r1 = randomDouble();
                double r2 = randomDouble();
                Velocity[i][j] = w * Velocity[i][j] +
                                 c1 * r1 * (P_best_pos[i][j] - Particle[i][j]) +
                                 c2 * r2 * (G_best_pos[j] - Particle[i][j]);

                Particle[i][j] += Velocity[i][j];
                if (Particle[i][j] > max)
                    Particle[i][j] = max;
                if (Particle[i][j] < min)
                    Particle[i][j] = min;
            }
        }
    }
    void Output(int run, int MAX_NFE, int dim, int pop, double START, double END, int fun_num)
    {
        double Run_AVG = 0;
        double Run_Best = DBL_MAX;
        for (int i = 0; i < run; i++)
        {
            Run_AVG += Run_result[i];

            if (Run_result[i] < Run_Best)
                Run_Best = Run_result[i];
        }

        Run_AVG /= run;
        for (int i = 0; i < Run_evaluation.size(); i++)
        {
            cout << (i + 1) * pop << ' ' << Run_evaluation[i] / run << endl;
        }
        cout << "# Run : " << run << endl;
        cout << "# Evaluation : " << MAX_NFE << endl;
        cout << "# Dimension : " << dim << endl;
        cout << "# Population : " << pop << endl;
        cout << "# Function number : " << fun_num << endl;
        cout << "# Best Objective : " << Run_Best << endl;
        cout << "# Average Objective : " << Run_AVG << endl;
        cout << "# Execution Time : " << (END - START) / CLOCKS_PER_SEC << "(s)" << endl;
    }
    void record_point(int pop, int dim)
    {
        fstream file;
        string A = "./2d_ackley_points/" + to_string(NFE) + ".txt";
        file.open(A, ios::out);
        for (int i = 0; i < pop; i++)
        {

            for (int j = 0; j < 2; j++)
            {

                file << Particle[i][j] << ' ';
            }
            file << endl;
        }
    }
};