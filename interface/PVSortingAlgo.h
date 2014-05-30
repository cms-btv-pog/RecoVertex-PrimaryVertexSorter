#ifndef RecoVertex_PrimaryVertexSorter_PVSortingAlgo_H
#define RecoVertex_PrimaryVertexSorter_PVSortingAlgo_H

#include "DataFormats/VertexReco/interface/Vertex.h"

namespace reco
{

class PVSortingAlgo
{
  public:
    bool operator() (const reco::Vertex & v1, const reco::Vertex & v2) const;

  private:
    double sumPtSquared(const reco::Vertex & v) const;
};

}

#endif