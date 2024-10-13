#define TreeConvert_cxx
#include "TreeConvert.h"
#include <TSystemDirectory.h>
#include <TList.h>
#include <TString.h>

// Constructor
TreeConvert::TreeConvert(TTree *tree) : fChain(0) {
    if (tree == nullptr) return;
    Init(tree);
}

// Destructor
TreeConvert::~TreeConvert() {
    if (!fChain) return;
    delete fChain->GetCurrentFile();
}

void TreeConvert::Init(TTree *tree) {
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);

    // Configurar las direcciones de las ramas de entrada
    fChain->SetBranchAddress("t", &t, &b_t);
    fChain->SetBranchAddress("v0", &v0, &b_v0);
    fChain->SetBranchAddress("v1", &v1, &b_v1);
    fChain->SetBranchAddress("v2", &v2, &b_v2);

    Notify();
}

void TreeConvert::Loop() {
    if (fChain == 0) return;

    // Archivo de salida y nuevo TTree
    TFile *outputFile = new TFile("global_TreeConvert.root", "UPDATE");
    TTree *myTree = new TTree("myTree", "Consolidated data");

    // Variables para las nuevas ramas
    Float_t tt[1024], vv0[1024], vv1[1024], vv2[1024];
    TString name;
    Int_t even = 0, nPw = 0;

    // Configuración de ramas
    myTree->Branch("tt", tt, "tt[1024]/F");
    myTree->Branch("vv0", vv0, "vv0[1024]/F");
    myTree->Branch("vv1", vv1, "vv1[1024]/F");
    myTree->Branch("vv2", vv2, "vv2[1024]/F");
    myTree->Branch("name", &name);
    myTree->Branch("even", &even, "even/I");
    myTree->Branch("nPw", &nPw, "nPw/I");

    // Cargar archivos del directorio
    TSystemDirectory dir(".", ".");
    TList *files = dir.GetListOfFiles();
    TIter next(files);
    TSystemFile *file;
    int EV = 0; // Definición evento marco global

    while ((file = (TSystemFile*)next())) {
        TString fileName = file->GetName();
        if (!file->IsDirectory() && fileName.EndsWith(".root")) {
            // Abrir archivo y cargar árbol
            TFile *inputFile = TFile::Open(fileName);
            inputFile->GetObject("drs4data", fChain);
            if (!fChain) continue;

            // Establecer el nombre del archivo y reiniciar nPw
            name = fileName(0, fileName.Length() - 5);  // Sin extensión
            nPw = 0;
            Long64_t nentries = fChain->GetEntries();

            // Procesar en bloques de 1024 eventos
            int index = 0;
            for (Long64_t i = 0; i < nentries; i++) {
                fChain->GetEntry(i);

                // Asignar cada evento en los arrays correspondientes
                tt[index] = t;
                vv0[index] = v0;
                vv1[index] = v1;
                vv2[index] = v2;
                index++;

                // Cuando completamos 1024 eventos, llenamos el árbol
                if (index == 1024) {
                    even++;   // Contador global de eventos
                    nPw++;    // Contador de eventos en el archivo actual
                    myTree->Fill(); // Guardar bloque de 1024 eventos
                    index = 0; // Reiniciar índice para el siguiente bloque
                }
            }

            inputFile->Close();
            delete inputFile;
        }
    }

    // Guardar y cerrar archivo de salida
    outputFile->cd();
    myTree->Write();
    outputFile->Close();
}

Int_t TreeConvert::Cut(Long64_t entry) {
    return 1;
}

Int_t TreeConvert::GetEntry(Long64_t entry) {
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}

Long64_t TreeConvert::LoadTree(Long64_t entry) {
    if (!fChain) return -5;
    Long64_t centry = fChain->LoadTree(entry);
    if (centry < 0) return centry;
    if (fChain->GetTreeNumber() != fCurrent) {
        fCurrent = fChain->GetTreeNumber();
        Notify();
    }
    return centry;
}

Bool_t TreeConvert::Notify() {
    return kTRUE;
}

void TreeConvert::Show(Long64_t entry) {
    if (!fChain) return;
    fChain->Show(entry);
}

