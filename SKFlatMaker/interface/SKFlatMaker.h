#ifndef SKFlatMaker_H
#define SKFlatMaker_H

////////////////////////////////
// -- system include files -- //
////////////////////////////////
#include <memory>
#include <iostream>
#include <random>

//////////////////////
// -- FrameWorks -- //
//////////////////////
#include "FWCore/Framework/interface/Frameworkfwd.h" // -- Forward declarations of types in the EDM(Event Data Model).
#include "FWCore/Framework/interface/EDAnalyzer.h" // -- EDAnalyzer is the base class for all analyzer "modules".
#include "FWCore/Framework/interface/Event.h" // -- This is the primary interface for accessing EDProducts from a single collision and inserting new derived products.
#include "FWCore/Framework/interface/MakerMacros.h" // -- including temporary until a better solution can be found (leads to more physical coupling than is probably necessary)
#include "FWCore/ParameterSet/interface/ParameterSet.h" // -- Declaration for ParameterSet(parameter set) and related types 
#include "FWCore/ParameterSet/interface/ParameterSetfwd.h" // -- Foward declarations of variables for ParameterSet
#include "FWCore/Framework/interface/ESHandle.h" // -- No description
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/RegexMatch.h"


/////////////////////
// -- For Muons -- //
/////////////////////
#include "DataFormats/MuonReco/interface/MuonFwd.h" // -- Forward declarations of muon variables
#include "DataFormats/MuonReco/interface/Muon.h" // -- A reconstructed Muon. (tracker alone, muon detector alone, combined muon plus tracker)
#include "DataFormats/PatCandidates/interface/Muon.h" // -- Analysis-level muon class, pat::Muon implements the analysis-level muon class within the 'pat' namespace. PAT(Physics Analysis Toolkit)
#include "DataFormats/MuonReco/interface/MuonTimeExtra.h"
#include "DataFormats/MuonReco/interface/MuonTimeExtraMap.h"
#include "DataFormats/MuonReco/interface/MuonCocktails.h"
#include "DataFormats/MuonReco/interface/MuonCosmicCompatibility.h" // -- Variables shows how muon is cosmic-like
#include "SKFlatMaker/SKFlatMaker/interface/RoccoR.h"

/////////////////////////
// -- For Electrons -- //
/////////////////////////
#include "DataFormats/PatCandidates/interface/Photon.h" // -- Analysis-level Photon class, pat::Photon implements the analysis-level photon class within the 'pat' namespace
#include "DataFormats/PatCandidates/interface/Electron.h" // -- Analysis-level electron class,  pat::Electron implements the analysis-level electron class within the 'pat' namespace
#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h" // -- It seems as a function refer effective areas of ECAL
#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"


///////////////////
// -- For MET -- //
///////////////////
#include "DataFormats/PatCandidates/interface/MET.h" // -- Analysis-level MET class, pat::MET implements an analysis-level missing energy class as a 4-vector within the 'pat' namespace
#include "DataFormats/METReco/interface/PFMETFwd.h"
#include "DataFormats/METReco/interface/PFMET.h" // --  MET made from Particle Flow candidates, with various fraction functions ex)photonEtFraction()
#include "DataFormats/METReco/interface/PFMETCollection.h"

////////////////////
// -- For Jets -- //
////////////////////
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/PatCandidates/interface/Jet.h" // -- Analysis-level calorimeter jet class, Jet implements the analysis-level calorimeter jet class within the 'pat' namespace.
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "SKFlatMaker/SKFlatMaker/interface/JetTools.h"

////////////////////////////
// -- For GenParticles -- //
////////////////////////////
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h" // -- LHE info like PDF
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h" // -- ??
#include "DataFormats/HepMCCandidate/interface/GenParticle.h" // -- 
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h" // -- ???
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h" // -- contains information related to the details of the pileup simulation for a given event, ex) Nvtx, z of PU, sum(pt) of vtxs


//#include "SimDataFormats/HepMCProduct/interface/HepMCProduct.h"

