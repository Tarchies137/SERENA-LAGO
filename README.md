Tratamiento de datos para estanque LAGO

Los archivos .root son obtenidos de la medida del estanque ROOT

OBJ: Convertir las Tuplas a Tree.

LAGOmu/PWs10_Ntrig1000_ScTrig
/myTree.C

------------------------------------------------------------￼

27/03/24 Continuamos con la cración de Tree. 

Estructura del script usando MakeClass()

Este repositorio no comparte los archivos .root debido a su tamaño
--------------------------------------------------------------

29/04/24
 Se estabelecen los objetivos semanales
Objetivos de la Semana:

(*) Repasar Cesión de Exploración medidas Carga Eléctrica
( ) CAlcular Valor Medio Q1 y Q2 respecto al pedestal
(->) Modificar la clase para incluir los 10000 datos
    (*)Verifica que archivo contiene drs4data
    (*)Trabajar a partir de un directorio
	(*)Crear Directorio de Analisis de datos
	(*)Revisar ReadData.C y ReadData.h y verificar que funciona usando ruta de archivos
        (*)Macrodata crea un directorio de resultados donde se generan los _Tree.root individuales 
        (->)un arbol con data completa
		(*) Crear "arbol".C que concatena los arboles dados
		( ) Incluir en la tupla el nombre del archivo de origen.
		( ) Combinar la rama FOREST con main
		( ) Deshechar la rama FOREST-2
	() Crear manual de ususriao del script
	 

( ) CAlaculo del tiempo de llegada al PMT
    ( ) Crear un histograma de tiempos
    ( ) Encontrar la diferenciua de tiempos entre ambos picks del histograma tiempos del minimo en el ultimo dinodo
(*) Encontrar los mínimos y sus respectivos tiempos  
( ) Crear Srcitps con todos los graficos solicitados
( ) Encontrar los Picks, buscar en ROOTCERN Picks.C ejemplo de implementación
----------------------------------------------------------
10/05/2024 
Se crea nueva rama de git $git checkout FOREST  para trabajar union de árboles 
Continuamos trabajando data

20/05/2024
Se logra unir las tuplas en un solo árbol. Resultado se encuentra en branch FOREST DIR analysis-FOREST. 
Se plantean las siguientes tareas de depuración.
	()CAmbiar nombre a los archivos ReadData.C y ReadData.h para diferenciar del archivo que está en main
	() Unificar las branch para continuar el trabajo de análisis de Datos

