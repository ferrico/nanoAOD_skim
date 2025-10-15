#ifndef H4LTools_h
#define H4LTools_h

#include <utility>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TLorentzVector.h>
#include <TSpline.h>
#include <vector>
#include "yaml-cpp/yaml.h"
#include "../JHUGenMELA/MELA/interface/Mela.h"
//#include "KinZfitter/KinZfitter/interface/KinZfitter.h"
//#include "PhysicsTools/NanoAODTools/interface/KinZfitter.h"
#include <TMVA/Tools.h>
#include <TMVA/Reader.h>
#include <TMVA/MsgLogger.h>

class H4LTools {
    public:
      H4LTools(int year, bool isMC_);
      std::vector<float> mvaEstimation(TString weight);
      float elePtcut, MuPtcut, eleEtacut, MuEtacut, elesip3dCut, Musip3dCut,Zmass,MZ1cut,MZcutup,MZcutdown,MZZcut,HiggscutUp,HiggscutDown;
      float eleLoosedxycut,eleLoosedzcut,MuLoosedxycut,MuLoosedzcut,MuTightdxycut,MuTightdzcut,MuTightTrackerLayercut,MuTightpTErrorcut,MuHighPtBound,eleIsocut,MuIsocut;
      float fsrphotonPtcut,fsrphotonEtacut,fsrphotonIsocut,fsrphotondRlcut,fsrphotondRlOverPtcut, JetPtcut,JetEtacut, JetbTagcut;
      float eleBDTWPLELP,eleBDTWPMELP,eleBDTWPHELP,eleBDTWPLEHP,eleBDTWPMEHP,eleBDTWPHEHP;
      float mass3l;
      bool passedZ1LSelection;
      bool RecoFourMuEvent, RecoFourEEvent, RecoTwoETwoMuEvent, RecoTwoMuTwoEEvent;
      void InitializeElecut(float elePtcut_,float eleEtacut_,float elesip3dCut_,float eleLoosedxycut_,float eleLoosedzcut_,float eleIsocut_,float eleBDTWPLELP_,float eleBDTWPMELP_, float eleBDTWPHELP_,float eleBDTWPLEHP_,float eleBDTWPMEHP_,float eleBDTWPHEHP_){
        elePtcut = elePtcut_;
        eleEtacut = eleEtacut_;
        elesip3dCut = elesip3dCut_;
        eleLoosedxycut = eleLoosedxycut_;
        eleLoosedzcut = eleLoosedzcut_;
        eleIsocut = eleIsocut_;
        eleBDTWPLELP = eleBDTWPLELP_;
        eleBDTWPMELP = eleBDTWPMELP_;
        eleBDTWPHELP = eleBDTWPHELP_;
        eleBDTWPLEHP = eleBDTWPLEHP_;
        eleBDTWPMEHP = eleBDTWPMEHP_;
        eleBDTWPHEHP = eleBDTWPHEHP_;
      }
      void InitializeMucut(float MuPtcut_,float MuEtacut_,float Musip3dCut_,float MuLoosedxycut_,float MuLoosedzcut_,float MuIsocut_,float MuTightdxycut_,float MuTightdzcut_,float MuTightTrackerLayercut_,float MuTightpTErrorcut_,float MuHighPtBound_){
        MuPtcut = MuPtcut_;
        MuEtacut = MuEtacut_;
        Musip3dCut = Musip3dCut_;
        MuLoosedxycut = MuLoosedxycut_;
        MuLoosedzcut = MuLoosedzcut_;
        MuIsocut = MuIsocut_;
        MuTightdxycut = MuTightdxycut_;
        MuTightdzcut = MuTightdzcut_;
        MuTightTrackerLayercut = MuTightTrackerLayercut_;
        MuTightpTErrorcut = MuTightpTErrorcut_;
        MuHighPtBound = MuHighPtBound_;
      }
      void InitializeFsrPhotonCut(float fsrphotonPtcut_, float fsrphotonEtacut_, float fsrphotonIsocut_, float fsrphotondRlcut_, float fsrphotondRlOverPtcut_){
        fsrphotonPtcut = fsrphotonPtcut_;
        fsrphotonEtacut = fsrphotonEtacut_;
        fsrphotonIsocut = fsrphotonIsocut_;
        fsrphotondRlcut = fsrphotondRlcut_;
        fsrphotondRlOverPtcut = fsrphotondRlOverPtcut_;
      }
      void InitializeJetcut(float JetPtcut_, float JetEtacut_, float JetbTagcut_){
        JetPtcut = JetPtcut_;
        JetEtacut = JetEtacut_;
	JetbTagcut = JetbTagcut_;
      }
      void InitializeEvtCut(float MZ1cut_,float MZZcut_,float HiggscutDown_,float HiggscutUp_,float Zmass_,float MZcutdown_, float MZcutup_){
        MZ1cut = MZ1cut_;
        MZZcut = MZZcut_;
        HiggscutDown = HiggscutDown_;
        HiggscutUp = HiggscutUp_;
        Zmass = Zmass_;
        MZcutdown = MZcutdown_;
        MZcutup = MZcutup_;
      }
      void SetElectrons(float Electron_pt_, float Electron_eta_, float Electron_phi_, float Electron_mass_, float Electron_dxy_,float Electron_dz_,
                        float Electron_sip3d_, float Electron_mvaHZZIso_, int Electron_pdgId_, int Electron_charge_, float Electron_pfRelIso03_all_, float Electron_uncorrected_pt_, float Electron_energyErr_, float Electron_deltaEtaSC_){
        Electron_pt.push_back(Electron_pt_); 
        Electron_phi.push_back(Electron_phi_);
        Electron_eta.push_back(Electron_eta_);
        Electron_mass.push_back(Electron_mass_);
        Electron_dxy.push_back(Electron_dxy_);
        Electron_dz.push_back(Electron_dz_);
        Electron_sip3d.push_back(Electron_sip3d_);
        Electron_mvaHZZIso.push_back(Electron_mvaHZZIso_);
        Electron_pdgId.push_back(Electron_pdgId_);
	Electron_charge.push_back(Electron_charge_);
        Electron_pfRelIso03_all.push_back(Electron_pfRelIso03_all_);
	Electron_uncorrected_pt.push_back(Electron_uncorrected_pt_);
	Electron_energyErr.push_back(Electron_energyErr_);
	Electron_deltaEtaSC.push_back(Electron_deltaEtaSC_);
      }

