//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Apr 25 12:08:11 2024 by ROOT version 6.18/04
// from TTree drs4data/drs4 data
// found on file: PW3_LAGOmu.root
//////////////////////////////////////////////////////////

#ifndef drs4data_h
#define drs4data_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class drs4data {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         evn;
   Float_t         evn_time;
   Float_t         t;
   Float_t         v0;
   Float_t         v1;
   Float_t         v2;

   // List of branches
   TBranch        *b_evn;   //!
   TBranch        *b_evn_time;   //!
   TBranch        *b_t;   //!
   TBranch        *b_v0;   //!
   TBranch        *b_v1;   //!
   TBranch        *b_v2;   //!

   drs4data(TTree *tree=0);
   virtual ~drs4data();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef drs4data_cxx
drs4data::drs4data(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("PW3_LAGOmu.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("PW3_LAGOmu.root");
      }
      f->GetObject("drs4data",tree);

   }
   Init(tree);
}

drs4data::~drs4data()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t drs4data::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t drs4data::LoadTree(Long64_t entry)
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

void drs4data::Init(TTree *tree)
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
   Notify();
}

Bool_t drs4data::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void drs4data::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t drs4data::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef drs4data_cxx
