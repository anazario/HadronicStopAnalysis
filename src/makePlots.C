#include <stdio.h>
#include <unistd.h>

#include "HadStop.h"
#include "Plotter.h"

int main(int argc, char *argv[]){

  if(gSystem->OpenDirectory("plots") == 0)
    gSystem->mkdir("plots");

  if(argc < 2){
    cout << "Please specify input file." << endl;
    printf("For usage information type: %s -h\n", argv[0]);
    return 0;
  }

  int opt;

  char* filename;

  while((opt = getopt(argc, argv, "i:h")) != -1){
    switch(opt)
      {
      case 'i':
        filename = optarg;
        break;

      case 'h':
        printf("Usage: %s [-i] inputfile\n", argv[0]);
        return 0;

      case '?':
        fprintf(stderr,"Usage: %s [-s] samplename [-i] inputfile \n", argv[0]);
        exit(EXIT_FAILURE);
      }
    
  }

  TH1F *h1 = new TH1F("h1", "Jet Multiplicity", 13, 0.,13.);
  int nJets = -999;

  TChain *tch = new TChain("HadStop");
  tch->Add(filename);

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

  Plotter::Plot1D(h1,"plots/Njets","t#bar{t} sample 14 TeV","N Jets","Events");

  delete h1;
  delete hadstop;

  return 0;
}
