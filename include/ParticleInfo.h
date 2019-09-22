#ifndef PARTICLEINFO_H
#define PARTICLEINFO_H

#include <iostream>
#include <vector>

#include <TLorentzVector.h>

#include "HadStop.h"

using namespace std;

class ParticleInfo{

 public:
  
  ParticleInfo(){};
  virtual ~ParticleInfo(){};
  
  static void OrderByPt(vector<TLorentzVector> &evt_selection);

};

#endif