      void SetElectrons_BDT_2024(bool Electron_mvaIso_WPHZZ_){
	     Electron_mvaIso_WPHZZ.push_back(Electron_mvaIso_WPHZZ_);
      }

	void SetLowElectrons(float LowElectron_pt_, float LowElectron_eta_, float LowElectron_phi_, float LowElectron_mass_, float LowElectron_dxy_, 
		float LowElectron_dz_, float LowElectron_ID_, int LowElectron_pdgId_, int LowElectron_charge_, float LowElectron_miniPFRelIso_all_, float LowElectron_energyErr_){

		LowElectron_pt.push_back(LowElectron_pt_);
	        LowElectron_eta.push_back(LowElectron_eta_);
        	LowElectron_phi.push_back(LowElectron_phi_);
	        LowElectron_mass.push_back(LowElectron_mass_);
        	LowElectron_dxy.push_back(LowElectron_dxy_);
	        LowElectron_dz.push_back(LowElectron_dz_);
        	LowElectron_ID.push_back(LowElectron_ID_);
	        LowElectron_pdgId.push_back(LowElectron_pdgId_);
        	LowElectron_charge.push_back(LowElectron_charge_);
	        LowElectron_miniPFRelIso_all.push_back(LowElectron_miniPFRelIso_all_);
		LowElectron_energyErr.push_back(LowElectron_energyErr_);
	}


