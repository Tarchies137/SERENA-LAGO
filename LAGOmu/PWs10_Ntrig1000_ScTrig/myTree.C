#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include <memory> //Esto esá sugerido por chat GPT ---------------

void tree() {

//Utilizar punteros inteligentes para gestionar la memoria del equipo
    // Crear el archivo ROOT
   

    // Abrir el archivo de datos
    std::unique_ptr<TFile> _file0(TFile::Open("PW0_LAGOmu.root"));
     std::unique_ptr<TFile> f(new TFile("myTree.root", "recreate"));
//--------------------------------------------------------------     
/*  //Se cambia por punteros inteligentes
   TFile *f = new TFile("myTree.root","recreate");
   TFile *_file0 = TFile::Open("PW0_LAGOmu.root");
  */
    TNtuple *drs4data = (TNtuple*)_file0->Get("drs4data");
    TTree myTree("myTree", "Conversión de Tupla a Tree");

    Float_t tt[1024],t,vv0[1024], v0,vv1[1024], v1,vv2[1024], v2; 
    Int_t ev;
   
    // Establecer la dirección de memoria de t,v0,v1 y v2
    drs4data->SetBranchAddress("t", &t);
    drs4data->SetBranchAddress("v0", &v0);
    drs4data->SetBranchAddress("v1", &v1);
    drs4data->SetBranchAddress("v2", &v2);
    myTree.Branch("ev", &ev, "ev/I");
    myTree.Branch("tt", tt, "tt[1024]/F");
    myTree.Branch("vv0", vv0, "vv0[1024]/F");
    myTree.Branch("vv1", vv1, "vv1[1024]/F");
    myTree.Branch("vv2", vv2, "vv2[1024]/F");
    // Llenar el árbol
    for (Int_t i = 0; i < 1000; i++) {
        ev = i;
       for (Int_t j = 0; j < 1024; j++) {
            drs4data->GetEntry(j + i * 1024);
            tt[j] = t;
            vv0[j] = v0;
            vv0[j] = v1;
            vv0[j] = v2;
        }
        myTree.Fill();
    }

    // Cerrar el archivo de datos
    _file0->Close();

    // Guardar la cabecera del árbol
    myTree.Write();

    // Cerrar el archivo ROOT
    f->Close();
}


