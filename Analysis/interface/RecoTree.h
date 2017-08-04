#ifndef _RECO__TREE
#define _RECO__TREE

#include "ExternalTools/DynamicTTree/interface/DynamicTTreeBase.h"



//---Define the TTree branches
#define DYNAMIC_TREE_NAME RecoTree

#define DATA_TABLE \
  DATA(int, entry) \
  DATA(int, event) \
  DATA(int, lumi) \
  DATA(int, run) \
  DATA(int, trgs_n) \
  DATA(int, vtxs_n) \
  DATA(int, pfCandidates_n) \
  DATA(int, muons_n) \
  DATA(int, taus_n) \
  DATA(int, jets_n)

#define DATA_CLASS_TABLE \
  DATA(std::vector<std::string>, trgs_name) \
  DATA(std::vector<int>, trgs_pass) \
  DATA(std::vector<int>, trgs_prescale) \
  DATA(std::vector<float>, vtxs_x) \
  DATA(std::vector<float>, vtxs_y) \
  DATA(std::vector<float>, vtxs_z) \
  DATA(std::vector<float>, vtxs_t) \
  DATA(std::vector<float>, vtxs_normalizedChi2) \
  DATA(std::vector<float>, vtxs_sumPt) \
  DATA(std::vector<float>, vtxs_sumPt2) \
  DATA(std::vector<float>, pfCandidates_pt) \
  DATA(std::vector<float>, pfCandidates_eta) \
  DATA(std::vector<float>, pfCandidates_phi) \
  DATA(std::vector<float>, pfCandidates_energy) \
  DATA(std::vector<int>,   pfCandidates_charge) \
  DATA(std::vector<int>,   pfCandidates_pdgId) \
  DATA(std::vector<float>, pfCandidates_vx) \
  DATA(std::vector<float>, pfCandidates_vy) \
  DATA(std::vector<float>, pfCandidates_vz) \
  DATA(std::vector<float>, pfCandidates_dxy) \
  DATA(std::vector<float>, pfCandidates_dz) \
  DATA(std::vector<int>,   pfCandidates_fromPV) \
  DATA(std::vector<int>,   pfCandidates_pvAssociationQuality) \
  DATA(std::vector<int>,   pfCandidates_isHighPurity) \
  DATA(std::vector<float>, muons_pt) \
  DATA(std::vector<float>, muons_eta) \
  DATA(std::vector<float>, muons_phi) \
  DATA(std::vector<float>, muons_energy) \
  DATA(std::vector<int>,   muons_charge) \
  DATA(std::vector<float>, muons_isLoose) \
  DATA(std::vector<float>, muons_isMedium) \
  DATA(std::vector<float>, muons_isTight) \
  DATA(std::vector<float>, muons_trackIso) \
  DATA(std::vector<float>, muons_ecalIso) \
  DATA(std::vector<float>, muons_hcalIso) \
  DATA(std::vector<float>, muons_pfIsoChargedHadron) \
  DATA(std::vector<float>, muons_pfIsoChargedParticle) \
  DATA(std::vector<float>, muons_pfIsoNeutralHadron) \
  DATA(std::vector<float>, muons_pfIsoPhoton) \
  DATA(std::vector<float>, muons_pfIsoPU) \
  DATA(std::vector<float>, taus_pt) \
  DATA(std::vector<float>, taus_eta) \
  DATA(std::vector<float>, taus_phi) \
  DATA(std::vector<float>, taus_energy) \
  DATA(std::vector<int>,   taus_charge) \
  DATA(std::vector<int>,   taus_numberOfDaughters) \
  DATA(std::vector<float>, jets_pt) \
  DATA(std::vector<float>, jets_eta) \
  DATA(std::vector<float>, jets_phi) \
  DATA(std::vector<float>, jets_energy) \
  DATA(std::vector<int>,   jets_charge) \
  DATA(std::vector<int>,   jets_numberOfDaughters) 
  
#include "ExternalTools/DynamicTTree/interface/DynamicTTreeInterface.h"

#endif