      void SetJets(float Jet_pt_, float Jet_eta_, float Jet_phi_, float Jet_mass_, int Jet_jetId_,
                       float Jet_neHEF_, float Jet_neEmEF_, float Jet_muEF_, float Jet_chEmEF_,
                     //float Jet_btagDeepC_, int Jet_puId_, 
		     float Jet_btagDeepFlavB_){
        Jet_pt.push_back(Jet_pt_); 
        Jet_phi.push_back(Jet_phi_);
        Jet_eta.push_back(Jet_eta_);
        Jet_mass.push_back(Jet_mass_);
        Jet_jetId.push_back(Jet_jetId_);
        Jet_neHEF.push_back(Jet_neHEF_);
        Jet_neEmEF.push_back(Jet_neEmEF_);
        Jet_muEF.push_back(Jet_muEF_);
        Jet_chEmEF.push_back(Jet_chEmEF_);
        //Jet_btagDeepC.push_back(Jet_btagDeepC_);
        //Jet_puId.push_back(Jet_puId_); //1 or 0?
	Jet_btagDeepFlavB.push_back(Jet_btagDeepFlavB_);
      }
    
      
      void SetMuons(float Muon_pt_, float Muon_eta_, float Muon_phi_, float Muon_mass_, bool Muon_isGlobal_, bool Muon_isTracker_,
                        float Muon_dxy_, float Muon_dz_,float Muon_sip3d_, float Muon_ptErr_,
			int Muon_nTrackerLayers_, bool Muon_isPFcand_, int Muon_pdgId_,int Muon_charge_, float Muon_pfRelIso03_all_, float Muon_pfRelIso03_chg_, float Muon_mva_, Int_t Muon_nStations_, bool Muon_isStandalone_, float Muon_bsConstrainedPt_, float Muon_bsConstrainedPtErr_, bool Muon_inTimeMuon_
//##### for muon time information ---> need to add branches from miniaod
			, float Muon_timeAtIpInOut_, float Muon_timeAtIpInOutErr_, float Muon_timeAtIpOutIn_, float Muon_timeAtIpOutInErr_, float Muon_inverseBeta_, float Muon_inverseBetaErr_
//##### for muon time information ---> need to add branches from miniaod
		   ){
        Muon_pt.push_back(Muon_pt_); 
        Muon_phi.push_back(Muon_phi_);
        Muon_eta.push_back(Muon_eta_);
        Muon_mass.push_back(Muon_mass_);
        Muon_isGlobal.push_back(Muon_isGlobal_);
        Muon_isTracker.push_back(Muon_isTracker_);
        Muon_dxy.push_back(Muon_dxy_);
        Muon_dz.push_back(Muon_dz_);
        Muon_sip3d.push_back(Muon_sip3d_);
        Muon_ptErr.push_back(Muon_ptErr_);
        Muon_nTrackerLayers.push_back(Muon_nTrackerLayers_);
        Muon_isPFcand.push_back(Muon_isPFcand_);
        Muon_pdgId.push_back(Muon_pdgId_);
        Muon_charge.push_back(Muon_charge_);
        Muon_pfRelIso03_all.push_back(Muon_pfRelIso03_all_);
	Muon_pfRelIso03_chg.push_back(Muon_pfRelIso03_chg_);
        Muon_mva.push_back(Muon_mva_);  
	Muon_nStations.push_back(Muon_nStations_);
	Muon_isStandalone.push_back(Muon_isStandalone_);
	Muon_bsConstrainedPt.push_back(Muon_bsConstrainedPt_);
	Muon_bsConstrainedPtErr.push_back(Muon_bsConstrainedPtErr_);
	Muon_inTimeMuon.push_back(Muon_inTimeMuon_);
///*
        Muon_timeAtIpInOut.push_back(Muon_timeAtIpInOut_);
        Muon_timeAtIpInOutErr.push_back(Muon_timeAtIpInOutErr_);
        Muon_timeAtIpOutIn.push_back(Muon_timeAtIpOutIn_);
        Muon_timeAtIpOutInErr.push_back(Muon_timeAtIpOutInErr_);
        Muon_inverseBeta.push_back(Muon_inverseBeta_);
        Muon_inverseBetaErr.push_back(Muon_inverseBetaErr_);
//*/
      }
      void SetMuonsGen(int Muon_genPartIdx_){
        Muon_genPartIdx.push_back(Muon_genPartIdx_);
      }
      void SetElectronsGen(int Electron_genPartIdx_){
        Electron_genPartIdx.push_back(Electron_genPartIdx_);
      }
      /*void SetMuons(TTreeReaderArray<float> *Muon_pt_, TTreeReaderArray<float> *Muon_eta_,
                        TTreeReaderArray<float> *Muon_phi_, TTreeReaderArray<float> *Muon_mass_, TTreeReaderArray<bool> *Muon_isGlobal_, TTreeReaderArray<bool> *Muon_isTracker_,
                        TTreeReaderArray<float> *Muon_dxy_, TTreeReaderArray<float> *Muon_dz_,TTreeReaderArray<float> *Muon_sip3d_, TTreeReaderArray<float> *Muon_ptErr_,
                        TTreeReaderArray<int> *Muon_nTrackerLayers_, TTreeReaderArray<bool> *Muon_isPFcand_, TTreeReaderArray<int> *Muon_pdgId_,TTreeReaderArray<int> *Muon_charge_, TTreeReaderArray<float> *Muon_pfRelIso03_all_,
                        TTreeReaderArray<int> *Muon_genPartIdx_){
        Muon_pt = Muon_pt_; 
        Muon_phi = Muon_phi_;
        Muon_eta = Muon_eta_;
        Muon_mass = Muon_mass_;
        Muon_isGlobal = Muon_isGlobal_;
        Muon_isTracker = Muon_isTracker_;
        Muon_dxy = Muon_dxy_;
        Muon_dz = Muon_dz_;
        Muon_sip3d = Muon_sip3d_;
        Muon_nTrackerLayers = Muon_nTrackerLayers_;
        Muon_isPFcand = Muon_isPFcand_;
        Muon_pdgId = Muon_pdgId_;
        Muon_charge = Muon_charge_;
        Muon_pfRelIso03_all = Muon_pfRelIso03_all_;
        Muon_genPartIdx = Muon_genPartIdx_;
      }*/
      void SetFsrPhotons(float FsrPhoton_dROverEt2_, float FsrPhoton_eta_,
                        float FsrPhoton_phi_, float FsrPhoton_pt_, float FsrPhoton_relIso03_, int FsrPhoton_electronIdx_, int FsrPhoton_muonIdx_){
        FsrPhoton_dROverEt2.push_back(FsrPhoton_dROverEt2_); 
        FsrPhoton_phi.push_back(FsrPhoton_phi_);
        FsrPhoton_eta.push_back(FsrPhoton_eta_);
        FsrPhoton_pt.push_back(FsrPhoton_pt_);
        FsrPhoton_relIso03.push_back(FsrPhoton_relIso03_);
        FsrPhoton_electronIdx.push_back(FsrPhoton_electronIdx_);
        FsrPhoton_muonIdx.push_back(FsrPhoton_muonIdx_);
      }
      /*void SetFsrPhotons(TTreeReaderArray<float> *FsrPhoton_dROverEt2_, TTreeReaderArray<float> *FsrPhoton_eta_,
                        TTreeReaderArray<float> *FsrPhoton_phi_, TTreeReaderArray<float> *FsrPhoton_pt_, 
                        TTreeReaderArray<float> *FsrPhoton_relIso03_){
        FsrPhoton_dROverEt2 = FsrPhoton_dROverEt2_; 
        FsrPhoton_phi = FsrPhoton_phi_;
        FsrPhoton_eta = FsrPhoton_eta_;
        FsrPhoton_pt = FsrPhoton_pt_;
        FsrPhoton_relIso03 = FsrPhoton_relIso03_;
        
      }*/
      void SetGenParts(float GenPart_pt_){
        GenPart_pt.push_back(GenPart_pt_);
      }
      /*void SetGenParts(TTreeReaderArray<float> *GenPart_pt_){
        GenPart_pt = GenPart_pt_;
      }*/
      void SetObjectNum(unsigned nElectron_,unsigned nMuon_,unsigned nJet_,unsigned nFsrPhoton_){
        nElectron = nElectron_; 
        nMuon = nMuon_;
        nJet = nJet_;
        nFsrPhoton = nFsrPhoton_;
      }
      void SetObjectNumGen(unsigned nGenPart_){
        nGenPart = nGenPart_;
      }
      bool isMC;
      bool ZXdistributions();
      std::vector<unsigned int> goodLooseElectrons2012();
      std::vector<unsigned int> goodLooseLowElectrons2012();
      std::vector<unsigned int> goodLooseMuons2012();
      std::vector<unsigned int> goodMuons2015_noIso_noPf(std::vector<unsigned int> Muonindex);
      std::vector<unsigned int> goodElectrons2015_noIso_noBdt(std::vector<unsigned int> Electronindex);
      std::vector<unsigned int> goodLowElectrons2015_noIso_noBdt(std::vector<unsigned int> Electronindex);
      std::vector<bool> passTight_BDT_Id(int year);
      std::vector<bool> passTight_BDT_Id_LowElectron();
      std::vector<bool> passTight_Id();
      std::vector<unsigned int> goodFsrPhotons();
      std::vector<float> leptonsWeight(int year, int id, float pt, float eta, bool isCrack);
      unsigned doFsrRecovery(TLorentzVector Lep);
      std::vector<int> doFsrRecovery_Run3(std::vector<unsigned int> goodfsridx, unsigned lepidx, int lepflavor);//lepflavor 11 or 13

 //      unsigned doFsrRecovery_Run3(std::vector<unsigned int> goodfsridx, unsigned lepidx, int lepflavor);//lepflavor 11 or 13
      std::vector<TLorentzVector> BatchFsrRecovery(std::vector<TLorentzVector> LepList);
      void BatchFsrRecovery_Run3();

