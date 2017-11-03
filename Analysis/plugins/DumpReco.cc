#include "WtoJPsiDs/Analysis/plugins/DumpReco.h"



DumpReco::DumpReco(const edm::ParameterSet& pSet) :
  trgsToken_        (consumes<edm::TriggerResults>             (pSet.getUntrackedParameter<edm::InputTag>("trgsTag"))),
  trgPrescalesToken_(consumes<pat::PackedTriggerPrescales>     (pSet.getUntrackedParameter<edm::InputTag>("trgPrescalesTag"))),
  vtxsToken_        (consumes<reco::VertexCollection>          (pSet.getUntrackedParameter<edm::InputTag>("vtxTag"))),    
  pfCandidatesToken_(consumes<edm::View<pat::PackedCandidate> >(pSet.getUntrackedParameter<edm::InputTag>("pfCandidatesTag"))),
  muonsToken_       (consumes<pat::MuonCollection>             (pSet.getUntrackedParameter<edm::InputTag>("muonsTag"))),
  tausToken_        (consumes<pat::TauCollection>              (pSet.getUntrackedParameter<edm::InputTag>("tausTag"))),
  jetsToken_        (consumes<pat::JetCollection>              (pSet.getUntrackedParameter<edm::InputTag>("jetsTag")))
{
  //---TFileService for output ntuples
  if( !fs_ )
  {
    throw edm::Exception(edm::errors::Configuration, "TFile Service is not registered in cfg file");
  }
  
  outTree_ = RecoTree(pSet.getUntrackedParameter<std::string>("treeName").c_str(),"Reco tree for W > J/Psi D_s studies");
  entry_ = 0;
}