//////////////////////////
// -- Track & Vertex -- //
//////////////////////////
#include "DataFormats/TrackReco/interface/TrackFwd.h" // -- Forward definitions for tracker variables
#include "DataFormats/TrackReco/interface/Track.h" // -- reconstructed tracks that are stored in the AOD and RECO. also contains a reference to more detailed information(RECO)
#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h" // -- A composite Candidate  with error matrix and other vertex fix information. 
#include "DataFormats/Candidate/interface/VertexCompositeCandidateFwd.h" // -- Foward declaration of VertexCompositeCandidate class's variables
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h" // -- Least-squares vertex fitter implemented in the Kalman Filter formalism
#include "PhysicsTools/RecoUtils/interface/CandCommonVertexFitter.h" // -- 
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h" // -- Helper class to build TransientTrack from the persistent Track.
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/Measurement1D.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "DataFormats/PatCandidates/interface/Vertexing.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/VertexTools/interface/InvariantMassFromVertex.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/IPTools/interface/IPTools.h"

////////////////////
// -- Triggers -- //
////////////////////
#include "FWCore/Common/interface/TriggerNames.h" // -- Used to access the names and indices of the triggers corresponding to a particular TriggerResults object
#include "FWCore/Common/interface/TriggerResultsByName.h" // --  Class which provides methods to access trigger results
#include "DataFormats/Common/interface/TriggerResults.h" // -- The trigger path results are maintained here as a sequence of entries, one per trigger path
#include "DataFormats/HLTReco/interface/TriggerEvent.h" // -- The single EDProduct to be saved for each event (AOD case) describing the (HLT) trigger table
#include "DataFormats/HLTReco/interface/TriggerObject.h" // --  A single trigger object (e.g., an isolated muon, or MET) described by its 4-momentum and physics type
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h" // -- Analysis-level trigger object class (stand-alone). (within the 'pat' namespace.)
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h" // -- This class provides access routines to get hold of the HLT Configuration


////////////////
// -- Else -- //
////////////////
#include "DataFormats/Math/interface/LorentzVector.h" // -- (pt, eta, phi, E) OR (pt, eta, phi, M)
#include "DataFormats/GeometrySurface/interface/GloballyPositioned.h" // -- Base class for surfaces and volumes positioned in global 3D space.
#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h" // -- The Muon DetUnit geometry.
#include "DataFormats/Common/interface/RefToBaseVector.h" // -- 
#include "DataFormats/Candidate/interface/NamedCompositeCandidateFwd.h" // -- Foward definition of NamedCompositeCandidate class
#include "DataFormats/Candidate/interface/NamedCompositeCandidate.h" // -- A Candidate composed of daughters. The daughters are owned by the composite candidate.
#include "DataFormats/Candidate/interface/CompositeCandidateFwd.h" // -- Foward definition of CompositeCandidate class
#include "DataFormats/Candidate/interface/CompositeCandidate.h" // A Candidate composed of daughters. The daughters are owned by the composite candidate.
#include "DataFormats/Common/interface/View.h" // -- Provide access to the collected elements contained by any WrapperBase that is a sequence.
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h" // -- 
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h" // -- Class to provide lumi weighting for analyzers to weight "flat-to-N" MC samples to data
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h" // -- contains information related to the details of the pileup simulation for a given event
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Candidate/interface/CandMatchMap.h"
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositFwd.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "PhysicsTools/IsolationAlgos/interface/IsoDepositVetoFactory.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/PFIsolation.h"


////////////////
// -- ROOT -- //
////////////////
#include <TFile.h>
#include <TTree.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TFrame.h>
#include <TMath.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TF1.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <boost/foreach.hpp>
#include <TRandom.h>

using namespace std;
using namespace pat;
using namespace edm;

namespace reco { class CandCommonVertexFitterBase; class VertexCompositeCandidate; class CandCommonVertexFitter; }

class SKFlatMaker : public edm::EDAnalyzer
{
 public:
  explicit SKFlatMaker(const edm::ParameterSet&);
  ~SKFlatMaker();
  
 private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  virtual void beginRun(const edm::Run &, const edm::EventSetup & );
  virtual void endRun(const edm::Run &, const edm::EventSetup & );
  
