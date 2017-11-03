#ifndef _PU_TREE
#define _PU_TREE

#include "ExternalTools/DynamicTTree/interface/DynamicTTreeBase.h"



//---Define the TTree branches
#define DYNAMIC_TREE_NAME PUTree

#define DATA_TABLE \
  DATA(int, entry) \
  DATA(int, event) \
  DATA(int, lumi) \
  DATA(int, run) \
  DATA(int, trueNumInteractions)
  
#include "ExternalTools/DynamicTTree/interface/DynamicTTreeInterface.h"

#endif
