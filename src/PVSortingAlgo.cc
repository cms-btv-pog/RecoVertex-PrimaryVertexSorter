#include "RecoVertex/PrimaryVertexSorter/interface/PVSortingAlgo.h"

using namespace reco;


std::vector<unsigned int> PVSortingAlgo::getSortedIndices(const edm::Handle<reco::VertexCollection> & primaryVertices) const
{
  // initialize (index,value) pairs vector
  std::vector<SortingPair> sortingPairs;
  // fill pairs
  for(reco::VertexCollection::const_iterator it=primaryVertices->begin(); it!=primaryVertices->end(); ++it)
    sortingPairs.push_back( std::make_pair( it - primaryVertices->begin(), sortingValue(*it) ) );
  // sort pairs
  std::sort(sortingPairs.begin(), sortingPairs.end(), sortByValue());

  // initialize sorted indices vector
  std::vector<unsigned int> sortedIndices;
  // fill sorted indices vector
  for(std::vector<SortingPair>::const_iterator it=sortingPairs.begin(); it!=sortingPairs.end(); ++it)
    sortedIndices.push_back( it->first );

  return sortedIndices;
}


double PVSortingAlgo::sortingValue(const Vertex & v) const
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