  virtual void fillPrimaryVertex(const edm::Event &iEvent);  // fill primary vertex information
  virtual void fillMET(const edm::Event &iEvent);            // fill MET information
  virtual void fillPhotons(const edm::Event &iEvent);
  virtual void fillMuons(const edm::Event &iEvent, const edm::EventSetup& iSetup);
  virtual void fillElectrons(const edm::Event &iEvent, const edm::EventSetup& iSetup);
  virtual void fillJet(const edm::Event &iEvent);            // fill jet and b-tagging information
  virtual void fillFatJet(const edm::Event &iEvent);            // fill jet and b-tagging information
  virtual void hltReport(const edm::Event &iEvent);          // fill list of triggers fired in an event
  virtual void fillLHEInfo(const edm::Event &iEvent);
  virtual void fillGENInfo(const edm::Event &iEvent);            // fill MET information

  virtual float miniIsoDr(const math::XYZTLorentzVector &p4, float mindr, float maxdr, float kt_scale);
  virtual PFIsolation GetMiniIso(edm::Handle<pat::PackedCandidateCollection> pfcands,
                                 const math::XYZTLorentzVector &p4,
                                 float mindr, float maxdr, float kt_scale,
                                 float ptthresh, float deadcone_ch, float deadcone_pu,
                                 float deadcone_ph, float deadcone_nh, float dZ_cut);

  int theDebugLevel;                   // 0 no prints, 1 some, 2 lots
  std::string processName;
  std::string theElectronID;
  
  HLTConfigProvider hltConfig_;
  
  // -- Tokens (for 76X) -- //
  edm::EDGetTokenT< std::vector<pat::Muon> >            MuonToken;
  edm::EDGetTokenT< edm::View<pat::Electron> >          ElectronToken;
  edm::EDGetTokenT< edm::View<pat::Photon> >            PhotonToken;
  edm::EDGetTokenT< std::vector<pat::Jet> >             JetToken;
  edm::EDGetTokenT< reco::GenJetCollection >            genJetToken;
  edm::EDGetTokenT< std::vector<pat::Jet> >             FatJetToken;
  edm::EDGetTokenT< reco::GenJetCollection >            genFatJetToken;
  edm::EDGetTokenT< std::vector<pat::MET> >             MetToken;

  edm::EDGetTokenT< LHEEventProduct >               LHEEventProductToken;
  edm::EDGetTokenT< LHERunInfoProduct >             LHERunInfoProductToken;
  edm::EDGetTokenT< reco::GenParticleCollection>    mcLabel_;

  edm::EDGetTokenT<pat::PackedCandidateCollection> pcToken_;
  std::vector<double> miniIsoParams_;
  std::vector<double> miniIsoParamsE_;
  std::vector<double> miniIsoParamsB_;

  edm::EDGetTokenT< edm::TriggerResults >          METFilterResultsToken_PAT;
  edm::EDGetTokenT< edm::TriggerResults >          METFilterResultsToken_RECO;
  
  edm::EDGetTokenT< double >                          RhoToken;
  edm::EDGetTokenT< std::vector<reco::Conversion> >   ConversionsToken;
  edm::EDGetTokenT< std::vector< reco::GsfTrack > >   GsfTrackToken;
  
  edm::EDGetTokenT< edm::TriggerResults >                          TriggerToken;
  edm::EDGetTokenT< edm::TriggerResults >                          TriggerTokenPAT;
  edm::EDGetTokenT< std::vector<pat::TriggerObjectStandAlone> >    TriggerObjectToken;
  
  edm::EDGetTokenT< GenEventInfoProduct >                GenEventInfoToken;
  edm::EDGetTokenT< reco::BeamSpot >                     BeamSpotToken;
  edm::EDGetTokenT< reco::VertexCollection >             PrimaryVertexToken;
  edm::EDGetTokenT< edm::View<reco::Track> >             TrackToken;
  edm::EDGetTokenT< std::vector< PileupSummaryInfo > >   PileUpInfoToken;

