#include <iostream>

#include <TH1D.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TStyle.h>
#include <TColor.h>

#include "../include/HadStop.h"
#include "../src/Plotter.cc"


void makePlot(){

  TH1F *h1 = new TH1F("h1", "Jet Multiplicity", 13, 0.,13.);
  int nJets = -999;

  TChain *tch = new TChain("HadStop");
  tch->Add("../ROOT/ttbar.root");

  HadStop *hadstop = new HadStop(tch);

  int nEntries = hadstop->fChain->GetEntries();

  for(int e = 0; e < nEntries; e++){
    if (e % 1000 == 0) {
      fprintf(stdout, "\r  Processed events: %8d of %8d ", e, nEntries);
    }
    fflush(stdout);

    hadstop->fChain->GetEntry(e);
    nJets = hadstop->nJets;
    h1->Fill(nJets);
  }
  cout << endl;

  Plotter::Plot1D(h1,"Njets","t#bar{t} sample 14 TeV","N Jets","Events");

}
