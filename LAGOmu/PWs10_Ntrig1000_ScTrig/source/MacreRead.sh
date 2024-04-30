#!/bin/bash
cd .. 
#--------------------------------
for archivo in *.root
do
   	 echo "Archivo: $archivo"

	if ! rootls "$archivo" | grep -q "drs4data"; then
		# Si no se encuentra "drs4data" en el archivo, ejecutar una acción
    		echo "El archivo $archivo no contiene 'drs4data'."
   		 # Agrega aquí la acción que deseas realizar
	else
#El codigo aplicado en root debe ir sin iodentación
root -l<<EOF
.L ReadData.C
ReadData *reader = new ReadData("$archivo");
reader->Loop();
.ls;
EOF
fi
done
#-------------------------------
ls 
cd -

