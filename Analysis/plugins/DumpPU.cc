#include "WtoJPsiDs/Analysis/plugins/DumpPU.h"



DumpPU::DumpPU(const edm::ParameterSet& pSet) :
  puInfoToken_(consumes<std::vector<PileupSummaryInfo> >(pSet.getUntrackedParameter<edm::InputTag>("puInfoTag")))
{
  //---TFileService for output ntuples
  if( !fs_ )
  {
    throw edm::Exception(edm::errors::Configuration, "TFile Service is not registered in cfg file");
  }
  
  entry_ = 0;
  
  histo_ = fs_ -> make<TH1F>("pileup","",100,-0.5,99.5);
}



// ------------ method called for each event  ------------
void DumpPU::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  //---get input collections
  iEvent.getByToken(puInfoToken_, puInfoHandle_);
  
  auto puInfo = *puInfoHandle_.product();
  for(std::vector<PileupSummaryInfo>::const_iterator PVIt = puInfo.begin(); PVIt != puInfo.end(); ++PVIt)
  {
    int BX = PVIt -> getBunchCrossing();
    
    if( BX == 0 )
    { 
      histo_ ->Fill( PVIt -> getTrueNumInteractions() );
      continue;
    }
  }
  
  ++entry_;
}
