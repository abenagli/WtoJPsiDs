import FWCore.ParameterSet.Config as cms
import os


#---------------
# My definitions
#---------------
sourceTag = "PoolSource"         # for global runs
inputTagRaw = "source"           # for global runs


#-----------------------------------
# Standard CMSSW Imports/Definitions
#-----------------------------------
import FWCore.ParameterSet.Config as cms
process = cms.Process('dumpReco')


#-----------
# Log output
#-----------
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'DEBUG'
process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    SkipEvent = cms.untracked.vstring('ProductNotFound'),
    )


#-----------------
# Files to process
#-----------------
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    )
process.source = cms.Source(
    "PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
    skipEvents = cms.untracked.uint32(0),
    fileNames = cms.untracked.vstring(
        'file:/gwteraz/users/benaglia/907579B8-7D8F-E611-97CA-001EC9ED4F72.root'
        )
    )


#--------------
# Output ntuple
#--------------
process.TFileService = cms.Service(
    "TFileService", 
    fileName = cms.string("ntuple_data.root"),
    closeFileFast = cms.untracked.bool(True)
    )


#------------------------------
# Analysis Sequences Definition
#------------------------------

process.load('WtoJPsiDs.Analysis.Preselection_cfi')
process.load('WtoJPsiDs.Analysis.DumpReco_cfi')
process.load('WtoJPsiDs.Analysis.DumpGenParticles_cfi')

process.analysisSequence = cms.Sequence(
    process.Preselection
    *process.DumpReco
)


#----------------------------
# Paths/Sequences Definitions
#----------------------------
process.p = cms.Path(
    process.analysisSequence
    )