      std::vector<TLorentzVector> ElectronFsr();
      std::vector<TLorentzVector> MuonFsr();
      std::vector<float> ElectronFsrPt();
      std::vector<float> ElectronFsrEta();
      std::vector<float> ElectronFsrPhi();
      std::vector<float> MuonFsrPt();
      std::vector<float> MuonFsrEta();
      std::vector<float> MuonFsrPhi();
      std::vector<unsigned int> SelectedJets(std::vector<unsigned int> ele, std::vector<unsigned int> mu);
      std::vector<TLorentzVector> LowElectrondressed_Run3;
      std::vector<TLorentzVector> Electrondressed_Run3;
      std::vector<TLorentzVector> Muondressed_Run3;
      std::vector<TLorentzVector> Zlist;
      std::vector<TLorentzVector> Zlistnofsr;
      std::vector<int> Zflavor; //mu->13, e->11
      std::vector<int> Zlep1index;
      std::vector<int> Zlep2index;
      std::vector<int> Zlep1lepindex;
      std::vector<int> Zlep2lepindex;
      std::vector<float> Zlep1pt;
      std::vector<float> Zlep1eta;
      std::vector<float> Zlep1phi;
      std::vector<float> Zlep1mass;
      std::vector<float> Zlep1chg;
      std::vector<float> Zlep2pt;
      std::vector<float> Zlep2eta;
      std::vector<float> Zlep2phi;
      std::vector<float> Zlep2mass;
      std::vector<float> Zlep2chg;
      std::vector<float> Zlep1ptNoFsr;
      std::vector<float> Zlep1etaNoFsr;
      std::vector<float> Zlep1phiNoFsr;
      std::vector<float> Zlep1massNoFsr;
      std::vector<float> Zlep2ptNoFsr;
      std::vector<float> Zlep2etaNoFsr;
      std::vector<float> Zlep2phiNoFsr;
      std::vector<float> Zlep2massNoFsr;
      std::vector<unsigned int> jetidx;
      bool CutFlow_4Lepton,CutFlow_4LeptonOSSF,CutFlow_getTightZ,CutFlow_getTightZ1,CutFlow_lep_pTcut,CutFlow_lepdRcut,CutFlow_QCDcut,CutFlow_Smartcut,CutFlow_MZ1MZ2cut,CutFlow_M4Lcut,CutFlow_CR,CutFlow_SR;
      bool CutFlow_3Lep,CutFlow_properID,CutFlow_3LepDRcut,CutFlow_3LepPtcut,CutFlow_3LepQCDcut,CutFlow_tightZ1cut;
      int nTightEle;
      int nTightMu;
      int nTightEleChgSum;
      int nTightMuChgSum;
      int njets_pt30_eta4p7;
      int nBtaggedjets_pt30_eta4p7;
      int Lepointer;
    
      bool flag4e;
      bool flag4mu;
      bool flag2e2mu;

      void LeptonSelection(int year);
      void findZ1LCandidate();
      std::vector<unsigned int> looseEle,looseLowEle,looseMu,bestEle,bestLowEle,bestMu, tighteleforjetidx, tightmuforjetidx;
      std::vector<unsigned int> Electronindex;
      std::vector<unsigned int> LowElectronindex;
      std::vector<unsigned int> Muonindex;
      std::vector<bool> AllEid;
      std::vector<bool> AllLowEid;
      std::vector<bool> AllMuid;
      std::vector<TLorentzVector> Elelist;
      std::vector<TLorentzVector> Mulist;
      std::vector<TLorentzVector> ElelistFsr;
      std::vector<TLorentzVector> MulistFsr;
      std::vector< std::vector<float> > Candidate;
      std::vector< std::vector<float> > Candidate_VXBS;
      std::map<unsigned int, TLorentzVector> fsrmap;
      std::vector<float> lep_pt;
      std::vector<float> lep_ptError;
      std::vector<float> lep_ptVXBS;
      std::vector<float> lep_ptErrorVXBS;
      std::vector<float> lep_eta;
      std::vector<float> lep_etaSC;
      std::vector<float> lep_phi;
      std::vector<float> lep_mass;
      std::vector<float> lepFSR_pt;
      std::vector<float> lepFSR_ptVXBS;
      std::vector<float> lepFSR_eta;
      std::vector<float> lepFSR_phi;
      std::vector<float> lepFSR_mass;
      std::vector<int> lep_charge;
      std::vector<int> lep_id;
      std::vector<float> lep_tightId;
      std::vector<float> lep_looseId;
      std::vector<float> lep_RelIsoNoFSR;
      std::vector<float> lep_lowEleBDT;
      std::vector<bool> lep_inTimeMuon;
      std::vector<float> lep_timeAtIpInOut;
      std::vector<float> lep_timeAtIpInOutErr;
      std::vector<float> lep_timeAtIpOutIn;
      std::vector<float> lep_timeAtIpOutInErr;
      std::vector<float> lep_inverseBeta;
      std::vector<float> lep_inverseBetaErr;

      float mass4l_VXBS;
      std::vector<int> Elechg;
      std::vector<int> Muchg;
      std::vector<float> Muiso,Eiso;
      std::vector<float> Mumva;
      std::vector<bool> Eid;
      std::vector<bool> muid;
      std::vector<bool> istightele;
      std::vector<bool> istightmu;
      std::vector<int> lep_genindex;
      std::vector<int> TightElelep_index;
      std::vector<int> TightMulep_index;
      int lep_Hindex[4];
      TLorentzVector Z1;
      TLorentzVector Z1nofsr;
      TLorentzVector Z2;
      TLorentzVector Z2nofsr;
      TLorentzVector ZZsystem;
      TLorentzVector ZZsystemnofsr;
      
