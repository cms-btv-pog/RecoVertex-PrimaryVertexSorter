#include "RecoVertex/PrimaryVertexSorter/interface/PVSortingAlgo.h"

using namespace reco;


std::vector<unsigned int> PVSortingAlgo::getSortedIndices(const edm::Handle<reco::VertexCollection> & primaryVertices,
                                                          const edm::Handle<reco::TrackIPTagInfoCollection> & ipTagInfos,
                                                          double jetPtMin) const
{
  // initialize (index,value) pairs vector
  std::vector<SortingPair> sortingPairs;
  // initialize pairs
  for(reco::VertexCollection::const_iterator it=primaryVertices->begin(); it!=primaryVertices->end(); ++it)
    sortingPairs.push_back( std::make_pair( it - primaryVertices->begin(), 0. ) );

  // jet counter
  int nSelectedJets = 0;
  // track counter
  int nSelectedTracks = 0;
  // loop over IPTagInfos
  for(reco::TrackIPTagInfoCollection::const_iterator it=ipTagInfos->begin(); it!=ipTagInfos->end(); ++it)
  {
    if( it->jet()->pt() < jetPtMin ) continue; // skip low-Pt jets

    const reco::TrackRefVector & selectedTracks( it->selectedTracks() );

    // loop over selected tracks
    for(reco::TrackRefVector::const_iterator trkIt=selectedTracks.begin(); trkIt!=selectedTracks.end(); ++trkIt)
    {
      int iPV = -1;
      double bestweight = 0.;

      const reco::TrackBaseRef trackBaseRef( *trkIt );

      typedef reco::VertexCollection::const_iterator IV;
      typedef reco::Vertex::trackRef_iterator IT;

      for(IV iv=primaryVertices->begin(); iv!=primaryVertices->end(); ++iv)
      {
        const reco::Vertex & vtx = *iv;
        // loop over tracks in vertices
        for(IT it=vtx.tracks_begin(); it!=vtx.tracks_end(); ++it)
        {
          const reco::TrackBaseRef & baseRef = *it;
          // one of the tracks in the vertex is the same as the track considered in the function
          if( baseRef == trackBaseRef )
          {
            float w = vtx.trackWeight(baseRef);
            // select the vertex for which the track has the highest weight
            if( w > bestweight )
            {
              bestweight = w;
              iPV = ( iv - primaryVertices->begin() );
              break;
            }
          }
        }
      }
      // if track assigned to a vertex
      if( iPV>=0 )
      {
        sortingPairs.at(iPV).second += trackPt2( *trkIt );
        // increment track counter
        ++nSelectedTracks;
      }
    }
    // increment jet counter
    ++nSelectedJets;
  }
  // sort pairs if any jets and tracks were selected
  if( nSelectedJets>0 && nSelectedTracks>0 )
    std::sort(sortingPairs.begin(), sortingPairs.end(), sortByValue());
  // initialize sorted indices vector
  std::vector<unsigned int> sortedIndices;
  // fill sorted indices vector
  for(std::vector<SortingPair>::const_iterator it=sortingPairs.begin(); it!=sortingPairs.end(); ++it)
    sortedIndices.push_back( it->first );

  return sortedIndices;
}


double PVSortingAlgo::trackPt2(const reco::TrackRef & trk) const
{
  double pT = trk->pt();
  double epT = trk->ptError(); 
  pT = ( pT>epT ? pT-epT : 0. );

  return pT*pT;
}
