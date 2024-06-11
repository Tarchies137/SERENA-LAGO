Análisis de DAtos 
Convierte las tuplas de los datos en estructura de árbol que contienen  los 10000 datos.

()Adjuntar modo de uso


----------------------------------------------
10/06/2024

Leer en global_Tree.root myTree->Print()

nPw: ID de archivo Data de origen
ev: nº de evento de nPw
ePw: nº de evento en myTree 
tt: variable temporal 
vv0: Señal del MPPC
vv1: señal del Anodo
vv2: Señal del último dinodo

-----------------------------------------------
	Compilar en root
-----------------------------------------------
.L ReadData.C
ReadData *reader = new ReadData("pwd(Data)")
reader->Loop()
TFile::Open("global_Tree.root")
-----------------------------------------------
