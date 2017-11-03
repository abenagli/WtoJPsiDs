#ifndef _DUMP_GEN_PARTICLES_
#define _DUMP_GEN_PARTICLES_

#include "WtoJPsiDs/Analysis/interface/ParticleNames.h"
#include "WtoJPsiDs/Analysis/interface/GenTree.h"

#include <iostream>

#include "TLorentzVector.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"



class DumpGenParticles : public edm::EDAnalyzer
{
public:
  explicit DumpGenParticles(const edm::ParameterSet&);
  ~DumpGenParticles();
  
private:
  
  //---methods
  virtual void beginJob() override {};
  virtual void analyze(edm::Event const&, edm::EventSetup const&) override;
  virtual void endJob() override {};
  
  const reco::GenParticle* IsDecayed(const reco::GenParticle*);
  void GetFinalStateDaughters(const reco::GenParticle* particle, std::vector<const reco::GenParticle*>& daughters);
    
  //---inputs
  edm::Handle<reco::GenParticleCollection>     genParticlesHandle_;
  edm::EDGetTokenT<reco::GenParticleCollection> genParticlesToken_;
  edm::Handle<edm::View<reco::GenJet> >             genJetsHandle_;
  edm::EDGetTokenT<edm::View<reco::GenJet> >         genJetsToken_;
  bool verbosity_;
  
  //---outputs
  edm::Service<TFileService> fs_;
  GenTree outTree_;
  
  int entry_;
  std::vector<const reco::GenParticle*> resonances_;
  std::map<const reco::GenParticle*,std::vector<const reco::GenParticle*> > resonanceDaughters_;
  std::map<const reco::GenParticle*,std::map<const reco::GenParticle*, std::vector<const reco::GenParticle*> > > resonanceDaughters2_;
};

std::ostream& operator<<(std::ostream& os,const reco::GenParticle* particle);

#endif
