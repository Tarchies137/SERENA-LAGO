#!/bin/bash
cd .. 

for archivo in *.root
do
    echo "Archivo: $archivo"

root -l<<EOF
.L ReadData.C
ReadData *reader = new ReadData("$archivo");
reader->Loop();
.ls;
EOF
done
ls 
cd -
for i in {1..5}
do
    echo "Número: $i"
done
