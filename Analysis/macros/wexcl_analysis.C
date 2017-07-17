void wexcl_analysis(const std::string& inFileName)
{
  //--- open files and get trees
  TFile* inFile = TFile::Open(inFileName.c_str());
  
  TTree* genTree = (TTree*)( inFile->Get("DumpGenParticles/gen_tree") );
  int nEntries_genTree = genTree -> GetEntries();
  std::cout << "Read " << nEntries_genTree << " in tree " << genTree->GetName() << std::endl;
  
  TTree* recoTree = (TTree*)( inFile->Get("DumpReco/reco_tree") );
  int nEntries_recoTree = recoTree -> GetEntries();
  std::cout << "Read " << nEntries_recoTree << " in tree " << recoTree->GetName() << std::endl;
  
  
  //--- set tree branch addresses
  std::vector<float>* reso_pt = new std::vector<float>;
  std::vector<float>* reso_eta = new std::vector<float>;
  std::vector<float>* reso_mass = new std::vector<float>;
  
  genTree -> SetBranchAddress("reso_pt",&reso_pt);
  genTree -> SetBranchAddress("reso_eta",&reso_eta);
  genTree -> SetBranchAddress("reso_mass",&reso_mass);
  
  int muons_n;
  std::vector<float>* muons_pt = new std::vector<float>;
  std::vector<float>* muons_eta = new std::vector<float>;
  std::vector<float>* muons_phi = new std::vector<float>;
  std::vector<float>* muons_energy = new std::vector<float>;
  
  recoTree -> SetBranchAddress("muons_n",&muons_n);
  recoTree -> SetBranchAddress("muons_pt",&muons_pt);
  recoTree -> SetBranchAddress("muons_eta",&muons_eta);
  recoTree -> SetBranchAddress("muons_phi",&muons_phi);
  recoTree -> SetBranchAddress("muons_energy",&muons_energy);
  
  
  //--- define histograms
  TH1F* h_genW_pt = new TH1F("h_genW_pt","",100,0.,200.);
  TH1F* h_genW_eta = new TH1F("h_genW_eta","",100,-10.,10.);
  TH1F* h_genW_mass = new TH1F("h_genW_mass","",100,50.,150.);
  
  TH1F* h_recoJPsi_mass = new TH1F("h_recoJPsi_mass","",100,0.,10);
  
  
  //--- loop over the events
  for(int entry = 0; entry < genTree->GetEntries(); ++entry)
  {
    if( entry%100 == 0 ) std::cout << ">>> loop 1/1: reading entry " << entry << " / " << nEntries_genTree << "\r" << std::flush;
    genTree -> GetEntry(entry);
    recoTree -> GetEntry(entry);
    
    h_genW_pt -> Fill( reso_pt->at(0) );
    h_genW_eta -> Fill( reso_eta->at(0) );
    h_genW_mass -> Fill( reso_mass->at(0) );
    
    if( muons_n != 2 ) continue;
    
    TLorentzVector muon1, muon2;
    muon1.SetPtEtaPhiE(muons_pt->at(0),muons_eta->at(0),muons_phi->at(0),muons_energy->at(0));
    muon2.SetPtEtaPhiE(muons_pt->at(1),muons_eta->at(1),muons_phi->at(1),muons_energy->at(1));
    
    h_recoJPsi_mass -> Fill( (muon1+muon2).M() );
  }
  std::cout << std::endl;
  
  
  TCanvas* c1 = new TCanvas("c1","genW",1500,500);
  c1 -> Divide(3,1);
  c1 -> cd(1);
  h_genW_pt -> SetTitle(";p_{T}^{gen. W} [GeV/c];entries");
  h_genW_pt -> Draw();
  c1 -> cd(2);
  h_genW_eta -> SetTitle(";#eta^{gen. W};entries");
  h_genW_eta -> Draw();
  c1 -> cd(3);
  h_genW_mass -> SetTitle(";mass^{gen. W} [GeV/c^{2}];entries");
  h_genW_mass -> Draw();
  
  TCanvas* c2 = new TCanvas("c2","recoJ/Psi",500,500);
  c2 -> cd();
  h_recoJPsi_mass -> SetTitle(";mass^{J/#psi} [GeV/c^{2}];entries");
  h_recoJPsi_mass -> Draw();
}
