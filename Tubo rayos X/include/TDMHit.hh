//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: LXePMTHit.hh 72250 2013-07-12 08:59:26Z gcosmo $
//
/// \file optical/LXe/include/LXePMTHit.hh
/// \brief Definition of the LXePMTHit class
//
//
#ifndef TDMHit_h
#define TDMHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VPhysicalVolume.hh"


#include "tls.hh"

class G4VTouchable;

class TDMHit : public G4VHit
{
  public:

    TDMHit();
    virtual ~TDMHit();
    TDMHit(const TDMHit &right);

    const TDMHit& operator=(const TDMHit &right);

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    //set methods
    inline void setfener(G4double n ){fener =n;}
   // inline void setfpos(G)
    inline G4double Getfener() {return fener;}

    inline void SetTDMPos(G4ThreeVector aVector){
      fPos=aVector;

    }

    inline G4ThreeVector GetTDMPos(){return fPos;}

  private:

    G4ThreeVector fPos;
    G4double fener;

};

typedef G4THitsCollection<TDMHit> TDMHitsCollection;

extern G4ThreadLocal G4Allocator<TDMHit>* TDMHitAllocator;

inline void* TDMHit::operator new(size_t){
  if(!TDMHitAllocator)
      TDMHitAllocator = new G4Allocator<TDMHit>;
  return (void *) TDMHitAllocator->MallocSingle();
}

inline void TDMHit::operator delete(void *aHit){
  TDMHitAllocator->FreeSingle((TDMHit*) aHit);
}

#endif
