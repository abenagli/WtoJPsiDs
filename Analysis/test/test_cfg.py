import subprocess
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')
options.register('eosdirs',
                 '',
                 VarParsing.multiplicity.list,
                 VarParsing.varType.string,
                 "files location(s) on EOS")
options.register('datasets',
                 '',
                 VarParsing.multiplicity.list,
                 VarParsing.varType.string,
                 "Input dataset(s)")
options.register('debug',
                 False,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "Print debug messages")
options.parseArguments()

process = cms.Process("FTLDumpTracks")
process.options = cms.untracked.PSet(allowUnscheduled = cms.untracked.bool(True))

process.load('FWCore/MessageService/MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1

# Global tag
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_asymptotic_2016_TrancheIV_v6', '')

# Magnetic field
process.load('Configuration.StandardSequences.MagneticField_cff')

files = []
###---get list of files from EOS
for eosdir in options.eosdirs:
    if eosdir[-1] != '/':
        eosdir += '/'
    print('>> Creating list of files from: \n'+eosdir)
    lsCmd = subprocess.Popen(['eos', 'ls', eosdir+'*.root'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    str_files, err = lsCmd.communicate()
    files.extend(['root://eoscms/'+eosdir+ifile for ifile in str_files.split("\n")])
    files.pop()
###---get list of files from DAS    
for dataset in options.datasets:
    print('>> Creating list of files from: \n'+dataset)
    query = "--query='file instance=prod/phys03 dataset="+dataset+"'"
    if options.debug:
        print(query)
    lsCmd = subprocess.Popen(['das_client.py '+query+' --limit=0'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    str_files, err = lsCmd.communicate()
    files.extend(['root://cms-xrd-global.cern.ch/'+ifile for ifile in str_files.split("\n")])
    files.pop()
    
if options.debug:
    for ifile in files:
        print(ifile)

# Input source
process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/gwteraz/users/benaglia/WtoJPsiDs/step2_WToJPsiDsToMuMuKKPi.root'
        )
    )

process.load('WtoJPsiDs.Analysis.DumpReco_cfi')
DumpReco = process.DumpReco

# Output TFile
process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string("ftl_tracks.root")
    )

process.path = cms.Path(DumpReco)

process.schedule = cms.Schedule(process.path)
