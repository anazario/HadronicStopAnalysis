#include <stdio.h>
#include <unistd.h>

#include "HadStop.h"
#include "Plotter.h"

int main(int argc, char *argv[]){

  //Create "plots" directory if it doesn't exist 
  if(gSystem->OpenDirectory("plots") == 0)
    gSystem->mkdir("plots");

  //Give warning if insuficient arguments are given
  if(argc < 2){
    cout << "Please specify input file." << endl;
    printf("For usage information type: %s -h\n", argv[0]);
    return 0;
  }

  //Parameters used for command line arguments
  int opt;
  char* filename;

  //Command line option definitions
  while((opt = getopt(argc, argv, "i:h")) != -1){
    switch(opt)
      {
      //Input filename option [-i]
      case 'i':
	filename = optarg;
	break;
	
      //input Help option [-h]
      case 'h':
        printf("Usage: %s [-i] inputfile\n", argv[0]);
        return 0;
	
      //If unknown option is given, return error 
      case '?':
        fprintf(stderr,"Usage: %s [-s] samplename [-i] inputfile \n", argv[0]);
        exit(EXIT_FAILURE);
      }
    
  }

  //----------//
  //Main code://
  //----------//  

  TH1F *h1 = new TH1F("h1", "Jet Multiplicity", 13, 0.,13.); //Histogram definition
  int nJets = -999;

  //Define TChain based on the reduced nTuple (HadStop) 
  TChain *tch = new TChain("HadStop");
  tch->Add(filename);

  //Use HadStop class to set branches
  HadStop *hadstop = new HadStop(tch);

  //Get total entries in tree
  int nEntries = hadstop->fChain->GetEntries();

  //Loop over entries in tree and fill histogram
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

  //Plot 1D histogram using Plotter class
  Plotter::Plot1D(h1,"plots/Njets","t#bar{t} sample 14 TeV","N Jets","Events");

  //Delete pointers
  delete h1;
  delete tch;
  delete hadstop;

  return 0;
}
