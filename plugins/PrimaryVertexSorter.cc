// -*- C++ -*-
//
// Package:    PrimaryVertexSorter
// Class:      PrimaryVertexSorter
// 
/**\class PrimaryVertexSorter PrimaryVertexSorter.cc RecoVertex/PrimaryVertexSorter/src/PrimaryVertexSorter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Dinko Ferencek
//         Created:  Thu May 29 18:38:21 CDT 2014
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "RecoVertex/PrimaryVertexSorter/interface/PVSortingAlgo.h"

//
// class declaration
//

class PrimaryVertexSorter : public edm::EDProducer {
   public:
      explicit PrimaryVertexSorter(const edm::ParameterSet&);
      ~PrimaryVertexSorter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      // ----------member data ---------------------------
      const edm::InputTag src_;
};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
PrimaryVertexSorter::PrimaryVertexSorter(const edm::ParameterSet& iConfig) :
   src_(iConfig.getParameter<edm::InputTag>("src"))
{
   //register your products
   produces<reco::VertexCollection>();

   //now do what ever other initialization is needed

}


PrimaryVertexSorter::~PrimaryVertexSorter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
PrimaryVertexSorter::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   // get primary vertices
   edm::Handle<reco::VertexCollection> primaryVertices;
   iEvent.getByLabel(src_,primaryVertices);

   std::auto_ptr<reco::VertexCollection> pvs(new reco::VertexCollection(*primaryVertices));

   if( pvs->size()>1 )
      sort(pvs->begin(), pvs->end(), reco::PVSortingAlgo());

   // put sorted vertices into the event
   iEvent.put(pvs);
}

// ------------ method called once each job just before starting event loop  ------------
void 
PrimaryVertexSorter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
PrimaryVertexSorter::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
PrimaryVertexSorter::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
PrimaryVertexSorter::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
PrimaryVertexSorter::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
PrimaryVertexSorter::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PrimaryVertexSorter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(PrimaryVertexSorter);
