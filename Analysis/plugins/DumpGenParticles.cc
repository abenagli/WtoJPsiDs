#include "WtoJPsiDs/Analysis/plugins/DumpGenParticles.h"



DumpGenParticles::DumpGenParticles(const edm::ParameterSet& pSet):
  genParticlesToken_(consumes<reco::GenParticleCollection>(pSet.getUntrackedParameter<edm::InputTag>("genParticlesTag"))),
  genJetsToken_     (consumes<edm::View<reco::GenJet> >   (pSet.getUntrackedParameter<edm::InputTag>("genJetsTag"))),
  verbosity_(pSet.getParameter<bool>("verbosity"))
{
  //---TFileService for output ntuples
  if( !fs_ )
  {
    throw edm::Exception(edm::errors::Configuration, "TFile Service is not registered in cfg file");
  }

  outTree_ = GenTree(pSet.getUntrackedParameter<std::string>("treeName").c_str(),"Gen tree for W > J/Psi D_s studies");
  entry_ = 0;
}


DumpGenParticles::~DumpGenParticles()
{}



void DumpGenParticles::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  //---reset containers
  resonances_.clear();
  resonanceDaughters_.clear();
  resonanceDaughters2_.clear();
  
  
  //---reset output
  outTree_.Reset();
  outTree_.entry = entry_;
  outTree_.event = iEvent.id().event();
  outTree_.lumi = iEvent.id().luminosityBlock();
  outTree_.run = iEvent.id().run();
  
  
  //---load gen particles
  iEvent.getByToken(genParticlesToken_,genParticlesHandle_);
  auto genParticles = *genParticlesHandle_.product();
  
  for(size_t i = 0; i < genParticles.size(); ++i)
  {
    auto genParticle = genParticles[i];
    
    // std::cout << &genParticle << std::endl;
    
    // save resonance
    if ( ( abs(genParticle.pdgId()) == 23 ||
           abs(genParticle.pdgId()) == 24 ||
           abs(genParticle.pdgId()) == 25 ||
           abs(genParticle.pdgId()) == 39 ||
           abs(genParticle.pdgId()) == 41 ||
           abs(genParticle.pdgId()) == 42 ) &&
         ( genParticle.status() == 22 || 
           genParticle.status() == 23 ) )
    {
      const reco::GenParticle* resonance = IsDecayed(&genParticle);
      resonances_.push_back( resonance );
      
      outTree_.reso_pt     -> push_back( resonance->pt() );
      outTree_.reso_eta    -> push_back( resonance->eta() );
      outTree_.reso_phi    -> push_back( resonance->phi() );
      outTree_.reso_energy -> push_back( resonance->energy() );
      outTree_.reso_mass   -> push_back( resonance->mass() );
      outTree_.reso_charge -> push_back( resonance->charge() );
      outTree_.reso_pdgId  -> push_back( resonance->pdgId() );
      outTree_.reso_name   -> push_back( GetParticleName(resonance->pdgId()) );
      
      std::vector<float> dau1_pt;
      std::vector<float> dau1_eta;
      std::vector<float> dau1_phi;
      std::vector<float> dau1_energy;
      std::vector<float> dau1_mass;
      std::vector<int> dau1_charge;
      std::vector<int> dau1_pdgId;
      std::vector<std::string> dau1_name;
      
      std::vector<int> dau2_n;
      std::vector<std::vector<float> > dau2_pt;
      std::vector<std::vector<float> > dau2_eta;
      std::vector<std::vector<float> > dau2_phi;
      std::vector<std::vector<float> > dau2_energy;
      std::vector<std::vector<float> > dau2_mass;
      std::vector<std::vector<int> > dau2_charge;
      std::vector<std::vector<int> > dau2_pdgId;
      std::vector<std::vector<std::string> > dau2_name;
      
      for(size_t ii = 0; ii < resonance->numberOfDaughters(); ++ii)
      {
        const reco::GenParticle* daughter = (const reco::GenParticle*)(resonance -> daughter(ii));
        resonanceDaughters_[resonance].push_back( daughter );
        
        dau1_pt.push_back( daughter->pt() );
        dau1_eta.push_back( daughter->eta() );
        dau1_phi.push_back( daughter->phi() );
        dau1_energy.push_back( daughter->energy() );
        dau1_mass.push_back( daughter->mass() );
        dau1_charge.push_back( daughter->charge() );
        dau1_pdgId.push_back( daughter->pdgId() );
        dau1_name.push_back( GetParticleName(daughter->pdgId()) );
        
        std::vector<float> temp_pt;
        std::vector<float> temp_eta;
        std::vector<float> temp_phi;
        std::vector<float> temp_energy;
        std::vector<float> temp_mass;
        std::vector<int> temp_charge;
        std::vector<int> temp_pdgId;
        std::vector<std::string> temp_name;
        
        for(size_t jj = 0; jj < daughter->numberOfDaughters(); ++jj)
        {
          const reco::GenParticle* daughter2 = (const reco::GenParticle*)(daughter -> daughter(jj));
          
          std::vector<const reco::GenParticle*> finalStateDaughters;
          GetFinalStateDaughters(daughter2,finalStateDaughters);
          
          for(size_t zz = 0; zz < finalStateDaughters.size(); ++zz)
          {
            resonanceDaughters2_[resonance][daughter].push_back( finalStateDaughters.at(zz) );
            
            temp_pt.push_back( finalStateDaughters.at(zz)->pt() );
            temp_eta.push_back( finalStateDaughters.at(zz)->eta() );
            temp_phi.push_back( finalStateDaughters.at(zz)->phi() );
            temp_energy.push_back( finalStateDaughters.at(zz)->energy() );
            temp_mass.push_back( finalStateDaughters.at(zz)->mass() );
            temp_charge.push_back( finalStateDaughters.at(zz)->charge() );
            temp_pdgId.push_back( finalStateDaughters.at(zz)->pdgId() );
            temp_name.push_back( GetParticleName(finalStateDaughters.at(zz)->pdgId()) );
          }
        }
        
        dau2_n.push_back( temp_pt.size() );
        dau2_pt.push_back( temp_pt );
        dau2_eta.push_back( temp_eta );
        dau2_phi.push_back( temp_phi );
        dau2_energy.push_back( temp_energy );
        dau2_mass.push_back( temp_mass );
        dau2_charge.push_back( temp_charge );
        dau2_pdgId.push_back( temp_pdgId );
        dau2_name.push_back( temp_name );
      }
      
      outTree_.resoDau1_n      -> push_back( resonance->numberOfDaughters() );
      outTree_.resoDau1_pt     -> push_back( dau1_pt );
      outTree_.resoDau1_eta    -> push_back( dau1_eta );
      outTree_.resoDau1_phi    -> push_back( dau1_phi );
      outTree_.resoDau1_energy -> push_back( dau1_energy );
      outTree_.resoDau1_mass   -> push_back( dau1_mass );
      outTree_.resoDau1_charge -> push_back( dau1_charge );
      outTree_.resoDau1_pdgId  -> push_back( dau1_pdgId );
      outTree_.resoDau1_name   -> push_back( dau1_name );
      
      outTree_.resoDau2_n      -> push_back( dau2_n );
      outTree_.resoDau2_pt     -> push_back( dau2_pt );
      outTree_.resoDau2_eta    -> push_back( dau2_eta );
      outTree_.resoDau2_phi    -> push_back( dau2_phi );
      outTree_.resoDau2_energy -> push_back( dau2_energy );
      outTree_.resoDau2_mass   -> push_back( dau2_mass );
      outTree_.resoDau2_charge -> push_back( dau2_charge );
      outTree_.resoDau2_pdgId  -> push_back( dau2_pdgId );
      outTree_.resoDau2_name   -> push_back( dau2_name );
    }
    
    outTree_.reso_n = resonances_.size();
  }
  
  
  if( verbosity_ )
  {
    std::cout << "--------------------------" << std::endl;
 
    std::cout << ">>> RESONANCES" << std::endl;
    for(unsigned int ii = 0; ii < resonances_.size(); ++ii)
    {
      const reco::GenParticle* resonance = resonances_.at(ii);
      std::cout << resonance << std::endl;
      
      for(unsigned int jj = 0; jj < resonanceDaughters_[resonance].size(); ++jj)
      {
        const reco::GenParticle* daughter = (const reco::GenParticle*)(resonanceDaughters_[resonance].at(jj));
        std::cout << ">>>" << daughter << std::endl;
        
        TLorentzVector daughter2Sum;
        for(unsigned int zz = 0; zz < (resonanceDaughters2_[resonance])[daughter].size(); ++zz)
        {
          const reco::GenParticle* daughter2 = (const reco::GenParticle*)((resonanceDaughters2_[resonance])[daughter].at(zz));
          std::cout << ">>>>>>" << daughter2 << std::endl;
          
          TLorentzVector temp;
          temp.SetPtEtaPhiE(daughter2->pt(),daughter2->eta(),daughter2->phi(),daughter2->energy());
          daughter2Sum += temp;
        }
        std::cout << ">>>>>> mass of all decay products: " << daughter2Sum.M() << std::endl;
      }
    }
    std::cout << "<<< RESONANCES" << std::endl;
    
    std::cout << "--------------------------" << std::endl;
  }
  
  
  //---load gen jets
  iEvent.getByToken(genJetsToken_,genJetsHandle_);
  auto genJets = *genJetsHandle_.product();

  outTree_.genJets_n = genJets.size();  
  for(size_t i = 0; i < genJets.size(); ++i)
  {
    auto genJet = genJets[i];
    
    outTree_.genJets_pt       -> push_back( genJet.pt() );
    outTree_.genJets_eta      -> push_back( genJet.eta() );
    outTree_.genJets_phi      -> push_back( genJet.phi() );
    outTree_.genJets_energy   -> push_back( genJet.energy() );
    outTree_.genJets_numberOfDaughters -> push_back( genJet.numberOfDaughters() );
  }
  
  
  outTree_.GetTTreePtr()->Fill();
  ++entry_;
}



