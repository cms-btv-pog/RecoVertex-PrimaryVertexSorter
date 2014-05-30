#ifndef RecoVertex_PrimaryVertexSorter_PVSortingAlgo_H
#define RecoVertex_PrimaryVertexSorter_PVSortingAlgo_H

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BTauReco/interface/TrackIPTagInfo.h"

typedef std::pair<unsigned int, double> SortingPair;

struct sortByValue
{
  bool operator() (const SortingPair & sp1, const SortingPair & sp2) const
  {
    return sp1.second > sp2.second;
  }
};

namespace reco
{

class PVSortingAlgo
{
  public:
    std::vector<unsigned int> getSortedIndices(const edm::Handle<reco::VertexCollection> & primaryVertices,
                                               const edm::Handle<reco::TrackIPTagInfoCollection> & ipTagInfos,
                                               double jetPtMin) const;

  private:
    double trackPt2(const reco::TrackRef & trk) const;
};

}

#endif