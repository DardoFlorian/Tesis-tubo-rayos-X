#include <math.h>
#include "TDM_DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4RotationMatrix.hh"
//#include "TDMSD.hh" // Incluye la clase para utilizar Sensitive Detector
#include "G4SDManager.hh"
#include "G4SDManager.hh"
#include "G4SDChargedFilter.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4PSTrackLength.hh"
#include "G4PhysicalConstants.hh"

/*******Librerias para asignar color **************/
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Color.hh"


TDM_DetectorConstruction::TDM_DetectorConstruction()
: G4VUserDetectorConstruction()
{
	// World cube (world)
	WorldCube_SizeHalfX	= (4.770/2.0)*m + (0.2/2.0)*m ; // De la puerta a la pared del fondo
	WorldCube_SizeHalfY	= (3.476/2.0)*m + (0.2/2.0)*m; // De la pared derecha a la izquierda
	WorldCube_SizeHalfZ	= (2.460/2.0)*m + (0.2/2.0)*m; // Del piso al techo

	/****************** Water cube (world)********************************/

	WaterCube_SizeHalf	= 0.50*m;

	 /*************************Camilla*************************************/

	 camilla_X = (2.0/2.0)*m;
	 camilla_Y = (0.43/2.0)*m;
	 camilla_Z = (0.02/2.0)*m;

	 /***********Blindaje de forma cilindrica *******/

	 Grosor_cilindro = 0.5*cm;
	 Diagonal_campo = 8.2*cm;
	 Radio_interno = Diagonal_campo/2;
	 Radio_externo = Radio_interno + Grosor_cilindro;
	 Altura_cilindro = (0.425/2)*m;
	 Angulo_Inicial = 0. *deg;
	 Angulo_Final = 360. *deg;

	 /********** Tapadera *********************/
	 Radio_interno_tapadera = 0. *m;
	 Radio_externo_tapadera = Radio_externo;
	 Altura_tapadera = Grosor_cilindro/2;
	 Angulo_Inicial_tapadera = 0. *deg;
	 Angulo_Final_tapadera  = 360.*m;

	 /**************Detector de prueba *****/

	 //Placa Detectora
	 DetectorX_SizeHalf=1*m;
	 DetectorY_SizeHalf=1*m;
	 DetectorZ_SizeHalf=0.0005*m;
	 SensitiveDetector = 0;

	 //Detector brazo C
	 Radio_interno_detector = 0.0*m;
	 Radio_externo_detector = (38.2/2)*cm;
	 Altura_detector = (0.1/2.0)*m;
	 Angulo_Inicial_detector = 0*deg;
	 Angulo_Final_detector = 360*deg;

	 /************ Primitive Score *******/

	 TLD_HalfSizeY = (2.2/2.0)*cm;
	 TLD_HalfSizeX = (11.6/2.0)*cm;
	 TLD_HalfSizeZ = (1.25/2.0)*cm;

	 /************ TLDNumber **************/

	 TLDNumber = 3; //Número de detectores

	 /********************* PMMA ********************************/
	  PMMAX_SizeHalf=0.20/2*m;
	  PMMAY_SizeHalf=0.20/2*m;
      PMMAZ_SizeHalf=(16.7/2.0)*cm;

	  /**********************Paredes*****************************/

	  Pared_SizeHalfX = (4.770/2.0)*m;
	  Pared_SizeHalfY	= (3.476/2.0)*m ;
	  Pared_SizeHalfZ	= (2.460/2.0)*m ;
	  Pared_GrosorMedio = (0.1/2.0)*m;

}

TDM_DetectorConstruction::~TDM_DetectorConstruction()
{ }

