#ifndef _DUMP_PU_
#define _DUMP_PU_

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

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"



class DumpPU : public edm::EDAnalyzer
{
public:
  explicit DumpPU(const edm::ParameterSet& pSet);
  ~DumpPU() {};
  
  //---utils
  
  //---methods
  virtual void beginJob() override {};
  virtual void analyze(edm::Event const&, edm::EventSetup const&) override;
  virtual void endJob() override {};
  
  
private:
  //---inputs
  edm::EDGetTokenT<std::vector<PileupSummaryInfo> > puInfoToken_;
  edm::Handle<std::vector<PileupSummaryInfo> >     puInfoHandle_;
  
  //---options
  
  //---workers
  
  //---outputs
  edm::Service<TFileService> fs_;
  TH1F* histo_;
  
  int entry_;
};

//define this as a plug-in
DEFINE_FWK_MODULE(DumpPU);

#endif
