// root script file

#include "TFile.h"
#include "TTree.h"
#include <cmath>

void GetTDM_Totals(const char* TDMRootFileName){
	Long64_t Entries;
	Double_t Edep[4] = {0};
	Double_t Edep_total[4] ={ 0 };
	Double_t Dodep[4] = {0};
	Double_t Dodep_total[4] = {0};

	TFile *TDMRootFile = new TFile( TDMRootFileName );
	TTree *TDMTree = (TTree*)TDMRootFile->Get("TDM;1");
	Entries = TDMTree->GetEntriesFast();
	for( Int_t j = 0; j < 4 ; j++)
	{
		string n;
	 	std::stringstream convert;
	 	convert << j;
	 	n = convert.str();
		string name1 = n + "Edep";
		string name2 = n + "Dodep";
		TDMTree->SetBranchAddress(name1.c_str(),&Edep[j]);
		TDMTree->SetBranchAddress(name2.c_str(),&Dodep[j]);
	}

	for(Long64_t i = 0; i < Entries ; i++ )
	{
		TDMTree->GetEntry(i);
		for (Int_t k = 0; k < 4 ; k++ ) 
		{
			Edep_total[k] += Edep[k];
			Dodep_total[k] += Dodep[k];
		}
	}

	cout << "Número de entradas: "<< Entries << endl;
	for( Int_t l = 0; l < 4 ; l++)
	{
		cout << "Energía depositada: " << Edep_total[l]*1000 << " KeV"<< endl;
		cout << "Dosis: " << Dodep_total[l]*(1e12) << " Gy"<< endl;
	}
} 

