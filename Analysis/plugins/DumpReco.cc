#include "WtoJPsiDs/Analysis/plugins/DumpReco.h"



DumpReco::DumpReco(const edm::ParameterSet& pSet) :
  vtxsToken_  (consumes<reco::VertexCollection> (pSet.getUntrackedParameter<edm::InputTag>("vtxTag"))),    
  tracksToken_(consumes<edm::View<reco::Track> >(pSet.getUntrackedParameter<edm::InputTag>("tracksTag"))),
  muonsToken_ (consumes<reco::MuonCollection>   (pSet.getUntrackedParameter<edm::InputTag>("muonsTag")))
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
  iEvent.getByToken(vtxsToken_,     vtxsHandle_);
  iEvent.getByToken(tracksToken_, tracksHandle_);
  iEvent.getByToken(muonsToken_,   muonsHandle_);
  
  
  //---reset output
  outTree_.Reset();
  outTree_.entry = entry_;
  outTree_.event = iEvent.id().event();
  outTree_.lumi = iEvent.id().luminosityBlock();
  outTree_.run = iEvent.id().run(); 
  
  
  //---fill vtx information
  auto vtxs = *vtxsHandle_.product();
  outTree_.vtxs_n = vtxs.size();
  for(auto &vtx : *vtxsHandle_)
  {
    outTree_.vtxs_x -> push_back( vtx.x() );
    outTree_.vtxs_y -> push_back( vtx.y() );
    outTree_.vtxs_z -> push_back( vtx.z() );
    outTree_.vtxs_t -> push_back( -99 );
    outTree_.vtxs_normalizedChi2 -> push_back( vtx.normalizedChi2() );
    
    float sumPt = 0.;
    float sumPt2 = 0.;
    for(auto it = vtx.tracks_begin(); it != vtx.tracks_end(); ++it)
    {
      sumPt += (*it) -> pt();
      sumPt2 += (*it)->pt() * (*it)->pt();
    }
    outTree_.vtxs_sumPt  -> push_back( sumPt );
    outTree_.vtxs_sumPt2 -> push_back( sumPt2 );
  }
  
  
  //---fill track information
  auto tracks = *tracksHandle_.product();
  outTree_.tracks_n = tracks.size();
  for(auto &track : *tracksHandle_)
  {
    outTree_.tracks_pt     -> push_back( track.pt() );
    outTree_.tracks_eta    -> push_back( track.eta() );
    outTree_.tracks_phi    -> push_back( track.phi() );
    outTree_.tracks_energy -> push_back( track.p() );
    outTree_.tracks_charge -> push_back( track.charge() );
    outTree_.tracks_dxy    -> push_back( track.dxy((*vtxsHandle_)[0].position()) );
    outTree_.tracks_dsz    -> push_back( track.dsz((*vtxsHandle_)[0].position()) );
    outTree_.tracks_dz     -> push_back( track.dz((*vtxsHandle_)[0].position()) );
    outTree_.tracks_normalizedChi2 -> push_back( track.normalizedChi2() );
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
    outTree_.muons_isLoose  -> push_back( muon::isLooseMuon(muon) );
    outTree_.muons_isMedium -> push_back( muon::isMediumMuon(muon) );
    outTree_.muons_isTight  -> push_back( muon::isTightMuon(muon,(*vtxsHandle_)[0]) );
    outTree_.muons_trackIso -> push_back( muon.isolationR03().sumPt );
    outTree_.muons_ecalIso  -> push_back( muon.isolationR03().emEt );
    outTree_.muons_hcalIso  -> push_back( muon.isolationR03().hadEt );
    outTree_.muons_pfIsoChargedHadron   -> push_back( muon.pfIsolationR03().sumChargedHadronPt );
    outTree_.muons_pfIsoChargedParticle -> push_back( muon.pfIsolationR03().sumChargedParticlePt );
    outTree_.muons_pfIsoNeutralHadron   -> push_back( muon.pfIsolationR03().sumNeutralHadronEt );
    outTree_.muons_pfIsoPhoton          -> push_back( muon.pfIsolationR03().sumPhotonEt );
    outTree_.muons_pfIsoPU              -> push_back( muon.pfIsolationR03().sumPUPt );
  }
  
  
  outTree_.GetTTreePtr()->Fill();
  ++entry_;
}