// ------------ method called for each event  ------------
void DumpReco::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  //---get input collections
  iEvent.getByToken(trgsToken_,                 trgsHandle_);
  iEvent.getByToken(trgPrescalesToken_, trgPrescalesHandle_);
  iEvent.getByToken(vtxsToken_,                 vtxsHandle_);
  iEvent.getByToken(pfCandidatesToken_, pfCandidatesHandle_);
  iEvent.getByToken(muonsToken_,               muonsHandle_);
  iEvent.getByToken(tausToken_,                 tausHandle_);
  iEvent.getByToken(jetsToken_,                 jetsHandle_);
  
  
  //---reset output
  outTree_.Reset();
  outTree_.entry = entry_;
  outTree_.event = iEvent.id().event();
  outTree_.lumi = iEvent.id().luminosityBlock();
  outTree_.run = iEvent.id().run(); 
  
  
  //---fill trigger information
  outTree_.trgs_n = trgsHandle_->size();
  const edm::TriggerNames& names = iEvent.triggerNames(*trgsHandle_);
  for(unsigned int i = 0; i < trgsHandle_->size(); ++i)
  {
    outTree_.trgs_name -> push_back( names.triggerName(i) );
    outTree_.trgs_pass -> push_back( trgsHandle_->accept(i) );
    outTree_.trgs_prescale -> push_back( trgPrescalesHandle_->getPrescaleForIndex(i) );
  }
  
  
  //---fill track information
  auto pfCandidates = *pfCandidatesHandle_.product();
  outTree_.pfCandidates_n = pfCandidates.size();
  std::map<reco::VertexRef,float> sumPt;
  std::map<reco::VertexRef,float> sumPt2;
  for(auto &pfCandidate : *pfCandidatesHandle_)
  {
    outTree_.pfCandidates_pt     -> push_back( pfCandidate.pt() );
    outTree_.pfCandidates_eta    -> push_back( pfCandidate.eta() );
    outTree_.pfCandidates_phi    -> push_back( pfCandidate.phi() );
    outTree_.pfCandidates_energy -> push_back( pfCandidate.energy() );
    outTree_.pfCandidates_charge -> push_back( pfCandidate.charge() );
    outTree_.pfCandidates_pdgId  -> push_back( pfCandidate.pdgId() );
    outTree_.pfCandidates_vx     -> push_back( pfCandidate.vx() );
    outTree_.pfCandidates_vy     -> push_back( pfCandidate.vy() );
    outTree_.pfCandidates_vz     -> push_back( pfCandidate.vz() );
    outTree_.pfCandidates_PV_x   -> push_back( pfCandidate.vertexRef()->x() );
    outTree_.pfCandidates_PV_y   -> push_back( pfCandidate.vertexRef()->y() );
    outTree_.pfCandidates_PV_z   -> push_back( pfCandidate.vertexRef()->z() );
    outTree_.pfCandidates_dxy    -> push_back( pfCandidate.dxy((*vtxsHandle_)[0].position()) );
    outTree_.pfCandidates_dxyErr -> push_back( pfCandidate.dxyError() );
    outTree_.pfCandidates_dz     -> push_back( pfCandidate.dz((*vtxsHandle_)[0].position()) );
    outTree_.pfCandidates_dzErr  -> push_back( pfCandidate.dzError() );
    outTree_.pfCandidates_fromPV -> push_back( pfCandidate.fromPV(0) );
    outTree_.pfCandidates_pvAssociationQuality -> push_back( pfCandidate.pvAssociationQuality() );
    outTree_.pfCandidates_isHighPurity -> push_back( pfCandidate.trackHighPurity() );
    
    sumPt[pfCandidate.vertexRef()] += pfCandidate.pt();
    sumPt2[pfCandidate.vertexRef()] += pow(pfCandidate.pt(),2);
  }
  
  
  //---fill vtx information
  auto vtxs = *vtxsHandle_.product();
  outTree_.vtxs_n = vtxs.size();
  unsigned int it = 0;
  for(auto &vtx : *vtxsHandle_)
  {
    outTree_.vtxs_x -> push_back( vtx.x() );
    outTree_.vtxs_y -> push_back( vtx.y() );
    outTree_.vtxs_z -> push_back( vtx.z() );
    outTree_.vtxs_t -> push_back( -99 );
    outTree_.vtxs_normalizedChi2 -> push_back( vtx.normalizedChi2() );
    
    reco::VertexRef vtxRef(vtxsHandle_,it);
    outTree_.vtxs_sumPt  -> push_back( sumPt[vtxRef] );
    outTree_.vtxs_sumPt2 -> push_back( sumPt2[vtxRef] );
    ++it;
  }
  
  
  //---fill muon information
  auto muons = *muonsHandle_.product();
  outTree_.muons_n = muons.size();
  for(auto &muon : *muonsHandle_)
  {
    outTree_.muons_pt       -> push_back( muon.pt() );
    outTree_.muons_eta      -> push_back( muon.eta() );
    outTree_.muons_phi      -> push_back( muon.phi() );
    outTree_.muons_energy   -> push_back( muon.energy() );
    outTree_.muons_charge   -> push_back( muon.charge() );
    outTree_.muons_vx       -> push_back( muon.vx() );
    outTree_.muons_vy       -> push_back( muon.vy() );
    outTree_.muons_vz       -> push_back( muon.vz() );
    outTree_.muons_dxy      -> push_back( muon.muonBestTrack()->dxy((*vtxsHandle_)[0].position()) );
    outTree_.muons_dxyErr   -> push_back( muon.muonBestTrack()->dxyError() );
    outTree_.muons_dz       -> push_back( muon.muonBestTrack()->dz((*vtxsHandle_)[0].position()) );
    outTree_.muons_dzErr    -> push_back( muon.muonBestTrack()->dzError() );
    outTree_.muons_isLoose  -> push_back( muon.isLooseMuon() );
    outTree_.muons_isMedium -> push_back( muon.isMediumMuon() );
    outTree_.muons_isTight  -> push_back( muon.isTightMuon((*vtxsHandle_)[0]) );
    outTree_.muons_trackIso -> push_back( muon.trackIso() );
    outTree_.muons_ecalIso  -> push_back( muon.ecalIso() );
    outTree_.muons_hcalIso  -> push_back( muon.hcalIso() );
    outTree_.muons_pfIsoChargedHadron   -> push_back( muon.pfIsolationR03().sumChargedHadronPt );
    outTree_.muons_pfIsoChargedParticle -> push_back( muon.pfIsolationR03().sumChargedParticlePt );
    outTree_.muons_pfIsoNeutralHadron   -> push_back( muon.pfIsolationR03().sumNeutralHadronEt );
    outTree_.muons_pfIsoPhoton          -> push_back( muon.pfIsolationR03().sumPhotonEt );
    outTree_.muons_pfIsoPU              -> push_back( muon.pfIsolationR03().sumPUPt );
    
    reco::TrackRef innerTrack = muon.innerTrack();
    // std::cout << "pt: " << muon.pt() << "   innerTrack: " << innerTrack.isNull() << std::endl;
    if( !innerTrack.isNull() )
      outTree_.muons_trackerLayersWithMeasurement -> push_back( muon.innerTrack()->hitPattern().trackerLayersWithMeasurement() );
    else
      outTree_.muons_trackerLayersWithMeasurement -> push_back( -1 );
  }
  
  
  //---fill taus information
  auto taus = *tausHandle_.product();
  outTree_.taus_n = taus.size();
  for(auto &tau : *tausHandle_)
  {
    outTree_.taus_pt       -> push_back( tau.pt() );
    outTree_.taus_eta      -> push_back( tau.eta() );
    outTree_.taus_phi      -> push_back( tau.phi() );
    outTree_.taus_energy   -> push_back( tau.energy() );
    outTree_.taus_charge   -> push_back( tau.charge() );
    outTree_.taus_numberOfDaughters -> push_back( tau.numberOfDaughters() );
  }
  
  
  //---fill jets information
  auto jets = *jetsHandle_.product();
  outTree_.jets_n = jets.size();
  for(auto &jet : *jetsHandle_)
  {
    outTree_.jets_pt       -> push_back( jet.pt() );
    outTree_.jets_eta      -> push_back( jet.eta() );
    outTree_.jets_phi      -> push_back( jet.phi() );
    outTree_.jets_energy   -> push_back( jet.energy() );
    outTree_.jets_charge   -> push_back( jet.jetCharge() );
    outTree_.jets_numberOfDaughters -> push_back( jet.numberOfDaughters() );
    
    std::string constituentIds = "";
    for(unsigned int it = 0; it <  jet.numberOfSourceCandidatePtrs(); ++it)
    {
      reco::CandidatePtr pfCand = jet.sourceCandidatePtr(it);
      constituentIds += Form("%d,",int(pfCand.key()));
    }
    outTree_.jets_constituentIds -> push_back( constituentIds );
  }
  
  
  outTree_.GetTTreePtr()->Fill();
  ++entry_;
}
