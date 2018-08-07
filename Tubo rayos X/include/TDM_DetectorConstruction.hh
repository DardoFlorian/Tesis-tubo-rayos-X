#ifndef TDM_DetectorConstruction_h
#define TDM_DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"


class G4LogicalVolume;
class TDMMainVolume;


class TDM_DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  // constructor and destructor.
  TDM_DetectorConstruction();
  virtual ~TDM_DetectorConstruction();
  virtual void ConstructSDandField();
  void SetDefaults();

  // virtual method from G4VUserDetectorConstruction.
  virtual G4VPhysicalVolume* Construct();


  // TLD construction
  inline void TDM_TLD_Cons( G4Material* Material, G4LogicalVolume* MotherVolume, G4String Name, G4ThreeVector Position,G4double X, G4double Y,G4double Z, G4int T,G4double Rx,G4double Ry,G4double Rz);
  inline void TDM_SetTLD_SD(  G4String Name );
  inline void Paredes_Cons( G4Material* Material, G4LogicalVolume* MotherVolume, G4String Name, G4ThreeVector Position,G4double X, G4double Y,G4double Z);

  // Data members

  // World cube
  G4int WorldCube_SizeHalfX;
  G4int WorldCube_SizeHalfY;
  G4int WorldCube_SizeHalfZ;

  // Water cube
  G4int WaterCube_SizeHalf;

  /********************************Camilla ***************************/
  G4double camilla_X;
  G4double camilla_Y;
  G4double camilla_Z;

  /**************************  Cilindro para blindaje *********************/

  G4double Radio_interno;
    G4double Radio_externo;
    G4double Altura_cilindro;
    G4double Angulo_Inicial;
    G4double Angulo_Final;
    G4double Grosor_cilindro;
    G4double Diagonal_campo;

    /************************* Tapadera cilindro blindaje ****************/

    G4double Radio_interno_tapadera;
        G4double Radio_externo_tapadera;
        G4double Altura_tapadera;
        G4double Angulo_Inicial_tapadera;
        G4double Angulo_Final_tapadera;

     /***************************Detector de prueba *********************/
        //Placa Detectora
        G4double DetectorX_SizeHalf;
        G4double DetectorY_SizeHalf;
        G4double DetectorZ_SizeHalf;

        //Detector brazo C
        G4double Radio_interno_detector;
        G4double Radio_externo_detector;
        G4double Altura_detector;
		G4double Angulo_Inicial_detector;
		G4double Angulo_Final_detector;


       G4LogicalVolume* SensitiveDetector;

     /************************* Primitive Score ***********************/

       G4double TLD_HalfSizeX;
       G4double TLD_HalfSizeY;
       G4double TLD_HalfSizeZ;

       /****************** TLD100 Number **************************/
       G4int TLDNumber;

       /********************* PMMA ********************************/
       G4double PMMAX_SizeHalf;
       G4double PMMAY_SizeHalf;
       G4double PMMAZ_SizeHalf;

       /**********************Paredes********************************/
       G4double Pared_SizeHalfX;
	   G4double Pared_SizeHalfY;
	   G4double Pared_SizeHalfZ;
	   G4double Pared_GrosorMedio;
};
#endif