  // -- Tokens for L1 Prefiring reweight
  edm::EDGetTokenT< double > prefweight_token;
  edm::EDGetTokenT< double > prefweightup_token;
  edm::EDGetTokenT< double > prefweightdown_token;
  
  //edm::Handle<bool> ifilterbadChCand;
  //edm::Handle<bool> ifilterbadPFMuon;
  edm::Handle<edm::TriggerResults> METFilterResults;
  
  // // -- Photon information -- //
  // edm::InputTag thePhotonLabel;
  // edm::InputTag full5x5SigmaIEtaIEtaMapLabel; 
  // edm::InputTag phoChargedIsolationLabel; 
  // edm::InputTag phoNeutralHadronIsolationLabel; 
  // edm::InputTag phoPhotonIsolationLabel;     
  edm::FileInPath electron_EA_NHandPh_file;
  edm::FileInPath photon_EA_CH_file;
  edm::FileInPath photon_EA_HN_file;
  edm::FileInPath photon_EA_Ph_file;
  
    
  // -- Store flags -- // 
  bool theStorePriVtxFlag;                // Yes or No to store primary vertex
  bool theStoreJetFlag;                // Yes or No to store Jet
  bool theStoreFatJetFlag;                // Yes or No to store FatJet
  bool theStoreMETFlag;                // Yes or No to store MET 
  bool theStoreHLTReportFlag;             // Yes or No to store HLT reuslts (list of triggers fired)
  bool theStoreHLTObjectFlag;
  bool theStoreMuonFlag;
  bool theStoreElectronFlag;
  bool theStoreLHEFlag;
  bool theStoreGENFlag;
  bool theStorePhotonFlag;
  bool theKeepAllGen;
  bool IsData;
  bool DoPileUp;
  
  // double theCrossSection;
  // double theFilterEfficiency;
  // double theTotalNevents;
  double theBDiscriminant;
  // double theIntegratedLumi;
  double theBDiscriminant_alg1;
  double theBDiscriminant_alg2;
  double theBDiscriminant_alg3;
  int theNHighQualLeptons;
  
  edm::ESHandle<TransientTrackBuilder> theTTBuilder;

  std::vector<std::string > HLTName_WildCard;
  
  bool Flag_goodVertices;
  bool Flag_globalTightHalo2016Filter;
  bool Flag_globalSuperTightHalo2016Filter;
  bool Flag_HBHENoiseFilter;
  bool Flag_HBHENoiseIsoFilter;
  bool Flag_EcalDeadCellTriggerPrimitiveFilter;
  bool Flag_BadPFMuonFilter;
  bool Flag_BadChargedCandidateFilter;
  bool Flag_eeBadScFilter;
  bool Flag_ecalBadCalibFilter;
  
  // Pile-up Reweight
  // edm::LumiReWeighting LumiWeights_;
  // reweight::PoissonMeanShifter PShiftUp_;
  // reweight::PoissonMeanShifter PShiftDown_;
  // edm::LumiReWeighting LumiWeightsMuonPhys_;
  // reweight::PoissonMeanShifter PShiftUpMuonPhys_;
  // reweight::PoissonMeanShifter PShiftDownMuonPhys_;
  
  // std::vector<double> PileUpRD_;
  // std::vector<double> PileUpRDMuonPhys_;
  // std::vector<double> PileUpMC_;
  
  unsigned int nPileUp;
  double pileUpReweightIn;
  double pileUpReweight;
  double pileUpReweightPlus;
  double pileUpReweightMinus;
  
  double pileUpReweightInMuonPhys;
  double pileUpReweightMuonPhys;
  double pileUpReweightPlusMuonPhys;
  double pileUpReweightMinusMuonPhys;

  std::vector< int > ScaleIDRange_, PDFErrorIDRange_, PDFAlphaSIDRange_;
  std::string PDFErrorType_;
  std::vector< double > PDFAlphaSScaleValue_;

  TTree *DYTree;
  
  int nEvt;
  
  //FILL a tree
  static const int MPSIZE = 2000;
  
