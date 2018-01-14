#!/bin/bash

rm refCPU

nr=1
ntheta=1
nphi=1
c=0.1

while [ $nr != 0 ]
do
./out $nr $ntheta $nphi >> refCPU
nr=`echo "scale=5; $nr - $c" | bc`
echo $nr
done
