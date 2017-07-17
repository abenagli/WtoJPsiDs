# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step2 --mc --eventcontent AODSIM --runUnscheduled --datatier AODSIM --conditions 80X_mcRun2_asymptotic_2016_TrancheIV_v6 --step RAW2DIGI,L1Reco,RECO,EI --era Run2_2016 --filein file:step1.root --fileout file:step2.root
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('RECO',eras.Run2_2016)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('CommonTools.ParticleFlow.EITopPAG_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source(
    "PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
    fileNames = cms.untracked.vstring(
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_1.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_2.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_3.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_4.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_5.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_6.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_7.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_8.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_9.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_10.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_11.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_12.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_13.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_14.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_15.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_16.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_17.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_18.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_19.root',
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step1_WToJPsiDsToMuMuDs_20.root'
        ),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(
    allowUnscheduled = cms.untracked.bool(True)
)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step2 nevts:1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.AODSIMoutput = cms.OutputModule("PoolOutputModule",
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(4),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('AODSIM'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(15728640),
    fileName = cms.untracked.string('file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuDs.root'),
    outputCommands = process.AODSIMEventContent.outputCommands
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_asymptotic_2016_TrancheIV_v6', '')

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.eventinterpretaion_step = cms.Path(process.EIsequence)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.AODSIMoutput_step = cms.EndPath(process.AODSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.eventinterpretaion_step,process.endjob_step,process.AODSIMoutput_step)

#do not add changes to your config after this point (unless you know what you are doing)
from FWCore.ParameterSet.Utilities import convertToUnscheduled
process=convertToUnscheduled(process)
from FWCore.ParameterSet.Utilities import cleanUnscheduled
process=cleanUnscheduled(process)

