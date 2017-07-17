import FWCore.ParameterSet.Config as cms

DumpGenParticles = cms.EDAnalyzer(
    "DumpGenParticles",
    ###---Input tags
    genParticlesTag = cms.untracked.InputTag("genParticles"),
    
    ###---I/O options
    treeName = cms.untracked.string("gen_tree"),
    verbosity = cms.bool(False)
)
