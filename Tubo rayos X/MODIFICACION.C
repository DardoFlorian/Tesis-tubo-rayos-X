// root script file

#include "TFile.h"
#include "TTree.h"
#include <cmath>

void GetTDM_Totals(const char* TDMRootFileName){
	
	const Int_t m = 1; // Número de TLD utilizados en Geant4

	Long64_t Entries;
	Double_t AbsoEdep[m] = {0};
	Double_t Edep_total[m] ={ 0 };
	Double_t AbsoDodep[m] = {0};
	Double_t Dodep_total[m] = {0};

	TFile *TDMRootFile = new TFile( TDMRootFileName );
	TTree *TDMTree = (TTree*)TDMRootFile->Get("TDM;1");
	Entries = TDMTree->GetEntriesFast();
	for( Int_t j = 0; j < m ; j++)
	{
		string n;
	 	std::stringstream convert;
	 	convert << j;
	 	n = convert.str();
		string name1 = n + "AbsoEdep";
		string name2 = n + "AbsoDodep";
		TDMTree->SetBranchAddress(name1.c_str(),&AbsoEdep[j]);
		TDMTree->SetBranchAddress(name2.c_str(),&AbsoDodep[j]);
	}

	for(Long64_t i = 0; i < Entries ; i++ )
	{
		TDMTree->GetEntry(i);
		for (Int_t k = 0; k < m ; k++ ) 
		{
			Edep_total[k] += AbsoEdep[k];
			Dodep_total[k] += AbsoDodep[k];
		}
	}

	cout << "Número de entradas: "<< Entries << endl;
	for( Int_t l = 0; l < m ; l++)
	{
		cout << "Energía depositada: " << Edep_total[l]*1000 << " KeV"<< endl;
		cout << "Dosis: " << Dodep_total[l]*(1e+12) << " Gy"<< endl;
	}
} 

