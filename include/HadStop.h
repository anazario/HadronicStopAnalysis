//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Sep 19 18:39:24 2019 by ROOT version 6.18/00
// from TTree HadStop/ttbar sample
// found on file: ../ROOT/ttbar.root
//////////////////////////////////////////////////////////

#ifndef HadStop_h
#define HadStop_h

#include <vector>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TLorentzVector.h>

using namespace std;
// Header file for the classes stored in the TTree if any.

class HadStop {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Fixed size dimensions of array or collections stored in the TTree if any.
  
  // Declaration of leaf types
  vector<TLorentzVector> *electrons;
  Int_t           nElectrons;
  vector<TLorentzVector> *muons;
  Int_t           nMuons;
  vector<TLorentzVector> *photons;
  Int_t           nPhotons;
  vector<TLorentzVector> *jets;
  Int_t           nJets;
  
  // List of branches
  TBranch        *b_electrons;   //!
  TBranch        *b_nElectrons;   //!
  TBranch        *b_muons;   //!
  TBranch        *b_nMuons;   //!
  TBranch        *b_photons;   //!
  TBranch        *b_nPhotons;   //!
  TBranch        *b_jets;   //!
  TBranch        *b_nJets;   //!
  
  HadStop(TTree *tree=0);
  virtual ~HadStop();
  
  virtual void     Init(TTree *tree);
};

#endif

//#ifdef HadStop_cxx
inline HadStop::HadStop(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../ROOT/ttbar.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../ROOT/ttbar.root");
      }
      f->GetObject("HadStop",tree);

   }
   Init(tree);
}

inline HadStop::~HadStop()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

inline void HadStop::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   electrons = 0;
   muons = 0;
   photons = 0;
   jets = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("electrons", &electrons, &b_electrons);
   fChain->SetBranchAddress("nElectrons", &nElectrons, &b_nElectrons);
   fChain->SetBranchAddress("muons", &muons, &b_muons);
   fChain->SetBranchAddress("nMuons", &nMuons, &b_nMuons);
   fChain->SetBranchAddress("photons", &photons, &b_photons);
   fChain->SetBranchAddress("nPhotons", &nPhotons, &b_nPhotons);
   fChain->SetBranchAddress("jets", &jets, &b_jets);
   fChain->SetBranchAddress("nJets", &nJets, &b_nJets);
}
//#endif // #ifdef HadStop_cxx
