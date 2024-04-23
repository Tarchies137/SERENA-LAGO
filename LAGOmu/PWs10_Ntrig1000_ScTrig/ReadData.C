#define ReadData_cxx
#include "ReadData.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void ReadData::Loop()
{
//   In a ROOT session, you can do:
//      root> .L ReadData.C
//      root> ReadData t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast()/kNsample;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      	Long64_t ientry = LoadTree(jentry);
      
      
      	if (ientry < 0) break;
     	// número de evento
      	ev = jentry;
      	//
      	Float_t sR0=0,sR1=0,sR2=0;
      	for (Int_t j = 0; j < kNsample; j++) {
        	nb = fChain->GetEntry(j + jentry*kNsample);   nbytes += nb;   
       		tt[j] = t;
            	vv0[j] = v0;
            	vv1[j] = v1;
            	vv2[j] = v2;
            
            	sR0 += v0;// equivale a sR = sR+vv[k];
            	sR1 += v1;
            	sR2 += v2;
		}
		//carga total clectada
	Float_t dt = (tt[kNsample-1]-tt[0])/(kNsample - 1);
	/*Q[0] = (Float_t)sR0*dt/R;
	Q[1] = (Float_t)sR1*dt/R;
	Q[2] = (Float_t)sR2*dt/R;*/

	Q[0] = sR0*dt/R;
	Q[1] = sR1*dt/R;
	Q[2] = sR2*dt/R;

           
              myTree->Fill();
    }
    
        // Cerrar el archivo de entrada
    //f->Close();
    if (fChain->GetCurrentFile()) {
        fChain->GetCurrentFile()->Close();
    }
    // Guardar la cabecera del árbol
    myTree->Write();

    // Cerrar el archivo de salida
    outputFile->Close();
   }
      
   
  // Codigo
   
      // if (Cut(ientry) < 0) continue;
   

