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
    sourceTag,
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
    skipEvents = cms.untracked.uint32(0),
    fileNames = cms.untracked.vstring(
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_1.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_2.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_3.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_4.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_5.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_6.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_7.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_8.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_9.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_10.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_11.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_12.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_13.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_14.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_15.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_16.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_17.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_18.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_19.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_20.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_21.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_22.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_23.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_24.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_25.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_26.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_27.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_28.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_29.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_30.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_31.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_32.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_33.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_34.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_35.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_36.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_37.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_38.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_39.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_40.root'
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_41.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_42.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_43.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_44.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_45.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_46.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_47.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_48.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_49.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_50.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_51.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_52.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_53.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_54.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_55.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_56.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_57.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_58.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_59.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_60.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_61.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_62.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_63.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_64.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_65.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_66.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_67.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_68.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_69.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_70.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_71.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_72.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_73.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_74.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_75.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_76.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_77.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_78.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_79.root',
        #'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi_PU_80.root'
        )
    )


#--------------
# Output ntuple
#--------------
process.TFileService = cms.Service(
    "TFileService", 
    fileName = cms.string("ntuple_WToJPsiDsToMuMuKKPi_PU_noPreselection.root"),
    closeFileFast = cms.untracked.bool(True)
    )


#------------------------------
# Analysis Sequences Definition
#------------------------------

process.load('WtoJPsiDs.Analysis.Preselection_cfi')
process.load('WtoJPsiDs.Analysis.DumpReco_cfi')
process.load('WtoJPsiDs.Analysis.DumpPU_cfi')
process.load('WtoJPsiDs.Analysis.DumpGenParticles_cfi')

process.analysisSequence = cms.Sequence(
    process.DumpPU
    *process.Preselection
    *process.DumpGenParticles
    *process.DumpReco
)


#----------------------------
# Paths/Sequences Definitions
#----------------------------
process.p = cms.Path(
    process.analysisSequence
    )
