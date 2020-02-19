echo "version, procs, threads, time" > benchmark.csv
for cores in 20 16 10 5 4 6 8 12 14 18 1 ; do
    procs=$cores
    threads=$((20/$procs))
    if [ $threads -eq 1 ] ; then
       #########################################################
       file="../benchmarks/main_mpi_proc_${procs}_thpp_${threads}.out"
       echo "${threads} threads and ${procs} MPI procs (PURE MPI)"
       export OMP_NUM_THREADS=${threads}
       echo "export OMP_NUM_THREADS=${threads}" > $file
       echo "mpirun -np ${procs} ../main_mpi.x < argon_2916.inp > ../benchmarks/main_mpi_proc_${procs}_thpp_${threads}.out " >> $file
       mpirun -np ${procs} ../main_mpi.x < argon_2916.inp >> $file
       echo "MPI, $threads, $procs, "$(cat $file | grep "Time process 0" | awk '1{print $4}') >> benchmark.csv
    else
       #########################################################
       file="../benchmarks/main_mpi_proc_${procs}_thpp_${threads}.out"
       echo "${threads} threads and ${procs} MPI procs (HYBRID)"
       export OMP_NUM_THREADS=${threads}
       echo "export OMP_NUM_THREADS=${threads}" > $file
       echo "mpirun -np ${procs} -cpus-per-proc ${threads} ../main_mpi.x < argon_2916.inp > ../benchmarks/main_mpi_proc_${procs}_thpp_${threads}.out" >> $file
       mpirun -np ${procs} -cpus-per-proc ${threads} ../main_mpi.x < argon_2916.inp >> $file
       echo "HYBRID, $threads, $procs, "$(cat $file | grep "Time process 0" | awk '1{print $4}') >> benchmark.csv
       #########################################################
       threads=1
       file="../benchmarks/main_mpi_proc_${procs}_thpp_${threads}.out"
       echo "${threads} threads and ${procs} MPI procs (PURE MPI)"
       export OMP_NUM_THREADS=${threads}
       echo "export OMP_NUM_THREADS=${threads}"  > $file
       echo "mpirun -np ${procs} ../main_mpi.x < argon_2916.inp > ../benchmarks/main_mpi_proc_${procs}_thpp_${threads}.out" >> $file
       mpirun -np ${procs} ../main_mpi.x < argon_2916.inp >> $file
       echo "MPI, $threads, $procs, "$(cat $file | grep "Time process 0" | awk '1{print $4}') >> benchmark.csv
    fi
    echo "-----------------------------------------------------------"
done;

export OMP_PLACES=cores
export PROC_BIND=close

for cores in 20 16 10 5 4 6 8 12 14 18 1 ; do
    procs=$cores
    threads=${cores}
    echo "${threads} threads (PURE OPENMP)"
    export OMP_NUM_THREADS=${threads}
    echo "export OMP_NUM_THREADS=${threads}"  > ../benchmarks/main_optimized_thpp_${threads}.out
    echo "../main.x < argon_2916.inp > ../benchmarks/main_optimized_thpp_${threads}.out" >> ../benchmarks/main_optimized_thpp_${threads}.out
    ../main.x < argon_2916.inp >> ../benchmarks/main_optimized_thpp_${threads}.out
    echo "OPENMP, $threads, $procs, "$(cat $file | grep "Time process 0" | awk '1{print $4}') >> benchmark.csv
    echo "-----------------------------------------------------------"
done;
echo "ljmd_serial..."
echo "../ljmd-serial.x < argon_2916.inp) > ../benchmarks/main_ljmd-serial.out" > ../benchmarks/main_ljmd-serial.out
../ljmd-serial.x < argon_2916.inp >> ../benchmarks/main_ljmd-serial.out
