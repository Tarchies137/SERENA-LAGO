#define ReadData_cxx
#include "ReadData.h"
#include <TH2.h>
#include <dirent.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSystem.h> // Agregar la inclusión de la biblioteca TSystem


void ReadData::Loop()
{
//  

	//TTree *tree;
	 //outputFile = new TFile("global_Tree.root", "UPDATE");
	 
	 int EV=0 ; // Definición evento marco global
for(const auto& filename : filenameList) {

 std::cout << "Leyendo el archivo: " << filename << std::endl;
	  // Conecta el archivo especificado y lee el TTree "drs4data"
	TFile *f = TFile::Open(filename.c_str());

//    TFile *f = TFile::Open(filename);
    if (!f || !f->IsOpen()) {
        std::cerr << "Error: No se pudo abrir el archivo: " << filename << std::endl;
        return;
    }
    f->GetObject("drs4data",tree);
    
   if (!tree) {
        std::cerr << "Warning: No se encontró el árbol 'drs4data' en el archivo: " << filename << std::endl;
        f->Close(); // Cerrar el archivo antes de continuar
        continue; // Saltar al siguiente archivo
    }

char cPw = filename[filename.length()-13];
    nPw = cPw - '0'; // número de data
   // std::cout <<"nPw vale:"<< nPw << typeid(nPw).name() << std::endl;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast()/kNsample;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      	Long64_t ientry = LoadTree(jentry);
      
      
      	if (ientry < 0) break;
     	// número de evento
      	ev = jentry;
      	ePw = EV + ev; //Identificador evento global
      	//
      	Float_t sR0=0,sR1=0,sR2=0;
		Float_t dt = (tt[kNsample-1]-tt[0])/(kNsample - 1);

		Float_t t0_min,v0_min=1000,t1_min,v1_min=1000,t2_min,v2_min=1000;

      	for (Int_t j = 0; j < kNsample; j++) {
        	nb = fChain->GetEntry(j + jentry*kNsample);   nbytes += nb;   
       		tt[j] = t;
            	vv0[j] = v0;
            	vv1[j] = v1;
            	vv2[j] = v2;
            
            	sR0 += v0;// equivale a sR = sR+vv[k];
            	sR1 += v1;
            	sR2 += v2;
            	//Minimo ... [] Incluir como nueva rama
		if (v0<v0_min)
		{
			v0_min = v0;
			t0_min = t;
		}
		if (v1<v1_min)
		{
			v1_min = v1;
			t1_min = t;
		}
		if (v2<v2_min)
		{
			v2_min = v2;
			t2_min = t;
		}
		//___________CARga CUT_____________
		if (t<180e-9) // [] Trabajar ventana temporal
		{
			QC0 = sR0*dt/R;
			QC1 = sR1*dt/R;
			QC2 = sR2*dt/R;
		}


		}
		
		//carga total colectada
	


	Q[0] = sR0*dt/R;
	Q[1] = sR1*dt/R;
	Q[2] = sR2*dt/R;
	V_Min[0] = v0_min;
	V_Min[1] = v1_min;
	V_Min[2] = v2_min;
	T_Min[0] = t0_min;
	T_Min[1] = t1_min;
	T_Min[2] = t2_min;
				
	for (int i = 0; i <= 8; ++i) {
		if (i < 3) {  			// Carga Almacenada por evento 
		eVals[i] = Q[i];
		} else if (i >= 3 && i < 6) {	// Voltaje minimo por evento
		eVals[i] = V_Min[i-3];
		} else {    			// Tiempo asciado al Voltaje minimo por evento
		eVals[i] = T_Min[i-6] ;
		}
	}
           
              myTree->Fill();
    }
    
        // Cerrar el archivo de entrada
    //f->Close();
    if (fChain->GetCurrentFile()) {
        fChain->GetCurrentFile()->Close();
    }
    
std::cout << "Escribiendo los datos de: " << filename << std::endl;
	EV = ePw + 1; //evento global suma 1 para correlación correcta
}
    // Guardar la cabecera del árbol
   outputFile->cd(); // Establecer el directorio actual como el archivo de salida

    myTree->Write();

    // Cerrar el archivo de salida
    outputFile->Close();
   }
      

   
  // Codigo
   
      // if (Cut(ientry) < 0) continue;
   

