#include "ReducedTuple.h"

//Function for producing reduced nTuple
void ReducedTuple::ReduceTree(){

  //Mass definitions
  Float_t electronMass = 0.000510998902;
  Float_t muonMass = 0.105658389;

  //Temporary TLorentzVector
  TLorentzVector tmp_lvec;

  //End program if tree is null
  if(!fChain) return;

  //Turn on required branches
  InitBranches();

  //Specify output format
  outDir = "ROOT/";
  outFileName = Form(outDir+"%s.root",tag.Data());

  //Create output file and tree
  TFile* file = new TFile(outFileName, "RECREATE");
  TTree* tree = new TTree("HadStop",Form("%s sample",tag.Data()));

  //Define branches of reduced nTuple tree
  tree->Branch("electrons", &electrons);
  tree->Branch("nElectrons", &nElectrons);
  tree->Branch("muons", &muons);
  tree->Branch("nMuons", &nMuons);
  tree->Branch("photons", &photons);
  tree->Branch("nPhotons", &nPhotons);
  tree->Branch("jets", &jets);
  tree->Branch("nJets", &nJets);

  //Get total entries from input tree 
  int nEntries = fChain->GetEntries();
  
  //Loop over input tree and fill reduced nTuple branches
  for(int e = 0; e < nEntries; e++){
    if (e % 1000 == 0) {
      fprintf(stdout, "\r  Processed events: %8d of %8d ", e, nEntries);
    }
    fflush(stdout);

    fChain->GetEntry(e);

    //Reset branch content
    electrons.clear();
    muons.clear();
    photons.clear();
    jets.clear();

    //Fill vectors of TLorentzVectors
    for(int i = 0; i < Electron_size; i++){
      tmp_lvec.SetPtEtaPhiM(Electron_PT[i], Electron_Eta[i], Electron_Phi[i], electronMass);
      electrons.push_back(tmp_lvec);
    }

    for(int i = 0; i < Muon_size; i++){
      tmp_lvec.SetPtEtaPhiM(Muon_PT[i], Muon_Eta[i], Muon_Phi[i], muonMass);
      muons.push_back(tmp_lvec);
    }

    for(int i =0; i < Photon_size; i++){
      tmp_lvec.SetPtEtaPhiE(Photon_PT[i], Photon_Eta[i], Photon_Phi[i], Photon_E[i]);
      photons.push_back(tmp_lvec);
    }

    for(int i =0; i < Jet_size; i++){
      tmp_lvec.SetPtEtaPhiM(Jet_PT[i], Jet_Eta[i], Jet_Phi[i], Jet_Mass[i]);
      jets.push_back(tmp_lvec);
    }

    //Set amount of objects per event
    nElectrons = Electron_size;
    nMuons = Muon_size;
    nPhotons = Photon_size;
    nJets = Jet_size;

    //Organize event content by Pt
    ParticleInfo::OrderByPt(electrons);
    ParticleInfo::OrderByPt(muons);
    ParticleInfo::OrderByPt(photons);
    ParticleInfo::OrderByPt(jets);

    tree->Fill();
  }
  cout << endl;

  file->Write();
  file->Close();

  delete file;
}

//Turn on the required branches in Delphes.h
void ReducedTuple::InitBranches(){

  if(!fChain) return;

  fChain->SetBranchStatus("*",0);
  fChain->SetBranchStatus("Electron_size",1);
  fChain->SetBranchStatus("Muon_size",1);
  fChain->SetBranchStatus("Photon_size",1);
  fChain->SetBranchStatus("Jet_size",1);
  fChain->SetBranchStatus("Electron.PT",1);
  fChain->SetBranchStatus("Electron.Eta",1);
  fChain->SetBranchStatus("Electron.Phi",1);
  fChain->SetBranchStatus("Muon.PT",1);
  fChain->SetBranchStatus("Muon.Eta",1);
  fChain->SetBranchStatus("Muon.Phi",1);
  fChain->SetBranchStatus("Photon.PT",1);
  fChain->SetBranchStatus("Photon.Eta",1);
  fChain->SetBranchStatus("Photon.Phi",1);
  fChain->SetBranchStatus("Photon.E",1);
  fChain->SetBranchStatus("Jet.PT",1);
  fChain->SetBranchStatus("Jet.Eta",1);
  fChain->SetBranchStatus("Jet.Phi",1);
  fChain->SetBranchStatus("Jet.Mass",1);
}
