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
  DATA(int, vtxs_n) \
  DATA(int, tracks_n) \
  DATA(int, muons_n)

#define DATA_CLASS_TABLE \
  DATA(std::vector<float>, vtxs_x) \
  DATA(std::vector<float>, vtxs_y) \
  DATA(std::vector<float>, vtxs_z) \
  DATA(std::vector<float>, vtxs_t) \
  DATA(std::vector<float>, vtxs_normalizedChi2) \
  DATA(std::vector<float>, vtxs_sumPt) \
  DATA(std::vector<float>, vtxs_sumPt2) \
  DATA(std::vector<float>, tracks_pt) \
  DATA(std::vector<float>, tracks_eta) \
  DATA(std::vector<float>, tracks_phi) \
  DATA(std::vector<float>, tracks_energy) \
  DATA(std::vector<int>,   tracks_charge) \
  DATA(std::vector<float>, tracks_dxy) \
  DATA(std::vector<float>, tracks_dsz) \
  DATA(std::vector<float>, tracks_dz) \
  DATA(std::vector<float>, tracks_normalizedChi2) \
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
  DATA(std::vector<float>, muons_pfIsoPU)

#include "ExternalTools/DynamicTTree/interface/DynamicTTreeInterface.h"

#endif
