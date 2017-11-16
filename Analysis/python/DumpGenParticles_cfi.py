import FWCore.ParameterSet.Config as cms

DumpGenParticles = cms.EDAnalyzer(
    "DumpGenParticles",
    ###---Input tags
    genParticlesTag = cms.untracked.InputTag("prunedGenParticles"),
    genJetsTag = cms.untracked.InputTag("slimmedGenJets"),
    puInfoTag = cms.untracked.InputTag("slimmedAddPileupInfo"),
    
    ###---I/O options
    treeName = cms.untracked.string("gen_tree"),
    verbosity = cms.bool(False)
)
