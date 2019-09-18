#include <iostream>
#include <TH1D.h>
#include <TCanvas.h>

#include "Delphes.h"

void makePlot(){

  TH1D *h1 = new TH1D("h1", "Jet Multiplicity", 12, 0.,12.);
  int nJets = -999;

  TChain *tch = new TChain("Delphes");
  tch->Add("tag_1_delphes_events.root");

  Delphes *dph = new Delphes(tch);

  int nEntries = dph->fChain->GetEntries();

  for(int e = 0; e < nEntries; e++){
    if (e % 1000 == 0) {
      fprintf(stdout, "\r  Processed events: %8d of %8d ", e, nEntries);
    }
    fflush(stdout);

    tch->GetEntry(e);
    nJets = dph->Jet_size;
    h1->Fill(nJets);
  }

  gROOT->SetBatch(kTRUE);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(11111111);

  TCanvas *can = new TCanvas("can","can",600,800);

  can->SetLeftMargin(0.15);

  h1->SetLineWidth(2);
  h1->SetLineColor(1);

  h1->GetXaxis()->SetTitle("N Jets");
  h1->GetYaxis()->SetTitle("Events");

  h1->Draw();

  can->SaveAs("Njets.pdf");

}
