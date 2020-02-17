#!/bin/bash

# call: ./initial_times.sh 2> filename

fast_math="-Wall -pg -no-pie -O3 -ffast-math"

opt=( "${fast_math}" )

names=('fast_math')

head -10 ../reference/argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$1,$2,$3,$4);}'> ref.dat

for i in $(seq 1 ${#opt[@]})
do 
  idx=$((i-1))
  name=${names[$idx]}
  make -B CFLAGS="${opt[idx]}" EXE="$name.x"
  
  /usr/bin/time ./${name}.x < argon_108.inp 
  
  gprof ./${name}.x gmon.out > ${name}_analysis.txt
 
  head -10 argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$1,$2,$3,$4);}'> a.dat
  cmp a.dat ref.dat || exit 1
  rm -f a.dat
done

rm argon_108.dat
rm argon_108.xyz
rm ref.dat
rm gmon.out

