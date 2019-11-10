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
  tree->Branch("electron_charge", &electron_charge);
  tree->Branch("muons", &muons);
  tree->Branch("nMuons", &nMuons);
  tree->Branch("muon_charge", &muon_charge);
  tree->Branch("photons", &photons);
  tree->Branch("nPhotons", &nPhotons);
  tree->Branch("jets", &jets);
  tree->Branch("nJets", &nJets);
  tree->Branch("bJets", &bJets);
  tree->Branch("nBJets", &nBJets);
  tree->Branch("nMet", &nMet);
  tree->Branch("met", &met);
  tree->Branch("met_eta", &met_eta);
  tree->Branch("met_phi", &met_phi);
  tree->Branch("nHT", &nHT);
  tree->Branch("ht", &ht);

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
    bJets.clear();
    met.clear();
    met_eta.clear();
    met_phi.clear();
    ht.clear();

    //Fill vectors of TLorentzVectors
    for(int i = 0; i < Electron_size; i++){
      tmp_lvec.SetPtEtaPhiM(Electron_PT[i], Electron_Eta[i], Electron_Phi[i], electronMass);
      electrons.push_back(tmp_lvec);
      electron_charge.push_back(Electron_Charge[i]);
    }

    for(int i = 0; i < Muon_size; i++){
      tmp_lvec.SetPtEtaPhiM(Muon_PT[i], Muon_Eta[i], Muon_Phi[i], muonMass);
      muons.push_back(tmp_lvec);
      muon_charge.push_back(Muon_Charge[i]);
    }

    for(int i =0; i < Photon_size; i++){
      tmp_lvec.SetPtEtaPhiE(Photon_PT[i], Photon_Eta[i], Photon_Phi[i], Photon_E[i]);
      photons.push_back(tmp_lvec);
    }

    for(int i =0; i < Jet_size; i++){
      tmp_lvec.SetPtEtaPhiM(Jet_PT[i], Jet_Eta[i], Jet_Phi[i], Jet_Mass[i]);
      if(Jet_BTag[i])
	bJets.push_back(tmp_lvec);
      else
	jets.push_back(tmp_lvec);
    }

    //Fill other vectors
    for(int i = 0; i < MissingET_size; i++){
      met.push_back(MissingET_MET[i]);
      met_eta.push_back(MissingET_Eta[i]);
      met_phi.push_back(MissingET_Phi[i]);
    }

    for(int i = 0; i < ScalarHT_size; i++)
      ht.push_back(ScalarHT_HT[i]);

    //Set amount of objects per event
    nElectrons = Electron_size;
    nMuons = Muon_size;
    nPhotons = Photon_size;
    nJets = jets.size();
    nBJets = bJets.size();
    nMet = MissingET_size;
    nHT = ScalarHT_size;

    //Organize event content by Pt
    ParticleInfo::OrderByPt(electrons);
    ParticleInfo::OrderByPt(muons);
    ParticleInfo::OrderByPt(photons);
    ParticleInfo::OrderByPt(jets);
    ParticleInfo::OrderByPt(bJets);

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
  fChain->SetBranchStatus("Jet.BTag",1);
  fChain->SetBranchStatus("Electron.PT",1);
  fChain->SetBranchStatus("Electron.Eta",1);
  fChain->SetBranchStatus("Electron.Phi",1);
  fChain->SetBranchStatus("Electron.Charge",1);
  fChain->SetBranchStatus("Muon.PT",1);
  fChain->SetBranchStatus("Muon.Eta",1);
  fChain->SetBranchStatus("Muon.Phi",1);
  fChain->SetBranchStatus("Muon.Charge",1);
  fChain->SetBranchStatus("Photon.PT",1);
  fChain->SetBranchStatus("Photon.Eta",1);
  fChain->SetBranchStatus("Photon.Phi",1);
  fChain->SetBranchStatus("Photon.E",1);
  fChain->SetBranchStatus("Jet.PT",1);
  fChain->SetBranchStatus("Jet.Eta",1);
  fChain->SetBranchStatus("Jet.Phi",1);
  fChain->SetBranchStatus("Jet.Mass",1);
  fChain->SetBranchStatus("MissingET_size",1);
  fChain->SetBranchStatus("MissingET.MET",1);
  fChain->SetBranchStatus("MissingET.Eta",1);
  fChain->SetBranchStatus("MissingET.Phi",1);
  fChain->SetBranchStatus("ScalarHT_size",1);
  fChain->SetBranchStatus("ScalarHT.HT",1);
}
