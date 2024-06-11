//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Apr 18 12:50:05 2024 by ROOT version 6.30/04
// from TTree drs4data/drs4 data
// found on file: PW0_LAGOmu.root
//////////////////////////////////////////////////////////

#ifndef ReadDataGlobal_h
#define ReadDataGlobal_h

#include <TROOT.h>
#include <TChain.h>	
#include <TFile.h>
#include <string>


// Header file for the classes stored in the TTree if any.

class ReadDataGlobal {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

  TTree *global_Tree;
  TFile *outputFile;


// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   
  static const Int_t kNsample=1024;	// Número de Saples del drs4
   Float_t 	R=50; 			//Resistencia 50 [Ohm] de la impedancia.
   Float_t   	evn;
   Float_t   	evn_time;
   Float_t   	t;
   Float_t   	v0;
   Float_t   	v1;
   Float_t   	v2;
   Float_t tt[kNsample], vv0[kNsample], vv1[kNsample], vv2[kNsample]; //Branches
   Float_t eVals[9], Q[3], V_Min[3], T_Min[3];	//Branches eVals junta todos los valores, modif global_Tree->Brance("evals ... *160
   Int_t ev;
   
  std::string filename  ;
 


   // List of branches
   TBranch        *b_evn;   	//!
   TBranch        *b_evn_time; 	//!
   TBranch        *b_t;   	//!
   TBranch        *b_v0;   	//!
   TBranch        *b_v1;   	//!
   TBranch        *b_v2;   	//!

    ReadDataGlobal(const char* filename, TTree *tree=0);		//ReadDataGlobal(TTree *tree=0);
   virtual ~ReadDataGlobal();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(const char* filename, TTree *tree); 	//modificar parámetros de entrada INIT
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ReadDataGlobal_cxx

ReadDataGlobal::ReadDataGlobal(const char* filename, TTree *tree) : fChain(0) 
{
    // Conecta el archivo especificado y lee el TTree "drs4data"
    TFile *f = TFile::Open(filename);
    if (!f || !f->IsOpen()) {
        std::cerr << "Error: No se pudo abrir el archivo: " << filename << std::endl;
        return;
    }
    f->GetObject("drs4data",tree);

    Init(filename, tree);
}



ReadDataGlobal::~ReadDataGlobal()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ReadDataGlobal::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ReadDataGlobal::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ReadDataGlobal::Init(const char* filename, TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("evn", &evn, &b_evn);
   fChain->SetBranchAddress("evn_time", &evn_time, &b_evn_time);
   fChain->SetBranchAddress("t", &t, &b_t);
   fChain->SetBranchAddress("v0", &v0, &b_v0);
   fChain->SetBranchAddress("v1", &v1, &b_v1);
   fChain->SetBranchAddress("v2", &v2, &b_v2);
   
     // outputFile = new TFile("global_Tree.root","RECREATE"); 
   
   /* Constructor de nombre outfile no es necesario
   std::string outputFileName = filename;  			// Copia el nombre de archivo de entrada
   std::size_t found = outputFileName.find_last_of("/\\."); 	// Busca la última ocurrencia de '/' o '\' para encontrar la extensión
   if (found != std::string::npos) { 				// Si se encontró la extensión
       outputFileName.insert(found, "_Tree"); 			// Inserta "_Tree" justo antes de la extensión
     } else { 							// Si no se encontró la extensión
       outputFileName += "_Tree"; 				// Agrega "_Tree" al final del nombre de archivo
     }
*/

  
    // Crear Archivo de Salida
   outputFile = new TFile("global_Tree.root", "RECREATE");

    //outputFile = new TFile(outputFileName,"RECREATE"); 
   
   global_Tree = new TTree("global_Tree", "Arbol global");
   
   
    global_Tree->Branch("ev", &ev, "ev/I");
    global_Tree->Branch("tt", tt, TString("tt[")+kNsample+"]/F");
    global_Tree->Branch("vv0", vv0,TString("vv0[")+kNsample+"]/F");
    global_Tree->Branch("vv1", vv1,TString("vv1[")+kNsample+"]/F");
    global_Tree->Branch("vv2", vv2,TString("vv2[")+kNsample+"]/F");
    global_Tree->Branch("eVals", eVals,"eVals[9]/F");
   Notify();
}

Bool_t ReadDataGlobal::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ReadDataGlobal::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ReadDataGlobal::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ReadDataGlobal_cxx
