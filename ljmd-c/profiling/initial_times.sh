#!/bin/bash

# call: ./initial_times.sh 2> filename

no_opt="-Wall"
O2="-Wall -O2"
O3="-Wall -O3"
fast_math="-Wall -O3 -ffast-math"
expensive_opt="-Wall -O3 -ffast-math -fexpensive-optimizations" 
omit_frame="-Wall -O3 -ffast-math -fexpensive-optimizations -fomit-frame-pointer"
msse="-Wall -O3 -ffast-math -fexpensive-optimizations -msse3 -fomit-frame-pointer"


opt=( "$no_opt" "${O2}" "${O3}" "${fast_math}" "${expensive_opt}" "${omit_frame}" "${msse}")
#opt=( "$msse" )
names=('no_opt' 'O2' 'O3' 'fast_math' 'expensive_opt' 'omit_frame' 'msse')
#names=( 'msse' )

head -10 ../reference/argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$1,$2,$3,$4);}'> ref.dat

for i in $(seq 1 ${#opt[@]})
do 
  idx=$((i-1))
  name=${names[$idx]}
  make -B CFLAGS="${opt[idx]}" EXE="$name.x"
  
  /usr/bin/time ./${name}.x < argon_108.inp 
 
  head -10 argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$1,$2,$3,$4);}'> a.dat
  numdiff -a 1e-4 a.dat ref.dat || exit 1
  rm -f a.dat
done

rm argon_108.dat
rm argon_108.xyz
rm ref.dat
rm gmon.out