      std::vector<int> TightEleindex;
      std::vector<int> TightMuindex;
      void Initialize(){
        looseEle.clear();
	looseLowEle.clear();
        looseMu.clear();
        bestEle.clear();
	bestLowEle.clear();
        bestMu.clear();
        tighteleforjetidx.clear();
        tightmuforjetidx.clear();
        Electronindex.clear();
	LowElectronindex.clear();
        Muonindex.clear();
        AllEid.clear();
	AllLowEid.clear();
        AllMuid.clear();
        Elelist.clear();
        Mulist.clear();
        ElelistFsr.clear();
        MulistFsr.clear();
        Electron_pt.clear();Electron_phi.clear();Electron_eta.clear();Electron_mass.clear();Electron_dxy.clear();Electron_dz.clear();Electron_sip3d.clear();Electron_charge.clear();Electron_deltaEtaSC.clear();
        Electron_mvaHZZIso.clear();Electron_pdgId.clear();Electron_genPartIdx.clear();Electron_pfRelIso03_all.clear();
	Electron_uncorrected_pt.clear(); Electron_energyErr.clear();Electron_mvaIso_WPHZZ.clear();

	LowElectron_pt.clear(); LowElectron_eta.clear(); LowElectron_phi.clear();	LowElectron_mass.clear();
	LowElectron_dxy.clear(); LowElectron_dz.clear(); LowElectron_ID.clear(); LowElectron_miniPFRelIso_all.clear();
	LowElectron_pdgId.clear(); LowElectron_charge.clear(); LowElectron_energyErr.clear();

        Muon_pt.clear();Muon_phi.clear();Muon_eta.clear();Muon_mass.clear();Muon_dxy.clear();Muon_dz.clear();Muon_sip3d.clear();Muon_ptErr.clear();Muon_pfRelIso03_all.clear(); Muon_pfRelIso03_chg.clear(); Muon_mva.clear(); Muon_nStations.clear(); Muon_isStandalone.clear();
        Muon_nTrackerLayers.clear();Muon_genPartIdx.clear();Muon_pdgId.clear();Muon_charge.clear();
        Muon_isTracker.clear();Muon_isGlobal.clear();Muon_isPFcand.clear();
	Muon_bsConstrainedPt.clear(); Muon_bsConstrainedPtErr.clear(); 
	Muon_inTimeMuon.clear();
	Muon_timeAtIpInOut.clear();
        Muon_timeAtIpInOutErr.clear();
        Muon_timeAtIpOutIn.clear();
        Muon_timeAtIpOutInErr.clear();
        Muon_inverseBeta.clear();
        Muon_inverseBetaErr.clear();

	Jet_pt.clear();Jet_phi.clear();Jet_eta.clear();Jet_mass.clear();Jet_btagDeepC.clear();
        Jet_jetId.clear();Jet_puId.clear(); Zlep1lepindex.clear();Zlep2lepindex.clear();
	Jet_neHEF.clear(); Jet_neEmEF.clear(); Jet_muEF.clear(); Jet_chEmEF.clear();
	Jet_btagDeepFlavB.clear();
        FsrPhoton_dROverEt2.clear();FsrPhoton_phi.clear();FsrPhoton_eta.clear();FsrPhoton_pt.clear();FsrPhoton_relIso03.clear(); FsrPhoton_electronIdx.clear(); FsrPhoton_muonIdx.clear();
        Candidate.clear();
	Candidate_VXBS.clear();
	mass4l_VXBS = 0;
	fsrmap.clear();
	lep_pt.clear();
	lep_ptError.clear();
	lep_ptVXBS.clear();
	lep_ptErrorVXBS.clear();
        lep_eta.clear();
	lep_etaSC.clear();
        lep_phi.clear();
        lep_mass.clear();
        lepFSR_pt.clear();lepFSR_eta.clear(); lepFSR_phi.clear();lepFSR_mass.clear();lepFSR_ptVXBS.clear();
        lep_charge.clear();
        lep_id.clear();
        lep_tightId.clear();
        lep_looseId.clear();
        lep_RelIsoNoFSR.clear();
	lep_lowEleBDT.clear();
	lep_inTimeMuon.clear();
        lep_timeAtIpInOut.clear();
        lep_timeAtIpInOutErr.clear();
        lep_timeAtIpOutIn.clear();
        lep_timeAtIpOutInErr.clear();
        lep_inverseBeta.clear();
        lep_inverseBetaErr.clear();

	GenPart_pt.clear();
        Zlist.clear();
        Zlistnofsr.clear();
        Zflavor.clear();
        Electrondressed_Run3.clear();
	LowElectrondressed_Run3.clear();
        Muondressed_Run3.clear();
        Zlep1index.clear();
        Zlep2index.clear();
        Zlep1pt.clear(); Zlep1eta.clear(); Zlep1phi.clear(); Zlep1mass.clear();
        Zlep2pt.clear(); Zlep2eta.clear(); Zlep2phi.clear(); Zlep2mass.clear();
        Zlep1chg.clear(); Zlep2chg.clear();
        Zlep1ptNoFsr.clear(); Zlep1etaNoFsr.clear(); Zlep1phiNoFsr.clear(); Zlep1massNoFsr.clear();
        Zlep2ptNoFsr.clear(); Zlep2etaNoFsr.clear(); Zlep2phiNoFsr.clear(); Zlep2massNoFsr.clear();
        jetidx.clear(); lep_genindex.clear(); TightElelep_index.clear();TightMulep_index.clear();
        looseEle.clear(); looseMu.clear(); bestEle.clear(); bestMu.clear();  tighteleforjetidx.clear();  tightmuforjetidx.clear(); 
        Electronindex.clear();  Muonindex.clear(); AllEid.clear(); AllMuid.clear(); Elelist.clear(); Mulist.clear(); ElelistFsr.clear(); Mulist.clear(); 
        Elechg.clear(); Muchg.clear(); Muiso.clear(); Mumva.clear();Eiso.clear(); Eid.clear(); muid.clear(); istightele.clear(); istightmu.clear(); TightEleindex.clear(); TightMuindex.clear();
	mass3l = -99;
        for (int i=0; i<4; i++) {lep_Hindex[i]=-1;}
        passedZ1LSelection = false;
        Z1.SetPtEtaPhiM(0,0,0,0);
        Z1nofsr.SetPtEtaPhiM(0,0,0,0);
        Z2.SetPtEtaPhiM(0,0,0,0);
        Z2nofsr.SetPtEtaPhiM(0,0,0,0);
        ZZsystem.SetPtEtaPhiM(0,0,0,0);
        ZZsystemnofsr.SetPtEtaPhiM(0,0,0,0);
        nElectron = 0; nMuon = 0; nJet = 0; nFsrPhoton = 0; nGenPart = 0;
        nTightEle = 0; nTightMu = 0; nTightEleChgSum = 0; nTightMuChgSum = 0;
        Lepointer = 0; 
        
        pTL1 = -999; etaL1 = -999; phiL1 = -999; massL1 = -999;
        pTL2 = -999; etaL2 = -999; phiL2 = -999; massL2 = -999;
        pTL3 = -999; etaL3 = -999; phiL3 = -999; massL3 = -999;
        pTL4 = -999; etaL4 = -999; phiL4 = -999; massL4 = -999;

        pTj1 = -99;  etaj1 = -99;  phij1 = -99;  mj1 = -99;
        pTj2 = -99;  etaj2 = -99;  phij2 = -99;  mj2 = -99;
	mjj = -999; etajj = -999; phijj = -999; Detajj = -999; Dphijj = -999;
        mva_Rhard = -999; mva_zstar = -999; mva_cosTheta_star = -999;  mva_phiZZ = -999;  mva_phi1 = -999; mva_theta1 = -999; mva_theta2 = -999;
	mva_output_ggH = -999; mva_output_VBF = -999; mva_output_WH = -999; mva_output_qqZZ = -999;
	njets_pt30_eta4p7 = 0;
	nBtaggedjets_pt30_eta4p7 = 0;
        RecoFourMuEvent=false; RecoFourEEvent=false; RecoTwoETwoMuEvent=false; RecoTwoMuTwoEEvent=false;
        flag4e=false; flag4mu=false; flag2e2mu=false;
	
	D_bkg_kin = -999;
	D_bkg_VHdec = -999;
	D_VBF1j = -999;
	D_HadWH = -999;
	D_HadZH = -999;
	D_VBF = -999;
      }
      bool isFSR=true;
      unsigned int Zsize=0;
      TSpline *spline_g4;
      TSpline *spline_g2;
      TSpline *spline_L1;
      TSpline *spline_L1Zgs;
      bool findZCandidate();
      bool ZZSelection();