  // Invariant Mass distribution of SS(OS) di-muon events GG (2 global)
  // GlbTree
  int runNum;
  unsigned long long evtNum;
  int lumiBlock;
  double PUweight;
  double sumEt;
  double photonEt;
  double chargedHadronEt;
  double neutralHadronEt;
  double Rho;
  
  int Nelectrons;
  
  // PV
  int nPV;
  int PVtrackSize;
  double PVchi2;
  double PVndof;
  double PVnormalizedChi2;
  double PVx;
  double PVy;
  double PVz;
  double PVprob;

  //==== L1 Prefiring Reweight
  double L1PrefiringReweight;
  double L1PrefiringReweight_Up;
  double L1PrefiringReweight_Down;

  //==== trigger object

  vector<string> HLT_TriggerName;
  vector<string> HLT_TriggerFilterName;
  vector<double> HLTObject_pt;
  vector<double> HLTObject_eta;
  vector<double> HLTObject_phi;
  vector<string> HLTObject_FiredFilters;
  vector<string> HLTObject_FiredPaths;

  //==== Jet

  vector<double> jet_pt;
  vector<double> jet_eta;
  vector<double> jet_phi;
  vector<double> jet_charge;
  vector<double> jet_area;
  vector<int> jet_partonFlavour;
  vector<int> jet_hadronFlavour;
  vector<double> jet_CSVv2;
  vector<double> jet_DeepCSV;
  vector<double> jet_CvsL;
  vector<double> jet_CvsB;
  vector<double> jet_DeepFlavour_b;
  vector<double> jet_DeepFlavour_bb;
  vector<double> jet_DeepFlavour_lepb;
  vector<double> jet_DeepFlavour_c;
  vector<double> jet_DeepFlavour_uds;
  vector<double> jet_DeepFlavour_g;
  vector<double> jet_DeepCvsL;
  vector<double> jet_DeepCvsB;
  vector<double> jet_chargedHadronEnergyFraction;
  vector<double> jet_neutralHadronEnergyFraction;
  vector<double> jet_neutralEmEnergyFraction;
  vector<double> jet_chargedEmEnergyFraction;
  vector<double> jet_muonEnergyFraction;
  vector<int> jet_chargedMultiplicity;
  vector<int> jet_neutralMultiplicity;
  vector<bool> jet_tightJetID;
  vector<bool> jet_tightLepVetoJetID;
  vector<int> jet_partonPdgId;
  vector<int> jet_vtxNtracks;
  vector<double> jet_m;
  vector<double> jet_energy;
  vector<double> jet_PileupJetId;
  vector<double> jet_shiftedEnUp;
  vector<double> jet_shiftedEnDown;
  vector<double> jet_smearedRes;
  vector<double> jet_smearedResUp;
  vector<double> jet_smearedResDown;
  vector<double> jet_JECL1FastJet;
  vector<double> jet_JECFull;

  //==== JEC
  JetCorrectionUncertainty *jet_jecUnc;
  //JetCorrectionUncertainty *jet_jecUnc_methodB; // for cross check
  std::string jet_payloadName_;
  JetCorrectionUncertainty *fatjet_jecUnc;
  std::string fatjet_payloadName_;

  //==== JER

  static constexpr const double MIN_JET_ENERGY = 1e-2;
  std::mt19937 m_random_generator;
  template<class T>
  const reco::GenJet* match(const T& jet, double resolution, TString whichjet);

  JME::JetResolution jet_resolution;
  JME::JetResolutionScaleFactor jet_resolution_sf;
  edm::Handle<reco::GenJetCollection> m_genJets;

  JME::JetResolution fatjet_resolution;
  JME::JetResolutionScaleFactor fatjet_resolution_sf;
  edm::Handle<reco::GenJetCollection> m_genFatJets;

  //==== FatJet

