import FWCore.ParameterSet.Config as cms

DumpReco = cms.EDAnalyzer(
    "DumpReco",
    ###---Input tags
    trgsTag = cms.untracked.InputTag("TriggerResults", "", "HLT"),
    trgPrescalesTag = cms.untracked.InputTag("patTrigger", "", "RECO"),
    vtxTag = cms.untracked.InputTag("offlineSlimmedPrimaryVertices", "", "RECO"),
    pfCandidatesTag = cms.untracked.InputTag("packedPFCandidates", "", "RECO"),
    muonsTag = cms.untracked.InputTag("slimmedMuons", "", "RECO"),
    tausTag = cms.untracked.InputTag("slimmedTaus", "", "RECO"),
    jetsTag = cms.untracked.InputTag("slimmedJets", "", "RECO"),
    
    ###---I/O options
    treeName = cms.untracked.string("reco_tree"),
)
