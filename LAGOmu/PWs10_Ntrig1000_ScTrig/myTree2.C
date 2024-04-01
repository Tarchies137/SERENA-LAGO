#include <stdio.h>
#include <stdlib.h>
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"

void tree1w() {
    // Crear un archivo ROOT llamado myTree.root
    TFile *f = new TFile("myTree.root", "recreate");
    // Crear un árbol y ramas
    TTree *myTree = new TTree("myTree", "Conversión de Tupla a Tree");

    // Abrir el archivo de datos
    TFile *_file0 = TFile::Open("PW0_LAGOmu.root");
    if (!_file0) {
        fprintf(stderr, "Error: No se pudo abrir el archivo PW0_LAGOmu.root\n");
        return;
    }

    // Obtener la tupla del archivo de datos
    TNtuple *drs4data = (TNtuple*)_file0->Get("drs4data");

    // Declarar las variables
    Float_t vv0[1024], v0; 
    Int_t ev;

    // Establecer la dirección de memoria de v0
    drs4data->SetBranchAddress("v0", &v0);

    // Crear las ramas del árbol
    myTree->Branch("ev", &ev, "ev/I");
    myTree->Branch("vv0", vv0, "vv0[1024]/F");

    // Llenar el árbol
    for (Int_t i = 0; i < 10000; i++) {
        ev = i;
        for (Int_t j = 0; j < 1024; j++) {
            drs4data->GetEntry(j + i * 1024);
            vv0[j] = v0;
        }
        myTree->Fill();
    }

    // Cerrar el archivo de datos
    _file0->Close();

    // Guardar la cabecera del árbol. El archivo se cerrará automáticamente
    myTree->Write();
    delete f;
}

void tree1() {
    tree1w();
}

int main() {
    tree1();
    return 0;
}