  vector<double> fatjet_pt;
  vector<double> fatjet_eta;
  vector<double> fatjet_phi;
  vector<double> fatjet_charge;
  vector<double> fatjet_area;
  vector<int> fatjet_partonFlavour;
  vector<int> fatjet_hadronFlavour;
  vector<double> fatjet_CSVv2;
  vector<double> fatjet_DeepCSV;
  vector<double> fatjet_CvsL;
  vector<double> fatjet_CvsB;
  vector<double> fatjet_DeepFlavour_b;
  vector<double> fatjet_DeepFlavour_bb;
  vector<double> fatjet_DeepFlavour_lepb;
  vector<double> fatjet_DeepFlavour_c;
  vector<double> fatjet_DeepFlavour_uds;
  vector<double> fatjet_DeepFlavour_g;
  vector<double> fatjet_DeepCvsL;
  vector<double> fatjet_DeepCvsB;
  vector<bool> fatjet_tightJetID;
  vector<bool> fatjet_tightLepVetoJetID;
  vector<int> fatjet_partonPdgId;
  vector<int> fatjet_vtxNtracks;
  vector<double> fatjet_m;
  vector<double> fatjet_energy;
  vector<double> fatjet_puppi_tau1;
  vector<double> fatjet_puppi_tau2;
  vector<double> fatjet_puppi_tau3;
  vector<double> fatjet_puppi_tau4;
  vector<double> fatjet_softdropmass;
  vector<double> fatjet_chargedHadronEnergyFraction;
  vector<double> fatjet_neutralHadronEnergyFraction;
  vector<double> fatjet_neutralEmEnergyFraction;
  vector<double> fatjet_chargedEmEnergyFraction;
  vector<double> fatjet_muonEnergyFraction;
  vector<int> fatjet_chargedMultiplicity;
  vector<int> fatjet_neutralMultiplicity;
  vector<double> fatjet_shiftedEnUp;
  vector<double> fatjet_shiftedEnDown;
  vector<double> fatjet_smearedRes;
  vector<double> fatjet_smearedResUp;
  vector<double> fatjet_smearedResDown;
  vector<double> fatjet_LSF;
  vector<double> fatjet_LSFlep_PID;
  vector<double> fatjet_LSFlep_Pt;
  vector<double> fatjet_LSFlep_Eta;
  vector<double> fatjet_LSFlep_Phi;

  //==== Electron

  vector<std::string> electron_IDtoSave;
  vector<double> electron_MVAIso;
  vector<double> electron_MVANoIso;
  vector<double> electron_Energy;
  vector<double> electron_Energy_Scale_Up;
  vector<double> electron_Energy_Scale_Down;
  vector<double> electron_Energy_Smear_Up;
  vector<double> electron_Energy_Smear_Down;
  vector<double> electron_eta;
  vector<double> electron_phi;
  vector<int> electron_charge;
  vector<double> electron_gsfpt;
  vector<double> electron_gsfEta;
  vector<double> electron_gsfPhi;
  vector<int> electron_gsfCharge;
  vector<double> electron_scEta;
  vector<double> electron_scPhi;
  vector<double> electron_etaWidth;
  vector<double> electron_phiWidth;
  vector<double> electron_dEtaIn;
  vector<double> electron_dEtaInSeed;
  vector<double> electron_dPhiIn;
  vector<double> electron_sigmaIEtaIEta;
  vector<double> electron_Full5x5_SigmaIEtaIEta;
  vector<double> electron_e2x5OverE5x5;
  vector<double> electron_e1x5OverE5x5;
  vector<double> electron_HoverE;
  vector<double> electron_fbrem;
  vector<double> electron_eOverP;
  vector<double> electron_InvEminusInvP;
  vector<double> electron_dxyVTX;
  vector<double> electron_dxyerrVTX;
  vector<double> electron_dzVTX;
  vector<double> electron_dzerrVTX;
  vector<double> electron_3DIPVTX;
  vector<double> electron_3DIPerrVTX;
  vector<double> electron_dxy;
  vector<double> electron_sigdxy;
  vector<double> electron_dz;
  vector<double> electron_dxyBS;
  vector<double> electron_dzBS;
  vector<double> electron_chIso03;
  vector<double> electron_nhIso03;
  vector<double> electron_phIso03;
  vector<double> electron_puChIso03;
  vector<bool> electron_passConversionVeto;
  vector<bool> electron_isGsfCtfScPixChargeConsistent;
  vector<bool> electron_isGsfScPixChargeConsistent;
  vector<bool> electron_isGsfCtfChargeConsistent;
  vector<int> electron_mHits;
  vector<int> electron_ecalDriven;
  vector<double> electron_r9;
  vector<double> electron_scEnergy;
  vector<double> electron_scPreEnergy;
  vector<double> electron_scRawEnergy;
  vector<double> electron_scEt;
  vector<double> electron_E15;
  vector<double> electron_E25;
  vector<double> electron_E55;
  vector<double> electron_RelPFIso_dBeta;
  vector<double> electron_RelPFIso_Rho;
  vector<unsigned int> electron_IDBit;
  vector<double> electron_EnergyUnCorr;
  vector<double> electron_chMiniIso;
  vector<double> electron_nhMiniIso;
  vector<double> electron_phMiniIso;
  vector<double> electron_puChMiniIso;
  vector<double> electron_trackIso;
  vector<double> electron_dr03EcalRecHitSumEt;
  vector<double> electron_dr03HcalDepth1TowerSumEt;

