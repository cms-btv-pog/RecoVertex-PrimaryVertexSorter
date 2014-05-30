import FWCore.ParameterSet.Config as cms

from RecoJets.JetAssociationProducers.j2tParametersVX_cfi import *
ak5CaloJetTracksAssociatorAtVertexR04 = cms.EDProducer("JetTracksAssociatorAtVertex",
    j2tParametersVX.clone(coneSize = cms.double(0.4)),
    jets = cms.InputTag("ak5CaloJets")
)

from RecoBTag.ImpactParameter.impactParameter_cfi import *
impactParameterTagInfosForPVSorting = impactParameterTagInfos.clone(
    jetTracks = cms.InputTag("ak5CaloJetTracksAssociatorAtVertexR04")
)

sortedOfflinePrimaryVertices = cms.EDProducer("PrimaryVertexSorter",
   src = cms.InputTag("offlinePrimaryVertices"),
   ipTagInfos = cms.InputTag("impactParameterTagInfosForPVSorting"),
   jetPtMin = cms.double(30.)
)

pvSortingSequence = cms.Sequence(ak5CaloJetTracksAssociatorAtVertexR04 * impactParameterTagInfosForPVSorting * sortedOfflinePrimaryVertices)
