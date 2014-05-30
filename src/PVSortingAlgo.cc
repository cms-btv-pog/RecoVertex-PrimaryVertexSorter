#include "RecoVertex/PrimaryVertexSorter/interface/PVSortingAlgo.h"

using namespace reco;


bool PVSortingAlgo::operator() (const Vertex & v1, const Vertex & v2) const
{
  return (sumPtSquared(v1) > sumPtSquared(v2));
}


double PVSortingAlgo::sumPtSquared(const Vertex & v) const
{
  double sum = 0.;
  double pT;
  for (Vertex::trackRef_iterator it = v.tracks_begin(); it != v.tracks_end(); it++) {
    pT = (**it).pt();
    double epT=(**it).ptError(); 
    pT=pT>epT ? pT-epT : 0;

    sum += pT*pT;
  }
  return sum;
}