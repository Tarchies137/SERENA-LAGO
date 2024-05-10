#!/bin/bash
#-------------------------------------------------------
# Verificar si se proporcionó un argumento
if [ $# -ne 1 ]; then
    echo "Uso: $0 <directorio>"
    exit 1
fi
#--------------------------------------------------------
# Almacenar el directorio proporcionado en una variable
directorio="$1"

# Verificar si el directorio existe
if [ ! -d "$directorio" ]; then
    echo "El directorio '$directorio' no existe."
    exit 1
fi
#-------------------------------------------------------
# Procesar el directorio
echo "Procesando el directorio '$directorio'..."
#cd $directorio
pwd
mkdir -p $directorio/Resultados
# Aquí puedes agregar el código para procesar el contenido del directorio

#-------------------------------------------------------
#--------------------------------
for archivo in $directorio*.root
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
mv $directorio/*_Tree.root $directorio/Resultados
for arbol in $directorio/Resultados*.root
do
    echo "Archivo: $arbol"
    if ! rootls "$arbol" | grep -q "myTree"; then
        # Si no se encuentra "drs4data" en el archivo, ejecutar una acción
        echo "El arbol $arbol no contiene 'myTree'."
        # Agrega aquí la acción que deseas realizar
    else
        # Ejecuta el script en C para combinar los árboles
        root -l -q -b 'CombineTrees.C("'$arbol'")'
    fi
done

#-------------------------------
mv $directorio/*_Tree.root $directorio/Resultados
echo $directorio/Resultados
ls $directorio/Resultados
ls