G4VPhysicalVolume* TDM_DetectorConstruction::Construct()
{
//rotation

	G4RotationMatrix* myRotation = new G4RotationMatrix();
	 myRotation->rotateX(90.*deg);
	 myRotation->rotateY(0.*deg);
	 myRotation->rotateZ(0.*rad);


  // Some elements
  G4double a, z, density;
  G4int nelements;

  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* H = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
  G4Element* C = new G4Element("Carbon", "C",z=12, a = 12.01*g/mole);
  G4Element* Pb = new G4Element("Lead" , "L" , z=82, a=207.2*g/mole);
  G4Element* Li6 = new G4Element("Lithium6", "Li6", z=3, a=6.015*g/mole);
  G4Element* Li7 = new G4Element("Lithium7", "Li7", z=3, a=7.016*g/mole);
  G4Element* F = new G4Element("Fluorine", "F", z=9, a=18.99*g/mole);
  G4Element* Ti = new G4Element("Titanium", "Ti",z=22,a=47.867*g/mole);
  G4Element* Mg = new G4Element("Magnesium", "Mg",z=12,a=24.305*g/mole);

  //Vacuum Geant4
  //  G4Material* vacuum = new G4Material("vacuum", z=1., a=1.01*g/mole, density=universe_mean_density, kStateGas, 0.1*kelvin, 1.e-19*pascal);

    //Fluoruros de Litio
    G4Material* LiF6 = new G4Material("LiF6", density= 2.55*g/cm3, nelements=2);
    LiF6->AddElement(F, 1);
    LiF6->AddElement(Li6, 1);

    G4Material* LiF7 = new G4Material("LiF7", density= 2.65*g/cm3, nelements=2);
    LiF7->AddElement(F, 1);
    LiF7->AddElement(Li7, 1);

    // TLD100
    G4Material* TLD100 = new G4Material("TLD100", density= 2.65*g/cm3, nelements=4);
    TLD100->AddMaterial(LiF6, 7.5995*perCent);
    TLD100->AddMaterial(LiF7, 92.3795*perCent);
    TLD100->AddElement(Mg, 0.02*perCent);
    TLD100->AddElement(Ti, 0.001*perCent);

  // Air (definido por nosotros)
  G4Material* air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
  air->AddElement(N, 70.*perCent);
  air->AddElement(O, 30.*perCent);

  // Water material
  G4Material* water = new G4Material("Water", density= 1.0*g/cm3, nelements=2);
  water->AddElement(H, 2);
  water->AddElement(O, 1);

  //PMMA material
  G4Material* pmma = new G4Material("pmma", density=1.19*g/cm3, nelements=3);
  pmma->AddElement(C, 5);
  pmma->AddElement(H, 8);
  pmma->AddElement(O, 2);


  // Carbon Fiber
  G4Material* CarbonFiber = new G4Material("CarbonFiber", density= 0.145*g/cm3, nelements=1);
  CarbonFiber->AddElement(C, 1);

  //Lead
  G4Material* Lead = new G4Material("Lead", density=11.35*g/cm3, nelements=1);
  Lead->AddElement(Pb,1);

  //Concreto
  G4NistManager* man = G4NistManager::Instance(); // G4NistManager permite construir de la base de datos del NIST
  G4Material* concreto = man->FindOrBuildMaterial("G4_CONCRETE");

  //Aire de la base de datos de Geant4
  G4Material* AIRE = man->FindOrBuildMaterial("G4_AIR");

  //Acero para el brazo en C
  G4Material* Acero = man->FindOrBuildMaterial("G4_STAINLESS-STEEL");

  /************************ POLIMERO para el PMMA ************************/

      man->SetVerbose(0);
      G4int polyPmmA = 1;

      std::vector<G4String> PmmA_elm;
      PmmA_elm.push_back("C");
      PmmA_elm.push_back("H");
      PmmA_elm.push_back("O");
      std::vector<G4int> PmmA_nbAtoms;
      PmmA_nbAtoms.push_back(3+2*polyPmmA);
      PmmA_nbAtoms.push_back(6+2*polyPmmA);
      PmmA_nbAtoms.push_back(2);

       //Fiber(PMMA)
     G4Material*  PmmA = man->ConstructNewMaterial("PMMA",PmmA_elm,PmmA_nbAtoms, density=1190*kg/m3);

  /**********************Asignando colores a los sólidos *******************************************/

  // Visualization attributes

  G4VisAttributes* blue = new G4VisAttributes(G4Colour(0.,0.,0.8));
  	  blue -> SetVisibility(true);
  	  blue -> SetForceSolid(true);
  G4VisAttributes* gris = new G4VisAttributes(G4Colour(0.3,0.3,0.3));
  	  gris -> SetVisibility(true);
  	  gris -> SetForceSolid(true);
  G4VisAttributes* black = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
      black -> SetVisibility(true);
      black -> SetForceSolid(true);
  G4VisAttributes* red = new G4VisAttributes(G4Colour(0.7,0.,0.));
      red -> SetVisibility(true);
      red -> SetForceSolid(true);
  G4VisAttributes* green = new G4VisAttributes(G4Colour(0.,0.7,0.));
      green -> SetVisibility(true);
      green -> SetForceSolid(true);
  G4VisAttributes* Brown = new G4VisAttributes(G4Colour(0.7, 0.4, 0.1));
      Brown -> SetVisibility(true);
      Brown -> SetForceSolid(true);

  	  	  	  	  	  	  //=====================================

   /******************************* Volumes definitions************************************/

  // Option to switch on/off checking of volumes overlaps

  G4bool checkOverlaps = false;

  /**************************World: WorldCube acts as world**************************/

  G4Box* solid_WorldCube=
    new G4Box("WorldCube_solid",                       						//its name
    		WorldCube_SizeHalfX, WorldCube_SizeHalfY, WorldCube_SizeHalfZ);    //its size

  G4LogicalVolume* logic_WorldCube =
    new G4LogicalVolume(solid_WorldCube,          							//its solid
                        AIRE,           										//its material
                        "WorldCube_logic");    								//its name

  G4VPhysicalVolume* physical_WorldCube =
    new G4PVPlacement(0,                 								    //no rotation
                      G4ThreeVector(),       								//at (0,0,0)
                      logic_WorldCube,			          					//its logical volume
                      "WorldCube_physical",               					//its name
                      0,                     								//its mother  volume
                      false,                 								//no boolean operation
                      0,                     								//copy number
                      checkOverlaps);        								//overlaps checking

  	 /**************************camilla********************************************/

  G4Box* solid_camilla=
      new G4Box("camilla",
      		camilla_X, camilla_Y, camilla_Z);

  G4LogicalVolume* logic_camilla =
      new G4LogicalVolume(solid_camilla,
                          CarbonFiber,
                          "camilla_logic");

  //G4VPhysicalVolume* physical_camilla =
    new G4PVPlacement(0,
                      G4ThreeVector(-0.105*m,0.288*m,-0.2265*m),
                      logic_camilla,
                      "camilla_physical",
                      logic_WorldCube,
                      false,
                      0,
                      checkOverlaps);
    logic_camilla -> SetVisAttributes(black);

    /***************** Blindaje de forma cilindrica *************/

 G4Tubs* Blindaje_cilindro
   = new G4Tubs("cilindroblindaje",
 		  Radio_interno,
 		  Radio_externo,
 		  Altura_cilindro,
 		  Angulo_Inicial,
 		  Angulo_Final
 		  );

 G4LogicalVolume* logic_cilindroblindaje =
 		new G4LogicalVolume(Blindaje_cilindro,
 				Lead,
 				"cilindroblindaje_logic");

 //G4VPhysicalVolume* physical_WaterCylinder =
 		new G4PVPlacement(0,
 				G4ThreeVector(-0.105*m,0.288*m, 0.538*m ),
 				logic_cilindroblindaje,
 				"Leadclinder_physical",
 				logic_WorldCube,
 				false,
 				0,
 				checkOverlaps
 				);
 logic_cilindroblindaje -> SetVisAttributes(gris);

/*****************Tapadera Blindaje *********************/

 		G4Tubs* Tapadera
 		   = new G4Tubs("tapaderablindaje",
 		 		  Radio_interno_tapadera,
 		 		  Radio_externo_tapadera,
 		 		  Altura_tapadera,
 		 		  Angulo_Inicial_tapadera,
 		 		  Angulo_Final_tapadera
 		 		  );

 		 G4LogicalVolume* logic_tapadera =
 		 		new G4LogicalVolume(Tapadera,
 		 				Lead,
 		 				"tapadera_logic");

 		 //G4VPhysicalVolume* physical_WaterCylinder =
 		 		new G4PVPlacement(0,
 		 				G4ThreeVector(-0.105*m,0.288*m, 0.538*m+Altura_cilindro+Altura_tapadera),
 		 				logic_tapadera,
 		 				"Leadtapadera_physical",
 		 				logic_WorldCube,
 		 				false,
 		 				0,
 		 				checkOverlaps
 		 				);
 		logic_tapadera -> SetVisAttributes(gris);

 /******************* Detector   ****************/
 		//Detector
 		 		G4Tubs* Detector_prueba
 		 		 		   = new G4Tubs("Detector",
 		 		 		 		  Radio_interno_detector ,
 		 		 		 		  Radio_externo_detector ,
 		 		 		 		  Altura_detector,
 		 		 		 		  Angulo_Inicial_detector ,
 		 		 		 		  Angulo_Final_detector
 		 		 		 		  );

 		 		 		 G4LogicalVolume* Logic_Detector =
 		 		 		 		new G4LogicalVolume(Detector_prueba,
 		 		 		 				Acero,
 		 		 		 				"detector_prueba_logic");

 		 		 		 //G4VPhysicalVolume* physical_WaterCylinder =
 		 		 		 		new G4PVPlacement(0,
 		 		 		 				G4ThreeVector(-0.105*m,0.288*m, 0.5255*m - 0.974*m - Altura_detector),
 		 		 		 				Logic_Detector,
 		 		 		 				"Detector_physical",
 		 		 		 				logic_WorldCube,
 		 		 		 				false,
 		 		 		 				0,
 		 		 		 				checkOverlaps
 		 		 		 				);

 		 		 	Logic_Detector -> SetVisAttributes(gris);


 		 //Placa detectora
 		 	/*	G4Box* Detector_prueba=
 		 		 new G4Box("Detector_prueba",
 		 		 		DetectorX_SizeHalf, DetectorY_SizeHalf, DetectorZ_SizeHalf);

 		 		G4LogicalVolume* Logic_Detector =
 		 		 new G4LogicalVolume(Detector_prueba,
 		 		                     vacuum,
 		 		                     "logic_detector");
 		 		//G4VPhysicalVolume* physical_Colimator4 =
 		 		 new G4PVPlacement(0,
 		 		                   G4ThreeVector(-0.5495*m,0.265*m,-0.209*m + camilla_Z),
 		 		                   Logic_Detector,
 		 		                   "physical_detector",
 		 							  logic_WorldCube,
 		 		                   false,
 		 		                   0,
 		 		                   checkOverlaps);     //overlaps checking*/

 		/* 	SensitiveDetector = Logic_Detector;*/   // Definiendo este sólido como SensitiveDetector




 /******************************** Medio Dispersor PMMA *********************************/

G4Box* PMMA=
 		    new G4Box("PMMA",
 		 	PMMAX_SizeHalf,PMMAY_SizeHalf, PMMAZ_SizeHalf);

G4LogicalVolume* logic_PMMA =
 		 		      new G4LogicalVolume(PMMA,
 		 		                          PmmA,
 		 		                          "pmma_logic");

 //G4VPhysicalVolume* physical_camilla =
 new G4PVPlacement(0,
 		 		//G4ThreeVector(-0.105*m,0.288*m,-0.2265*m +camilla_Z + PMMAZ_SizeHalf+ 2*TLD_HalfSizeZ), //Haz Directo o Detector abajo del PMMA
				G4ThreeVector(-0.124*m,0.299*m,-0.2265*m +camilla_Z + PMMAZ_SizeHalf),      //3 Detectores
 		 		logic_PMMA,
 		 		"PMMA_physical",
 		 		logic_WorldCube,
 		 		false,
 		 		0,
 		 		checkOverlaps);

logic_PMMA -> SetVisAttributes(blue);

 /**************************************Arco en C ***********************************************************/

 	//Rectangulo vertical que ilustra un poste

G4Box* Poste = new G4Box("Poste", (0.12/2.0)*m,(0.12/2.0)*m, (1.074/2.0)*m);
G4LogicalVolume* Logic_Poste = new G4LogicalVolume(Poste,Acero,"Poste_Logic");

new G4PVPlacement(0,
  	  	  	  	 G4ThreeVector(-0.105*m,-0.299*m,0.5255*m-(1.074/2.0)*m ),
				 Logic_Poste,
				 "Poste_Physical",
				 logic_WorldCube,
				 false,0,checkOverlaps);

Logic_Poste -> SetVisAttributes(Brown);

 	// C Superior

G4Box* CSuperior = new G4Box("CSuperior", (0.12/2.0)*m,(0.481/2.0)*m, (0.12/2.0)*m);
G4LogicalVolume* Logic_CSuperior = new G4LogicalVolume(CSuperior,Acero,"CS_Logic");

new G4PVPlacement(0,
 		 		 G4ThreeVector(-0.105*m,-0.239*m + (0.481/2.0)*m,0.5255*m-(0.12/2.0)*m),
 		 		 Logic_CSuperior,
 		 		"CS_Physical",
 		 		logic_WorldCube,
 		 		false,0,checkOverlaps);

Logic_CSuperior -> SetVisAttributes(Brown);

 	// C Inferior

G4Box* CInferior = new G4Box("CInferior", (0.12/2.0)*m,(0.336/2.0)*m, (0.10/2.0)*m);
G4LogicalVolume* Logic_CInferior = new G4LogicalVolume(CInferior,Acero,"CI_Logic");

new G4PVPlacement(0,
 		 		G4ThreeVector(-0.105*m,-0.239*m + (0.336/2.0)*m,0.5255*m - 0.974*m - Altura_detector),
 		 		Logic_CInferior,
 		 		"CS_Physical",
 		 		logic_WorldCube,
 		 		false,0,checkOverlaps);

Logic_CInferior -> SetVisAttributes(Brown);


 /*************************************Detectors Primitive Score ****************************/

 		 		/****************Detector 0 ************************************/
//TDM_TLD_Cons(water, logic_WorldCube, "0Abso", G4ThreeVector(-0.105*m,0.288*m,-0.2265*m + camilla_Z+TLD_HalfSizeZ),TLD_HalfSizeX,TLD_HalfSizeY,TLD_HalfSizeZ,1,0,0,0); //ABAJO DEL CENTRO DEL PMMA Y DIRECTA
 		 		/****************Detector 1 ************************************/
TDM_TLD_Cons(water, logic_WorldCube, "0Abso", G4ThreeVector(-0.109*m ,0.301*m,-0.2265*m + camilla_Z + 2*PMMAZ_SizeHalf + TLD_HalfSizeZ),TLD_HalfSizeX,TLD_HalfSizeY,TLD_HalfSizeZ,1,0,0,0); // ARRIBA DEL CENTRO DEL PMMA
 		 		/****************Detector 2 ************************************/
TDM_TLD_Cons(water, logic_WorldCube, "1Abso", G4ThreeVector(-0.091*m,0.299*m + PMMAX_SizeHalf - 0.0025*m + 0.906*m ,-0.147*m),TLD_HalfSizeX,(6.5/2.0)*cm,(0.5/2.0)*cm,0,90.0,0,0.0); // A 1 METRO DEL CENTRO DEL PMMA
 		 		/****************Detector 3 ************************************/
TDM_TLD_Cons(water, logic_WorldCube, "2Abso", G4ThreeVector(-0.124*m + PMMAX_SizeHalf + 2.148*m - 0.0025*m,0.254*m,-0.147*m),TLD_HalfSizeZ,(6.5/2.0)*cm,(0.5/2.0)*cm,0,0.0,90.0,0.0); // PUERTA DE LA CLINICA

/*****************************************Paredes***************************************************/

Paredes_Cons(concreto,logic_WorldCube,"Pared-Puerta1",G4ThreeVector(WorldCube_SizeHalfX-Pared_GrosorMedio,0,0),Pared_GrosorMedio,WorldCube_SizeHalfY,WorldCube_SizeHalfZ);//Pared de la puerta
Paredes_Cons(concreto,logic_WorldCube,"Pared-Puerta2",G4ThreeVector(-WorldCube_SizeHalfX+Pared_GrosorMedio,0,0),Pared_GrosorMedio,WorldCube_SizeHalfY,WorldCube_SizeHalfZ);//Pared de la parte trasera
Paredes_Cons(concreto,logic_WorldCube,"Pared-izquierda",G4ThreeVector(0,WorldCube_SizeHalfY-Pared_GrosorMedio,0),WorldCube_SizeHalfX-2*(Pared_GrosorMedio),Pared_GrosorMedio,WorldCube_SizeHalfZ);//Pared del lado izquierdo
Paredes_Cons(concreto,logic_WorldCube,"Pared-derecho",G4ThreeVector(0,-WorldCube_SizeHalfY+Pared_GrosorMedio,0),WorldCube_SizeHalfX-2*(Pared_GrosorMedio),Pared_GrosorMedio,WorldCube_SizeHalfZ);//Pared del lado derecho
Paredes_Cons(concreto,logic_WorldCube,"Pared-Arriba",G4ThreeVector(0,0,WorldCube_SizeHalfZ-Pared_GrosorMedio),WorldCube_SizeHalfX-2*(Pared_GrosorMedio),WorldCube_SizeHalfY-2*(Pared_GrosorMedio),Pared_GrosorMedio);//Pared de arriba
Paredes_Cons(concreto,logic_WorldCube,"Pared-Abajo",G4ThreeVector(0,0,-WorldCube_SizeHalfZ+Pared_GrosorMedio),WorldCube_SizeHalfX-2*(Pared_GrosorMedio),WorldCube_SizeHalfY-2*(Pared_GrosorMedio),Pared_GrosorMedio);//Pared de abajo


/****************************************************************************************************/


   return physical_WorldCube;
}

