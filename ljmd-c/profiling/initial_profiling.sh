#!/bin/bash

no_opt="-Wall -pg -no-pie"
O2="-Wall -O2 -pg -no-pie"
O3="-Wall -O3 -pg -no-pie"
fast_math="-Wall -O3 -ffast-math -pg -no-pie"
expensive_opt="-Wall -O3 -ffast-math -fexpensive-optimizations -pg -no-pie" 


opt=( "$no_opt" "${O2}" "${O3}" "${fast_math}" "${expensive_opt}" )
#opt=( "$msse" )
names=('no_opt' 'O2' 'O3' 'fast_math' 'expensive_opt' )
#names=( 'msse' )

head -10 ../reference/argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$1,$2,$3,$4);}'> ref.dat

for i in $(seq 1 ${#opt[@]})
do 
  idx=$((i-1))
  name=${names[$idx]}
  make -B CFLAGS="${opt[idx]}" EXE="$name.x"
  
  ./${name}.x < argon_108.inp 
  
  gprof ./${name}.x gmon.out > ${name}_analysis.txt
 
  head -10 argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$1,$2,$3,$4);}'> a.dat
  numdiff -a 1e-4 a.dat ref.dat || exit 1
  rm -f a.dat
done

rm argon_108.dat
rm argon_108.xyz
rm ref.dat
rm gmon.out