  //==== Muon

  vector<double> muon_PfChargedHadronIsoR04;
  vector<double> muon_PfNeutralHadronIsoR04;
  vector<double> muon_PfGammaIsoR04;
  vector<double> muon_PFSumPUIsoR04;
  vector<double> muon_PfChargedHadronIsoR03;
  vector<double> muon_PfNeutralHadronIsoR03;
  vector<double> muon_PfGammaIsoR03;
  vector<double> muon_PFSumPUIsoR03;
  vector<unsigned int> muon_TypeBit;
  vector<unsigned int> muon_IDBit;
  vector<double> muon_dB;
  vector<double> muon_phi;
  vector<double> muon_eta;
  vector<double> muon_pt;
  vector<double> muon_mass;
  vector<double> muon_trkiso;
  vector<double> muon_hcaliso;
  vector<double> muon_ecaliso;
  vector<double> muon_trkisoR05;
  vector<double> muon_hcalisoR05;
  vector<double> muon_ecalisoR05;
  vector<int> muon_charge;
  vector<int> muon_nChambers;
  vector<int> muon_matchedstations;
  vector<int> muon_stationMask;
  vector<int> muon_nSegments;
  vector<double> muon_normchi;
  vector<int> muon_validhits;
  vector<int> muon_trackerHits;
  vector<int> muon_pixelHits;
  vector<int> muon_validmuonhits;
  vector<int> muon_trackerLayers;
  vector<int> muon_trackerHitsGLB;
  vector<int> muon_trackerLayersGLB;
  vector<int> muon_pixelHitsGLB;
  vector<double> muon_qoverp;
  vector<double> muon_theta;
  vector<double> muon_lambda;
  vector<double> muon_dxy;
  vector<double> muon_d0;
  vector<double> muon_dsz;
  vector<double> muon_dz;
  vector<double> muon_dxyBS;
  vector<double> muon_dzBS;
  vector<double> muon_dszBS;
  vector<double> muon_dxyVTX;
  vector<double> muon_dxyerrVTX;
  vector<double> muon_dzVTX;
  vector<double> muon_dzerrVTX;
  vector<double> muon_3DIPVTX;
  vector<double> muon_3DIPerrVTX;
  vector<double> muon_dszVTX;
  vector<double> muon_vx;
  vector<double> muon_vy;
  vector<double> muon_vz;
  vector<double> muon_Best_pt;
  vector<double> muon_Best_ptError;
  vector<double> muon_Best_eta;
  vector<double> muon_Best_phi;
  vector<double> muon_Inner_pt;
  vector<double> muon_Inner_ptError;
  vector<double> muon_Inner_eta;
  vector<double> muon_Inner_phi;
  vector<double> muon_Outer_pt;
  vector<double> muon_Outer_ptError;
  vector<double> muon_Outer_eta;
  vector<double> muon_Outer_phi;
  vector<double> muon_GLB_pt;
  vector<double> muon_GLB_ptError;
  vector<double> muon_GLB_eta;
  vector<double> muon_GLB_phi;
  vector<double> muon_TuneP_pt;
  vector<double> muon_TuneP_ptError;
  vector<double> muon_TuneP_eta;
  vector<double> muon_TuneP_phi;
  vector<double> muon_TuneP_charge;
  vector<double> muon_roch_sf;
  vector<double> muon_roch_sf_up;
  vector<double> muon_PfChargedHadronMiniIso;
  vector<double> muon_PfNeutralHadronMiniIso;
  vector<double> muon_PfGammaMiniIso;
  vector<double> muon_PFSumPUMiniIso;

