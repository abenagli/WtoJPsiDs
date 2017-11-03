#include "WtoJPsiDs/Analysis/plugins/DumpPU.h"



DumpPU::DumpPU(const edm::ParameterSet& pSet) :
  puInfoToken_(consumes<std::vector<PileupSummaryInfo> >(pSet.getUntrackedParameter<edm::InputTag>("puInfoTag")))
{
  //---TFileService for output ntuples
  if( !fs_ )
  {
    throw edm::Exception(edm::errors::Configuration, "TFile Service is not registered in cfg file");
  }
  
  outTree_ = PUTree(pSet.getUntrackedParameter<std::string>("treeName").c_str(),"PU tree for W > J/Psi D_s studies");
  entry_ = 0;
  
  histo_ = fs_ -> make<TH1F>("pileup","",100,-0.5,99.5);
}



// ------------ method called for each event  ------------
void DumpPU::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  //---reset output
  outTree_.Reset();
  outTree_.entry = entry_;
  outTree_.event = iEvent.id().event();
  outTree_.lumi = iEvent.id().luminosityBlock();
  outTree_.run = iEvent.id().run();
  
  
  //---get input collections
  iEvent.getByToken(puInfoToken_, puInfoHandle_);
  
  auto puInfo = *puInfoHandle_.product();
  for(std::vector<PileupSummaryInfo>::const_iterator PVIt = puInfo.begin(); PVIt != puInfo.end(); ++PVIt)
  {
    int BX = PVIt -> getBunchCrossing();
    
    if( BX == 0 )
    { 
      outTree_.trueNumInteractions = PVIt -> getTrueNumInteractions();
      histo_ ->Fill( PVIt -> getTrueNumInteractions() );
      continue;
    }
  }
  
  outTree_.GetTTreePtr()->Fill();
  ++entry_;
}