const reco::GenParticle* DumpGenParticles::IsDecayed(const reco::GenParticle* particle)
{
  for(size_t i = 0; i< particle->numberOfDaughters(); ++i)
  {
    if( particle->daughter(i)->pdgId() == particle->pdgId() )
      return IsDecayed((reco::GenParticle*)particle->daughter(i));
  }
  
  return particle;
}



void DumpGenParticles::GetFinalStateDaughters(const reco::GenParticle* particle, std::vector<const reco::GenParticle*>& daughters)
{
  if( particle->status() == 1 )
  {
    daughters.push_back( particle );
    return;
  }
  
  else
  {
    for(size_t i = 0; i< particle->numberOfDaughters(); ++i)
    {    
      GetFinalStateDaughters( (const reco::GenParticle*)(particle->daughter(i)),daughters );
    }
  }
  
  return;
}



std::ostream& operator<<(std::ostream& os, const reco::GenParticle* particle)
{
  os << ">>> pdgId: "      << std::fixed << std::setw(8) << particle->pdgId() << " ( " << std::fixed << std::setw(12) << GetParticleName(particle->pdgId()) << " )"
     << "        status: " << std::fixed << std::setw(2) << particle->status()
     << "        pT: "     << std::fixed << std::setprecision(3) << std::setw(6) << particle->pt()
     << "        eta: "    << std::fixed << std::setprecision(3) << std::setw(10) << particle->eta()
     << "        mass: "   << std::fixed << std::setprecision(3) << std::setw(6) << particle->mass();
  
  return os;
}

//define this as a plug-in
DEFINE_FWK_MODULE(DumpGenParticles);
