//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Apr 18 12:50:05 2024 by ROOT version 6.30/04
// from TTree drs4data/drs4 data
// found on file: PW0_LAGOmu.root
//////////////////////////////////////////////////////////

#ifndef ReadData_h
#define ReadData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <string>
#include <vector> 	// Agregar la inclusión de la biblioteca de vector
#include <TSystem.h> 	// Agregar la inclusión de la biblioteca TSystem
#include <cstdlib> 	// Para usar atoi

// Header file for the classes stored in the TTree if any.

class ReadData {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

  TTree *myTree;
  TFile *outputFile;
  

// Fixed size dimensions of array or collections stored in the TTree if any.

// Declaration of leaf types
   
  static const Int_t kNsample=1024;	// Número de Samples del drs4
   Float_t   	R=50; 			//Resistencia 50 [Ohm] de la impedancia.


   Float_t   	evn;
   Float_t   	evn_time;
   Float_t   	t;
   Float_t   	v0;
   Float_t   	v1;
   Float_t   	v2;
   Float_t tt[kNsample], vv0[kNsample], vv1[kNsample], vv2[kNsample]; //Branches
   Float_t eVals[9], Q[3], V_Min[3], T_Min[3];	//Branches eVals junta todos los valores, modif myTree->Brance("evals ... *160
   Int_t ev, ePw, nPw;
   Float_t QC0, QC1, QC2; //Cargas integradas corregidas 190e-9
   
   
  //std::string filename  ;
 std::string directory; // Agregar esta variable miembro para almacenar el directorio



   // List of branches
   TBranch        *b_evn;   	//!
   TBranch        *b_evn_time; 	//!
   TBranch        *b_t;   	//!
   TBranch        *b_v0;   	//!
   TBranch        *b_v1;   	//!
   TBranch        *b_v2;   	//!

//*****    ReadData(const char* filename, TTree *tree=0);		//ReadData(TTree *tree=0);
   ReadData(const char* dir, TTree *tree=0); // Se Modifica la declaración del constructor

   virtual ~ReadData();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree); 	//modificar parámetros de entrada INIT
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void listFiles(const char* dirPath);
   std::vector<std::string> filenameList; // Definimos el vector filenameList

 TTree *tree;
 

private:
    
};

#endif

#ifdef ReadData_cxx

ReadData::ReadData(const char* dir, TTree *tree) : fChain(0) 
{
   
 std::cout << "HAciendo las listas" << std::endl;
listFiles(dir);
   std::cout << "Concluye las listas" << std::endl;

        // Conecta el archivo especificado y lee el TTree "drs4data"
   TFile *f = TFile::Open(filenameList[1].c_str());

//    TFile *f = TFile::Open(filename);
    if (!f || !f->IsOpen()) {
        std::cerr << "Error: No se pudo abrir el archivo: " << filenameList[0] << std::endl;
        return;
    }
    f->GetObject("drs4data",tree);
    Init(tree);

}



ReadData::~ReadData()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ReadData::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ReadData::LoadTree(Long64_t entry)
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

void ReadData::listFiles(const char* dirPath) {                                                        //-
    void* dir = gSystem->OpenDirectory(dirPath);                                                //
    if (!dir) {                                                     
        std::cerr << "Error: cannot open directory " << dirPath << std::endl;
        return;
    }
const char* entry;
//std::vector<std::string> filenameList; // Definimos el vector filenameList
 while ((entry = gSystem->GetDirEntry(dir)) != nullptr) {
    //std::string filename(entry);

    std::string filename(dirPath); // Comienza con el directorio
        filename = filename + entry;             // Agrega el nombre del archivo al final del directorio
       // std::cout<<"filename="<<filename<<std::endl;
    
    // Check if the file has a .root extension
    if (filename.length() >= 5 && filename.substr(filename.length() - 5) == ".root") {
   /* char cPW = filename[filename.length()-13];
    int nPW = cPW - '0';
    //int nPW = atoi(cPW);
*/    std::cout << entry << std::endl;
	std::cout << nPw << std::endl;
std::cout << filename << std::endl;
        filenameList.push_back(filename); // Aadimos el nombre del archivo al vector
    }
}
    gSystem->FreeDirectory(dir);

    // Ordenar el vector filenameList alfabéticamente
    std::sort(filenameList.begin(), filenameList.end());
    for(const auto& archivo : filenameList) {

 std::cout << "Leyendo el archivo: " << archivo << std::endl;
}
}


void ReadData::Init(TTree *tree)
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
   

  
    // Crear Archivo de Salida
   std::cout << "Antes de crear el archivo" << std::endl;
    outputFile = new TFile("global_Tree.root", "UPDATE"); //se crea el archivo global_Tree.root y si existe lo abre para editarlo
std::cout << "Despues de crear global_Tree.root" << std::endl;
    //outputFile = new TFile(outputFileName,"RECREATE"); 
 
   myTree = new TTree("myTree", "Conversión de Tupla a Tree");
   
   

    myTree->Branch("nPw", &nPw, "nPw/I: Indicacor de Data origen");
    myTree->Branch("ev", &ev, "ev/I:numero de Evento dentro de nPw");
    myTree->Branch("ePw", &ePw, "ePw/I: numero de evento macro");
    myTree->Branch("tt", tt, TString("tt[")+kNsample+"]/F: variable temporal");
    myTree->Branch("vv0", vv0,TString("vv0[")+kNsample+"]/F: Señal MPPC");
    myTree->Branch("vv1", vv1,TString("vv1[")+kNsample+"]/F: Señal Anodo");
    myTree->Branch("vv2", vv2,TString("vv2[")+kNsample+"]/F: Señal último dinodo");
    myTree->Branch("eVals", eVals,"eVals[9]/F:Calculos Q[3], min(V[3]) min(T[3])");
    //----------CArga  con corte temporal 
    myTree->Branch("QC0",&QC0, "QC0/F: Carga con corte Señal MPPC ");
    myTree->Branch("QC1",&QC1, "QC1/F: Carga con corte Señal Anodo ");
    myTree->Branch("QC2",&QC2, "QC2/F: Carga con corte Señal último dinodo ");

   Notify();
}

Bool_t ReadData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ReadData::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ReadData::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ReadData_cxx
