// root script file

#include "TFile.h"
#include "TTree.h"
#include "TThread.h"
#include <cmath>

const unsigned N_Thread     = 3;    // número de hilos a usar
const Int_t    TLD_Number   = 4;    // numero de TLD utilizados en Geant4

struct TDM_Struct
{
  const char    *RootFileName;
  Double_t       EdepTotal     [ TLD_Number ];
  Double_t       DodepTotal    [ TLD_Number ];
} TDM_Data;
  
void *GetTDM_Partials(void *ThreadId_ptr)
{

  long Thread_Id = (long) ThreadId_ptr;
        Long64_t Entries;
        Double_t AbsoEdep      [ TLD_Number ] = { 0 };
        Double_t AbsoDodep     [ TLD_Number ] = { 0 };
        Double_t Edep_partial  [ TLD_Number ] = { 0 };
        Double_t Dodep_partial [ TLD_Number ] = { 0 };

        TFile *TDMRootFile = new TFile( TDM_Data.RootFileName );
        TTree *TDMTree = (TTree*)(TDMRootFile)->Get("TDM;1");

        Entries = TDMTree->GetEntriesFast();
        Long64_t Init_val;
        Long64_t End_val;


        switch( Thread_Id ){
        case -2 :
          {
            Init_val = 0;
            End_val = Entries;
            break;
          }
        case -1 :
          {
            Long64_t N_Elems = (Long64_t)floor( Entries / (N_Thread - 1));
            Init_val = (N_Thread-1)*N_Elems;
            End_val = Entries;
            break;
          }
        default :
          {
            if( ( Thread_Id >= 0 ) && ( Thread_Id < ( N_Thread - 1 ) ) ){
                Long64_t N_Elems = (Long64_t)floor( Entries / (N_Thread - 1));
                Init_val = Thread_Id*N_Elems;
                End_val = (Thread_Id + 1)*N_Elems;
  }
            else
              {
                std::cout << "Numero de hilo invalido! (Thread_Id = " << Thread_Id << " )" << std::endl;
                return 0;
              }
            break;
          }
        }

        for( Int_t j = 0; j < TLD_Number ; j++)
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

        for(Long64_t i = Init_val; i < End_val ; i++ )
        {
                TDMTree->GetEntry(i);
                for (Int_t k = 0; k < TLD_Number  ; k++ ) 
                {
                        Edep_partial[k] += AbsoEdep[k];
Dodep_partial[k] += AbsoDodep[k];
                }
        }


        TThread::Lock();
        for (Int_t m = 0; m < TLD_Number  ; m++ ) 
        {
          TDM_Data.EdepTotal[m]  += Edep_partial[m];
          TDM_Data.DodepTotal[m] += Dodep_partial[m];
        }
        cout << "-------------------------------------------" << endl;
        cout << "(Th_ID "<< Thread_Id << ") Número de entradas: "<< End_val - Init_val << endl;
        cout << "(Th_ID "<< Thread_Id << ") Intervalo: "<< Init_val << " - " << End_val << endl;
        for( Int_t l = 0; l < TLD_Number ; l++)
        {
          cout << "(Th_ID "<< Thread_Id << ") Energía depositada: " << Edep_partial[l]*1000 << " KeV"<< endl;
          cout << "(Th_ID "<< Thread_Id << ") Dosis: " << Dodep_partial[l]*(1e+12) << " Gy"<< endl;
        }
        TThread::UnLock();

        return 0;
} 


void GetTDM_Totals_p(const char* TDMRootFileName)
{



  TDM_Data.RootFileName = TDMRootFileName;
  
        TThread *Threads     [ N_Thread -1 ];
        for(long i=0 ; i < ( N_Thread - 1 ) ; ++i )
        {
          Threads[i] = new TThread( GetTDM_Partials, (void*) i);
          Threads[i] -> Run();
        }
        GetTDM_Partials( (void*) -1 );


        //gSystem->Sleep(100);
        //gSystem->ProcessEvents();

        for(unsigned j=0 ; j < ( N_Thread - 1 ) ; ++j )
          Threads[j] -> Join();

        gSystem->Sleep(100);

        for( Int_t l = 0; l < TLD_Number ; l++)
        {
          cout << "================= TOTALES =================" << endl;
          cout << "Energía depositada: " << TDM_Data.EdepTotal[l]*1000 << " KeV"<< endl;
          cout << "Dosis: " << TDM_Data.DodepTotal[l]*(1e+12) << " Gy"<< endl;
          cout << "===========================================" << endl;
        }
}

void GetTDM_Totals(const char* TDMRootFileName)
{
    TDM_Data.RootFileName = TDMRootFileName;
    GetTDM_Partials( (void*) -2 );
}

