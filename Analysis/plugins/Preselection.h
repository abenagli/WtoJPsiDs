#ifndef _PRESELECTION_
#define _PRESELECTION_

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/Provenance.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "TLorentzVector.h"



class Preselection : public edm::EDFilter
{
public:
  explicit Preselection(const edm::ParameterSet& pSet);
  ~Preselection() {};
  
  //---utils
  
  //---methods
  virtual void beginJob() override {};
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob() override {};
  
  
private:
  int entry_;
  
  //---inputs
  edm::EDGetTokenT<reco::VertexCollection> vtxsToken_;
  edm::Handle<reco::VertexCollection>     vtxsHandle_;
  edm::EDGetTokenT<pat::MuonCollection>   muonsToken_;
  edm::Handle<pat::MuonCollection>       muonsHandle_;
  
  //---options
};

//define this as a plug-in
DEFINE_FWK_MODULE(Preselection);

#endif
