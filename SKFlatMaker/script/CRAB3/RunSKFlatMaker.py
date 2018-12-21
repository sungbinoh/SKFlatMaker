import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('python')
options.register('sampletype', "DATA", VarParsing.multiplicity.singleton, VarParsing.varType.string, "sampletype: DATA/MC/PrivateMC")
options.register('ScaleIDRange', "-999,-999", VarParsing.multiplicity.singleton, VarParsing.varType.string, "PDF Scale ID range: 1,9")
options.register('PDFErrorType', "", VarParsing.multiplicity.singleton, VarParsing.varType.string, "PDF Error type: gaussian,hessian")
options.register('PDFErrorIDRange', "-999,-999", VarParsing.multiplicity.singleton, VarParsing.varType.string, "PDF Error ID range: 1001,1100")
options.register('PDFAlphaSIDRange', "-999,-999", VarParsing.multiplicity.singleton, VarParsing.varType.string, "PDF AlphaS ID range: 1101,1102")
options.register('PDFAlphaSScaleValue', "-999,-999", VarParsing.multiplicity.singleton, VarParsing.varType.string, "PDF AlphaS Scale values: 1.5,1.5")
options.register('year',-1, VarParsing.multiplicity.singleton, VarParsing.varType.int, "year: Which year")
options.parseArguments()

import sys

Is2016 = False
Is2017 = False
Is2018 = False
if options.year==2016:
  Is2016 = True
elif options.year==2017:
  Is2017 = True
elif options.year==2018:
  Is2018 = True
else:
  ErrorMgs = "year is not correct; "+str(options.year)
  sys.exit(ErrorMgs)

isMC = True
if "data" in options.sampletype.lower():
  isMC = False
if "mc" in options.sampletype.lower():
  isMC = True
isPrivateSample = False
if "private" in options.sampletype.lower():
  isPrivateSample = True

options.outputFile = "SKFlatNtuple.root"
if len(options.inputFiles)==0:
  if Is2016:
    if isMC:
      options.inputFiles.append('root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv3/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1/120000/80DBA5F3-16BE-E811-854E-A0369FC5E530.root')
      options.outputFile = "SKFlatNtuple_2016_MC.root"
    else:
      options.inputFiles.append('root://cms-xrd-global.cern.ch//store/data/Run2016B/SingleMuon/MINIAOD/17Jul2018_ver1-v1/80000/306DAB6C-068C-E811-9E30-0242AC1C0501.root')
      options.outputFile = "SKFlatNtuple_2016_DATA.root"
  elif Is2017:
    if isMC:
      options.inputFiles.append('root://cms-xrd-global.cern.ch//store/mc/RunIIFall17MiniAODv2/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/40000/D87C6B2A-5C42-E811-8FD7-001E677926A8.root')
      options.outputFile = "SKFlatNtuple_2017_MC.root"
    else:
      options.inputFiles.append('root://cms-xrd-global.cern.ch//store/data/Run2017B/SingleMuon/MINIAOD/31Mar2018-v1/80000/54F30BE9-423C-E811-A315-0CC47A7C3410.root')
      options.outputFile = "SKFlatNtuple_2017_DATA.root"
  elif Is2018:
    if isMC:
      options.inputFiles.append('root://cms-xrd-global.cern.ch//store/mc/RunIIAutumn18MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/120000/B3F93EA2-04C6-E04E-96AF-CB8FAF67E6BA.root')
      options.outputFile = "SKFlatNtuple_2018_MC.root"
    else:
      options.inputFiles.append('root://cms-xrd-global.cern.ch//store/data/Run2018A/SingleMuon/MINIAOD/17Sep2018-v2/00000/11697BCC-C4AB-204B-91A9-87F952F9F2C6.root')
      options.outputFile = "SKFlatNtuple_2018_DATA.root"

ScaleIDRange = [int(options.ScaleIDRange.split(',')[0]), int(options.ScaleIDRange.split(',')[1])]
PDFErrorIDRange = [int(options.PDFErrorIDRange.split(',')[0]), int(options.PDFErrorIDRange.split(',')[1])]
PDFAlphaSIDRange = [int(options.PDFAlphaSIDRange.split(',')[0]), int(options.PDFAlphaSIDRange.split(',')[1])]
PDFAlphaSScaleValue = [float(options.PDFAlphaSScaleValue.split(',')[0]), float(options.PDFAlphaSScaleValue.split(',')[1])]

