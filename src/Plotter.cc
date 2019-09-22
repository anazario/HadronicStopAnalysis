#include "Plotter.h"

//Write label on Plot
void Plotter::SetTitle(TString plotTitle){
  TLatex l;
  l.SetTextFont(42);
  l.SetNDC();
  l.SetTextSize(0.035);
  l.SetTextFont(42);
  l.DrawLatex(0.65,0.91,plotTitle);
}

//Plot input TH1F histogram
void Plotter::Plot1D(TH1F *h1, TString name, TString title, TString xlabel, TString ylabel){

  gROOT->SetBatch(kTRUE);//Produce plot in batch mode
  gStyle->SetOptTitle(0);//Remove title
  gStyle->SetOptStat(0);//Remove stat box

  //Define canvas to draw plot
  TCanvas *can = new TCanvas("can","can",600,800);

  //Modify canvas
  can->SetLeftMargin(0.15);
  can->SetGrid();

  //Modify input histogram
  h1->SetLineWidth(2);
  h1->SetLineColor(kBlue+2);

  //Set x and y axis labels
  h1->GetXaxis()->SetTitle(xlabel);
  h1->GetYaxis()->SetTitle(ylabel);

  //Draw histogram
  h1->Draw();

  //Draw label
  SetTitle(title);

  //Save plot as pdf
  can->SaveAs(name+".pdf");

  can->Close();
  delete can;
}
