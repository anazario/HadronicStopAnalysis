#include "ParticleInfo.h"

void ParticleInfo::OrderByPt(vector<TLorentzVector> &evt_selection){

  sort(evt_selection.begin(),
       evt_selection.end(),
       [](const TLorentzVector& lhs, const TLorentzVector& rhs)
       {
	 return lhs.Pt() < rhs.Pt();
       });
}
