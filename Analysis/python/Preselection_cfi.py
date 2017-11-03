import FWCore.ParameterSet.Config as cms

Preselection = cms.EDFilter(
    "Preselection",
    ###---Input tags
    vtxTag = cms.untracked.InputTag("offlineSlimmedPrimaryVertices", "", "RECO"),
    muonsTag = cms.untracked.InputTag("slimmedMuons", "", "RECO"),
)
