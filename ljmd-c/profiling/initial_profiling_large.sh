#!/bin/bash

no_opt="-Wall -pg -no-pie"
O2="-Wall -O2 -pg -no-pie"
O3="-Wall -O3 -pg -no-pie"
fast_math="-Wall -O3 -ffast-math -pg -no-pie"
expensive_opt="-Wall -O3 -ffast-math -fexpensive-optimizations -pg -no-pie" 


#opt=( "$no_opt" "${O2}" "${O3}" "${fast_math}" "${expensive_opt}" )
opt=( "${fast_math}" "${expensive_opt}" )
#names=('no_opt' 'O2' 'O3' 'fast_math' 'expensive_opt' )
names=( 'fast_math' 'expensive_opt' )

head -10 ../reference/argon_2916.dat | awk '{printf("%d %.6f %.6f %.6f\n",$1,$2,$3,$4);}'> ref.dat

for i in $(seq 1 ${#opt[@]})
do 
  idx=$((i-1))
  name=${names[$idx]}
  cd ..
  make serial -B CFLAGS="${opt[idx]}" EXE="$name.x"
  
  cd profiling
  ./../${name}.x < argon_2916.inp 
  
  gprof ./../${name}.x gmon.out > ${name}_analysis.txt
 
  head -10 argon_2916.dat | awk '{printf("%d %.6f %.6f %.6f\n",$1,$2,$3,$4);}'> a.dat
  cmp a.dat ref.dat || exit 1
  rm -f a.dat
done

rm argon_2916.dat
rm argon_2916.xyz
rm ref.dat
rm gmon.out


