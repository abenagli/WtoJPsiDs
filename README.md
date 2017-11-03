# Exclusive W decays Analysis
Code to produce ntuples for the analysis of exclusive W decays

## Setup
   ```
   cmsrel CMSSW_8_0_25
   cd CMSSW_8_0_25/src
   cmsenv
   git cms-init
   git clone -b CMSSW git@github.com:abenagli/DynamicTTree.git ExternalTools/DynamicTTree/
   git clone git@github.com:abenagli/WExclAnalysis.git
   scram b -j 8
   ```