      Mela* mela;
      float me_0plus_JHU, me_qqZZ_MCFM, p0plus_m4l, bkg_m4l;
      float D_bkg_kin, D_bkg, D_g4, D_g1g4, D_0m, D_CP, D_0hp, D_int, D_L1, D_L1_int, D_L1Zg, D_L1Zgint;
      float D_bkg_kin_vtx_BS;
      float D_bkg_VHdec, D_VBF1j;
      float D_HadWH, D_HadZH, D_VBF;
      float p0minus_VAJHU, Dgg10_VAMCFM, pg1g4_VAJHU;
      float p0plus_VAJHU, p_GG_SIG_ghg2_1_ghz1prime2_1E4_JHUGen, p_GG_SIG_ghg2_1_ghza1prime2_1E4_JHUGen, p_GG_SIG_ghg2_1_ghz1_1_ghza1prime2_1E4_JHUGen, p_GG_SIG_ghg2_1_ghz1_1_ghz1prime2_1E4_JHUGen, p_GG_SIG_ghg2_1_ghz1_1_ghz2_1_JHUGen, pDL1_VAJHU, pD_L1Zgint; //, p0plus_VAJHU;

      int cut4e, cut4mu, cut2e2mu, cutZZ4e, cutZZ4mu, cutZZ2e2mu, cutm4l4e, cutm4l4mu, cutm4l2e2mu, cutghost2e2mu, cutQCD2e2mu, cutLepPt2e2mu, cutghost4e, cutQCD4e, cutLepPt4e, cutghost4mu, cutQCD4mu, cutLepPt4mu;
      float pTL1, etaL1, phiL1, massL1, pTL2, etaL2, phiL2, massL2, pTL3, etaL3, phiL3, massL3, pTL4, etaL4, phiL4, massL4;
      float pTj1, etaj1, phij1, mj1, pTj2, etaj2, phij2, mj2, mjj, etajj, phijj, Detajj, Dphijj;

      float mva_Rhard, mva_zstar, mva_cosTheta_star, mva_phiZZ, mva_phi1, mva_theta1, mva_theta2;
      float mva_output_ggH, mva_output_VBF, mva_output_WH, mva_output_qqZZ;

      float getDbkgkinConstant(int ZZflav, float ZZMass);
      float getDbkgConstant(int ZZflav, float ZZMass);
      float getDg4Constant(float ZZMass);
      float getDg2Constant(float ZZMass);
      float getDL1Constant(float ZZMass);
      float getDL1ZgsConstant(float ZZMass);
      float getDVBF2jetsConstant(float ZZMass);
      float getDVBF1jetConstant(float ZZMass);
      float getDWHhConstant(float ZZMass);
      float getDZHhConstant(float ZZMass);
      float getDbkgVBFdecConstant(int ZZflav, float ZZMass);
      float getDbkgVHdecConstant(int ZZflav, float ZZMass);
      
      TSpline3 *DbkgkinSpline2e2mu;
      TSpline3 *DbkgkinSpline4e;
      TSpline3 *DbkgkinSpline4mu;

      TSpline3 *DbkgVBFdecSpline2l2l;
      TSpline3 *DbkgVBFdecSpline4l;
      TSpline3 *DbkgVHdecSpline2l2l;
      TSpline3 *DbkgVHdecSpline4l;

      TSpline3 *DjjVBFSpline;
      TSpline3 *DjVBFSpline;
      TSpline3 *DjjZHSpline;
      TSpline3 *DjjWHSpline;


    private:
      //KinZfitter
      //KinZfitter *kinZfitter;

      std::vector<float> Electron_pt,Electron_phi,Electron_eta,Electron_mass,Electron_dxy,Electron_dz,Electron_sip3d, Electron_charge, Electron_deltaEtaSC;
      std::vector<float> Electron_mvaHZZIso,Electron_pfRelIso03_all;
      std::vector<int> Electron_pdgId,Electron_genPartIdx;
      std::vector<float> Electron_uncorrected_pt;
      std::vector<float> Electron_energyErr;
      std::vector<bool> Electron_mvaIso_WPHZZ;

      std::vector<float> LowElectron_pt, LowElectron_eta, LowElectron_phi, LowElectron_mass;
      std::vector<float> LowElectron_dxy, LowElectron_dz, LowElectron_ID, LowElectron_miniPFRelIso_all;
      std::vector<int> LowElectron_pdgId, LowElectron_charge; 
      std::vector<float> LowElectron_energyErr;

      std::vector<float> Jet_pt,Jet_phi,Jet_eta,Jet_mass,Jet_btagDeepC;
      std::vector<float> Jet_neHEF, Jet_neEmEF, Jet_muEF, Jet_chEmEF;
      std::vector<float> Jet_btagDeepFlavB;
      std::vector<int> Jet_jetId,Jet_puId;
      std::vector<float> Muon_pt,Muon_phi,Muon_eta,Muon_mass,Muon_dxy,Muon_dz,Muon_sip3d,Muon_ptErr,Muon_pfRelIso03_all, Muon_pfRelIso03_chg, Muon_mva;
      std::vector<int> Muon_nTrackerLayers,Muon_genPartIdx,Muon_pdgId,Muon_charge;
      std::vector<Int_t> Muon_nStations;
      std::vector<bool> Muon_isTracker,Muon_isGlobal,Muon_isPFcand, Muon_isStandalone;
      std::vector<float> Muon_bsConstrainedPt; std::vector<float> Muon_bsConstrainedPtErr; std::vector<bool> Muon_inTimeMuon;
      std::vector<float> Muon_timeAtIpInOut; std::vector<float> Muon_timeAtIpInOutErr; std::vector<float> Muon_timeAtIpOutIn; std::vector<float> Muon_timeAtIpOutInErr; std::vector<float> Muon_inverseBeta; std::vector<float> Muon_inverseBetaErr;
      std::vector<float> FsrPhoton_dROverEt2,FsrPhoton_phi,FsrPhoton_pt,FsrPhoton_relIso03,FsrPhoton_eta,FsrPhoton_muonIdx,FsrPhoton_electronIdx;
      