print 'isMC = '+str(isMC)
print 'isPrivateSample = '+str(isPrivateSample)
print 'ScaleIDRange = ',
print ScaleIDRange
print 'PDFErrorType = '+options.PDFErrorType
print 'PDFErrorIDRange = ',
print PDFErrorIDRange
print 'PDFAlphaSIDRange = ',
print PDFAlphaSIDRange
print 'PDFAlphaSScaleValue = ',
print PDFAlphaSScaleValue
print 'year = '+str(options.year)


#### Global Tag
#### https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMiniAOD#2017_and_2016_re_miniAOD_94X_ver
#### https://twiki.cern.ch/twiki/bin/view/CMS/JECDataMC
GT_MC = '94X_mc2017_realistic_v17'
GT_DATA = '94X_dataRun2_v11'
if Is2016:
  GT_DATA = '94X_dataRun2_v10'
  GT_MC = '94X_mcRun2_asymptotic_v3'
elif Is2017:
  GT_MC = '94X_mc2017_realistic_v17'
  GT_DATA = '94X_dataRun2_v11'
elif Is2018:
  GT_MC = '102X_upgrade2018_realistic_v16'
  GT_DATA = '102X_dataRun2_Sep2018Rereco_v1'
  if (not isMC) and '2018Prompt' in options.sampletype:
    GT_DATA = '102X_dataRun2_Prompt_v12'


####################################################################################################################

process = cms.Process("NTUPLE")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

## Options and Output Report
process.options   = cms.untracked.PSet( 
  SkipEvent = cms.untracked.vstring('ProductNotFound'),
  wantSummary = cms.untracked.bool(True) 
)
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring( options.inputFiles ),
  #skipEvents=cms.untracked.uint32(5),
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

# -- Geometry and Detector Conditions (needed for a few patTuple production steps) -- #
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("Configuration.Geometry.GeometryRecoDB_cff")
#process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

# -- Global Tags -- #
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")

if isMC == True:
  process.GlobalTag.globaltag = cms.string(GT_MC)
else:
  process.GlobalTag.globaltag = cms.string(GT_DATA) #prompt-reco global tag


process.TFileService = cms.Service("TFileService",
  fileName = cms.string( options.outputFile )
)

#################
# -- DY Tree -- #
#################
from SKFlatMaker.SKFlatMaker.SKFlatMaker_cfi import *

process.recoTree = SKFlatMaker.clone()
process.recoTree.DebugLevel = cms.untracked.int32(0)
process.recoTree.StoreHLTObjectFlag = False ##FIXME

# -- Objects without Corrections -- # 
process.recoTree.Muon = cms.untracked.InputTag("slimmedMuons") # -- miniAOD -- #
process.recoTree.Electron = cms.untracked.InputTag("slimmedElectrons") # -- miniAOD -- #
process.recoTree.Photon = cms.untracked.InputTag("slimmedPhotons") # -- miniAOD -- #
process.recoTree.Jet = cms.untracked.InputTag("slimmedJets") # -- miniAOD -- #
process.recoTree.FatJet = cms.untracked.InputTag("slimmedJetsAK8")
process.recoTree.MET = cms.InputTag("slimmedMETs")
process.recoTree.GenParticle = cms.untracked.InputTag("prunedGenParticles") # -- miniAOD -- #

process.recoTree.ScaleIDRange = cms.untracked.vint32(ScaleIDRange)
process.recoTree.PDFErrorType = cms.untracked.string(options.PDFErrorType)
process.recoTree.PDFErrorIDRange = cms.untracked.vint32(PDFErrorIDRange)
process.recoTree.PDFAlphaSIDRange = cms.untracked.vint32(PDFAlphaSIDRange)
process.recoTree.PDFAlphaSScaleValue = cms.untracked.vdouble(PDFAlphaSScaleValue)

if isPrivateSample:
  process.recoTree.LHEEventProduct = cms.untracked.InputTag("source")
  process.recoTree.LHERunInfoProduct = cms.untracked.InputTag("source")

