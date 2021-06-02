#ifndef COMMON_MAIN_H
#define COMMON_MAIN_H

#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#if defined(__GNUC__) || defined(__SUNPRO_CC)
#include <pthread.h>
#endif

#include "gm.h"

class main_t 
{
  protected:
    gm_graph G;
    int num_threads;
    bool is_all_thread_mode()  {return num_threads == -1;}

  public:
    main_t() {time_to_exclude = 0; num_threads = 0;}

        void pin_CPU()
        {
#if (defined(__GNUC__) || defined(__SUNPRO_CC)) && !defined(_WIN32)
            #pragma omp parallel 
            {
                pthread_t thread;
                thread = pthread_self();
                cpu_set_t CPU;
                CPU_ZERO(&CPU);
                CPU_SET(omp_get_thread_num(), &CPU);
                pthread_setaffinity_np(thread, sizeof(CPU), &CPU);
            }
#endif
        }

    virtual void main(int argc, char** argv)
    {
        bool b;
        if (argc < 3) {

            printf("%s <graph_name> <num_threads> ", argv[0]); 
            print_arg_info();
            printf("\n");

            exit(EXIT_FAILURE);
        }

        int new_argc = argc - 3;
        char** new_argv = &(argv[3]);
        b = check_args(new_argc, new_argv);
        if (!b) {
            printf("error procesing argument\n");
            printf("%s <graph_name> <num_threads> ", argv[0]); 
            print_arg_info();
            printf("\n");
            exit(EXIT_FAILURE);
        }


        int num = atoi(argv[2]);
        num_threads = num;
        if (num == -1)
        {
            printf("exploration mode\n", num);
        }
        else 
        {
            printf("running with %d threads\n", num);

        }

        //--------------------------------------------
        // Load graph and creating reverse edges
        //--------------------------------------------
        time_t T1, T2;
        char *fname = argv[1];
        time(&T1); 
        b = G.load_binary(fname);
        if (!b) {
            printf("error reading graph\n");
            exit(EXIT_FAILURE);
        }
        time(&T2); 
        printf("graph loading time=%lf\n", 
            (double) ((T2 - T1) * 1000)
        );

        time(&T1);
        G.make_reverse_edges();
        time(&T2);
        printf("reverse edge creation time=%lf\n", 
            (double)((T2 - T1) * 1000)
        );

        
        //------------------------------------------------
        // Any extra preperation Step (provided by the user)
        //------------------------------------------------
        if (num == -1) 
        {
            int max=32;
            for(int i =1; i <=max; i=i*2)
            {
                gm_rt_set_num_threads(i); // gm_runtime.h
                do_main_steps();
            }

        }
        else {
            gm_rt_set_num_threads(num); // gm_runtime.h
            do_main_steps();
        }
    }

    void do_main_steps()
    {
        time_t T1, T2;
        printf("\n");
        pin_CPU();

        bool b = prepare();
        if (!b) {
            printf("Error prepare data\n");
            exit(EXIT_FAILURE);
        }

        time(&T1); 
        b = run();
        time(&T2);
        printf("[%d]running_time(ms)=%lf\n", 
            gm_rt_get_num_threads(),
            (double) ((T2 - T1) * 1000)
            - time_to_exclude
        );
        fflush(stdout);
        if (!b) {
            printf("Error runing algortihm\n");
            exit(EXIT_FAILURE);
        }


        b = post_process();
        if (!b) {
            printf("Error post processing\n");
            exit(EXIT_FAILURE);
        }

        //----------------------------------------------
        // Clean up routine
        //----------------------------------------------
        b = cleanup();
        if (!b) exit(EXIT_FAILURE);
    }

    virtual bool check_answer() { return true; }
    virtual bool run() = 0;
    virtual bool prepare()      { return true;}
    virtual bool post_process() { return true;}
    virtual bool cleanup()      {return true;}
    // check remaining arguments
    virtual bool check_args(int argc, char** argv) {return true;}
    virtual void print_arg_info() {}
protected:
    gm_graph& get_graph() {return G;}
    void add_time_to_exlude(double ms) {time_to_exclude += ms;}
    double time_to_exclude;

};

#endif
