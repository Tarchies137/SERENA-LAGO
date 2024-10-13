//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Based on the provided specifications.
//////////////////////////////////////////////////////////

#ifndef TreeConvert_h
#define TreeConvert_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>

// Constante para definir el tamaño de los bloques
const Int_t kNsample = 1024;

class TreeConvert {
public:
    TTree          *fChain;    //! Pointer to the analyzed TTree or TChain
    Int_t           fCurrent;  //! Current Tree number in a TChain

    // Variables para las ramas de entrada
    Float_t t, v0, v1, v2;

    // Variables para las ramas de salida
    Float_t tt[kNsample], vv0[kNsample], vv1[kNsample], vv2[kNsample];
    TString name;
    Int_t even;    // Contador global de eventos
    Int_t nPw;     // Contador de eventos por archivo

    // Ramas de entrada
    TBranch *b_t;    //! Branch for t
    TBranch *b_v0;   //! Branch for v0
    TBranch *b_v1;   //! Branch for v1
    TBranch *b_v2;   //! Branch for v2

    // Métodos estándar
    TreeConvert(TTree *tree = nullptr);
    virtual ~TreeConvert();
    virtual Int_t    Cut(Long64_t entry);
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     Loop();
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);
};

#endif