process.recoTree.rho = cms.untracked.InputTag("fixedGridRhoFastjetAll")
process.recoTree.conversionsInputTag = cms.untracked.InputTag("reducedEgamma:reducedConversions") # -- miniAOD -- #

# -- for Track & Vertex -- #
process.recoTree.PrimaryVertex = cms.untracked.InputTag("offlineSlimmedPrimaryVertices") # -- miniAOD -- #

# -- Else -- #
process.recoTree.PileUpInfo = cms.untracked.InputTag("slimmedAddPileupInfo")

# -- Filters -- #
process.recoTree.ApplyFilter = False

# -- Store Flags -- #
process.recoTree.StoreMuonFlag = True
process.recoTree.StoreElectronFlag = True
process.recoTree.StorePhotonFlag = True # -- photon part should be updated! later when it is necessary -- #
process.recoTree.StoreJetFlag = True
process.recoTree.StoreMETFlag = True
process.recoTree.StoreGENFlag = isMC
process.recoTree.KeepAllGen = isMC
process.recoTree.StoreLHEFlag = isMC

#### EGamma ####

myEleID =  [
'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff',
'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff',
'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V2_cff',
'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_iso_V2_cff',
]

###############################################
#### -- Official L1 Prefiring reweight -- ####
###############################################
#### Default L1 prefiring reweight : 2017 Campaign
process.prefiringweight = cms.EDProducer("L1ECALPrefiringWeightProducer",
                                         ThePhotons = cms.InputTag("slimmedPhotons"),
                                         TheJets = cms.InputTag("slimmedJets"),
                                         L1Maps = cms.string("L1PrefiringMaps_new.root"), # location of map root file
                                         DataEra = cms.string("2017BtoF"),
                                         UseJetEMPt = cms.bool(True), #False : jet pt VS eta map. True : jet pt(em) VS eta map
                                         PrefiringRateSystematicUncty = cms.double(0.2) #Minimum relative prefiring uncty per object
                                         )
#### L1 prefiring reweight : 2016 Campaign
if Is2016:
  process.prefiringweight = cms.EDProducer("L1ECALPrefiringWeightProducer",
                                           hePhotons = cms.InputTag("slimmedPhotons"),
                                           TheJets = cms.InputTag("slimmedJets"),
                                           L1Maps = cms.string("L1PrefiringMaps_new.root"),
                                           DataEra = cms.string("2016BtoH"),
                                           UseJetEMPt = cms.bool(True),
                                           PrefiringRateSystematicUncty = cms.double(0.2)
                                           }


if Is2016:

  print "################"
  print "Running 2016"
  print "################"

  from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
  setupEgammaPostRecoSeq(process,
                         runVID=True,
                         era='2016-Legacy',
                         eleIDModules=myEleID,
                         runEnergyCorrections=False)

  process.p = cms.Path(
    process.egammaPostRecoSeq *
    process.prefiringweight *
    process.recoTree
  )

elif Is2017:

  print "################"
  print "Running 2017"
  print "################"

  from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
  setupEgammaPostRecoSeq(process,
                         runVID=True, #saves CPU time by not needlessly re-running VID
                         era='2017-Nov17ReReco',
                         eleIDModules=myEleID)
  #a sequence egammaPostRecoSeq has now been created and should be added to your path, eg process.p=cms.Path(process.egammaPostRecoSeq)

  from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD

  runMetCorAndUncFromMiniAOD (
          process,
          isData = (not isMC), # false for MC
          fixEE2017 = True,
          fixEE2017Params = {'userawPt': True, 'ptThreshold':50.0, 'minEtaThreshold':2.65, 'maxEtaThreshold': 3.139} ,
          postfix = "ModifiedMET"
  )
  process.recoTree.MET = cms.InputTag("slimmedMETsModifiedMET")

  process.p = cms.Path(
    process.egammaPostRecoSeq *
    process.fullPatMetSequenceModifiedMET *
    process.prefiringweight *
    process.recoTree
  )

elif Is2018:

  print "################"
  print "Running 2018"
  print "################"

  process.p = cms.Path(
    process.recoTree
  )
