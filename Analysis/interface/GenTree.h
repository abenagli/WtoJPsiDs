#ifndef _GEN__TREE
#define _GEN__TREE

#include "ExternalTools/DynamicTTree/interface/DynamicTTreeBase.h"



//---Define the TTree branches
#define DYNAMIC_TREE_NAME GenTree

#define DATA_TABLE \
  DATA(int, entry) \
  DATA(int, event) \
  DATA(int, lumi) \
  DATA(int, run) \
  DATA(int, reso_n) \
  DATA(int, genJets_n) \
  DATA(int, trueNumInteractions) \
  
#define DATA_CLASS_TABLE \
  DATA(std::vector<float>, reso_pt)  \
  DATA(std::vector<float>, reso_eta) \
  DATA(std::vector<float>, reso_phi) \
  DATA(std::vector<float>, reso_energy) \
  DATA(std::vector<float>, reso_mass) \
  DATA(std::vector<int>,   reso_charge) \
  DATA(std::vector<int>,   reso_pdgId) \
  DATA(std::vector<std::string>, reso_name) \
  DATA(std::vector<int>, resoDau1_n) \
  DATA(std::vector<std::vector<float> >, resoDau1_pt) \
  DATA(std::vector<std::vector<float> >, resoDau1_eta) \
  DATA(std::vector<std::vector<float> >, resoDau1_phi) \
  DATA(std::vector<std::vector<float> >, resoDau1_energy) \
  DATA(std::vector<std::vector<float> >, resoDau1_mass) \
  DATA(std::vector<std::vector<int> >,   resoDau1_charge) \
  DATA(std::vector<std::vector<int> >,   resoDau1_pdgId) \
  DATA(std::vector<std::vector<std::string> >,   resoDau1_name) \
  DATA(std::vector<std::vector<int> >, resoDau2_n) \
  DATA(std::vector<std::vector<std::vector<float> > >, resoDau2_pt) \
  DATA(std::vector<std::vector<std::vector<float> > >, resoDau2_eta) \
  DATA(std::vector<std::vector<std::vector<float> > >, resoDau2_phi) \
  DATA(std::vector<std::vector<std::vector<float> > >, resoDau2_energy) \
  DATA(std::vector<std::vector<std::vector<float> > >, resoDau2_mass) \
  DATA(std::vector<std::vector<std::vector<int> > >,   resoDau2_charge) \
  DATA(std::vector<std::vector<std::vector<int> > >,   resoDau2_pdgId) \
  DATA(std::vector<std::vector<std::vector<std::string> > >,   resoDau2_name) \
  DATA(std::vector<float>, genJets_pt) \
  DATA(std::vector<float>, genJets_eta) \
  DATA(std::vector<float>, genJets_phi) \
  DATA(std::vector<float>, genJets_energy) \
  DATA(std::vector<int>,   genJets_charge) \
  DATA(std::vector<int>,   genJets_numberOfDaughters)
  
#include "ExternalTools/DynamicTTree/interface/DynamicTTreeInterface.h"

#endif
