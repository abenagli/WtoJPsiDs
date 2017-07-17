#ifndef _DUMP_RECO_
#define _DUMP_RECO_

#include "WtoJPsiDs/Analysis/interface/RecoTree.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/Provenance.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Common/interface/RefToBase.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"



class DumpReco : public edm::EDAnalyzer
{
public:
  explicit DumpReco(const edm::ParameterSet& pSet);
  ~DumpReco() {};
  
  //---utils
  
  //---methods
  virtual void beginJob() override {};
  virtual void analyze(edm::Event const&, edm::EventSetup const&) override;
  virtual void endJob() override {};
  
  
private:
  int entry_;
  
  //---inputs
  edm::EDGetTokenT<reco::VertexCollection>    vtxsToken_;
  edm::Handle<reco::VertexCollection>        vtxsHandle_;    
  edm::EDGetTokenT<edm::View<reco::Track> > tracksToken_;
  edm::Handle<edm::View<reco::Track> >     tracksHandle_; 
  edm::EDGetTokenT<reco::MuonCollection>     muonsToken_;
  edm::Handle<reco::MuonCollection>         muonsHandle_;    
  
  //---options
  
  //---workers
  
  //---outputs
  edm::Service<TFileService> fs_;
  RecoTree outTree_;
};

//define this as a plug-in
DEFINE_FWK_MODULE(DumpReco);

#endif
