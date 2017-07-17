import FWCore.ParameterSet.Config as cms

DumpReco = cms.EDAnalyzer(
    "DumpReco",
    ###---Input tags
    vtxTag = cms.untracked.InputTag("offlinePrimaryVertices", "", "RECO"),
    tracksTag = cms.untracked.InputTag("generalTracks", "", "RECO"),
    muonsTag = cms.untracked.InputTag("muons", "", "RECO"),
    
    ###---I/O options
    treeName = cms.untracked.string("reco_tree"),
)
