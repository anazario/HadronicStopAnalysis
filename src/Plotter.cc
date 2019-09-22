#include "Plotter.h"
//#include "../include/Plotter.h"

void Plotter::SetTitle(TString plotTitle){
  TLatex l;
  l.SetTextFont(42);
  l.SetNDC();
  l.SetTextSize(0.035);
  l.SetTextFont(42);
  l.DrawLatex(0.65,0.91,plotTitle);
}

void Plotter::Plot1D(TH1F *h1, TString name, TString title, TString xlabel, TString ylabel){

  gROOT->SetBatch(kTRUE);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(11111111);

  TCanvas *can = new TCanvas("can","can",600,800);

  can->SetLeftMargin(0.15);
  can->SetGrid();

  h1->SetLineWidth(2);
  h1->SetLineColor(kBlue+2);

  h1->GetXaxis()->SetTitle(xlabel);
  h1->GetYaxis()->SetTitle(ylabel);

  h1->Draw();

  SetTitle(title);

  can->SaveAs(name+".pdf");

  can->Close();
  delete can;
}
