#include "TFile.h"
#include "TTree.h"

void CombineTrees(const char* inputFileName) {
    // Abre el archivo de entrada
    TFile* inputFile = TFile::Open(inputFileName);
    if (!inputFile || inputFile->IsZombie()) {
        std::cerr << "Error: No se pudo abrir el archivo de entrada: " << inputFileName << std::endl;
        return;
    }

    // Obtiene el árbol del archivo de entrada
    TTree* inputTree = dynamic_cast<TTree*>(inputFile->Get("myTree"));
    if (!inputTree) {
        std::cerr << "Error: No se encontró el árbol 'myTree' en el archivo de entrada: " << inputFileName << std::endl;
        inputFile->Close();
        return;
    }

    // Abre el archivo de salida
    TFile* outputFile = TFile::Open("global_Tree.root", "UPDATE"); //Si no existe se crea
    if (!outputFile || outputFile->IsZombie()) {
        std::cerr << "Error: No se pudo abrir el archivo de salida: global_Tree.root" << std::endl;
        inputFile->Close();
        return;
    }
//-------------------------------------------------------------------------------
    // Crea un nuevo árbol en el archivo de salida
    TTree* outputTree = dynamic_cast<TTree*>(outputFile->Get("global_Tree"));
    if (!outputTree) {
        outputTree = new TTree("global_Tree", "Árbol combinado");   
          // Copia las ramas del árbol de entrada al árbol de salida
    TObjArray* branches = inputTree->GetListOfBranches();
    for (Int_t i = 0; i < branches->GetEntries(); ++i) {
        TBranch* branch = dynamic_cast<TBranch*>(branches->At(i));
        if (branch) {
            // Obtiene la información de la rama y la agrega al árbol de salida
            outputTree->Branch(branch->GetName(), branch->GetAddress(), branch->GetTitle());
        }
    }
    }
    
        // Agrega las entradas del árbol de entrada al árbol de salida como amigos
    outputTree->AddFriend(inputTree);

    // Escribe el árbol combinado en el archivo de salida
    outputFile->cd();
    outputTree->Write("", TObject::kOverwrite);

    // Cierra los archivos
    inputFile->Close();
    outputFile->Close();
}

// Función principal
void CombineTrees() {
    // Llama a la función para combinar los árboles
    CombineTrees("archivo_de_entrada.root");
}
