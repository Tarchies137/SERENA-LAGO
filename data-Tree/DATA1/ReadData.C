#define ReadData_cxx
#include "ReadData.h"
#include <TH2.h>
#include <dirent.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSystem.h> // Agregar la inclusión de la biblioteca TSystem

void ReadData::Loop() {
    int EV = 0; // Definición evento marco global

    if (fChain == 0) {
        std::cerr << "Error: fChain no está inicializado." << std::endl;
        return;
    }

    for (const auto& filename : filenameList) {
        std::cout << "Leyendo el archivo: " << filename << std::endl;
        sleep(1);

        // Conectar el archivo y leer el TTree "drs4data"
        TFile* f = TFile::Open(filename.c_str());
        if (!f || !f->IsOpen()) {
            std::cerr << "Error: No se pudo abrir el archivo: " << filename << std::endl;
            continue; // Saltar al siguiente archivo en caso de error
        }

        // Intentar obtener el TTree "drs4data"
        TTree* tree = nullptr;
        f->GetObject("drs4data", tree);
        if (!tree) {
            std::cerr << "Warning: No se encontró el TTree 'drs4data' en el archivo: " << filename << std::endl;
            f->Close(); // Cerrar el archivo antes de continuar
            continue; // Saltar al siguiente archivo
        }

        // Obtener el número de data
        char cPw = filename[filename.length() - 13];
        nPw = cPw - '0';

        Long64_t nentries = fChain->GetEntriesFast() / kNsample;
        Long64_t nbytes = 0, nb = 0;

        for (Long64_t jentry = 0; jentry < nentries; jentry++) {
            Long64_t ientry = LoadTree(jentry);
            if (ientry < 0) break;

            // Número de evento
            ev = jentry;
            ePw = EV + ev; // Identificador evento global

            Float_t sR0 = 0, sR1 = 0, sR2 = 0;
            Float_t t0_min, v0_min = 1000, t1_min, v1_min = 1000, t2_min, v2_min = 1000;

            for (Int_t j = 0; j < kNsample; j++) {
                nb = fChain->GetEntry(j + jentry * kNsample);
                nbytes += nb;
                tt[j] = t;
                vv0[j] = v0;
                vv1[j] = v1;
                vv2[j] = v2;

                sR0 += v0;
                sR1 += v1;
                sR2 += v2;

                if (v0 < v0_min) {
                    v0_min = v0;
                    t0_min = t;
                }
                if (v1 < v1_min) {
                    v1_min = v1;
                    t1_min = t;
                }
                if (v2 < v2_min) {
                    v2_min = v2;
                    t2_min = t;
                }
            }

            // Carga total colectada
            Float_t dt = (tt[kNsample - 1] - tt[0]) / (kNsample - 1);

            Q[0] = sR0 * dt / R;
            Q[1] = sR1 * dt / R;
            Q[2] = sR2 * dt / R;
            V_Min[0] = v0_min;
            V_Min[1] = v1_min;
            V_Min[2] = v2_min;
            T_Min[0] = t0_min;
            T_Min[1] = t1_min;
            T_Min[2] = t2_min;

            for (int i = 0; i <= 8; ++i) {
                if (i < 3) {
                    eVals[i] = Q[i];
                } else if (i >= 3 && i < 6) {
                    eVals[i] = V_Min[i - 3];
                } else {
                    eVals[i] = T_Min[i - 6];
                }
            }

            std::cout << "evento " << ePw << " en archivo " << filename << " con v0: " << v0 << std::endl;

            myTree->Fill();
        }

        // Cerrar el archivo de entrada
        f->Close();

        std::cout << "Escribiendo los datos de: " << filename << std::endl;

        // Actualizar el contador de eventos global
        EV = ePw + 1;
    }

    // Guardar el árbol en el archivo de salida
    outputFile->cd();
    myTree->Write();

    // Cerrar el archivo de salida
    outputFile->Close();
}
