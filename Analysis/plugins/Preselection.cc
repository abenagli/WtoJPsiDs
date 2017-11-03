#include "WtoJPsiDs/Analysis/plugins/Preselection.h"



Preselection::Preselection(const edm::ParameterSet& pSet) :
  vtxsToken_ ( consumes<reco::VertexCollection>(pSet.getUntrackedParameter<edm::InputTag>("vtxTag")) ),
  muonsToken_( consumes<pat::MuonCollection>   (pSet.getUntrackedParameter<edm::InputTag>("muonsTag")) )
{}



// ------------ method called for each event  ------------
bool Preselection::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  //---get input collections
  iEvent.getByToken(vtxsToken_,   vtxsHandle_);
  iEvent.getByToken(muonsToken_, muonsHandle_);
  auto vtxs = *vtxsHandle_.product();
  auto muons = *muonsHandle_.product();
  
  
  //---muon information
  if( muons.size() < 2 ) return false;
  
  int nGoodCombs = 0;
  for(unsigned int it1 = 0; it1 < muons.size(); ++it1)
  {
    auto muon1 = muons.at(it1);
    
    int charge1 = muon1.charge();
    int isMedium1 = muon1.isMediumMuon();
    float dxy1 = muon1.muonBestTrack() -> dxy( (*vtxsHandle_)[0].position() );
    float dxyErr1 = muon1.muonBestTrack() -> dxyError();
    float dz1 = muon1.muonBestTrack() -> dz( (*vtxsHandle_)[0].position() );
    float dzErr1 = muon1.muonBestTrack() -> dzError();
    float iso1 = muon1.pfIsolationR03().sumChargedHadronPt + std::max(0.,muon1.pfIsolationR03().sumNeutralHadronEt+muon1.pfIsolationR03().sumPhotonEt-0.5*muon1.pfIsolationR03().sumPUPt);
    
    if( isMedium1 != 1 ) continue;
    if( fabs(dxy1/dxyErr1) > 5. ) continue;
    if( fabs(dz1/dzErr1) > 5. ) continue;
    if( iso1/muon1.pt() > 0.25 ) continue;
    
    for(unsigned int it2 = it1+1; it2 < muons.size(); ++it2)
    {
      auto muon2 = muons.at(it2);
      
      int charge2 = muon2.charge();
      int isMedium2 = muon2.isMediumMuon();
      float dxy2 = muon2.muonBestTrack() -> dxy( (*vtxsHandle_)[0].position() );
      float dxyErr2 = muon2.muonBestTrack() -> dxyError();
      float dz2 = muon2.muonBestTrack() -> dz( (*vtxsHandle_)[0].position() );
      float dzErr2 = muon2.muonBestTrack() -> dzError();
      float iso2 = muon2.pfIsolationR03().sumChargedHadronPt + std::max(0.,muon2.pfIsolationR03().sumNeutralHadronEt+muon2.pfIsolationR03().sumPhotonEt-0.5*muon2.pfIsolationR03().sumPUPt);
      
      if( charge1*charge2 == 1 ) continue;
      if( isMedium2 != 1 ) continue;
      if( fabs(dxy2/dxyErr2) > 5. ) continue;
      if( fabs(dz2/dzErr2) > 5. ) continue;
      if( iso2/muon2.pt() > 0.25 ) continue;
      if( fabs(muon1.eta()-muon2.eta()) > 0.5 ) continue;
      
      TLorentzVector mu1;
      mu1.SetPtEtaPhiM(muon1.pt(),muon1.eta(),muon1.phi(),muon1.mass());
      TLorentzVector mu2;
      mu2.SetPtEtaPhiM(muon2.pt(),muon2.eta(),muon2.phi(),muon2.mass());
      
      if( (mu1+mu2).M() < 2. ) continue;
      if( (mu1+mu2).M() > 5. ) continue;
      
      ++nGoodCombs;
    }
  }
  
  return bool(nGoodCombs);
}
