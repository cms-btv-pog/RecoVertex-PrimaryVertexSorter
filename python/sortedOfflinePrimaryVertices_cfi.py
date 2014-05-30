import FWCore.ParameterSet.Config as cms

sortedOfflinePrimaryVertices = cms.EDProducer('PrimaryVertexSorter',
   src = cms.InputTag('offlinePrimaryVertices')
)