/********************************************
 *
 * Esta función define un detector como Primitive Score
 * Se define sus dimensiones,
 * la forma del detector (Rectangulo = 1; Cilindro = 0)
 * Asi como, el angulo que se desea rotar el detector
 *
 ***************************************/
inline void  TDM_DetectorConstruction::TDM_TLD_Cons( G4Material* Material, G4LogicalVolume* MotherVolume, G4String Name, G4ThreeVector Position,G4double X, G4double Y,G4double Z, G4int T,G4double Rx,G4double Ry,G4double Rz)
{
	/************************** Primitive Score ************************/

G4RotationMatrix* myRotation = new G4RotationMatrix();  //Matriz de rotación
		 myRotation->rotateX(Rx*deg);
		 myRotation->rotateY(Ry*deg);
		 myRotation->rotateZ(Rz*deg);

	 if (T == 1){
auto absorberS
	= new G4Box(Name,            // its name
					  X, Y, Z); // its size

auto absorberLV
	= new G4LogicalVolume(
					 absorberS,        // its solid
					 Material, // its material
					 Name.append("LV")); // its name
										//.append() agrega a un texto lo que se encuentre dentro de los parentesis

G4cout << "TDM_TLD_Cons Name: " << Name << G4endl;

new G4PVPlacement(0,
				Position,
				absorberLV,
				Name.append("PL"),
				MotherVolume,
				false,
				0,
				false);

G4VisAttributes* color = new G4VisAttributes(G4Colour(1.0,1.0,0.));//Yellow
color -> SetVisibility(true);
color -> SetForceSolid(true);
color-> SetForceSolid(true);
absorberLV -> SetVisAttributes(color);
	 }

	 if (T == 0){

auto absorberS
			= new G4Tubs(Name,
		  		 		 0.0 ,
		  		 		 Y ,
		  		 		 Z,
		  		 		 0. *deg,
		  		 		 360. *deg);

auto absorberLV
			= new G4LogicalVolume(
						 absorberS,
						 Material,
						 Name.append("LV"));

G4cout << "TDM_TLD_Cons Name: " << Name << G4endl;

new G4PVPlacement(myRotation,
				Position,
				absorberLV,
				Name.append("PL"),
				MotherVolume,
				false,
				0,
				false);

G4VisAttributes* color = new G4VisAttributes(G4Colour(1.0,1.0,0.));//Yellow
color -> SetVisibility(true);
color -> SetForceSolid(true);
color-> SetForceSolid(true);
absorberLV -> SetVisAttributes(color);
		 }
}

