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
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"



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
  edm::EDGetTokenT<edm::TriggerResults>                      trgsToken_;
  edm::Handle<edm::TriggerResults>                          trgsHandle_;
  edm::EDGetTokenT<pat::PackedTriggerPrescales>      trgPrescalesToken_;
  edm::Handle<pat::PackedTriggerPrescales>          trgPrescalesHandle_;
  edm::EDGetTokenT<reco::VertexCollection>                   vtxsToken_;
  edm::Handle<reco::VertexCollection>                       vtxsHandle_;    
  edm::EDGetTokenT<edm::View<pat::PackedCandidate> > pfCandidatesToken_;
  edm::Handle<edm::View<pat::PackedCandidate> >     pfCandidatesHandle_; 
  edm::EDGetTokenT<pat::MuonCollection>                     muonsToken_;
  edm::Handle<pat::MuonCollection>                         muonsHandle_;
  edm::Handle<pat::TauCollection>                           tausHandle_;
  edm::EDGetTokenT<pat::TauCollection>                       tausToken_;
  edm::Handle<pat::JetCollection>                           jetsHandle_;
  edm::EDGetTokenT<pat::JetCollection>                       jetsToken_;
  edm::Handle<pat::JetCollection>                      jetsPuppiHandle_;
  edm::EDGetTokenT<pat::JetCollection>                  jetsPuppiToken_;
  edm::Handle<pat::METCollection>                           metsHandle_;
  edm::EDGetTokenT<pat::METCollection>                       metsToken_;
  edm::Handle<pat::METCollection>                      metsPuppiHandle_;
  edm::EDGetTokenT<pat::METCollection>                  metsPuppiToken_;
  
  std::vector<std::string> bDiscriminators_;
  
  //---options
  
  //---workers
  
  //---outputs
  edm::Service<TFileService> fs_;
  RecoTree outTree_;
};

//define this as a plug-in
DEFINE_FWK_MODULE(DumpReco);

#endif