      std::vector<float> GenPart_pt;
      
      
      unsigned nElectron,nMuon,nJet,nGenPart,nFsrPhoton;



};

H4LTools::H4LTools(int year, bool isMC_){
  isMC = isMC_;
  mela = new Mela(13.6, 125.0, TVar::ERROR);//TVar::SILENT);
  mela->setCandidateDecayMode(TVar::CandidateDecay_ZZ);  
  TFile *gConstant_g4 = TFile::Open("CoupleConstantsForMELA/gConstant_HZZ2e2mu_g4.root");
  spline_g4 = (TSpline*) gConstant_g4->Get("sp_tgfinal_HZZ2e2mu_SM_over_tgfinal_HZZ2e2mu_g4");
  gConstant_g4->Close();
  delete gConstant_g4;
  TFile *gConstant_g2 = TFile::Open("CoupleConstantsForMELA/gConstant_HZZ2e2mu_g2.root");
  spline_g2 = (TSpline*) gConstant_g2->Get("sp_tgfinal_HZZ2e2mu_SM_over_tgfinal_HZZ2e2mu_g2");
  gConstant_g2->Close();
  delete gConstant_g2;
  TFile *gConstant_L1 = TFile::Open("CoupleConstantsForMELA/gConstant_HZZ2e2mu_L1.root");
  spline_L1 = (TSpline*) gConstant_L1->Get("sp_tgfinal_HZZ2e2mu_SM_over_tgfinal_HZZ2e2mu_L1");
  gConstant_L1->Close();
  delete gConstant_L1;
  TFile *gConstant_L1Zgs = TFile::Open("CoupleConstantsForMELA/gConstant_HZZ2e2mu_L1Zgs.root");
  spline_L1Zgs = (TSpline*) gConstant_L1Zgs->Get("sp_tgfinal_HZZ2e2mu_SM_photoncut_over_tgfinal_HZZ2e2mu_L1Zgs");
  gConstant_L1Zgs->Close();
  delete gConstant_L1Zgs;



    TFile *fDbkgkinSpline2e2mu = TFile::Open("/afs/cern.ch/work/f/ferrico/private/HZZ_UL/CMSSW_10_6_26/src/UFHZZAnalysisRun2/UFHZZ4LAna/data/SmoothKDConstant_m4l_Dbkgkin_2e2mu13TeV.root");
    DbkgkinSpline2e2mu = (TSpline3*) fDbkgkinSpline2e2mu->Get("sp_gr_varReco_Constant_Smooth");
    fDbkgkinSpline2e2mu->Close();
    delete fDbkgkinSpline2e2mu;
    TFile *fDbkgkinSpline4e = TFile::Open("/afs/cern.ch/work/f/ferrico/private/HZZ_UL/CMSSW_10_6_26/src/UFHZZAnalysisRun2/UFHZZ4LAna/data/SmoothKDConstant_m4l_Dbkgkin_4e13TeV.root");
    DbkgkinSpline4e = (TSpline3*) fDbkgkinSpline4e->Get("sp_gr_varReco_Constant_Smooth");
    fDbkgkinSpline4e->Close();
    delete fDbkgkinSpline4e;
    TFile *fDbkgkinSpline4mu = TFile::Open("/afs/cern.ch/work/f/ferrico/private/HZZ_UL/CMSSW_10_6_26/src/UFHZZAnalysisRun2/UFHZZ4LAna/data/SmoothKDConstant_m4l_Dbkgkin_4mu13TeV.root");
    DbkgkinSpline4mu = (TSpline3*) fDbkgkinSpline4mu->Get("sp_gr_varReco_Constant_Smooth");
    fDbkgkinSpline4mu->Close();
    delete fDbkgkinSpline4mu;

    TFile *fDbkgVBFdecSpline2l2l = TFile::Open("/afs/cern.ch/work/f/ferrico/private/HZZ_UL/CMSSW_10_6_26/src/UFHZZAnalysisRun2/UFHZZ4LAna/data/SmoothKDConstant_m4l_DbkgjjEWQCD_2l2l_JJVBFTagged_13TeV.root");
    DbkgVBFdecSpline2l2l = (TSpline3*) fDbkgVBFdecSpline2l2l->Get("sp_gr_varReco_Constant_Smooth");
    fDbkgVBFdecSpline2l2l->Close();
    delete fDbkgVBFdecSpline2l2l;
    TFile *fDbkgVBFdecSpline4l = TFile::Open("/afs/cern.ch/work/f/ferrico/private/HZZ_UL/CMSSW_10_6_26/src/UFHZZAnalysisRun2/UFHZZ4LAna/data/SmoothKDConstant_m4l_DbkgjjEWQCD_4l_JJVBFTagged_13TeV.root");
    DbkgVBFdecSpline4l = (TSpline3*) fDbkgVBFdecSpline4l->Get("sp_gr_varReco_Constant_Smooth");
    fDbkgVBFdecSpline4l->Close();
    delete fDbkgVBFdecSpline4l;

    TFile *fDbkgVHdecSpline2l2l = TFile::Open("/afs/cern.ch/work/f/ferrico/private/HZZ_UL/CMSSW_10_6_26/src/UFHZZAnalysisRun2/UFHZZ4LAna/data/SmoothKDConstant_m4l_DbkgjjEWQCD_2l2l_HadVHTagged_13TeV.root");
    DbkgVHdecSpline2l2l = (TSpline3*) fDbkgVHdecSpline2l2l->Get("sp_gr_varReco_Constant_Smooth");
    fDbkgVHdecSpline2l2l->Close();
    delete fDbkgVHdecSpline2l2l;
    TFile *fDbkgVHdecSpline4l = TFile::Open("/afs/cern.ch/work/f/ferrico/private/HZZ_UL/CMSSW_10_6_26/src/UFHZZAnalysisRun2/UFHZZ4LAna/data/SmoothKDConstant_m4l_DbkgjjEWQCD_4l_HadVHTagged_13TeV.root");
    DbkgVHdecSpline4l = (TSpline3*) fDbkgVHdecSpline4l->Get("sp_gr_varReco_Constant_Smooth");
    fDbkgVHdecSpline4l->Close();
    delete fDbkgVHdecSpline4l;

    TFile *fDjjVBFSpline = TFile::Open("/afs/cern.ch/work/f/ferrico/private/HZZ_UL/CMSSW_10_6_26/src/UFHZZAnalysisRun2/UFHZZ4LAna/data/SmoothKDConstant_m4l_DjjVBF13TeV.root");
    DjjVBFSpline = (TSpline3*) fDjjVBFSpline->Get("sp_gr_varReco_Constant_Smooth");
    fDjjVBFSpline->Close();
    delete fDjjVBFSpline;
    TFile *fDjVBFSpline = TFile::Open("/afs/cern.ch/work/f/ferrico/private/HZZ_UL/CMSSW_10_6_26/src/UFHZZAnalysisRun2/UFHZZ4LAna/data/SmoothKDConstant_m4l_DjVBF13TeV.root");
    DjVBFSpline = (TSpline3*) fDjVBFSpline->Get("sp_gr_varReco_Constant_Smooth");
    fDjVBFSpline->Close();
    delete fDjVBFSpline;

    TFile *fDjjZHSpline = TFile::Open("/afs/cern.ch/work/f/ferrico/private/HZZ_UL/CMSSW_10_6_26/src/UFHZZAnalysisRun2/UFHZZ4LAna/data/SmoothKDConstant_m4l_DjjZH13TeV.root");
    DjjZHSpline = (TSpline3*) fDjjZHSpline->Get("sp_gr_varReco_Constant_Smooth");
    fDjjZHSpline->Close();
    delete fDjjZHSpline;
    TFile *fDjjWHSpline = TFile::Open("/afs/cern.ch/work/f/ferrico/private/HZZ_UL/CMSSW_10_6_26/src/UFHZZAnalysisRun2/UFHZZ4LAna/data/SmoothKDConstant_m4l_DjjWH13TeV.root");
    DjjWHSpline = (TSpline3*) fDjjWHSpline->Get("sp_gr_varReco_Constant_Smooth");
    fDjjWHSpline->Close();
    delete fDjjWHSpline;


  cut2e2mu = 0;
  cut4e = 0;
  cut4mu = 0;
  cutghost2e2mu = 0;
  cutghost4e = 0;
  cutghost4mu = 0;
  cutLepPt2e2mu = 0;
  cutLepPt4e = 0;
  cutLepPt4mu = 0;
  cutQCD2e2mu = 0;
  cutQCD4e = 0;
  cutQCD4mu = 0;
  cutZZ2e2mu = 0;
  cutZZ4e = 0;
  cutZZ4mu = 0;
  cutm4l2e2mu = 0;
  cutm4l4e = 0;
  cutm4l4mu = 0;

}