/***********************
 *
 * En esta función se declara la información
 * que se desea extraer de los detectores
 *
 ***********************/

inline void TDM_DetectorConstruction::TDM_SetTLD_SD(  G4String Name )
{
	G4SDManager::GetSDMpointer()->SetVerboseLevel(0);
	    // Scorers

	    // declare Absorber as a MultiFunctionalDetector scorer

	    auto Detector = new G4MultiFunctionalDetector(Name);
	    G4SDManager::GetSDMpointer()->AddNewDetector(Detector);

	    G4VPrimitiveScorer* primitive;
	    G4String Edepname = Name+"Edep";
	    primitive = new G4PSEnergyDeposit(Edepname);
	    Detector->RegisterPrimitive(primitive);
	    G4String Dodepname = Name+"Dodep";
	    primitive = new G4PSDoseDeposit(Dodepname);
	    Detector->RegisterPrimitive(primitive);

	    SetSensitiveDetector(Name.append("LV"),Detector);
}


//Superficies Sensibles

void TDM_DetectorConstruction::ConstructSDandField() {

   /*************** Sensitive Detector  *********************/
/* if (!SensitiveDetector) return;

  TDMSD* test_SD = new TDMSD("/TDM/testSD");
  G4SDManager::GetSDMpointer()->AddNewDetector(test_SD);
  SetSensitiveDetector(SensitiveDetector, test_SD);*/

  /*************** Primitive Score  *********************/

  G4SDManager::GetSDMpointer()->SetVerboseLevel(0);
    // Scorers
    // declare Absorber as a MultiFunctionalDetector scorer

    auto absDetector = new G4MultiFunctionalDetector("Absorber");
    G4SDManager::GetSDMpointer()->AddNewDetector(absDetector);

    G4VPrimitiveScorer* primitive;
    primitive = new G4PSEnergyDeposit("Edep");
    absDetector->RegisterPrimitive(primitive);
    primitive = new G4PSDoseDeposit("Dodep");
    absDetector->RegisterPrimitive(primitive);

 for (G4int i = 0; i < TLDNumber; i++){

	 	 /* Cambiar i en String */

	 	 G4String n;
	 	 std::stringstream convert;
	 	 convert << i;
	 	 n = convert.str();
	 	 G4String a = n+"Abso";
	 	 TDM_SetTLD_SD(a);
 	 	 	 }
}

// Definiendo las Paredes de la clinica

inline void  TDM_DetectorConstruction::Paredes_Cons( G4Material* Material, G4LogicalVolume* MotherVolume, G4String Name, G4ThreeVector Position,G4double X, G4double Y,G4double Z)
{
	 // Paredes
	  //
	  auto Pared
		= new G4Box(Name,
					 X, Y, Z);

	  auto paredLV
		= new G4LogicalVolume(
					 Pared,
					 Material,
					 Name.append("LV"));

	   new G4PVPlacement(
					 0,
					 Position,
					 paredLV,
					 Name.append("PL"),
					 MotherVolume,
					 false,
					 0,
					 false);
}

