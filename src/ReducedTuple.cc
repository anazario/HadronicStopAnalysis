#include "ReducedTuple.h"

void ReducedTuple::ReduceTree(){

  Float_t electronMass = 0.000510998902;
  Float_t muonMass = 0.105658389;

  TLorentzVector tmp_lvec;

  if(!fChain) return;

  InitBranches();

  outDir = "ROOT/";
  outFileName = Form(outDir+"%s.root",tag.Data());

  TFile* file = new TFile(outFileName, "RECREATE");
  TTree* tree = new TTree("HadStop",Form("%s sample",tag.Data()));

  tree->Branch("electrons", &electrons);
  tree->Branch("nElectrons", &nElectrons);
  tree->Branch("muons", &muons);
  tree->Branch("nMuons", &nMuons);
  tree->Branch("photons", &photons);
  tree->Branch("nPhotons", &nPhotons);
  tree->Branch("jets", &jets);
  tree->Branch("nJets", &nJets);

  int nEntries = fChain->GetEntries();
  
  for(int e = 0; e < nEntries; e++){
    if (e % 1000 == 0) {
      fprintf(stdout, "\r  Processed events: %8d of %8d ", e, nEntries);
    }
    fflush(stdout);

    fChain->GetEntry(e);

    nElectrons = 0;
    nMuons = 0;
    nPhotons = 0;
    nJets = 0;

    electrons.clear();
    muons.clear();
    photons.clear();
    jets.clear();

    for(int i = 0; i < Electron_size; i++){
      tmp_lvec.SetPtEtaPhiM(Electron_PT[i], Electron_Eta[i], Electron_Phi[i], electronMass);
      electrons.push_back(tmp_lvec);
      nElectrons++;
    }

    for(int i = 0; i < Muon_size; i++){
      tmp_lvec.SetPtEtaPhiM(Muon_PT[i], Muon_Eta[i], Muon_Phi[i], muonMass);
      muons.push_back(tmp_lvec);
      nMuons++;
    }

    for(int i =0; i < Photon_size; i++){
      tmp_lvec.SetPtEtaPhiE(Photon_PT[i], Photon_Eta[i], Photon_Phi[i], Photon_E[i]);
      photons.push_back(tmp_lvec);
      nPhotons++;
    }

    for(int i =0; i < Jet_size; i++){
      tmp_lvec.SetPtEtaPhiM(Jet_PT[i], Jet_Eta[i], Jet_Phi[i], Jet_Mass[i]);
      jets.push_back(tmp_lvec);
      nJets++;
    }

    ParticleInfo::OrderByPt(electrons);
    ParticleInfo::OrderByPt(muons);
    ParticleInfo::OrderByPt(photons);
    ParticleInfo::OrderByPt(jets);

    tree->Fill();
  }
  cout << endl;

  file->Write();
  file->Close();

}

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