float H4LTools::getDbkgkinConstant(int ZZflav, float ZZMass){ // ZZflav==id1*id2*id3*id4
    if (abs(ZZflav)==11*11*11*11 || abs(ZZflav)==2*11*11*11*11 || abs(ZZflav)==2*11*11*2*11*11) return DbkgkinSpline4e->Eval(ZZMass);
    if (abs(ZZflav)==11*11*13*13 || abs(ZZflav)==2*11*11*13*13 || abs(ZZflav)==2*11*11*2*13*13) return DbkgkinSpline2e2mu->Eval(ZZMass);
    if (abs(ZZflav)==13*13*13*13 || abs(ZZflav)==2*13*13*13*13 || abs(ZZflav)==2*13*13*2*13*13) return DbkgkinSpline4mu->Eval(ZZMass);
    return 0.0;
}

float H4LTools::getDbkgConstant(int ZZflav, float ZZMass){
    return getDbkgkinConstant(ZZflav, ZZMass);
}

float H4LTools::getDVBF2jetsConstant(float ZZMass){
    return DjjVBFSpline->Eval(ZZMass);
}

float H4LTools::getDVBF1jetConstant(float ZZMass){
    return DjVBFSpline->Eval(ZZMass);
}

float H4LTools::getDWHhConstant(float ZZMass){
    return DjjWHSpline->Eval(ZZMass);
}

float H4LTools::getDZHhConstant(float ZZMass){
    return DjjZHSpline->Eval(ZZMass);
}

float H4LTools::getDbkgVBFdecConstant(int ZZflav, float ZZMass) { // ZZflav==id1*id2*id3*id4
    if (abs(ZZflav)==11*11*11*11 || abs(ZZflav)==2*11*11*11*11 || abs(ZZflav)==2*11*11*2*11*11) return DbkgVBFdecSpline4l->Eval(ZZMass);
    if (abs(ZZflav)==11*11*13*13 || abs(ZZflav)==2*11*11*13*13 || abs(ZZflav)==2*11*11*2*13*13) return DbkgVBFdecSpline2l2l->Eval(ZZMass);
    if (abs(ZZflav)==13*13*13*13 || abs(ZZflav)==2*13*13*13*13 || abs(ZZflav)==2*13*13*2*13*13) return DbkgVBFdecSpline4l->Eval(ZZMass);
    return 0.0;
}

float H4LTools::getDbkgVHdecConstant(int ZZflav, float ZZMass) { // ZZflav==id1*id2*id3*id4
    if (abs(ZZflav)==11*11*11*11 || abs(ZZflav)==2*11*11*11*11 || abs(ZZflav)==2*11*11*2*11*11) return DbkgVHdecSpline4l->Eval(ZZMass);
    if (abs(ZZflav)==11*11*13*13 || abs(ZZflav)==2*11*11*13*13 || abs(ZZflav)==2*11*11*2*13*13) return DbkgVHdecSpline2l2l->Eval(ZZMass);
    if (abs(ZZflav)==13*13*13*13 || abs(ZZflav)==2*13*13*13*13 || abs(ZZflav)==2*13*13*2*13*13) return DbkgVHdecSpline4l->Eval(ZZMass);
    return 0.0;
}

#endif

