#include <stdio.h>  
#include <unistd.h>

#include "ReducedTuple.h"

int main(int argc, char *argv[]){

  if(gSystem->OpenDirectory("ROOT") == 0){
    gSystem->mkdir("ROOT");
    cout << "Created ROOT folder." << endl;
  }

  if(argc < 2){
    cout << "Please specify sample name and input file." << endl;
    printf("For usage information type: %s -h\n", argv[0]);
    return 0;
  }

  int opt; 

  char* filename;
  char* samplename;

  while((opt = getopt(argc, argv, "i:s:h")) != -1){
    switch(opt)  
      {
      case 'i':
	filename = optarg;
	break;

      case 's':
	samplename = optarg;
	break;

      case 'h':
	printf("Usage: %s [-s] samplename [-i] inputfile\n", argv[0]);
	return 0;

      case '?':
	fprintf(stderr,"Usage: %s [-s] samplename [-i] inputfile \n", argv[0]);
	exit(EXIT_FAILURE);
      }
  }
 
  TChain *tch = new TChain("Delphes");
  tch->Add(filename);

  ReducedTuple *rt = new ReducedTuple(tch);
  
  rt->SetSampleName(samplename);
  rt->ReduceTree();
  
  delete tch;
  delete rt;
  
  return 0;
}
