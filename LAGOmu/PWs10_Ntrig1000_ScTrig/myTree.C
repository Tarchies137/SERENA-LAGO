#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

 
void tree1w()
{
   //create a Tree file tree1.root
 
   //create the file, the Tree and a few branches
   TFile f("myTree.root","recreate");
   TTree t1("t1","Conversión  de Tupla a Tree");
   TFile *_file0 = TFile::Open("PW0_LAGOmu.root");

   /*Float_t px, py, pz;
   Double_t random;*/
   Int_t ev;
   /*t1.Branch("px",&px,"px/F");
   t1.Branch("py",&py,"py/F");
   t1.Branch("pz",&pz,"pz/F");
   t1.Branch("random",&random,"random/D");*/
   t1.Branch("ev",&ev,"ev/I");
 
   //fill the tree
   for (Int_t i=0;i<10000;i++) {/*
     gRandom->Rannor(px,py);
     pz = px*px + py*py;
     random = gRandom->Rndm();*/
     ev = i;
     t1.Fill();
  }
/* _file0->Close();*/

  //save the Tree header. The file will be automatically closed
  //when going out of the function scope
  t1.Write();
}
 
void tree1() {
   tree1w();
  // tree1r();
}
