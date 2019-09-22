#ifndef REDUCEDTUPLE_H
#define REDUCEDTUPLE_H

#include<iostream>
#include<vector>

#include <TLorentzVector.h>
#include <TSystem.h>

#include "Delphes.h"
#include "ParticleInfo.h"

using namespace std;

class ReducedTuple : public Delphes{

 public:
  
 ReducedTuple(TTree *tree) : Delphes(tree){};
  
  virtual ~ReducedTuple(){};
  
  void SetSampleName(TString name){tag = name;}

  void ReduceTree();

 private:

  TString tag;
  TString inDir;
  TString outDir;
  TString outFileName;
  vector<TString> inFileName;

  //Reduced nTuple content
  Int_t nElectrons;
  Int_t nMuons;
  Int_t nPhotons;
  Int_t nJets;

  vector<TLorentzVector> photons;
  vector<TLorentzVector> electrons;
  vector<TLorentzVector> muons;
  vector<TLorentzVector> met;
  vector<TLorentzVector> jets;

  void InitBranches();

};

#endif
