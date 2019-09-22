#ifndef PLOTTER_H
#define PLOTTER_H

#include <iostream>

#include <TH1F.h>
#include <TColor.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <TSystem.h>

class Plotter{

 public:
  
  Plotter(){};
  virtual ~Plotter(){};

  static void Plot1D(TH1F *h1, TString name, TString title, TString xlabel, TString ylabel);

 private:

  static void SetTitle(TString plotTitle);

};

#endif