  //==== Rochestor correction
  RoccoR rc;

  //==== LHE

  vector<double> PDFWeights_Scale;
  vector<double> PDFWeights_Error;
  vector<double> PDFWeights_AlphaS;
 
  //==== GEN

  vector<double> gen_phi;
  vector<double> gen_eta;
  vector<double> gen_pt;
  vector<double> gen_mass;
  vector<double> gen_charge;
  vector<int> gen_mother_index;
  vector<int> gen_status;
  vector<int> gen_PID;
  vector<int> gen_isPrompt;
  vector<int> gen_isPromptFinalState;
  vector<int> gen_isTauDecayProduct;
  vector<int> gen_isPromptTauDecayProduct;
  vector<int> gen_isDirectPromptTauDecayProductFinalState;
  vector<int> gen_isHardProcess;
  vector<int> gen_isLastCopy;
  vector<int> gen_isLastCopyBeforeFSR;
  vector<int> gen_isPromptDecayed;
  vector<int> gen_isDecayedLeptonHadron;
  vector<int> gen_fromHardProcessBeforeFSR;
  vector<int> gen_fromHardProcessDecayed;
  vector<int> gen_fromHardProcessFinalState;
  vector<int> gen_isMostlyLikePythia6Status3;
  double gen_weight;
  double genWeight_Q;
  double genWeight_X1;
  double genWeight_X2;
  int genWeight_id1;
  int genWeight_id2;
  double genWeight_alphaQCD;
  double genWeight_alphaQED;
  
  //==== Photon information
  vector<double> photon_Energy;
  vector<double> photon_EnergyUnCorr;
  vector<double> photon_eta;
  vector<double> photon_phi;
  vector<double> photon_scEta;
  vector<double> photon_scPhi;
  vector<double> photon_HoverE;
  vector<int> photon_hasPixelSeed;
  vector<double> photon_Full5x5_SigmaIEtaIEta;
  vector<double> photon_ChIso;
  vector<double> photon_NhIso;
  vector<double> photon_PhIso;
  vector<double> photon_ChIsoWithEA;
  vector<double> photon_NhIsoWithEA;
  vector<double> photon_PhIsoWithEA;
  vector<bool> photon_passMVAID_WP80;
  vector<bool> photon_passMVAID_WP90;
  vector<bool> photon_passLooseID;
  vector<bool> photon_passMediumID;
  vector<bool> photon_passTightID;

  // Effective area constants for all isolation types
  // EffectiveAreas effAreaChHadrons_;
  // EffectiveAreas effAreaNeuHadrons_;
  // EffectiveAreas effAreaPhotons_;

  //==== MET
  double pfMET_pt;
  double pfMET_phi;
  double pfMET_SumEt;
  double pfMET_Type1_pt;
  double pfMET_Type1_phi;
  double pfMET_Type1_SumEt;
  double pfMET_Type1_PhiCor_pt;
  double pfMET_Type1_PhiCor_phi;
  double pfMET_Type1_PhiCor_SumEt;
  vector<double> pfMET_pt_shifts;
  vector<double> pfMET_phi_shifts;
  vector<double> pfMET_SumEt_shifts;
  vector<double> pfMET_Type1_pt_shifts;
  vector<double> pfMET_Type1_phi_shifts;
  vector<double> pfMET_Type1_SumEt_shifts;
  vector<double> pfMET_Type1_PhiCor_pt_shifts;
  vector<double> pfMET_Type1_PhiCor_phi_shifts;
  vector<double> pfMET_Type1_PhiCor_SumEt_shifts;

};
#endif
