import FWCore.ParameterSet.Config as cms
import os


#---------------
# My definitions
#---------------
sourceTag = "PoolSource"         # for global runs
inputTagRaw = "source"           # for global runs

#sourceTag = "PoolSource"              # for global runs
#inputTagRaw = "hltHcalCalibrationRaw" # for global runs - calibration stream

#sourceTag = "HcalTBSource" # for local runs
#inputTagRaw = "source"     # for local  runs

#runNumber = "290617"


#-----------------------------------
# Standard CMSSW Imports/Definitions
#-----------------------------------
import FWCore.ParameterSet.Config as cms
process = cms.Process('dumpGenParticles')

#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = '90X_dataRun2_HLT_v1'


#from Configuration.StandardSequences.Eras import eras
#process = cms.Process('TPDigi', eras.Run2_2017)



#-----------
# Conditions
#-----------
#process.load("CondCore.CondDB.CondDB_cfi")
#process.load("CondCore.DBCommon.CondDBSetup_cfi")

#process.es_pool = cms.ESSource(
#    "PoolDBESSource",
#    process.CondDBSetup,
#    timetype = cms.string('runnumber'),
#    toGet = cms.VPSet(
#        cms.PSet(
#            record = cms.string("HcalL1TriggerObjectsRcd"),
#            tag = cms.string("HcalL1TriggerObjects_Physics2016v5B38T")
#            )
#        ),
#    connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
#    authenticationMethod = cms.untracked.uint32(0)
#    )
#process.es_prefer_es_pool = cms.ESPrefer("PoolDBESSource", "es_pool" )


#-----------
# Load e-map
#-----------
#process.es_ascii = cms.ESSource(
#    'HcalTextCalibrations',
#    input = cms.VPSet(
#        cms.PSet(
#            object = cms.string('ElectronicsMap'),
#            file = cms.FileInPath('version_G_emap_all_ngHF2016.txt')
#            )
#        #cms.PSet(
#        #    object = cms.string('ChannelQuality'),
#        #    #file = cms.FileInPath('DumpChannelQuality_Run197520.txt')
#        #    file = cms.FileInPath('DumpChannelQuality_Run254100.txt')
#        #    ),
#        #cms.PSet(
#        #    object = cms.string('Pedestals'),
#        #    #file = cms.FileInPath('DumpPedestals_Run197520.txt')
#        #    file = cms.FileInPath('DumpPedestals_Run247220.txt')
#        #    ),
#        #cms.PSet(
#        #    object = cms.string('Gains'),
#        #    #file = cms.FileInPath('DumpGains_Run190410.txt')
#        #    file = cms.FileInPath('DumpGains_Run250698.txt')
#        #    ),
#        #cms.PSet(
#        #    object = cms.string('RespCorrs'),
#        #    #file = cms.FileInPath('DumpRespCorrs_Run190410.txt')
#        #    file = cms.FileInPath('DumpRespCorrs_Run254100.txt')
#        #    )
#        )
#    )
#process.es_prefer = cms.ESPrefer('HcalTextCalibrations', 'es_ascii')


#-----------
# Log output
#-----------
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'DEBUG'
process.MessageLogger.cerr.FwkReport.reportEvery = 1
#process.MessageLogger.cout = cms.untracked.PSet(
#    WARNING = cms.untracked.PSet(reportEvery = cms.untracked.int32(10))
#    )
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
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi.root'
        )
    )


#--------------
# Output ntuple
#--------------
process.TFileService = cms.Service(
    "TFileService", 
    fileName = cms.string("ntuple.root"),
    closeFileFast = cms.untracked.bool(True)
    )


#------------------------------
# Analysis Sequences Definition
#------------------------------

process.load('WtoJPsiDs.Analysis.DumpGenParticles_cfi')

process.analysisSequence = cms.Sequence(
    process.dumpGenParticles
)


#----------------------------
# Paths/Sequences Definitions
#----------------------------
process.p = cms.Path(
    process.analysisSequence
    )
