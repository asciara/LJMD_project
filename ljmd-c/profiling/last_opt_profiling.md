BEFORE LAST OPTIMIZATION LAYER

```
Evolve time: 35.109601

 Performance counter stats for '../main.x':

      35581.172046      task-clock (msec)         #    0.999 CPUs utilized          
               185      context-switches          #    0.005 K/sec                  
                 5      cpu-migrations            #    0.000 K/sec                  
               113      page-faults               #    0.003 K/sec                  
   124,187,773,089      cycles                    #    3.490 GHz                    
   147,673,667,736      instructions              #    1.19  insn per cycle
       127,453,310      cache-references                                            
         8,434,924      cache-misses              #    6.618 % of all cache refs  
    37,782,300,161      branches                  # 1061.862 M/sec                  
     2,260,307,183      branch-misses             #    5.98% of all branches        

      35.603604495 seconds time elapsed

```

BEFORE LAST OPTIMIZATION LAYER (108 atoms)

```
Evolve time: 1.100160

Performance counter stats for '../main.x':

       1121.006401      task-clock (msec)         #    0.999 CPUs utilized          
                 9      context-switches          #    0.008 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
                64      page-faults               #    0.057 K/sec                  
     3,818,553,519      cycles                    #    3.406 GHz                    
     2,960,165,769      instructions              #    0.78  insn per cycle
         1,724,978      cache-references                                            
           910,551      cache-misses              #   52.786 % of all cache refs 
       560,551,149      branches                  #  500.043 M/sec                  
        87,191,783      branch-misses             #   15.55% of all branches        

       1.122353338 seconds time elapsed

```



AFTER LAST OPTIMIZATION LAYER (108 atoms)

```
Evolve time: 1.081362

Performance counter stats for '../main.x':

       1099.120589      task-clock (msec)         #    0.999 CPUs utilized          
                 8      context-switches          #    0.007 K/sec                  
                 1      cpu-migrations            #    0.001 K/sec                  
            12,798      page-faults               #    0.012 M/sec                  
     3,739,226,030      cycles                    #    3.402 GHz                    
     2,629,548,032      instructions              #    0.70  insn per cycle         
         4,951,491      cache-references                                            
         2,514,690      cache-misses              #   50.787 % of all cache refs
       568,839,950      branches                  #  517.541 M/sec                  
        90,690,447      branch-misses             #   15.94% of all branches        

       1.100490502 seconds time elapsed

```



AFTER LAST OPTIMIZATION LAYER (2916 atoms)

```
Evolve time: 31.132160

 Performance counter stats for '../main.x':

      31624.351582      task-clock (msec)         #    1.000 CPUs utilized          
                55      context-switches          #    0.002 K/sec                  
                 2      cpu-migrations            #    0.000 K/sec                  
            34,327      page-faults               #    0.001 M/sec                  
   110,329,150,159      cycles                    #    3.489 GHz                    
   121,692,644,085      instructions              #    1.10  insn per cycle
       109,657,647      cache-references                                            
        13,907,178      cache-misses              #   12.682 % of all cache refs
    37,802,268,600      branches                  # 1195.353 M/sec                  
     2,328,234,384      branch-misses             #    6.16% of all branches        

      31.627499914 seconds time elapsed

```

OMP COMPATIBILITY (2916 atoms) : BEFORE LAST OPT. OMP_NUM_THREADS=2

(Hyperthreading disabled on my machine less performance)

```
Evolve time: 19.977002
Simulation Done.

 Performance counter stats for '../main.x':

      40083.017528      task-clock (msec)         #    1.953 CPUs utilized          
             2,683      context-switches          #    0.067 K/sec                  
                 1      cpu-migrations            #    0.000 K/sec                  
               148      page-faults               #    0.004 K/sec                  
   128,850,228,838      cycles                    #    3.215 GHz                    
   147,977,660,258      instructions              #    1.15  insn per cycle
        77,857,770      cache-references                                            
        12,095,369      cache-misses              #   15.535 % of all cache refs 
    37,860,212,003      branches                  #  944.545 M/sec                  
     2,272,772,703      branch-misses             #    6.00% of all branches        

      20.526552651 seconds time elapsed


```

OMP COMPATIBILITY (2916 atoms): AFTER LAST OPT. OMP_NUM_THREADS=2

(Hyperthreading disabled on my machine less performance)

```
Evolve time: 17.026178
Simulation Done.

 Performance counter stats for '../main.x':

      34135.812936      task-clock (msec)         #    1.944 CPUs utilized          
             3,384      context-switches          #    0.099 K/sec                  
                 3      cpu-migrations            #    0.000 K/sec                  
            52,280      page-faults               #    0.002 M/sec                  
   118,627,998,083      cycles                    #    3.475 GHz                    
   134,784,564,238      instructions              #    1.14  insn per cycle 
       100,175,745      cache-references                                            
        17,937,006      cache-misses              #   17.906 % of all cache refs
    37,879,590,001      branches                  # 1109.673 M/sec                  
     2,388,623,352      branch-misses             #    6.31% of all branches        

      17.556866156 seconds time elapsed
```

MPI COMPATIBILITY (2916 atoms): BEFORE LAST OPT. MPI_NUM_PROC=2

(Hyperthreading disabled on my machine less performance)

```
Time process 1: 20.921596
Time process 0: 20.428976
Evolve time: 20.921596
```



MPI COMPATIBILITY (2916 atoms): MPI_NUM_PROC=2

(Hyperthreading disabled on my machine less performance)

```
Time process 1: 18.457735
Time process 0: 17.993986
Evolve time: 18.457735
```

