#include "../interface/H4LTools.h"
#include <TLorentzVector.h>
#include <TRandom3.h>
#include <vector>
#include "DataFormats/Math/interface/deltaR.h"

std::vector<unsigned int> H4LTools::goodLooseElectrons2012(){
    std::vector<unsigned int> LooseElectronindex;
    for (unsigned int i=0; i<Electron_pt.size(); i++){
//	    std::cout<<"FILIPPO ALL = "<<Electron_pt[i]<<"\t"<<Electron_eta[i]<<std::endl;
        if ((Electron_pt[i]>elePtcut)&&(fabs(Electron_eta[i])<eleEtacut)){
//		std::cout<<"FILIPPO "<<i<<std::endl;
            LooseElectronindex.push_back(i);
        }
    }

    return LooseElectronindex;
}

std::vector<unsigned int> H4LTools::goodLooseLowElectrons2012(){
    std::vector<unsigned int> LooseLowElectronindex;
    for (unsigned int i=0; i<LowElectron_pt.size(); i++){
        if ((LowElectron_pt[i]>3 && LowElectron_pt[i]<7) && (fabs(LowElectron_eta[i])<eleEtacut)){
            LooseLowElectronindex.push_back(i);
        }
    }

    return LooseLowElectronindex;
}


std::vector<unsigned int> H4LTools::goodLooseMuons2012(){
    std::vector<unsigned int> LooseMuonindex;
    for (unsigned int i=0; i<Muon_eta.size(); i++){
//	std::cout<<"FILIPPO ALL = "<<Muon_pt[i]<<"\t"<<Muon_eta[i]<<"\t"<<Muon_isGlobal[i]<<"\t"<<Muon_isTracker[i]<<"\t"<<Muon_isPFcand[i]<<std::endl;
        if ((Muon_pt[i]>MuPtcut)&&(fabs(Muon_eta[i])<MuEtacut)&&((Muon_isGlobal[i]||Muon_isTracker[i]||Muon_isPFcand[i]))){
            LooseMuonindex.push_back(i);
//		std::cout<<"FILIPPO --->"<<Muon_pt[i]<<"\t"<<Muon_eta[i]<<std::endl;
        }
    }

    return LooseMuonindex;
}
std::vector<unsigned int> H4LTools::goodMuons2015_noIso_noPf(std::vector<unsigned int> Muonindex){
    std::vector<unsigned int> bestMuonindex;
    for (unsigned int i=0; i<Muonindex.size(); i++){
//std::cout<<"FILIPPO ----------------> pt: "<<Muon_pt[Muonindex[i]]<<"\t nStation = "<<Muon_nStations[Muonindex[i]]<<std::endl;
//std::cout<<"FILIPPO --- "<<Muon_isGlobal[Muonindex[i]]<<"\t"<<(Muon_isTracker[Muonindex[i]] && Muon_nStations[Muonindex[i]] > 0 )<<"\t"<<Muon_isStandalone[Muonindex[i]]<<std::endl;
        if ((Muon_pt[Muonindex[i]]>MuPtcut)&&(fabs(Muon_eta[Muonindex[i]])<MuEtacut)&&(Muon_isGlobal[Muonindex[i]] || (Muon_isTracker[Muonindex[i]] && Muon_nStations[Muonindex[i]] > 0 ))){
//std::cout<<"FILIPPO ------- "<<Muon_sip3d[Muonindex[i]]<<"\t"<<fabs(Muon_dxy[Muonindex[i]])<<"\t"<<fabs(Muon_dz[Muonindex[i]])<<std::endl;
            if (Muon_sip3d[Muonindex[i]]<Musip3dCut){
                if((fabs(Muon_dxy[Muonindex[i]])<MuLoosedxycut)&&(fabs(Muon_dz[Muonindex[i]])<MuLoosedzcut)){
                    bestMuonindex.push_back(Muonindex[i]);
//			 std::cout<<"FILIPPO ----ok  --> pt: "<<Muon_pt[Muonindex[i]]<<std::endl;
                }
            }
        }
    }
    
    return bestMuonindex;
}
std::vector<unsigned int> H4LTools::goodElectrons2015_noIso_noBdt(std::vector<unsigned int> Electronindex){
    std::vector<unsigned int> bestElectronindex;
    for (unsigned int i=0; i<Electronindex.size(); i++){
        if ((Electron_pt[Electronindex[i]])>elePtcut){
            if(Electron_sip3d[Electronindex[i]]<elesip3dCut){
                if((fabs(Electron_dxy[Electronindex[i]])<eleLoosedxycut)&&(fabs(Electron_dz[Electronindex[i]])<eleLoosedzcut)){
                    bestElectronindex.push_back(Electronindex[i]);
                }
            }
        }
    }

    return bestElectronindex;
}


std::vector<unsigned int> H4LTools::goodLowElectrons2015_noIso_noBdt(std::vector<unsigned int> Electronindex){
    std::vector<unsigned int> bestLowElectronindex;
    for (unsigned int i=0; i<Electronindex.size(); i++){
        if (LowElectron_pt[Electronindex[i]] > 3 && LowElectron_pt[Electronindex[i]] < 7){
		if((fabs(LowElectron_dxy[Electronindex[i]])<eleLoosedxycut)&&(fabs(LowElectron_dz[Electronindex[i]])<eleLoosedzcut)){
                    bestLowElectronindex.push_back(Electronindex[i]);
                }
        }
    }
    return bestLowElectronindex;
}
std::vector<bool> H4LTools::passTight_BDT_Id(){
    std::vector<bool> tightid;
    float cutVal,mvaVal;
    cutVal = 1000;
    mvaVal = -1;
    //unsigned nE = (*nElectron).Get()[0];
    for (unsigned int i=0; i<Electron_pt.size(); i++){
        if(Electron_uncorrected_pt[i]<10){
            if(fabs(Electron_eta[i])<0.8) cutVal = eleBDTWPLELP;
            if((fabs(Electron_eta[i])>=0.8)&&(fabs(Electron_eta[i])<1.479)) cutVal = eleBDTWPMELP;
            if(fabs(Electron_eta[i])>=1.479) cutVal = eleBDTWPHELP;
        }
        else{
            if(fabs(Electron_eta[i])<0.8) cutVal = eleBDTWPLEHP;
            if((fabs(Electron_eta[i])>=0.8)&&(fabs(Electron_eta[i])<1.479)) cutVal = eleBDTWPMEHP;
            if(fabs(Electron_eta[i])>=1.479) cutVal = eleBDTWPHEHP;
        }

        mvaVal = Electron_mvaHZZIso[i];
//	std::cout<<"FILIPPO = "<<Electron_uncorrected_pt[i]<<"\t"<<Electron_eta[i]<<std::endl;
//	std::cout<<"FILIPPO = "<<mvaVal<<"\t"<<cutVal<<std::endl;
	if(mvaVal > cutVal){
            tightid.push_back(true);
        }
        else{
            tightid.push_back(false);
        }
    
    }
    
    return tightid;
    
}

std::vector<bool> H4LTools::passTight_BDT_Id_LowElectron(){
    std::vector<bool> tightid;
    float cutVal = 2.5; // just random value --> BDT_ID from 0 to 10
    float mvaVal = -1000;
    for (unsigned int i=0; i<LowElectron_pt.size(); i++){
//	if(LowElectron_pt[i] > 7) continue;

        mvaVal = LowElectron_ID[i];
        if(mvaVal > cutVal){
            tightid.push_back(true);
        }
        else{
            tightid.push_back(false);
        }
    }
    return tightid;
}

std::vector<bool> H4LTools::passTight_Id(){
    std::vector<bool> tightid;
    //unsigned nMu = (*nMuon).Get()[0];
    for (unsigned int i=0; i<Muon_pt.size(); i++){
        if (Muon_pt[i]<MuHighPtBound){
//            tightid.push_back(Muon_isPFcand[i]);
//		std::cout<<Muon_mva[i]<<std::endl;
		 // MVA - filippo
		if(Muon_mva[i] > -0.6){
			tightid.push_back(true);
//			std::cout<<"true"<<std::endl;
		}
		else{
			tightid.push_back(false);
//			std::cout<<"false"<<std::endl;
		}
		// MVA - filippo
        }
        else{
            tightid.push_back(Muon_isPFcand[i]||(((Muon_ptErr[i]/Muon_pt[i])<MuTightpTErrorcut)&&(fabs(Muon_dxy[i])<MuTightdxycut)&&(fabs(Muon_dz[i])<MuTightdzcut)&&(Muon_nTrackerLayers[i]>MuTightTrackerLayercut)));
        }

    }
    return tightid;
}

std::vector<unsigned int> H4LTools::goodFsrPhotons(){
    std::vector<unsigned int> goodFsrPhoton;
    //unsigned nFsr = (*nFsrPhoton).Get()[0];
    for (unsigned int i=0; i<FsrPhoton_pt.size(); i++){
//	std::cout<<"FILIPPO fsr photon = "<<i<<"\t"<<FsrPhoton_pt[i]<<"\t"<<FsrPhoton_eta[i]<<"\t"<<FsrPhoton_relIso03[i]<<"\t"<<FsrPhoton_dROverEt2[i]<<std::endl;
    	    if((FsrPhoton_pt[i]>fsrphotonPtcut)&&(fabs(FsrPhoton_eta[i])<fsrphotonEtacut)&&(FsrPhoton_relIso03[i]<fsrphotonIsocut)){
//        std::cout<<"FILIPPO fsr photon 2x = "<<i<<"\t"<<FsrPhoton_pt[i]<<"\t"<<FsrPhoton_eta[i]<<"\t"<<FsrPhoton_relIso03[i]<<"\t"<<FsrPhoton_dROverEt2[i]<<std::endl;
		if(FsrPhoton_dROverEt2[i]<fsrphotondRlOverPtcut){
//        std::cout<<"FILIPPO fsr photon 3x = "<<i<<"\t"<<FsrPhoton_pt[i]<<"\t"<<FsrPhoton_eta[i]<<"\t"<<FsrPhoton_relIso03[i]<<"\t"<<FsrPhoton_dROverEt2[i]<<std::endl;
			goodFsrPhoton.push_back(i);
//			std::cout<<"FILIPPO fsr photon 4x index = "<<i<<std::endl;
		}
	}
    }
    return goodFsrPhoton;
}

std::vector<unsigned int> H4LTools::SelectedJets(std::vector<unsigned int> ele, std::vector<unsigned int> mu){
    std::vector<unsigned int> goodJets;
    //unsigned nJ = (*nJet).Get()[0];
    for(unsigned int i=0;i<Jet_pt.size();i++){
	if(Jet_pt[i] < 50 && fabs(Jet_eta[i]) > 2.5 && fabs(Jet_eta[i]) < 3.0) continue; // to cure the horns

        if((Jet_pt[i]>JetPtcut)&&(fabs(Jet_eta[i])<JetEtacut)){
		bool Jet_passJetIdTight = false;
		if (fabs(Jet_eta[i]) <= 2.7) Jet_passJetIdTight = Jet_jetId[i] & (1 << 1);
		else if (abs(Jet_eta[i]) > 2.7 && abs(Jet_eta[i]) <= 3.0) Jet_passJetIdTight = (Jet_jetId[i] & (1 << 1)) && (Jet_neHEF[i] < 0.99);
		else if (abs(Jet_eta[i]) > 3.0) Jet_passJetIdTight = (Jet_jetId[i] & (1 << 1)) && (Jet_neEmEF[i] < 0.4);

		bool Jet_passJetIdTightLepVeto = false;
		if (abs(Jet_eta[i]) <= 2.7) Jet_passJetIdTightLepVeto = Jet_passJetIdTight && (Jet_muEF[i] < 0.8) && (Jet_chEmEF[i] < 0.8);
		else Jet_passJetIdTightLepVeto = Jet_passJetIdTight;

		if(Jet_passJetIdTightLepVeto && Jet_passJetIdTight){
//            if((Jet_jetId[i]>0)&&((Jet_pt[i]>50)||(Jet_puId[i]==7))){
                int overlaptag=0;
                TLorentzVector jettest;
                jettest.SetPtEtaPhiM(Jet_pt[i],Jet_eta[i],Jet_phi[i],Jet_mass[i]);
                for(unsigned int ie=0;ie<ele.size();ie++){
                    TLorentzVector eletest;
                    eletest.SetPtEtaPhiM(Electron_pt[ele[ie]],Electron_eta[ele[ie]],Electron_phi[ele[ie]],Electron_mass[ele[ie]]);
                    if(eletest.DeltaR(jettest)<0.4) overlaptag++;
                }
                for(unsigned int im=0;im<mu.size();im++){
                    TLorentzVector mutest;
                    mutest.SetPtEtaPhiM(Muon_pt[mu[im]],Muon_eta[mu[im]],Muon_phi[mu[im]],Muon_mass[mu[im]]);
                    if(mutest.DeltaR(jettest)<0.4) overlaptag++;
                }
                if(overlaptag==0){
                        goodJets.push_back(i);
                        if(Jet_btagDeepFlavB[i] > JetbTagcut)
                                nBtaggedjets_pt30_eta4p7++;
                }
                if(overlaptag==0){
       				if(Jet_pt[i] > 100000)
						std::cout<<"Jet_pt[i] = "<<Jet_pt[i]<<"\t Jet_eta[i] = "<<Jet_eta[i]<<"\t Jet_phi[i] = "<<Jet_phi[i]<<"\t Jet_puId[i] = "<<Jet_puId[i]<<std::endl;
                }
            }
        }
    } 
    njets_pt30_eta4p7 = goodJets.size();
//    std::cout<<"njets_pt30_eta4p7 = "<<njets_pt30_eta4p7<<std::endl;

    return goodJets;
}

unsigned H4LTools::doFsrRecovery(TLorentzVector Lep){
    // This Function returns the index for the possible FsrPhoton
    unsigned int FsrIdx = 999; //only Idx>0 works, pay attention!
    std::vector<unsigned int> BestFsrPhotons;
    BestFsrPhotons = goodFsrPhotons();
    float dRl,dRlOverPt;
    dRl = 999;
    dRlOverPt = 999;
    for(unsigned int i=0;i<BestFsrPhotons.size();i++){
        TLorentzVector fsrcand;
        fsrcand.SetPtEtaPhiM(FsrPhoton_pt[BestFsrPhotons[i]],FsrPhoton_eta[BestFsrPhotons[i]],FsrPhoton_phi[BestFsrPhotons[i]],0);
        float dRlC,dRlOverPtC;
        dRlC = fsrcand.DeltaR(Lep);
        if ((dRlC<fsrphotondRlcut)&&(FsrPhoton_dROverEt2[BestFsrPhotons[i]]<fsrphotondRlOverPtcut)){
            if(FsrPhoton_dROverEt2[BestFsrPhotons[i]]<dRlOverPt){
                dRl = dRlC;
                dRlOverPt = FsrPhoton_dROverEt2[BestFsrPhotons[i]];
                FsrIdx = BestFsrPhotons[i];
            }
        }
    }

    return FsrIdx;
    
}

std::vector<int> H4LTools::doFsrRecovery_Run3(std::vector<unsigned int> goodfsridx, unsigned lepidx, int lepflavor){//lepflavor 11 or 13
	    
	std::vector<int> matchedfsridx;
//	std::cout<<"FILIPPO: goodfsridx.size() = "<<goodfsridx.size()<<std::endl;
	for(unsigned fsridx=0; fsridx<goodfsridx.size(); fsridx++){
//		std::cout<<"FILIPPO: fsridx = "<<fsridx<<"\tph_pt = "<<FsrPhoton_pt[goodfsridx.at(fsridx)]<<"\t eta = "<<FsrPhoton_eta[goodfsridx.at(fsridx)]<<"\t ph_phi = "<<FsrPhoton_phi[goodfsridx.at(fsridx)]<<"\t goodfsridx.at(fsridx) = "<<goodfsridx.at(fsridx)<<std::endl;
		float deltaR_min = 999;
			int flavour = 999;
			int lepton_index = 999;
			int photon_index = 999;
			int photon_deltaR_Egamma = 999;

			for(unsigned int iele = 0; iele<Eid.size(); iele++){
//				if(lep_pt.at(iele) > 7 && lep_eta.at(iele) != Electron_eta[Electronindex[iele]])
//					std::cout<<"FILIPPO: problema con eta"<<std::endl;
//				if(lep_pt.at(iele) > 7 && lep_phi.at(iele) != Electron_phi[Electronindex[iele]])
//					std::cout<<"FILIPPO: problema con phi"<<std::endl;
//				if(lep_pt.at(iele) < 7)
//					std::cout<<"FILIPPO: pt < 7"<<std::endl;
//				if (!TMath::Finite(Electron_phi[Electronindex[iele]])|| !TMath::Finite(FsrPhoton_phi[goodfsridx.at(fsridx)])){
//        		                std::cout<<Electron_eta[Electronindex[iele]]<<"\t"<<Electron_phi[Electronindex[iele]]<<"\t"<<FsrPhoton_eta[goodfsridx.at(fsridx)]<<"\t"<<FsrPhoton_phi[goodfsridx.at(fsridx)]<<std::endl;
//	        	        } 
				float DeltaR_tmp = deltaR(lep_eta.at(iele), lep_phi.at(iele), FsrPhoton_eta[goodfsridx.at(fsridx)], FsrPhoton_phi[goodfsridx.at(fsridx)]);
//				float DeltaR_tmp = deltaR(Electron_eta[Electronindex[iele]], Electron_phi[Electronindex[iele]], FsrPhoton_eta[goodfsridx.at(fsridx)], FsrPhoton_phi[goodfsridx.at(fsridx)]);
				if(DeltaR_tmp < deltaR_min){
					deltaR_min = DeltaR_tmp;
					flavour = 11;
					lepton_index = iele;
					photon_index = goodfsridx.at(fsridx);
				}
			}

//			std::cout<<"FILIPPO: muid.size() = "<<muid.size()<<std::endl;
			for(unsigned int imu=0; imu<muid.size();imu++){
//				std::cout<<"FILIPPO: imu = "<<imu<<std::endl;
                                if (!TMath::Finite(Muon_phi[Muonindex[imu]])|| !TMath::Finite(FsrPhoton_phi[goodfsridx.at(fsridx)])){
                                        std::cout<<Muon_eta[Muonindex[imu]]<<"\t"<<Muon_phi[Muonindex[imu]]<<"\t"<<FsrPhoton_eta[goodfsridx.at(fsridx)]<<"\t"<<FsrPhoton_phi[goodfsridx.at(fsridx)]<<std::endl;
                                }
				float DeltaR_tmp = deltaR(Muon_eta[Muonindex[imu]], Muon_phi[Muonindex[imu]], FsrPhoton_eta[goodfsridx.at(fsridx)], FsrPhoton_phi[goodfsridx.at(fsridx)]);
//				std::cout<<"FILIPPO: Muon_eta[Muonindex[imu]] = "<<Muon_eta[Muonindex[imu]]<<"\t Muon_phi[Muonindex[imu]] = "<<Muon_phi[Muonindex[imu]]<<"\t FsrPhoton_eta[goodfsridx.at(fsridx)] = "<<FsrPhoton_eta[goodfsridx.at(fsridx)]<<"\t FsrPhoton_phi[goodfsridx.at(fsridx)] = "<<FsrPhoton_phi[goodfsridx.at(fsridx)]<<std::endl;
//				std::cout<<"FILIPPO: imu = "<<imu<<"\tdeltaR_min = "<<deltaR_min<<"\t DeltaR_tmp = "<<DeltaR_tmp<<std::endl;
				if(DeltaR_tmp < deltaR_min){
//                                        std::cout<<"FILIPPO: imu = "<<imu<<"\tdeltaR_min = "<<deltaR_min<<"\t DeltaR_tmp = "<<DeltaR_tmp<<std::endl;
					deltaR_min = DeltaR_tmp;
					flavour = 13;
					lepton_index = imu;
					photon_index = goodfsridx.at(fsridx);
				}
			}
//			std::cout<<"FILIPPO: deltaR_min = "<<deltaR_min<<std::endl;
			if(deltaR_min < 0.5){
//				std::cout<<"FILIPPO: flavour = "<<flavour<<"\t lepton_index = "<<lepton_index<<"\t photon_index = "<<photon_index<<std::endl;
//				if(fsridx == 0){
				if(matchedfsridx.size() == 0){
//					std::cout<<"FILIPPO matchedfsridx.size() == 0"<<std::endl;
					matchedfsridx.push_back(flavour);
					matchedfsridx.push_back(lepton_index);
					matchedfsridx.push_back(photon_index);
				}
				else{
//					std::cout<<"FILIPPO: FsrPhoton_dROverEt2[goodfsridx.at(fsridx)] = "<<FsrPhoton_dROverEt2[goodfsridx.at(fsridx)]<<"\t FsrPhoton_dROverEt2[matchedfsridx.at(2)] = "<< FsrPhoton_dROverEt2[matchedfsridx.at(2)]<<std::endl;
					if(matchedfsridx.at(0) == flavour && matchedfsridx.at(1) == lepton_index){
						if(FsrPhoton_dROverEt2[goodfsridx.at(fsridx)] < FsrPhoton_dROverEt2[matchedfsridx.at(2)]){
							matchedfsridx.clear();
							matchedfsridx.push_back(flavour);
							matchedfsridx.push_back(lepton_index);
							matchedfsridx.push_back(photon_index);
						}
					}
					else{
					        matchedfsridx.push_back(flavour);
                                                matchedfsridx.push_back(lepton_index);
                                        	matchedfsridx.push_back(photon_index);
					}
				}
			}
	}
//	std::cout<<"FILIPPO =========== matchedfsridx.size = "<<matchedfsridx.size()<<std::endl;
//	for(std::size_t i = 0 ; i < matchedfsridx.size(); i++){
//		std::cout<<"FILIPPO ==========================\t";
//		std::cout<<"matchedfsridx.at("<<i<<") = "<<matchedfsridx.at(i)<<std::endl;
//	}

	/*
     
	if(lepflavor == 11){
//          std::cout<<"FILIPPO ELE doRecovery"<<std::endl;
        for(unsigned fsridx=0; fsridx<goodfsridx.size(); fsridx++){
//			std::cout<<"FILIPPO ele fsridx = "<<fsridx<<"\t Eid size = "<<Eid.size()<<std::endl;
			float deltaR_min = 999;
			unsigned eletmp = 999;
			unsigned phtmp = 999;
			for(unsigned int iele = 0; iele<Eid.size(); iele++){
//                            std::cout<<"FILIPPO etaFSR electron = "<<Electron_pt[Electronindex[iele]]<<"\t"<<Electron_eta[Electronindex[iele]]<<"\t"<<Electron_phi[Electronindex[iele]]<<"\t"<<iele<<std::endl;
//			    std::cout<<"FILIPPO etaFSR photon = "<<FsrPhoton_pt[fsridx]<<"\t"<<FsrPhoton_eta[fsridx]<<"\t"<<FsrPhoton_phi[fsridx]<<"\t"<<fsridx<<std::endl;
			    float DeltaR = deltaR(Electron_eta[Electronindex[iele]], Electron_phi[Electronindex[iele]], FsrPhoton_eta[fsridx], FsrPhoton_phi[fsridx]);
//                                std::cout<<"FILIPPO = deltaR "<<DeltaR<<"\t"<<deltaR_min<<std::endl;
                            if(DeltaR < deltaR_min){
                                        deltaR_min = DeltaR;
                                        eletmp = iele;
					phtmp = fsridx;
			    }
                        }
//			std::cout<<"FILIPPO = "<<fsridx<<"\t"<<eletmp<<std::endl;
			matchedfsridx.push_back(eletmp);
			if(fsridx > 0 && matchedfsridx.size() > 0 && matchedfsridx.at(0) == eletmp){
                                std::cout<<"ELE x 2"<<std::endl;
                                if(FsrPhoton_dROverEt2[fsridx] < FsrPhoton_dROverEt2[phtmp])
	                                matchedfsridx.push_back(fsridx);
                                std::cout<<"FILIPPO Stored = "<<FsrPhoton_dROverEt2[phtmp]<<"\t new = "<<FsrPhoton_dROverEt2[fsridx]<<"\tfsridx = "<<fsridx<<"\tmatchedfsridx.size = "<<matchedfsridx.size()<<"\tgoodfsridx.size() = "<<goodfsridx.size()<<std::endl;
			}
	}
    }


   if(lepflavor == 13){
//          std::cout<<"FILIPPO MUON doRecovery"<<std::endl;
        for(unsigned fsridx=0; fsridx<goodfsridx.size(); fsridx++){
			float deltaR_min = 999;
                        unsigned mutmp = 999;
                        unsigned phtmp = 999;
			for(unsigned int imu=0; imu<muid.size();imu++){
//			    std::cout<<"FILIPPO etaFSR muon = "<<Muon_pt[Muonindex[imu]]<<"\t"<<Muon_eta[Muonindex[imu]]<<"\t"<<Muon_phi[Muonindex[imu]]<<"\t"<<imu<<std::endl;
//			    std::cout<<"FILIPPO etaFSR photon = "<<FsrPhoton_pt[fsridx]<<"\t"<<FsrPhoton_eta[fsridx]<<"\t"<<FsrPhoton_phi[fsridx]<<"\t"<<fsridx<<std::endl;
			    float DeltaR = deltaR(Muon_eta[Muonindex[imu]], Muon_phi[Muonindex[imu]], FsrPhoton_eta[fsridx], FsrPhoton_phi[fsridx]);
//				std::cout<<"FILIPPO = deltaR "<<DeltaR<<"\t"<<deltaR_min<<std::endl;
			    if(DeltaR < deltaR_min){
					deltaR_min = DeltaR;
					 mutmp = imu;
                                        phtmp = fsridx;
				}
			}
//                        std::cout<<"FILIPPO = "<<fsridx<<"\t"<<mutmp<<std::endl;
                        matchedfsridx.push_back(mutmp);
                        if(fsridx > 0 && matchedfsridx.size() > 0 && matchedfsridx.at(0) == mutmp){
				std::cout<<"MUON x 2"<<std::endl;
				if(FsrPhoton_dROverEt2[fsridx] < FsrPhoton_dROverEt2[phtmp])
                                        matchedfsridx.push_back(fsridx);
				std::cout<<"FILIPPO Stored = "<<FsrPhoton_dROverEt2[phtmp]<<"\t new = "<<FsrPhoton_dROverEt2[fsridx]<<"\tfsridx = "<<fsridx<<"\tmatchedfsridx.size = "<<matchedfsridx.size()<<"\tgoodfsridx.size() = "<<goodfsridx.size()<<std::endl;
                        }

//			std::cout<<"FILIPPO = "<<fsridx<<"\t"<<mutmp<<std::endl;
    	}
	}
*/
/*
   if(lepflavor == 11){
        for(unsigned fsridx=0; fsridx<goodfsridx.size(); fsridx++){
            if(FsrPhoton_electronIdx[goodfsridx[fsridx]] == lepidx){
                matchedfsridx = fsridx;
                break;
            }
        }
    }
    if(lepflavor == 13){
//	    std::cout<<"FILIPPO MUON"<<std::endl;
        for(unsigned fsridx=0; fsridx<goodfsridx.size(); fsridx++){
//		std::cout<<"FILIPPO fsridx = "<<fsridx<<std::endl;
		if(FsrPhoton_muonIdx[goodfsridx[fsridx]] == lepidx){
//                std::cout<<"FILIPPO = "<<FsrPhoton_muonIdx[goodfsridx[fsridx]]<<"\t = FsrPhoton_muonIdx[goodfsridx[fsridx]]"<<std::endl;
                matchedfsridx = fsridx;
                break;
            }
        }
    }
*/
   return matchedfsridx;
}
void H4LTools::BatchFsrRecovery_Run3(){
    unsigned fsridx = 999;
    std::vector<unsigned> fsrlist;
    fsrlist = goodFsrPhotons();

    for(unsigned int i=0; i<Electron_pt.size(); i++){
        TLorentzVector fsr,lep;
        lep.SetPtEtaPhiM(Electron_pt[i],Electron_eta[i],Electron_phi[i],Electron_mass[i]);
//        std::cout<<"FILIPPO for dressing electron\t"<<i<<std::endl;
        //fsridx = doFsrRecovery_Run3(fsrlist,i,11);
//        std::cout<<"FILIPPO for dressing fsridx = "<<fsridx<<std::endl;
//        if(fsridx<900){
	if(fsridx == i){
            fsr.SetPtEtaPhiM(FsrPhoton_pt[fsrlist[fsridx]], FsrPhoton_eta[fsrlist[fsridx]], FsrPhoton_phi[fsrlist[fsridx]], 0);
            lep = lep + fsr;
            Electrondressed_Run3.push_back(lep);
        }
        else{
            Electrondressed_Run3.push_back(lep);
        }
    }
//    std::cout<<"FILIPPO ---------- "<<std::endl;


    std::vector<int> fsr_list;
    for(unsigned int j=0; j<Muon_pt.size(); j++){
        TLorentzVector fsr,lep;
        lep.SetPtEtaPhiM(Muon_pt[j],Muon_eta[j],Muon_phi[j],Muon_mass[j]);
//	std::cout<<"FILIPPO for dressing muon\t"<<j<<std::endl;
	//fsridx = doFsrRecovery_Run3(fsrlist,j,13);
//	std::cout<<"FILIPPO for dressing fsridx = "<<fsridx<<std::endl;
//        if(fsridx<900){
	if(fsridx == j){
            fsr.SetPtEtaPhiM(FsrPhoton_pt[fsrlist[fsridx]], FsrPhoton_eta[fsrlist[fsridx]], FsrPhoton_phi[fsrlist[fsridx]], 0);
            lep = lep + fsr;
            Muondressed_Run3.push_back(lep);
            fsr_list.push_back(fsridx);
        }
        else{
            Muondressed_Run3.push_back(lep);
        }
    }
//    std::cout<<"FILIPPO ---------- "<<std::endl;

//// fsr for Run 2 including Low electron
    for(unsigned int i=1; i<Electron_pt.size(); i++){
        TLorentzVector fsr,lep;
        lep.SetPtEtaPhiM(Electron_pt[i],Electron_eta[i],Electron_phi[i],Electron_mass[i]);
	int j_fsr = -1;
	for(std::size_t j = 0; j < FsrPhoton_pt.size(); j++){
		int already = false;
		for(std::size_t k = 0; k < fsr_list.size(); k++){
			if(j == fsr_list[k]) already = true;
		}
		if(already) continue;
                if (!TMath::Finite(Electron_phi[i])|| !TMath::Finite(FsrPhoton_phi[j])){
                        std::cout<<Electron_eta[i]<<"\t"<<Electron_phi[i]<<"\t"<<FsrPhoton_eta[j]<<"\t"<<FsrPhoton_phi[j]<<std::endl;
                }		
		float DeltaR = deltaR(Electron_eta[i], Electron_phi[i], FsrPhoton_eta[j], FsrPhoton_phi[j]);

		if(DeltaR > 0.5) continue;
		if(FsrPhoton_dROverEt2[j] > 0.012) continue;
		if(FsrPhoton_relIso03[j] > 1.8) continue;
		if(FsrPhoton_pt[j] < 2 || fabs(FsrPhoton_eta[j]) < 2.5) continue;
		fsr.SetPtEtaPhiM(FsrPhoton_pt[j], FsrPhoton_eta[j], FsrPhoton_phi[j], 0);
	}
	if(j_fsr != -1){
	        lep = lep + fsr;
        	Electrondressed_Run3.push_back(lep);
		fsr_list.push_back(j_fsr);
        }
        else{
            Electrondressed_Run3.push_back(lep);
        }
    }
    for(unsigned int i=0; i<LowElectron_pt.size(); i++){
	if(LowElectron_pt[i] > 7) continue;

        TLorentzVector fsr,lep;
        lep.SetPtEtaPhiM(LowElectron_pt[i],LowElectron_eta[i],LowElectron_phi[i],LowElectron_mass[i]);
        int j_fsr = -1;
        for(std::size_t j = 0; j < FsrPhoton_pt.size(); j++){
                int already = false;
                for(std::size_t k = 0; k < fsr_list.size(); k++){
                        if(j == fsr_list[k]) already = true;
                }
                if(already) continue;

                float DeltaR = deltaR(LowElectron_eta[i], LowElectron_phi[i], FsrPhoton_eta[j], FsrPhoton_phi[j]);
                if (!TMath::Finite(LowElectron_phi[i])|| !TMath::Finite(FsrPhoton_phi[j])){
                        std::cout<<"low = "<<LowElectron_eta[i]<<"\t"<<LowElectron_phi[i]<<"\t"<<FsrPhoton_eta[j]<<"\t"<<FsrPhoton_phi[j]<<std::endl;      
                }
                if (!TMath::Finite(LowElectron_eta[i])|| !TMath::Finite(FsrPhoton_eta[j])){
                        std::cout<<"eta low = "<<LowElectron_eta[i]<<"\t"<<LowElectron_phi[i]<<"\t"<<FsrPhoton_eta[j]<<"\t"<<FsrPhoton_phi[j]<<std::endl;
                }       

                if(DeltaR > 0.5) continue;
                if(FsrPhoton_dROverEt2[j] > 0.012) continue;
                if(FsrPhoton_relIso03[j] > 1.8) continue;
                if(FsrPhoton_pt[j] < 2 || fabs(FsrPhoton_eta[j]) < 2.5) continue;
                fsr.SetPtEtaPhiM(FsrPhoton_pt[j], FsrPhoton_eta[j], FsrPhoton_phi[j], 0);
        }
        if(j_fsr != -1){
                lep = lep + fsr;
                LowElectrondressed_Run3.push_back(lep);
                std::cout<<"low j ok = "<<j_fsr<<std::endl;
        }
        else{
            LowElectrondressed_Run3.push_back(lep);
        }
    }
//// fsr for Run 2 including Low electron


}
/*
std::vector<TLorentzVector> H4LTools::BatchFsrRecovery(std::vector<TLorentzVector> LepList){
    
    std::vector<TLorentzVector> LepFsrList;
    
    for(unsigned int i=0;i<LepList.size();i++){
        int Fsrtag;
        Fsrtag = doFsrRecovery(LepList[i]);
        if (Fsrtag>900){
            LepFsrList.push_back(LepList[i]);
            continue;
        }
        TLorentzVector FsrPhoton;
        FsrPhoton.SetPtEtaPhiM(FsrPhoton_pt[Fsrtag],FsrPhoton_eta[Fsrtag],FsrPhoton_phi[Fsrtag],0);
        TLorentzVector LepFsrRecovery;
        LepFsrRecovery = FsrPhoton + LepList[i];
        LepFsrList.push_back(LepFsrRecovery);
    }
    return LepFsrList;
}
*/
/*
std::vector<TLorentzVector> H4LTools::ElectronFsr(){
    std::vector<TLorentzVector> leplist;
    std::vector<TLorentzVector> leplistfsr;
    //unsigned nlep = (*nElectron).Get()[0];
    for(unsigned int i=0;i<Electron_pt.size();i++){
        TLorentzVector Lep;
        Lep.SetPtEtaPhiM(Electron_pt[i],Electron_eta[i],Electron_phi[i],Electron_mass[i]);
        leplist.push_back(Lep);
    }
    leplistfsr = BatchFsrRecovery(leplist);
    return leplistfsr;
}

std::vector<TLorentzVector> H4LTools::MuonFsr(){
    std::vector<TLorentzVector> leplist;
    std::vector<TLorentzVector> leplistfsr;
    //unsigned nlep = (*nMuon).Get()[0];
    for(unsigned int i=0;i<Muon_pt.size();i++){
        TLorentzVector Lep;
        Lep.SetPtEtaPhiM(Muon_pt[i],Muon_eta[i],Muon_phi[i],Muon_mass[i]);
        leplist.push_back(Lep);
    }
    leplistfsr = BatchFsrRecovery(leplist);
    return leplistfsr;
}

std::vector<float> H4LTools::ElectronFsrPt(){
    std::vector<float> lepPt;
    for (unsigned int i=0;i<Electrondressed_Run3.size();i++){
        lepPt.push_back(Electrondressed_Run3[i].Pt());
    }
    return lepPt;
}

std::vector<float> H4LTools::ElectronFsrEta(){
    std::vector<float> lepEta;
    for (unsigned int i=0;i<Electrondressed_Run3.size();i++){
        lepEta.push_back(Electrondressed_Run3[i].Eta());
    }
    return lepEta;
}

std::vector<float> H4LTools::ElectronFsrPhi(){
    std::vector<float> lepPhi;
    for (unsigned int i=0;i<Electrondressed_Run3.size();i++){
        lepPhi.push_back(Electrondressed_Run3[i].Phi());
    }
    return lepPhi;
}
*/
/*
std::vector<float> H4LTools::MuonFsrPt(){
    std::vector<float> lepPt;
    for (unsigned int i=0;i<Muondressed_Run3.size();i++){
        lepPt.push_back(Muondressed_Run3[i].Pt());
    }
    return lepPt;
}

std::vector<float> H4LTools::MuonFsrEta(){
    std::vector<float> lepEta;
    for (unsigned int i=0;i<Muondressed_Run3.size();i++){
        lepEta.push_back(Muondressed_Run3[i].Eta());
    }
    return lepEta;
}

std::vector<float> H4LTools::MuonFsrPhi(){
    std::vector<float> lepPhi;
    for (unsigned int i=0;i<Muondressed_Run3.size();i++){
        lepPhi.push_back(Muondressed_Run3[i].Phi());
    }
    return lepPhi;
}
*/
/*std::vector<float> H4LTools::ElectronFsrPt(){
    std::vector<float> lepPt;
    std::vector<TLorentzVector> leplistfsr;
    leplistfsr = ElectronFsr();
    for (unsigned int i=0;i<leplistfsr.size();i++){
        lepPt.push_back(leplistfsr[i].Pt());
    }
    return lepPt;
}

std::vector<float> H4LTools::ElectronFsrEta(){
    std::vector<float> lepEta;
    std::vector<TLorentzVector> leplistfsr;
    leplistfsr = ElectronFsr();
    for (unsigned int i=0;i<leplistfsr.size();i++){
        lepEta.push_back(leplistfsr[i].Eta());
    }
    return lepEta;
}

std::vector<float> H4LTools::ElectronFsrPhi(){
    std::vector<float> lepPhi;
    std::vector<TLorentzVector> leplistfsr;
    leplistfsr = ElectronFsr();
    for (unsigned int i=0;i<leplistfsr.size();i++){
        lepPhi.push_back(leplistfsr[i].Phi());
    }
    return lepPhi;
}

std::vector<float> H4LTools::MuonFsrPt(){
    std::vector<float> lepPt;
    std::vector<TLorentzVector> leplistfsr;
    leplistfsr = MuonFsr();
    for (unsigned int i=0;i<leplistfsr.size();i++){
        lepPt.push_back(leplistfsr[i].Pt());
    }
    return lepPt;
}

std::vector<float> H4LTools::MuonFsrEta(){
    std::vector<float> lepEta;
    std::vector<TLorentzVector> leplistfsr;
    leplistfsr = MuonFsr();
    for (unsigned int i=0;i<leplistfsr.size();i++){
        lepEta.push_back(leplistfsr[i].Eta());
    }
    return lepEta;
}

std::vector<float> H4LTools::MuonFsrPhi(){
    std::vector<float> lepPhi;
    std::vector<TLorentzVector> leplistfsr;
    leplistfsr = MuonFsr();
    for (unsigned int i=0;i<leplistfsr.size();i++){
        lepPhi.push_back(leplistfsr[i].Phi());
    }
    return lepPhi;
}*/

void H4LTools::LeptonSelection(){
    looseEle = goodLooseElectrons2012();
    looseLowEle = goodLooseLowElectrons2012();
    looseMu = goodLooseMuons2012();

    bestEle = goodElectrons2015_noIso_noBdt(looseEle);
    bestLowEle = goodLowElectrons2015_noIso_noBdt(looseLowEle);
    bestMu = goodMuons2015_noIso_noPf(looseMu);

    Electronindex = bestEle;
    LowElectronindex = bestLowEle;
    Muonindex = bestMu;

    AllEid = passTight_BDT_Id();
    AllLowEid = passTight_BDT_Id_LowElectron();
    AllMuid = passTight_Id();

    for (unsigned int iuj=0;iuj<looseEle.size();iuj++){
        if(AllEid[looseEle[iuj]]) tighteleforjetidx.push_back(looseEle[iuj]);
    }
    for (unsigned int juj=0;juj<looseMu.size();juj++){
        if(AllMuid[looseMu[juj]]) tightmuforjetidx.push_back(looseMu[juj]);
    }
    jetidx = SelectedJets(tighteleforjetidx,tightmuforjetidx);
//    std::cout<<"jetidx = "<<jetidx.size()<<std::endl;

    for(unsigned int ie=0; ie<Electronindex.size();ie++){
        if(Electron_pdgId[Electronindex[ie]]>0){
            Elechg.push_back(-1);
        }
        else{
            Elechg.push_back(1);
        }
        TLorentzVector Ele;
        Ele.SetPtEtaPhiM(Electron_pt[Electronindex[ie]],Electron_eta[Electronindex[ie]],Electron_phi[Electronindex[ie]],Electron_mass[Electronindex[ie]]);
        Elelist.push_back(Ele);
        //ElelistFsr.push_back(Electrondressed_Run3[Electronindex[ie]]);
        Eiso.push_back(Electron_pfRelIso03_all[Electronindex[ie]]);
        Eid.push_back(AllEid[Electronindex[ie]]);
        lep_RelIsoNoFSR.push_back(-1234);
        lep_pt.push_back(Electron_pt[Electronindex[ie]]);
	lep_ptError.push_back(Electron_energyErr[Electronindex[ie]]);
	lep_eta.push_back(Electron_eta[Electronindex[ie]]);
        lep_phi.push_back(Electron_phi[Electronindex[ie]]);
        lep_mass.push_back(Electron_mass[Electronindex[ie]]);
        lep_id.push_back(Electron_pdgId[Electronindex[ie]]);
        lep_looseId.push_back(AllEid[Electronindex[ie]]);
	lep_ptVXBS.push_back(Electron_pt[Electronindex[ie]]);
	lep_ptErrorVXBS.push_back(Electron_energyErr[Electronindex[ie]]);
        lep_lowEleBDT.push_back(-999);
	lep_inTimeMuon.push_back(0);
        lep_timeAtIpInOut.push_back(-999);
        lep_timeAtIpInOutErr.push_back(-999);
        lep_timeAtIpOutIn.push_back(-999);
        lep_timeAtIpOutInErr.push_back(-999);
        lep_inverseBeta.push_back(-999);
        lep_inverseBetaErr.push_back(-999);

    }

    for(unsigned int ie=0; ie<LowElectronindex.size();ie++){ //lowPtInclusion ////FILIPPO
        if(LowElectron_pdgId[LowElectronindex[ie]]>0){
            Elechg.push_back(-1);
        }
        else{
            Elechg.push_back(1);
        }
	TLorentzVector Ele;
        Ele.SetPtEtaPhiM(LowElectron_pt[LowElectronindex[ie]],LowElectron_eta[LowElectronindex[ie]],LowElectron_phi[LowElectronindex[ie]],LowElectron_mass[LowElectronindex[ie]]);
        Elelist.push_back(Ele);
        //ElelistFsr.push_back(LowElectrondressed_Run3[Electronindex[ie]]);
        Eiso.push_back(LowElectron_miniPFRelIso_all[LowElectronindex[ie]]);
        Eid.push_back(AllLowEid[LowElectronindex[ie]]);
        lep_RelIsoNoFSR.push_back(-1234);
        lep_pt.push_back(LowElectron_pt[LowElectronindex[ie]]);
        lep_ptError.push_back(LowElectron_energyErr[LowElectronindex[ie]]);
        lep_eta.push_back(LowElectron_eta[LowElectronindex[ie]]);
        lep_phi.push_back(LowElectron_phi[LowElectronindex[ie]]);
        lep_mass.push_back(LowElectron_mass[LowElectronindex[ie]]);
        lep_id.push_back(LowElectron_pdgId[LowElectronindex[ie]]);
        lep_looseId.push_back(AllLowEid[LowElectronindex[ie]]);
        lep_ptVXBS.push_back(LowElectron_pt[LowElectronindex[ie]]);
        lep_ptErrorVXBS.push_back(LowElectron_energyErr[LowElectronindex[ie]]);
	lep_lowEleBDT.push_back(LowElectron_ID[LowElectronindex[ie]]);
	lep_inTimeMuon.push_back(0);
        lep_timeAtIpInOut.push_back(-999);
        lep_timeAtIpInOutErr.push_back(-999);
        lep_timeAtIpOutIn.push_back(-999);
        lep_timeAtIpOutInErr.push_back(-999);
        lep_inverseBeta.push_back(-999);
        lep_inverseBetaErr.push_back(-999);
    }


    for(unsigned int imu=0; imu<Muonindex.size();imu++){
        muid.push_back(AllMuid[Muonindex[imu]]);
    }

    std::vector<int> FsrIdx;
    FsrIdx = doFsrRecovery_Run3(goodFsrPhotons(),0,0);
    int flavour_fsr = 999;
    int lepton_index = 999;
    int fsr_index = 999;
    if(FsrIdx.size() > 0){
	flavour_fsr = FsrIdx.at(0);
       	lepton_index = FsrIdx.at(1);
       	fsr_index = FsrIdx.at(2);
    }

    for(std::size_t imu=0; imu<Muonindex.size();imu++){
        if(Muon_pdgId[Muonindex[imu]]>0){
            Muchg.push_back(-1);
//        std::cout<<"FILIPPO PT = "<<Muon_pt[Muonindex[imu]]<<"\t"<<Muon_pdgId[Muonindex[imu]]<<"\t-1"<<std::endl;
        }
        else{
            Muchg.push_back(1);
//        std::cout<<"FILIPPO PT = "<<Muon_pt[Muonindex[imu]]<<"\t"<<Muon_pdgId[Muonindex[imu]]<<"\t1"<<std::endl;
        }
        TLorentzVector Mu;
        Mu.SetPtEtaPhiM(Muon_pt[Muonindex[imu]],Muon_eta[Muonindex[imu]],Muon_phi[Muonindex[imu]],Muon_mass[Muonindex[imu]]);
	Mulist.push_back(Mu);
        //MulistFsr.push_back(Muondressed_Run3[Muonindex[imu]]);
//        muid.push_back(AllMuid[Muonindex[imu]]);
//	std::cout<<"FILIPPO = MuIso = "<<Muon_pfRelIso03_all[Muonindex[imu]]<<std::endl;
//	Muiso.push_back(Muon_pfRelIso03_all[Muonindex[imu]]);
        Mumva.push_back(Muon_mva[Muonindex[imu]]);
        lep_pt.push_back(Muon_pt[Muonindex[imu]]);
	lep_ptError.push_back(Muon_ptErr[Muonindex[imu]]);
	lep_eta.push_back(Muon_eta[Muonindex[imu]]);
        lep_phi.push_back(Muon_phi[Muonindex[imu]]);
        lep_mass.push_back(Muon_mass[Muonindex[imu]]);
        lep_id.push_back(Muon_pdgId[Muonindex[imu]]);
        lep_looseId.push_back(AllMuid[Muonindex[imu]]); //passing for FR
        lep_ptVXBS.push_back(Muon_bsConstrainedPt[Muonindex[imu]]);
	lep_ptErrorVXBS.push_back(Muon_bsConstrainedPtErr[Muonindex[imu]]);
        lep_lowEleBDT.push_back(-999);
	lep_inTimeMuon.push_back(Muon_inTimeMuon[Muonindex[imu]]);
	//////////// -----> time information
	lep_timeAtIpInOut.push_back(-999);
        lep_timeAtIpInOutErr.push_back(-999);
        lep_timeAtIpOutIn.push_back(-999);
        lep_timeAtIpOutInErr.push_back(-999);
        lep_inverseBeta.push_back(-999);
        lep_inverseBetaErr.push_back(-999);
        //////////// -----> time information
	/*
        lep_timeAtIpInOut.push_back(Muon_timeAtIpInOut[Muonindex[imu]]);
        lep_timeAtIpInOutErr.push_back(Muon_timeAtIpInOutErr[Muonindex[imu]]);
        lep_timeAtIpOutIn.push_back(Muon_timeAtIpOutIn[Muonindex[imu]]);
        lep_timeAtIpOutInErr.push_back(Muon_timeAtIpOutInErr[Muonindex[imu]]);
        lep_inverseBeta.push_back(Muon_inverseBeta[Muonindex[imu]]);
        lep_inverseBetaErr.push_back(Muon_inverseBetaErr[Muonindex[imu]]);
	*/
	float RelIsoNoFsr;
        RelIsoNoFsr = Muon_pfRelIso03_all[Muonindex[imu]];//Muiso[imu];
//	std::cout<<"FILIPPO RelIsoNoFsr = "<<RelIsoNoFsr<<"\t"<<imu<<std::endl;
//	std::cout<<"FILIPPO beforemuoniso"<<std::endl;
        bool already = false;
	if (isFSR && flavour_fsr < 999){
		for(std::size_t j = 0; j < FsrIdx.size(); j=j+3){
			if(FsrIdx.at(j) == 13 && FsrIdx.at(j+1) == imu){
                            already = 1;
			    fsr_index = FsrIdx.at(j+2);
		            TLorentzVector fsrmuon, nofsrmuon, dressedmuon;
        		    fsrmuon.SetPtEtaPhiM(FsrPhoton_pt.at(fsr_index),FsrPhoton_eta.at(fsr_index),FsrPhoton_phi.at(fsr_index),0);
		            nofsrmuon.SetPtEtaPhiM(Mulist[imu].Pt(),Mulist[imu].Eta(),Mulist[imu].Phi(),Mulist[imu].M());
//		    std::cout<<"FILIPPO delta R = "<<Mulist[imu].DeltaR(fsrmuon)<<std::endl;
			    if(Mulist[imu].DeltaR(fsrmuon)>0.01){
				float CHARGED = Muon_pfRelIso03_chg[Muonindex[imu]];
				float NEUTRAL = Muon_pfRelIso03_all[Muonindex[imu]] - CHARGED;
//     	         	std::cout<<"FILIPPO CHARGED = "<<CHARGED<<"\t NEUTRAL = "<<NEUTRAL<<std::endl;
//      	        std::cout<<"FILIPPO = "<<FsrPhoton_pt[ph]<<"\t"<<Mulist[imu].Pt()<<std::endl;
//			std::cout<<"FILIPPO RelIso = "<<RelIsoNoFsr<<"\t FSR contribution = "<<FsrPhoton_pt[ph]/Mulist[imu].Pt()<<std::endl;
				if(NEUTRAL <= 0){
//				std::cout<<"FILIPPO NEUTRAL <= 0: = "<<RelIsoNoFsr<<"\t as check: CHARGED = "<<CHARGED<<std::endl;
					lep_RelIsoNoFSR.push_back(Muon_pfRelIso03_all[Muonindex[imu]]);
					Muiso.push_back(Muon_pfRelIso03_all[Muonindex[imu]]);
//				std::cout<<"FILIPPO VALUE STORED = "<<Muon_pfRelIso03_all[Muonindex[imu]]<<std::endl;
				}
				else{
					float NEUTRAL_FSR = NEUTRAL - FsrPhoton_pt.at(fsr_index)/Mulist[imu].Pt();
//				std::cout<<"FILIPPO NEUTRAL NOT NEGATIVE: check FSR = "<<NEUTRAL_FSR<<std::endl;
					if(NEUTRAL_FSR < 0){
//					std::cout<<"FILIPPO NEUTRAL_FSR < 0"<<std::endl;
						lep_RelIsoNoFSR.push_back(CHARGED);
						Muiso.push_back(CHARGED);
//					std::cout<<"FILIPPO VALUE STORED = "<<CHARGED<<std::endl;
					}
					else{
//					std::cout<<"FILIPPO NEUTRAL_FSR > 0"<<std::endl;
						lep_RelIsoNoFSR.push_back(CHARGED + NEUTRAL_FSR);
						Muiso.push_back(CHARGED + NEUTRAL_FSR);
//					std::cout<<"FILIPPO VALUE STORED = "<<CHARGED + NEUTRAL_FSR<<std::endl;
					}
				}
		            }
			    else{
//			std::cout<<"FILIPPO ISO Delta > 0.1 = "<<Muon_pfRelIso03_all[Muonindex[imu]]<<std::endl;
				lep_RelIsoNoFSR.push_back(Muon_pfRelIso03_all[Muonindex[imu]]);
				Muiso.push_back(Muon_pfRelIso03_all[Muonindex[imu]]);
//			std::cout<<"FILIPPO VALUE STORED = "<<Muon_pfRelIso03_all[Muonindex[imu]]<<std::endl;
			    }
        		}
		}
		if(!already){
//                  std::cout<<"FILIPPO fsr!=imu:  "<<Muon_pfRelIso03_all[Muonindex[imu]]<<std::endl;
                    lep_RelIsoNoFSR.push_back(Muon_pfRelIso03_all[Muonindex[imu]]);
                    Muiso.push_back(Muon_pfRelIso03_all[Muonindex[imu]]);
//                      std::cout<<"FILIPPO VALUE STORED = "<<Muon_pfRelIso03_all[Muonindex[imu]]<<std::endl;	
		}
	}
	else{
//	  std::cout<<"FILIPPO ISO no FSR = Muon_pfRelIso03_all[Muonindex[imu]]"<<std::endl;
          lep_RelIsoNoFSR.push_back(Muon_pfRelIso03_all[Muonindex[imu]]);
       	  Muiso.push_back(Muon_pfRelIso03_all[Muonindex[imu]]);
//        std::cout<<"FILIPPO VALUE STORED = "<<Muon_pfRelIso03_all[Muonindex[imu]]<<std::endl;
	}
    }

    	//ElelistFsr = BatchFsrRecovery(Elelist); 
    //MulistFsr = BatchFsrRecovery(Mulist);
//    std::vector<unsigned>  FsrEleidx;
//    FsrEleidx = doFsrRecovery_Run3(goodFsrPhotons(), 0, 11);

    int map_fsr = 0;
    for(unsigned int ae=0; ae<Eid.size();ae++){
//	    std::cout<<"FILIPPO: ae = "<<ae<<std::endl;
     if(Elelist[ae].Pt() > 7){
//	     std::cout<<"FILIPPO: Elelist[ae].Pt() = "<<Elelist[ae].Pt()<<std::endl;
        float RelEleIsoNoFsr;
        RelEleIsoNoFsr = Eiso[ae];
//        std::cout<<"FILIPPO for lepFSR electron\t"<<ae<<std::endl;
//	ElelistFsr.push_back(Elelist[ae]);//FILIPPO
//	FsrEleidx = doFsrRecovery_Run3(goodFsrPhotons(), Electronindex[ae], 11);
	bool already = false;
	if (isFSR && flavour_fsr < 999){
                for(std::size_t j = 0; j < FsrIdx.size(); j=j+3){
                        if(FsrIdx.at(j) == 11 && FsrIdx.at(j+1) == ae){
                            fsr_index = FsrIdx.at(j+2);
		    
			    TLorentzVector fsrele, nofsrele, dressedele;
	        	    fsrele.SetPtEtaPhiM(FsrPhoton_pt.at(fsr_index),FsrPhoton_eta.at(fsr_index),FsrPhoton_phi.at(fsr_index),0);
        		    nofsrele.SetPtEtaPhiM(Elelist[ae].Pt(),Elelist[ae].Eta(),Elelist[ae].Phi(),Elelist[ae].M());
			    fsrmap[map_fsr] = nofsrele;
			    map_fsr++;
			    dressedele = fsrele + nofsrele;

			    lepFSR_pt.push_back(dressedele.Pt());
        		    lepFSR_eta.push_back(dressedele.Eta());
		            lepFSR_phi.push_back(dressedele.Phi());
        		    lepFSR_mass.push_back(dressedele.M());
		            lepFSR_ptVXBS.push_back(dressedele.Pt());
	        	    if(Elelist[ae].DeltaR(fsrele)>0.01){
	        	        RelEleIsoNoFsr = RelEleIsoNoFsr - FsrPhoton_pt[fsr_index]/Elelist[ae].Pt(); 
        		    }
		            ElelistFsr.push_back(dressedele);
				already = 1;
//            TLorentzVector fsrele;
//            fsrele.SetPtEtaPhiM(FsrPhoton_pt[FsrEleidx],FsrPhoton_eta[FsrEleidx],FsrPhoton_phi[FsrEleidx],0);
//            if(Elelist[ae].DeltaR(fsrele)>0.01){
//                RelEleIsoNoFsr = RelEleIsoNoFsr - FsrPhoton_pt[FsrEleidx]/Elelist[ae].Pt(); 
//            }
          //FsrEleidx = doFsrRecovery(Elelist[ae]);
          /*if(FsrEleidx<900){
              TLorentzVector fsrele;
              fsrele.SetPtEtaPhiM(FsrPhoton_pt[FsrEleidx],FsrPhoton_eta[FsrEleidx],FsrPhoton_phi[FsrEleidx],0);
              std::cout<<"Ele correction: "<< std::endl;
              if(Elelist[ae].DeltaR(fsrele)>0.01){
                RelEleIsoNoFsr = RelEleIsoNoFsr - FsrPhoton_pt[FsrEleidx]/Elelist[ae].Pt(); 
              }
          }*/
			}
		}
                if(!already){
			    lepFSR_pt.push_back(Elelist[ae].Pt());
		            lepFSR_eta.push_back(Elelist[ae].Eta());
        		    lepFSR_phi.push_back(Elelist[ae].Phi());
		            lepFSR_mass.push_back(Elelist[ae].M());
        		    lepFSR_ptVXBS.push_back(Elelist[ae].Pt());
	        	    ElelistFsr.push_back(Elelist[ae]);//FILIPPO
		}
	}
        else{
            lepFSR_pt.push_back(Elelist[ae].Pt());
            lepFSR_eta.push_back(Elelist[ae].Eta());
            lepFSR_phi.push_back(Elelist[ae].Phi());
            lepFSR_mass.push_back(Elelist[ae].M());
	    lepFSR_ptVXBS.push_back(Elelist[ae].Pt());
	    ElelistFsr.push_back(Elelist[ae]);//FILIPPO
        }

//        if((Eid[ae]==true)&&(RelEleIsoNoFsr<9999)){
        if((Eid[ae]==true)){ //removed the ISO condition from tight definition for electron
            nTightEle++;
            TightEleindex.push_back(ae);
            nTightEleChgSum += Elechg[ae];
            istightele.push_back(true);
            lep_tightId.push_back(true);
            TightElelep_index.push_back(Lepointer);
            Lepointer++;
//            if (isMC) lep_genindex.push_back(Electron_genPartIdx[Electronindex[ae]]);
//            else lep_genindex.push_back(-1);
        }
        else{
            istightele.push_back(false);
            lep_tightId.push_back(false);
            Lepointer++;
        }
     }
 //LowPt inclusion
// /*
     else{ // Elelist[ae].Pt() < 7
//             std::cout<<"FILIPPO: [Less than 7] Elelist[ae].Pt() = "<<Elelist[ae].Pt()<<std::endl;
	     //	std::cout<<"FILIPPO = Low pt electroni\t"<<Elelist[ae].Pt()<<"\t"<<Eid[ae]<<std::endl;
            lepFSR_pt.push_back(Elelist[ae].Pt());
            lepFSR_eta.push_back(Elelist[ae].Eta());
            lepFSR_phi.push_back(Elelist[ae].Phi());
            lepFSR_mass.push_back(Elelist[ae].M());
	    lepFSR_ptVXBS.push_back(Elelist[ae].Pt());
   
        float RelEleIsoNoFsr;

    	RelEleIsoNoFsr = Eiso[ae];
        ElelistFsr.push_back(Elelist[ae]);//FILIPPO

        if((Eid[ae]==true)){ // removed the ISO condition from tight definition for lowPt electron
//	std::cout<<"FILIPPO good electron"<<std::endl;
	    nTightEle++;
            TightEleindex.push_back(ae);
            nTightEleChgSum += Elechg[ae];
            istightele.push_back(true);
            lep_tightId.push_back(true);
            TightElelep_index.push_back(Lepointer);
            Lepointer++;
        }
        else{
            istightele.push_back(false);
            lep_tightId.push_back(false);
            Lepointer++;
        }
     } // Elelist[ae].Pt() < 7
//*/ 
    }

    for(unsigned int amu=0; amu<muid.size();amu++){
        float RelIsoNoFsr;
        RelIsoNoFsr = Muiso[amu];
        float mvaLowPt;
        mvaLowPt = Mumva[amu];
//        unsigned int FsrMuonidx;
//        std::cout<<"FILIPPO for lepFSR muon\t"<<amu<<std::endl;
//        FsrMuonidx = doFsrRecovery_Run3(goodFsrPhotons(), Muonindex[amu], 13);
//	MulistFsr.push_back(Mulist[amu]);//FILIPPO
	//	std::cout<<"FILIPPO = "<<isFSR<<"\t"<<FsrMuonidx<<std::endl;
	bool already = false;
	if (isFSR && flavour_fsr < 999){
                for(std::size_t j = 0; j < FsrIdx.size(); j=j+3){
                        if(FsrIdx.at(j) == 13 && FsrIdx.at(j+1) == amu){
                            fsr_index = FsrIdx.at(j+2);
			    TLorentzVector fsrmuon, nofsrmuon, dressedmuon, nofsrmuonVXBS;
		            fsrmuon.SetPtEtaPhiM(FsrPhoton_pt.at(fsr_index),FsrPhoton_eta.at(fsr_index),FsrPhoton_phi.at(fsr_index),0);
        		    nofsrmuon.SetPtEtaPhiM(Mulist[amu].Pt(),Mulist[amu].Eta(),Mulist[amu].Phi(),Mulist[amu].M());
			    fsrmap[map_fsr] = nofsrmuon;
			    map_fsr++;
			    dressedmuon = fsrmuon + nofsrmuon;

			    lepFSR_pt.push_back(dressedmuon.Pt());
		            lepFSR_eta.push_back(dressedmuon.Eta());
        		    lepFSR_phi.push_back(dressedmuon.Phi());
		            lepFSR_mass.push_back(dressedmuon.M());
			    MulistFsr.push_back(dressedmuon);//FILIPPO

			    nofsrmuonVXBS.SetPtEtaPhiM(Muon_bsConstrainedPt[Muonindex[amu]], Mulist[amu].Eta(),Mulist[amu].Phi(),Mulist[amu].M());
		            dressedmuon = fsrmuon + nofsrmuonVXBS;
			    lepFSR_ptVXBS.push_back(dressedmuon.Pt());

			    already = 1;
//            if(Mulist[amu].DeltaR(fsrmuon)>0.01){
//                RelIsoNoFsr = RelIsoNoFsr - FsrPhoton_pt[FsrMuonidx]/Mulist[amu].Pt();  
//            }
			}
		}
		if(!already){
			    lepFSR_pt.push_back(Mulist[amu].Pt());
		            lepFSR_eta.push_back(Mulist[amu].Eta());
        		    lepFSR_phi.push_back(Mulist[amu].Phi());
		            lepFSR_mass.push_back(Mulist[amu].M());
        		    lepFSR_ptVXBS.push_back(Muon_bsConstrainedPt[Muonindex[amu]]);
	        	    MulistFsr.push_back(Mulist[amu]);//FILIPPO
		}
	}
	else{
            lepFSR_pt.push_back(Mulist[amu].Pt());
            lepFSR_eta.push_back(Mulist[amu].Eta());
            lepFSR_phi.push_back(Mulist[amu].Phi());
            lepFSR_mass.push_back(Mulist[amu].M());
            lepFSR_ptVXBS.push_back(Muon_bsConstrainedPt[Muonindex[amu]]);
	    MulistFsr.push_back(Mulist[amu]);//FILIPPO
        }  

//            TLorentzVector fsrmuon;
//            fsrmuon.SetPtEtaPhiM(FsrPhoton_pt[FsrMuonidx],FsrPhoton_eta[FsrMuonidx],FsrPhoton_phi[FsrMuonidx],0);
//            if(Mulist[amu].DeltaR(fsrmuon)>0.01){
//                RelIsoNoFsr = RelIsoNoFsr - FsrPhoton_pt[FsrMuonidx]/Mulist[amu].Pt();  
//            }              

          /*if(FsrMuonidx<900){
              TLorentzVector fsrmuon;
              fsrmuon.SetPtEtaPhiM(FsrPhoton_pt[FsrMuonidx],FsrPhoton_eta[FsrMuonidx],FsrPhoton_phi[FsrMuonidx],0);
              std::cout<<"muon FSR recovered"<<endl;
              if(Mulist[amu].DeltaR(fsrmuon)>0.01){
                RelIsoNoFsr = RelIsoNoFsr - FsrPhoton_pt[FsrMuonidx]/Mulist[amu].Pt();  
              }
          }*/
        //if((muid[amu]==true)&&(RelIsoNoFsr<0.35)){
	// MVA - filippo */
        if((muid[amu]==true)){ //removed the ISO condition from tight definition in muons 
	 // MVA - filippo */
            nTightMu++;
            TightMuindex.push_back(amu);
            nTightMuChgSum += Muchg[amu];
            istightmu.push_back(true);
            lep_tightId.push_back(true);
            TightMulep_index.push_back(Lepointer);
            Lepointer++;
//           if (isMC) lep_genindex.push_back(Muon_genPartIdx[Muonindex[amu]]);
//           else lep_genindex.push_back(-1);
        }
        else{
            istightmu.push_back(false);
            lep_tightId.push_back(false);
            Lepointer++;
        }
    }
 
}
bool H4LTools::findZCandidate(){
    
    TLorentzVector z1,z2;
    
    if (nTightEle>=4) {
        cut4e++;
        flag4e = true;
    }
    else if (nTightMu>=4){
        cut4mu++;
        flag4mu = true;
    } 
    else if ((nTightMu>=2)&&(nTightEle>=2)){
        cut2e2mu++;
        flag2e2mu = true;
    }
   
    if(TightEleindex.size()>1){
        for(unsigned int ke=0; ke<(TightEleindex.size()-1);ke++){

//	   if(ElelistFsr[TightEleindex[ke]].Pt() < 7 && Eiso[TightEleindex[ke]] > 0.35) continue;

            for(unsigned int je=ke+1;je<TightEleindex.size();je++){

//		if(ElelistFsr[TightEleindex[je]].Pt() < 7 && Eiso[TightEleindex[je]] > 0.35) continue;
//		std::cout<<"FILIPPO = ele "<<ke<<"\t"<<je<<std::endl;
                if ((Elechg[TightEleindex[ke]]+Elechg[TightEleindex[je]])==0){
//                std::cout<<"FILIPPO: charge = 0; ele "<<ke<<"\t"<<je<<std::endl;
//		std::cout<<"FILIPPO pt = ElelistFsr[TightEleindex[ke]].Pt() = "<<ElelistFsr[TightEleindex[ke]].Pt()<<"\t ElelistFsr[TightEleindex[je]].Pt() = "<<ElelistFsr[TightEleindex[je]].Pt()<<std::endl;
		TLorentzVector Zcan;
                    Zcan = ElelistFsr[TightEleindex[ke]] + ElelistFsr[TightEleindex[je]];
                    if((Zcan.M()>MZcutdown)&&(Zcan.M()<MZcutup)){
                        Zlist.push_back(Zcan);
                        Zlep1index.push_back(TightEleindex[ke]);
                        Zlep2index.push_back(TightEleindex[je]);
                        Zlep1lepindex.push_back(TightElelep_index[ke]);
                        Zlep2lepindex.push_back(TightElelep_index[je]);
                        Zflavor.push_back(11);
                        Zlep1pt.push_back(ElelistFsr[TightEleindex[ke]].Pt());
                        Zlep2pt.push_back(ElelistFsr[TightEleindex[je]].Pt());
                        Zlep1eta.push_back(ElelistFsr[TightEleindex[ke]].Eta());
                        Zlep2eta.push_back(ElelistFsr[TightEleindex[je]].Eta());
                        Zlep1phi.push_back(ElelistFsr[TightEleindex[ke]].Phi());
                        Zlep2phi.push_back(ElelistFsr[TightEleindex[je]].Phi());
                        Zlep1mass.push_back(ElelistFsr[TightEleindex[ke]].M());
                        Zlep2mass.push_back(ElelistFsr[TightEleindex[je]].M());
                        Zlep1ptNoFsr.push_back(Elelist[TightEleindex[ke]].Pt());
                        Zlep2ptNoFsr.push_back(Elelist[TightEleindex[je]].Pt());
                        Zlep1etaNoFsr.push_back(Elelist[TightEleindex[ke]].Eta());
                        Zlep2etaNoFsr.push_back(Elelist[TightEleindex[je]].Eta());
                        Zlep1phiNoFsr.push_back(Elelist[TightEleindex[ke]].Phi());
                        Zlep2phiNoFsr.push_back(Elelist[TightEleindex[je]].Phi());
                        Zlep1massNoFsr.push_back(Elelist[TightEleindex[ke]].M());
                        Zlep2massNoFsr.push_back(Elelist[TightEleindex[je]].M());
                        Zlep1chg.push_back(Elechg[TightEleindex[ke]]);
                        Zlep2chg.push_back(Elechg[TightEleindex[je]]);
                    }
                }
            }
        }
    }

    if(TightMuindex.size()>1){
        for(unsigned int kmu=0; kmu<(TightMuindex.size()-1);kmu++){

//    	    if(Muiso[TightMuindex[kmu]] > 0.35) continue;  //filippo

            for(unsigned int jmu=kmu+1;jmu<TightMuindex.size();jmu++){

//		if(Muiso[TightMuindex[jmu]] > 0.35) continue; // filippo
//                std::cout<<"FILIPPO = mu "<<kmu<<"\t"<<jmu<<std::endl;

                if ((Muchg[TightMuindex[kmu]]+Muchg[TightMuindex[jmu]])==0){
//                std::cout<<"FILIPPO: charge = 0; mu "<<kmu<<"\t"<<jmu<<std::endl;
//		std::cout<<"FILIPPO: pt = MulistFsr[TightMuindex[kmu]].Pt() = "<<MulistFsr[TightMuindex[kmu]].Pt()<<"\t MulistFsr[TightMuindex[jmu]].Pt() = "<<MulistFsr[TightMuindex[jmu]].Pt()<<std::endl;
                    TLorentzVector Zcan;
                    Zcan = MulistFsr[TightMuindex[kmu]] + MulistFsr[TightMuindex[jmu]];
                    if((Zcan.M()>MZcutdown)&&(Zcan.M()<MZcutup)){
                        Zlist.push_back(Zcan);
                        Zlep1index.push_back(TightMuindex[kmu]);
                        Zlep2index.push_back(TightMuindex[jmu]);
                        Zlep1lepindex.push_back(TightMulep_index[kmu]);
                        Zlep2lepindex.push_back(TightMulep_index[jmu]);
			Zflavor.push_back(13);
                        Zlep1pt.push_back(MulistFsr[TightMuindex[kmu]].Pt());
                        Zlep2pt.push_back(MulistFsr[TightMuindex[jmu]].Pt());
                        Zlep1eta.push_back(MulistFsr[TightMuindex[kmu]].Eta());
                        Zlep2eta.push_back(MulistFsr[TightMuindex[jmu]].Eta());
                        Zlep1phi.push_back(MulistFsr[TightMuindex[kmu]].Phi());
                        Zlep2phi.push_back(MulistFsr[TightMuindex[jmu]].Phi());
                        Zlep1mass.push_back(MulistFsr[TightMuindex[kmu]].M());
                        Zlep2mass.push_back(MulistFsr[TightMuindex[jmu]].M());
                        Zlep1ptNoFsr.push_back(Mulist[TightMuindex[kmu]].Pt());
                        Zlep2ptNoFsr.push_back(Mulist[TightMuindex[jmu]].Pt());
                        Zlep1etaNoFsr.push_back(Mulist[TightMuindex[kmu]].Eta());
                        Zlep2etaNoFsr.push_back(Mulist[TightMuindex[jmu]].Eta());
                        Zlep1phiNoFsr.push_back(Mulist[TightMuindex[kmu]].Phi());
                        Zlep2phiNoFsr.push_back(Mulist[TightMuindex[jmu]].Phi());
                        Zlep1massNoFsr.push_back(Mulist[TightMuindex[kmu]].M());
                        Zlep2massNoFsr.push_back(Mulist[TightMuindex[jmu]].M());
                        Zlep1chg.push_back(Muchg[TightMuindex[kmu]]);
                        Zlep2chg.push_back(Muchg[TightMuindex[jmu]]);
                    }
                }
            }
        }
    }


    for (unsigned int znofsr = 0; znofsr<Zlist.size(); znofsr++){
        TLorentzVector Zlep1nofsr,Zlep2nofsr,Zcannofsr;
        Zlep1nofsr.SetPtEtaPhiM(Zlep1ptNoFsr[znofsr],Zlep1etaNoFsr[znofsr],Zlep1phiNoFsr[znofsr],Zlep1massNoFsr[znofsr]);
        Zlep2nofsr.SetPtEtaPhiM(Zlep2ptNoFsr[znofsr],Zlep2etaNoFsr[znofsr],Zlep2phiNoFsr[znofsr],Zlep2massNoFsr[znofsr]);
	Zcannofsr = Zlep1nofsr + Zlep2nofsr;
        Zlistnofsr.push_back(Zcannofsr);
    }
    
    
    Zsize = Zlist.size();    
//	std::cout<<"FILIPPO Zlist.size() = "<<Zsize<<std::endl;
    if (Zsize>0){
        return true;
    }
    else{
        return false;
    }


}


void H4LTools::findZ1LCandidate(){
    using namespace std;
    const double Zmass = 91.1876;
    
    unsigned int Nlep = lep_pt.size();
    if( Nlep < 3 ) return;
    CutFlow_3Lep = true;
    // First, make all Z candidates including any FSR photons
    int n_Zs=0;
    vector<int> Z_Z1L_lepindex1;
    vector<int> Z_Z1L_lepindex2;
    
    for(unsigned int i=0; i<Nlep; i++){
        for(unsigned int j=i+1; j<Nlep; j++){
            
            // same flavor opposite charge
            if((lep_id[i]+lep_id[j])!=0) continue;
            
            TLorentzVector li, lj;
            li.SetPtEtaPhiM(lep_pt[i],lep_eta[i],lep_phi[i],lep_mass[i]);
            lj.SetPtEtaPhiM(lep_pt[j],lep_eta[j],lep_phi[j],lep_mass[j]);
            
            TLorentzVector lifsr, ljfsr;
            lifsr.SetPtEtaPhiM(lepFSR_pt[i],lepFSR_eta[i],lepFSR_phi[i],lepFSR_mass[i]);
            ljfsr.SetPtEtaPhiM(lepFSR_pt[j],lepFSR_eta[j],lepFSR_phi[j],lepFSR_mass[j]);
            
            TLorentzVector liljfsr = lifsr+ljfsr;
                        
            TLorentzVector Z, Z_noFSR;
            Z = lifsr+ljfsr;
            Z_noFSR = li+lj;
            
            
            if (Z.M()>0.0) {
                n_Zs++;
                Z_Z1L_lepindex1.push_back(i);
                Z_Z1L_lepindex2.push_back(j);
            }
            
        } // lep i
    } // lep j
    
    bool properLep_ID = false; int Nmm = 0; int Nmp = 0; int Nem = 0; int Nep = 0;
    for(unsigned int i =0; i<Muonindex.size(); i++) {
        if(Muon_charge[Muonindex[i]]<0) Nmm = Nmm+1;
        if(Muon_charge[Muonindex[i]]>0) Nmp = Nmp+1;
    }
    for(unsigned int i =0; i<Electronindex.size(); i++) {
        if(Electron_charge[Electronindex[i]]<0) Nem = Nem+1;
        if(Electron_charge[Electronindex[i]]>0) Nep = Nep+1;
    }
    
    if(Nmm>=1 && Nmp>=1) properLep_ID = true; //2mu + x
    if(Nem>=1 && Nep>=1) properLep_ID = true; //2e + x
    
    // proper charge flavor combination for Z + 1L
    if(!properLep_ID) return;
    CutFlow_properID = true;
    
    // Consider all Z candidates
    double minZ1DeltaM=9999.9;
    
    for (int i=0; i<n_Zs; i++) {
        
        int i1 = Z_Z1L_lepindex1[i]; int i2 = Z_Z1L_lepindex2[i];
        int j1 = 3 - i1 - i2; // index of the third lepton (check if this works)
        
        TLorentzVector lep_i1, lep_i2, lep_j1;
        lep_i1.SetPtEtaPhiM(lepFSR_pt[i1],lepFSR_eta[i1],lepFSR_phi[i1],lepFSR_mass[i1]);
        lep_i2.SetPtEtaPhiM(lepFSR_pt[i2],lepFSR_eta[i2],lepFSR_phi[i2],lepFSR_mass[i2]);
        lep_j1.SetPtEtaPhiM(lepFSR_pt[j1],lepFSR_eta[j1],lepFSR_phi[j1],lepFSR_mass[j1]);
        
        TLorentzVector lep_i1_nofsr, lep_i2_nofsr, lep_j1_nofsr;
        lep_i1_nofsr.SetPtEtaPhiM(lep_pt[i1],lep_eta[i1],lep_phi[i1],lep_mass[i1]);
        lep_i2_nofsr.SetPtEtaPhiM(lep_pt[i2],lep_eta[i2],lep_phi[i2],lep_mass[i2]);
        lep_j1_nofsr.SetPtEtaPhiM(lep_pt[j1],lep_eta[j1],lep_phi[j1],lep_mass[j1]);
        
        TLorentzVector Zi;
        Zi = lep_i1+lep_i2;
        //Zi.SetPtEtaPhiM(Z_Z1L_pt[i],Z_Z1L_eta[i],Z_Z1L_phi[i],Z_Z1L_mass[i]);
        
        
        TLorentzVector Z1 = Zi;
        double Z1DeltaM = abs(Zi.M()-Zmass);
        int Z1_lepindex[2] = {0,0};
        if (lep_i1.Pt()>lep_i2.Pt()) { Z1_lepindex[0] = i1;  Z1_lepindex[1] = i2; }
        else { Z1_lepindex[0] = i2;  Z1_lepindex[1] = i1; }
        
        // Check Leading and Subleading pt Cut
        vector<double> allPt;
        allPt.push_back(lep_i1.Pt()); allPt.push_back(lep_i2.Pt());
        std::sort(allPt.begin(), allPt.end());
        if (allPt[1]<20 || allPt[0]<10 ) continue;
        CutFlow_3LepPtcut = true;
        // Check dR(li,lj)>0.02 for any i,j
        vector<double> alldR;
        alldR.push_back(lep_i1.DeltaR(lep_i2));
        alldR.push_back(lep_j1.DeltaR(lep_i2));
        alldR.push_back(lep_i1.DeltaR(lep_j1));
        if (*min_element(alldR.begin(),alldR.end())<0.02) continue;
        CutFlow_3LepDRcut = true;
        // Check M(l+,l-)>4.0 GeV for any OS pair
        // Do not include FSR photons
        vector<double> allM;
        TLorentzVector i1i2;
        i1i2 = (lep_i1_nofsr)+(lep_i2_nofsr); allM.push_back(i1i2.M());
        if (lep_id[i1]*lep_id[j1]<0) {
            TLorentzVector i1j1;
            i1j1 = (lep_i1_nofsr)+(lep_j1_nofsr); allM.push_back(i1j1.M());
        } else {
            TLorentzVector i2j1;
            i2j1 = (lep_i2_nofsr)+(lep_j1_nofsr); allM.push_back(i2j1.M());
        }
        if (*min_element(allM.begin(),allM.end())<4.0) continue;
        CutFlow_3LepQCDcut = true;
        // Check isolation cut (without FSR ) for Z1 leptons
//        if (lep_RelIsoNoFSR[Z1_lepindex[0]]>((abs(lep_id[Z1_lepindex[0]])==11) ? 9999 : 0.35)) continue; // checking iso with FSR removed
//        if (lep_RelIsoNoFSR[Z1_lepindex[1]]>((abs(lep_id[Z1_lepindex[1]])==11) ? 9999 : 0.35)) continue; // checking iso with FSR removed

//// Including lowPt condition
        /* MVA - filippo */
//	if(abs(lep_id[Z1_lepindex[0]])==13 && lep_RelIsoNoFSR[Z1_lepindex[0]] > 0.35) continue;
//	if(abs(lep_id[Z1_lepindex[1]])==13 && lep_RelIsoNoFSR[Z1_lepindex[1]] > 0.35) continue;
	/* MVA - filippo */
//	if(abs(lep_id[Z1_lepindex[0]])==11 && lepFSR_pt[Z1_lepindex[0]] < 7 && lep_RelIsoNoFSR[Z1_lepindex[0]] > 0.35) continue;
//	if(abs(lep_id[Z1_lepindex[1]])==11 && lepFSR_pt[Z1_lepindex[1]] < 7 && lep_RelIsoNoFSR[Z1_lepindex[1]] > 0.35) continue;
//// Including lowPt condition

        // Check tight ID cut for Z1 leptons
        if (!(lep_tightId[Z1_lepindex[0]])) continue; // checking tight lepton ID
        if (!(lep_tightId[Z1_lepindex[1]])) continue; // checking tight lepton ID
        
        if ( (Z1.M() < 40) || (Z1.M() > 120) ) continue;
        CutFlow_tightZ1cut = true;
        
        // Check if this candidate has the best Z1 and highest scalar sum of Z2 lepton pt
        
        if ( Z1DeltaM<=minZ1DeltaM ) {
            
            minZ1DeltaM = Z1DeltaM;
            
            TLorentzVector Z1L;
            Z1L = Z1+lep_j1;
            
            mass3l = Z1L.M();
            
            lep_Hindex[0] = Z1_lepindex[0];
            lep_Hindex[1] = Z1_lepindex[1];
            lep_Hindex[2] = j1;
            
            passedZ1LSelection=true;
            
        }
    }
}


bool H4LTools::ZZSelection(){

// 	std::cout<<"sono dentro la funzione"<<std::endl;
// 	std::cout<<"findZCandidate = "<<findZCandidate()<<std::endl;
    
    bool foundZZCandidate = false;
    if(!findZCandidate()){
        return foundZZCandidate;
    }

    if(lep_pt.size() < 4){
        return foundZZCandidate;
    } 
    
//     std::cout<<"nTightMu+nTightEle = "<<nTightMu+nTightEle<<std::endl;

    if((nTightMu+nTightEle)<4){
//     	std::cout<<"Zsize prima = "<<Zlist.size()<<std::endl;
        if(!ZXdistributions())	
	        return foundZZCandidate;
	    Zsize = Zlist.size();
    } 
    
//     std::cout<<"Zsize = "<<Zsize<<std::endl;
    
//     std::cout<<"ZXdistributions = "<<ZXdistributions()<<"\t lep_pt.size() = "<<lep_pt.size()<<"\t nTightMu = "<<nTightMu<<"\t nTightEle = "<<nTightEle<<std::endl;
//    	std::cout<<"Zsize dopo = "<<Zlist.size()<<std::endl;
// 
//     if((abs(nTightEleChgSum)+abs(nTightMuChgSum))>(nTightMu+nTightEle-4)){
//         return foundZZCandidate;
//     }

    if(Zsize<2){
// 	    std::cout<<"(Zsize<2) foundZZCandidate = "<<foundZZCandidate<<std::endl;
        return foundZZCandidate;
    }
//            std::cout<<"3FILIPPO = "<<std::endl;
   
    //Find ZZ candidate
    std::vector<int> Z1CanIndex;
    std::vector<int> Z2CanIndex;
    int ghosttag = 0, QCDtag=0, lepPtTag = 0;
    for (unsigned int m=0; m<(Zlist.size()-1); m++){
        for (unsigned int n=m+1; n<Zlist.size(); n++){
	    if (Zflavor[m]==Zflavor[n]){
               if ((Zlep1index[m] == Zlep1index[n])||(Zlep2index[m] == Zlep1index[n])) continue;  //non-overlapping
               if ((Zlep1index[m] == Zlep2index[n])||(Zlep2index[m] == Zlep2index[n])) continue;
            }
            if (Zlist[m].DeltaR(Zlist[n])<0.02) continue; //ghost removal
            ghosttag++;
            bool nPassPt20;
            int nPassPt10;
            nPassPt20 = (Zlep1pt[m]>20) || (Zlep2pt[m]>20) || (Zlep1pt[n]>20) || (Zlep2pt[n]>20);
            nPassPt10 = 0;
            if (Zlep1pt[m]>10) nPassPt10 += 1; 
            if (Zlep2pt[m]>10) nPassPt10 += 1; 
            if (Zlep1pt[n]>10) nPassPt10 += 1; 
            if (Zlep2pt[n]>10) nPassPt10 += 1; 
            if (nPassPt10 < 2) continue;
            if (nPassPt20 == false) continue; //lep Pt requirements
            lepPtTag++;
            if ((Zlep1chg[m]+Zlep1chg[n])==0){
                TLorentzVector lepA,lepB,lepAB;
                lepA.SetPtEtaPhiM(Zlep1ptNoFsr[m],Zlep1etaNoFsr[m],Zlep1phiNoFsr[m],Zlep1massNoFsr[m]);
                lepB.SetPtEtaPhiM(Zlep1ptNoFsr[n],Zlep1etaNoFsr[n],Zlep1phiNoFsr[n],Zlep1massNoFsr[n]);
//                lepB.SetPtEtaPhiM(Zlep2ptNoFsr[n],Zlep2etaNoFsr[n],Zlep2phiNoFsr[n],Zlep2massNoFsr[n]);
                lepAB = lepA + lepB;
//		std::cout<<"FILIPPO 1m1n lepAB.M() = "<<lepAB.M()<<"\t"<<Zlep1ptNoFsr[m]<<"\t"<<Zlep1ptNoFsr[n]<<std::endl;
		if(lepAB.M()<4) continue;  //QCD Supressionas
            }
            if ((Zlep1chg[m]+Zlep2chg[n])==0){
                TLorentzVector lepA,lepB,lepAB;
                lepA.SetPtEtaPhiM(Zlep1ptNoFsr[m],Zlep1etaNoFsr[m],Zlep1phiNoFsr[m],Zlep1massNoFsr[m]);
                lepB.SetPtEtaPhiM(Zlep2ptNoFsr[n],Zlep2etaNoFsr[n],Zlep2phiNoFsr[n],Zlep2massNoFsr[n]);
                lepAB = lepA + lepB;
//                std::cout<<"FILIPPO 1m2n lepAB.M() = "<<lepAB.M()<<"\t"<<Zlep1ptNoFsr[m]<<"\t"<<Zlep2ptNoFsr[n]<<std::endl;
                if(lepAB.M()<4) continue;
            }
            if ((Zlep2chg[m]+Zlep1chg[n])==0){
                TLorentzVector lepA,lepB,lepAB;
                lepA.SetPtEtaPhiM(Zlep2ptNoFsr[m],Zlep2etaNoFsr[m],Zlep2phiNoFsr[m],Zlep2massNoFsr[m]);
                lepB.SetPtEtaPhiM(Zlep1ptNoFsr[n],Zlep1etaNoFsr[n],Zlep1phiNoFsr[n],Zlep1massNoFsr[n]);
                lepAB = lepA + lepB;
//                std::cout<<"FILIPPO 2m1n lepAB.M() = "<<lepAB.M()<<"\t"<<Zlep2ptNoFsr[m]<<"\t"<<Zlep1ptNoFsr[n]<<std::endl;
                if(lepAB.M()<4) continue;
            }
            if ((Zlep2chg[m]+Zlep2chg[n])==0){
                TLorentzVector lepA,lepB,lepAB;
                lepA.SetPtEtaPhiM(Zlep2ptNoFsr[m],Zlep2etaNoFsr[m],Zlep2phiNoFsr[m],Zlep2massNoFsr[m]);
                lepB.SetPtEtaPhiM(Zlep2ptNoFsr[n],Zlep2etaNoFsr[n],Zlep2phiNoFsr[n],Zlep2massNoFsr[n]);
//                lepB.SetPtEtaPhiM(Zlep1ptNoFsr[n],Zlep1etaNoFsr[n],Zlep1phiNoFsr[n],Zlep1massNoFsr[n]);
                lepAB = lepA + lepB;
//                std::cout<<"FILIPPO 2m2n lepAB.M() = "<<lepAB.M()<<"\t"<<Zlep2ptNoFsr[m]<<"\t"<<Zlep2ptNoFsr[n]<<std::endl;
                if(lepAB.M()<4) continue;
            }
//            std::cout<<"3aFILIPPO = "<<std::endl;
            QCDtag++;
            if ((Zlist[m].M()<40) && (Zlist[n].M()<40))  continue; //Z1 mass
//           std::cout<<"3aFILIPPO = "<<std::endl;

            TLorentzVector zZ1,zZ2;
            if (fabs(Zlist[m].M()-Zmass)<fabs(Zlist[n].M()-Zmass)){
//		std::cout<<"FILIPPO: m < n: Zlist[m].M() = "<<Zlist[m].M()<<"\t Zlist[n].M() = "<<Zlist[n].M()<<std::endl;
                zZ1 = Zlist[m];
                zZ2 = Zlist[n];
            }
            else{
//                std::cout<<"FILIPPO: m > n: Zlist[m].M() = "<<Zlist[m].M()<<"\t Zlist[n].M() = "<<Zlist[n].M()<<std::endl;
                zZ1 = Zlist[n];
                zZ2 = Zlist[m];
            }    
            
            bool passSmartCut = true;
//            std::cout<<"4FILIPPO = "<<m<<n<<std::endl;
            if (Zflavor[m]==Zflavor[n]){
                TLorentzVector Za,Zb,lepM1,lepM2,lepN1,lepN2;
                int lepM1chg,lepM2chg,lepN1chg,lepN2chg;
                lepM1.SetPtEtaPhiM(Zlep1pt[m],Zlep1eta[m],Zlep1phi[m],Zlep1mass[m]);
                lepM2.SetPtEtaPhiM(Zlep2pt[m],Zlep2eta[m],Zlep2phi[m],Zlep2mass[m]);
                lepN1.SetPtEtaPhiM(Zlep1pt[n],Zlep1eta[n],Zlep1phi[n],Zlep1mass[n]);
                lepN2.SetPtEtaPhiM(Zlep2pt[n],Zlep2eta[n],Zlep2phi[n],Zlep2mass[n]);
                lepM1chg = Zlep1chg[m];
                lepM2chg = Zlep2chg[m];
                lepN1chg = Zlep1chg[n];
                lepN2chg = Zlep2chg[n];
                if(lepM1chg == lepN1chg){
                    Za = lepM1 + lepN2;
                    Zb = lepN1 + lepM2;
                }
                    
                else{
                    Za = lepM1 + lepN1;
                    Zb = lepN2 + lepM2;
                }
                if (fabs(Za.M()-Zmass)<fabs(Zb.M()-Zmass)){
                    if ( (fabs(Za.M()-Zmass)<abs(zZ1.M()-Zmass)) && (Zb.M()<12) ) passSmartCut=false;
                }        
                                    
                else{
                    if ( (fabs(Zb.M()-Zmass)<fabs(zZ1.M()-Zmass)) && (Za.M()<12) ) passSmartCut=false;
                }
            }
//            std::cout<<"6FILIPPO = "<<m<<n<<std::endl;
            if (passSmartCut==false) continue ;
//            std::cout<<"7FILIPPO = "<<m<<n<<"\t"<<zZ1.M()+zZ2.M()<<"\t"<<zZ1.M()<<"\t"<<zZ2.M()<<"\t"<<(zZ1+zZ2).M()<<std::endl;
            if ((zZ1+zZ2).M()<MZZcut) continue;
//            std::cout<<"8FILIPPO = "<<m<<n<<std::endl;
            foundZZCandidate = true;
//            if(Zlist[m].M()>Zlist[n].M()){
            if (fabs(Zlist[m].M()-Zmass)<fabs(Zlist[n].M()-Zmass)){
//                std::cout<<"FILIPPO: m < n: Zlist[m].M() = "<<Zlist[m].M()<<"\t Zlist[n].M() = "<<Zlist[n].M()<<std::endl;
//		std::cout<<"FILIPPO: m = "<<m<<"\t n = "<<n<<std::endl;
		Z1CanIndex.push_back(m);
                Z2CanIndex.push_back(n);
//		std::cout<<"FILIPPO: Z1CanIndex[0] = "<<Z1CanIndex[0]<<"\t Z2CanIndex[0] = "<<Z2CanIndex[0]<<std::endl;
//                std::cout<<"FILIPPO: Zlep1eta[m] = "<<Zlep1eta[m]<<"\t Zlep2eta[m] = "<<Zlep2eta[m]<<"\t Zlep1eta[n] = "<<Zlep1eta[n]<<"\t Zlep2eta[n] = "<<Zlep2eta[n]<<std::endl;
	    }
            else{
//                std::cout<<"FILIPPO: m > n: Zlist[m].M() = "<<Zlist[m].M()<<"\t Zlist[n].M() = "<<Zlist[n].M()<<std::endl;
//                std::cout<<"FILIPPO: m = "<<m<<"\t n = "<<n<<std::endl;
                Z1CanIndex.push_back(n);
                Z2CanIndex.push_back(m);
//                std::cout<<"FILIPPO: Z1CanIndex[0] = "<<Z1CanIndex[0]<<"\t Z2CanIndex[0] = "<<Z2CanIndex[0]<<std::endl;
//                std::cout<<"FILIPPO: Zlep1eta[n] = "<<Zlep1eta[n]<<"\t Zlep2eta[n] = "<<Zlep2eta[n]<<"\t Zlep1eta[m] = "<<Zlep1eta[m]<<"\t Zlep2eta[m] = "<<Zlep2eta[m]<<std::endl;
            }
                    
           
        }
    }
    if(ghosttag){
        if (flag2e2mu) cutghost2e2mu++;
        if (flag4e) cutghost4e++;
        if (flag4mu) cutghost4mu++;
    }
    if(lepPtTag){
        if (flag2e2mu) cutLepPt2e2mu++;
        if (flag4e) cutLepPt4e++;
        if (flag4mu) cutLepPt4mu++;
    }
    if(QCDtag){
        if (flag2e2mu) cutQCD2e2mu++;
        if (flag4e) cutQCD4e++;
        if (flag4mu) cutQCD4mu++;
    }
    if(foundZZCandidate == false){
//  	    std::cout<<"1. foundZZCandidate = "<<foundZZCandidate<<std::endl;   
        return foundZZCandidate;
    }
//    std::cout<<"9FILIPPO = "<<std::endl;
    if (flag2e2mu) cutZZ2e2mu++;
    if (flag4e) cutZZ4e++;
    if (flag4mu) cutZZ4mu++;
    int Z1index,Z2index; 
    Z1index = Z1CanIndex[0];
    Z2index = Z2CanIndex[0];
//    std::cout<<"FILIPPO: Z1CanIndex[0] = "<<Z1CanIndex[0]<<"\t Z2CanIndex[0] = "<<Z2CanIndex[0]<<std::endl;
    float Z2Ptsum;
    Z2Ptsum = Zlep1pt[Z2index] + Zlep2pt[Z2index];
    if(Z1CanIndex.size()>1){
//	std::cout<<"FILIPPO: Z1CanIndex.size()>1 = "<<Z1CanIndex.size()<<std::endl;
        for(unsigned int iz=0;iz<Z1CanIndex.size();iz++){
            if (Z1index==Z1CanIndex[iz]){
                if((Zlep1pt[Z2CanIndex[iz]] + Zlep2pt[Z2CanIndex[iz]])>Z2Ptsum){
                    Z1index = Z1CanIndex[iz];
                    Z2index = Z2CanIndex[iz];
                    Z2Ptsum = Zlep1pt[Z2index] + Zlep2pt[Z2index];
                }
            }
            if(fabs(Zlist[Z1CanIndex[iz]].M()-Zmass)<fabs(Zlist[Z1index].M()-Zmass)){
                Z1index = Z1CanIndex[iz];
                Z2index = Z2CanIndex[iz];
                Z2Ptsum = Zlep1pt[Z2index] + Zlep2pt[Z2index];
            }
        }
    }
       
    
    Z1 = Zlist[Z1index];
    Z2 = Zlist[Z2index];
//    std::cout<<"FILIPPO Z1 = "<<Z1.M()<<"\t Z2 = "<<Z2.M()<<std::endl;
//    std::cout<<"FILIPPO: Z1index = "<<Z1index<<"\t Z2index = "<<Z2index<<std::endl;

    Z1nofsr = Zlistnofsr[Z1index];
    Z2nofsr = Zlistnofsr[Z2index];
    ZZsystem = Z1+Z2;
    ZZsystemnofsr = Z1nofsr+Z2nofsr;

    /*if(abs(ZZsystemnofsr.M()-ZZsystem.M())>0.000001){
        std::cout<<"FSR works "<<abs(ZZsystemnofsr.M()-ZZsystem.M())<<std::endl;
        std::cout<<"FSR: "<<ZZsystem.M()<<" noFSR:"<<ZZsystemnofsr.M()<<std::endl;
    }*/
    
    float massZZ;
    if (isFSR) massZZ = ZZsystem.M();
    else massZZ = ZZsystemnofsr.M();
    if ((massZZ>HiggscutDown)&&(massZZ<HiggscutUp)){
        if (flag2e2mu) cutm4l2e2mu++;
        if (flag4e) cutm4l4e++;
        if (flag4mu) cutm4l4mu++;
    }

    unsigned int jet1index, jet2index;
    jet1index = 99;
    jet2index = 99;
    if(jetidx.size()>0)
    {
        if(jetidx.size()==1)
        {
            jet1index = jetidx[0];
        }
        if(jetidx.size()==2)
        {
            jet1index = jetidx[0];
            jet2index = jetidx[1];
//	    std::cout<<"jetidx.size()==2"<<"\t"<<jetidx[0]<<"\t"<<jetidx[1]<<"\t"<<jet1index<<"\t"<<jet2index<<std::endl;
            if(Jet_pt[jetidx[1]]>Jet_pt[jetidx[0]])
            {
                jet1index = jetidx[1];
                jet2index = jetidx[0];
//		std::cout<<"jetidx.size()==2 and pT > "<<"\t"<<jetidx[0]<<"\t"<<jetidx[1]<<"\t"<<jet1index<<"\t"<<jet2index<<std::endl;

            }
        }
        if(jetidx.size()>2)
        {
            jet1index = jetidx[0];
            jet2index = jetidx[1];
//           std::cout<<"jetidx.size() > 2"<<"\t"<<jetidx[0]<<"\t"<<jetidx[1]<<"\t"<<jet1index<<"\t"<<jet2index<<std::endl;
            if(Jet_pt[jetidx[1]]>Jet_pt[jetidx[0]])
            {
                jet1index = jetidx[1];
                jet2index = jetidx[0];
//                std::cout<<"jetidx.size() > 2 and pT > "<<"\t"<<jetidx[0]<<"\t"<<jetidx[1]<<"\t"<<jet1index<<"\t"<<jet2index<<std::endl;
            }
            for (unsigned int pj=2;pj<jetidx.size();pj++){
		if(Jet_pt[jetidx[pj]]>Jet_pt[jet1index]){
//			std::cout<<jet1index<<"\t"<<jet2index<<"\t"<<jetidx[pj]<<std::endl;
//			std::cout<<Jet_pt[jet1index]<<"\t"<<Jet_pt[jet2index]<<"\t"<<Jet_pt[jetidx[pj]]<<std::endl;
			int index_tmp = jet1index;
			jet1index = jetidx[pj];
			jet2index = index_tmp;
//			std::cout<<jet1index<<"\t"<<jet2index<<std::endl;
//			std::cout<<Jet_pt[jet1index]<<"\t"<<Jet_pt[jet2index]<<std::endl;
		}
		if(Jet_pt[jetidx[pj]]<Jet_pt[jet1index] && Jet_pt[jetidx[pj]]>Jet_pt[jet2index]){
//			std::cout<<Jet_pt[jet1index]<<"\t"<<Jet_pt[jet2index]<<"\t"<<Jet_pt[jetidx[pj]]<<std::endl;
//			std::cout<<jet1index<<"\t"<<jet2index<<"\t"<<jetidx[pj]<<std::endl;
			jet2index = jetidx[pj];
//			std::cout<<jet1index<<"\t"<<jet2index<<std::endl;
//                        std::cout<<Jet_pt[jet1index]<<"\t"<<Jet_pt[jet2index]<<std::endl;

		}
//		std::cout<<"jetidx.size() > 2 and loop "<<"\t"<<jetidx[0]<<"\t"<<jetidx[1]<<"\t"<<jet1index<<"\t"<<jet2index<<std::endl;
            }
        }
// 	if(Jet_pt[jet1index] < Jet_pt[jet2index])
// 		std::cout<<"PROBLEMA with jet pt:"<<Jet_pt[jet1index]<<"\t"<<Jet_pt[jet2index]<<"\t jetidx.size() = "<<jetidx.size()<<std::endl;
    }
    TLorentzVector Jet1,Jet2;
    SimpleParticleCollection_t associated;
    if(jetidx.size()>0){
        Jet1.SetPtEtaPhiM(Jet_pt[jet1index],Jet_eta[jet1index],Jet_phi[jet1index],Jet_mass[jet1index]);
        associated.push_back(SimpleParticle_t(0, Jet1));
        pTj1 = Jet1.Pt();
        etaj1 = Jet1.Eta();
        phij1 = Jet1.Phi();
        mj1 = Jet1.M();
        if(jetidx.size()>1){
//	   std::cout<<"jetidx.size>2"<<std::endl;
           Jet2.SetPtEtaPhiM(Jet_pt[jet2index],Jet_eta[jet2index],Jet_phi[jet2index],Jet_mass[jet2index]);
           associated.push_back(SimpleParticle_t(0, Jet2));
           pTj2 = Jet2.Pt();
           etaj2 = Jet2.Eta();
           phij2 = Jet2.Phi();
           mj2 = Jet2.M();
	   mjj = (Jet1 + Jet2).M();
	   etajj = (Jet1 + Jet2).Eta();
	   phijj = (Jet1 + Jet2).Phi();
	   Detajj = (Jet1 - Jet2).Eta();
	   Dphijj = (Jet1 - Jet2).Phi();
//	   std::cout<<"mjj = "<<mjj<<"\t etajj = "<<etajj<<std::endl;
           if(Jet1.Rapidity() - Jet2.Rapidity() == 0){
		   for(int j = 0; j < jetidx.size(); j++)
			   std::cout<<"jetidx: "<<j<<"\t"<<jetidx.at(j)<<"\t"<<jetidx[j]<<std::endl;
		   std::cout<<jet1index<<"\t"<<jet2index<<"\t"<<pTj1<<"\t"<<pTj2<<"\t"<<etaj1<<"\t"<<etaj2<<"\t"<<phij1<<"\t"<<phij2<<std::endl;

	   }
	}
    }
    
    
        
    SimpleParticleCollection_t daughters;
    TLorentzVector Lep1,Lep2,Lep3,Lep4;

//    std::cout<<"FILIPPO: Z1index = "<<Z1index<<"\t Z2index = "<<Z2index<<std::endl;
//    std::cout<<"FILIPPO: "<<Zlep1eta[Z1index]<<"\t"<<Zlep2eta[Z1index]<<"\t"<<Zlep1eta[Z2index]<<"\t"<<Zlep2eta[Z2index]<<std::endl;
    Lep1.SetPtEtaPhiM(Zlep1pt[Z1index],Zlep1eta[Z1index],Zlep1phi[Z1index],Zlep1mass[Z1index]);
    Lep2.SetPtEtaPhiM(Zlep2pt[Z1index],Zlep2eta[Z1index],Zlep2phi[Z1index],Zlep2mass[Z1index]);
    Lep3.SetPtEtaPhiM(Zlep1pt[Z2index],Zlep1eta[Z2index],Zlep1phi[Z2index],Zlep1mass[Z2index]);
    Lep4.SetPtEtaPhiM(Zlep2pt[Z2index],Zlep2eta[Z2index],Zlep2phi[Z2index],Zlep2mass[Z2index]);
//    std::cout<<"FILIPPO: Zflavor[Z1index] = "<<Zflavor[Z1index]<<"\t Zflavor[Z2index] = "<<Zflavor[Z2index]<<std::endl;
    if ((Zflavor[Z1index]==13)&&(Zflavor[Z2index]==13)) RecoFourMuEvent=true;
    if ((Zflavor[Z1index]==11)&&(Zflavor[Z2index]==11)) RecoFourEEvent=true;
    if ((Zflavor[Z1index]==11)&&(Zflavor[Z2index]==13)) RecoTwoETwoMuEvent=true;
    if ((Zflavor[Z1index]==13)&&(Zflavor[Z2index]==11)) RecoTwoMuTwoEEvent=true;
//    std::cout<<"FILIPPO: "<<RecoFourMuEvent<<RecoFourEEvent<<RecoTwoETwoMuEvent<<RecoTwoMuTwoEEvent<<std::endl;

	lep_Hindex[0] = Zlep1lepindex[Z1index];
	lep_Hindex[1] = Zlep2lepindex[Z1index];
	lep_Hindex[2] = Zlep1lepindex[Z2index];
	lep_Hindex[3] = Zlep2lepindex[Z2index];
	
// 	if(ZXdistributions()){
// 		std::cout<<lep_Hindex[0]<<"\t"<<lep_Hindex[1]<<"\t"<<lep_Hindex[2]<<"\t"<<lep_Hindex[3]<<std::endl;
// 		std::cout<<lep_pt[lep_Hindex[0]]<<"\t"<<lep_pt[lep_Hindex[1]]<<"\t"<<lep_pt[lep_Hindex[2]]<<"\t"<<lep_pt[lep_Hindex[3]]<<std::endl;
// 	}
		

//    std::cout<<"FILIPPO: Hindex= "<<lep_Hindex[0]<<lep_Hindex[1]<<lep_Hindex[2]<<lep_Hindex[3]<<std::endl;
    pTL1 = Lep1.Pt();
    etaL1 = Lep1.Eta();
    phiL1 = Lep1.Phi();
    massL1 = Lep1.M();
    pTL2 = Lep2.Pt();
    etaL2 = Lep2.Eta();
    phiL2 = Lep2.Phi();
    massL2 = Lep2.M();
    pTL3 = Lep3.Pt();
    etaL3 = Lep3.Eta();
    phiL3 = Lep3.Phi();
    massL3 = Lep3.M();
    pTL4 = Lep4.Pt();
    etaL4 = Lep4.Eta();
    phiL4 = Lep4.Phi();
    massL4 = Lep4.M();

    for(int i = 0; i < 4; i++){
		std::vector<float> tmp;
		tmp.push_back(lepFSR_pt[lep_Hindex[i]]);
		tmp.push_back(lepFSR_eta[lep_Hindex[i]]);
		tmp.push_back(lepFSR_phi[lep_Hindex[i]]);
		tmp.push_back(lepFSR_mass[lep_Hindex[i]]);
		tmp.push_back(lep_id[lep_Hindex[i]]);
		tmp.push_back(lep_ptError[lep_Hindex[i]]);
		Candidate.push_back(tmp);
    }
    TLorentzVector H_VXBS;
    for(int i = 0; i < 4; i++){
        std::vector<float> tmp;
        tmp.push_back(lepFSR_ptVXBS[lep_Hindex[i]]);
        tmp.push_back(lepFSR_eta[lep_Hindex[i]]);
        tmp.push_back(lepFSR_phi[lep_Hindex[i]]);
        tmp.push_back(lepFSR_mass[lep_Hindex[i]]);
        tmp.push_back(lep_id[lep_Hindex[i]]);
        tmp.push_back(lep_ptError[lep_Hindex[i]]);
        Candidate_VXBS.push_back(tmp);
		TLorentzVector lep_tmp;
		lep_tmp.SetPtEtaPhiM(lepFSR_ptVXBS[lep_Hindex[i]], lepFSR_eta[lep_Hindex[i]], lepFSR_phi[lep_Hindex[i]], lepFSR_mass[lep_Hindex[i]]);
		H_VXBS += lep_tmp;
		mass4l_VXBS = H_VXBS.M();
    }
  

        // HIGGS REST FRAME ///////////////////
  	TVector3 boostX,boost_z1,boost_z2,a_1;
  	TLorentzVector mup_z1, mum_z1, mup_z2, mum_z2;
  	TVector3 mup_z1_tr, mum_z1_tr, mup_z2_tr, mum_z2_tr,z2_tr;
  	TVector3 n_1, n_2, n_sc, n_z;
	n_z.SetXYZ(0,0,1);
	if(lep_id[lep_Hindex[0]] > lep_id[lep_Hindex[1]]){
			mup_z1.SetPtEtaPhiM(lepFSR_pt[lep_Hindex[0]], lep_eta[lep_Hindex[0]], lep_phi[lep_Hindex[0]], lep_mass[lep_Hindex[0]]);
			mum_z1.SetPtEtaPhiM(lepFSR_pt[lep_Hindex[1]], lep_eta[lep_Hindex[1]], lep_phi[lep_Hindex[1]], lep_mass[lep_Hindex[1]]);
	}
	else{
			mup_z1.SetPtEtaPhiM(lepFSR_pt[lep_Hindex[1]], lep_eta[lep_Hindex[1]], lep_phi[lep_Hindex[1]], lep_mass[lep_Hindex[1]]);
			mum_z1.SetPtEtaPhiM(lepFSR_pt[lep_Hindex[0]], lep_eta[lep_Hindex[0]], lep_phi[lep_Hindex[0]], lep_mass[lep_Hindex[0]]);
	}
	if(lep_id[lep_Hindex[2]] > lep_id[lep_Hindex[3]]){
			mup_z2.SetPtEtaPhiM(lepFSR_pt[lep_Hindex[2]], lep_eta[lep_Hindex[2]], lep_phi[lep_Hindex[2]], lep_mass[lep_Hindex[2]]);
			mum_z2.SetPtEtaPhiM(lepFSR_pt[lep_Hindex[3]], lep_eta[lep_Hindex[3]], lep_phi[lep_Hindex[3]], lep_mass[lep_Hindex[3]]);
	}
	else{
			mup_z2.SetPtEtaPhiM(lepFSR_pt[lep_Hindex[3]], lep_eta[lep_Hindex[3]], lep_phi[lep_Hindex[3]], lep_mass[lep_Hindex[3]]);
			mum_z2.SetPtEtaPhiM(lepFSR_pt[lep_Hindex[2]], lep_eta[lep_Hindex[2]], lep_phi[lep_Hindex[2]], lep_mass[lep_Hindex[2]]);
	}

	boostX=-(ZZsystem.BoostVector());
	TLorentzVector z1_X(Z1);
	z1_X.Boost(boostX);
	TVector3 z1_X_p3 = TVector3(z1_X.X(),z1_X.Y(),z1_X.Z());
	//cout<<"z1_X_p3: "<<z1_X_p3.X()<<" "<<z1_X_p3.Y()<<" "<<z1_X_p3.Z()<<endl;
	TLorentzVector z2_X(Z2);
	z2_X.Boost(boostX);
	TVector3 z2_X_p3= TVector3(z2_X.X(),z2_X.Y(),z2_X.Z());
	//cout<<"z2_X_p3: "<<z2_X_p3.X()<<" "<<z2_X_p3.Y()<<" "<<z2_X_p3.Z()<<endl;
	TLorentzVector mupZ1_X(mup_z1);
	mupZ1_X.Boost(boostX);
	TVector3 mupZ1_X_p3= TVector3(mupZ1_X.X(),mupZ1_X.Y(),mupZ1_X.Z());
	TLorentzVector mumZ1_X(mum_z1);
//cout<<"mumZ1_X = "<<mumZ1_X.X()<<"\t"<<mumZ1_X.Y()<<"\t"<<mumZ1_X.Z()<<std::endl;
	mumZ1_X.Boost(boostX);
	TVector3 mumZ1_X_p3= TVector3(mumZ1_X.X(),mumZ1_X.Y(),mumZ1_X.Z());
	TLorentzVector mupZ2_X(mup_z2);
	mupZ2_X.Boost(boostX);
	TVector3 mupZ2_X_p3= TVector3(mupZ2_X.X(),mupZ2_X.Y(),mupZ2_X.Z());
	TLorentzVector mumZ2_X(mum_z2);
	mumZ2_X.Boost(boostX);
	TVector3 mumZ2_X_p3= TVector3(mumZ2_X.X(),mumZ2_X.Y(),mumZ2_X.Z());

	n_1=(mumZ1_X_p3.Cross(mupZ1_X_p3)).Unit();
//cout<<"mumZ1_X_p3 = "<<mumZ1_X_p3.X()<<"\t"<<mumZ1_X_p3.Y()<<"\t"<<mumZ1_X_p3.Z()<<endl;
	//cout<<"n_1 : "<<n_1.X()<<" "<<n_1.Y()<<" "<<n_1.Z()<<endl;
	n_2=(mumZ2_X_p3.Cross(mupZ2_X_p3)).Unit();
//cout<<"mumZ2_X_p3 = "<<mumZ2_X_p3.X()<<"\t"<<mumZ2_X_p3.Y()<<"\t"<<mumZ2_X_p3.Z()<<endl;
	//cout<<"n_2 : "<<n_2.X()<<" "<<n_2.Y()<<" "<<n_2.Z()<<endl;
	n_sc=(n_z.Cross(z1_X_p3)).Unit();
	//cout<<"n_sc : "<<n_sc.X()<<" "<<n_sc.Y()<<" "<<n_sc.Z()<<endl;
	mva_cosTheta_star = (z1_X_p3.Unit()).Z();
	mva_phiZZ = ((z1_X_p3.Dot(n_1.Cross(n_2)))/fabs((z1_X_p3.Dot(n_1.Cross(n_2)))))*TMath::ACos(-n_1.Dot(n_2));
//std::cout<<"denomZZ = "<<fabs((z1_X_p3.Dot(n_1.Cross(n_2))))<<std::endl;
//std::cout<<"ACos = "<<TMath::ACos(-n_1.Dot(n_2))<<std::endl;
	mva_phi1 = ((z1_X_p3.Dot(n_1.Cross(n_sc)))/fabs(z1_X_p3.Dot(n_1.Cross(n_sc))))*TMath::ACos(n_1.Dot(n_sc));
//std::cout<<"denom1 = "<<fabs(z1_X_p3.Dot(n_1.Cross(n_sc)))<<std::endl;
//std::cout<<"ACos = "<<TMath::ACos(n_1.Dot(n_sc))<<std::endl;
	//cout<<"phi: "<<phi<<endl;

	// Z_i REST FRAME //////////////////////////////////////
	boost_z1=-(Z1.BoostVector());
	boost_z2=-(Z2.BoostVector());
	//leptons in Z parent reference frame

	TLorentzVector mupZ1_Z1(mup_z1);
	mupZ1_Z1.Boost(boost_z1);
	TVector3 mupZ1_Z1_p3= TVector3(mupZ1_Z1.X(),mupZ1_Z1.Y(),mupZ1_Z1.Z());
	TLorentzVector mumZ1_Z1(mum_z1);
	mumZ1_Z1.Boost(boost_z1);
	TVector3 mumZ1_Z1_p3= TVector3(mumZ1_Z1.X(),mumZ1_Z1.Y(),mumZ1_Z1.Z());

	TLorentzVector mupZ2_Z2(mup_z2);
	mupZ2_Z2.Boost(boost_z2);
	TVector3 mupZ2_Z2_p3= TVector3(mupZ2_Z2.X(),mupZ2_Z2.Y(),mupZ2_Z2.Z());

	TLorentzVector mumZ2_Z2(mum_z2);
	mumZ2_Z2.Boost(boost_z2);
	TVector3 mumZ2_Z2_p3= TVector3(mumZ2_Z2.X(),mumZ2_Z2.Y(),mumZ2_Z2.Z());

	// Z bosons in reciprocal reference frame
	TLorentzVector z1_Z2(Z1);
//std::cout<<"z1_Z2 mass = "<<z1_Z2.M()<<std::endl;
	z1_Z2.Boost(boost_z2);
	TVector3 z1_Z2_p3= TVector3(z1_Z2.X(),z1_Z2.Y(),z1_Z2.Z());

	TLorentzVector z2_Z1(Z2);
//std::cout<<"z2_Z1 mass = "<<z2_Z1.M()<<std::endl;
	z2_Z1.Boost(boost_z1);
	TVector3 z2_Z1_p3= TVector3(z2_Z1.X(),z2_Z1.Y(),z2_Z1.Z());

	n_1=(mumZ1_Z1_p3.Cross(mupZ1_Z1_p3)).Unit();
	n_2=(mumZ2_Z2_p3.Cross(mupZ2_Z2_p3)).Unit();
	n_sc=(n_z.Cross(z1_Z2_p3)).Unit();
	//cout<<"z1_tr.Z: "<<z1_tr.Z()<<endl;
	mva_theta1 = -(z2_Z1_p3.Unit()).Dot(mumZ1_Z1_p3.Unit());
	mva_theta2 = -(z1_Z2_p3.Unit()).Dot(mumZ2_Z2_p3.Unit());

	if(jetidx.size()>2){
		if(Jet1.Rapidity() - Jet2.Rapidity() == 0){
			std::cout<<pTj1<<"\t"<<etaj1<<"\t"<<phij1<<"\t"<<mj1<<std::endl;
			std::cout<<pTj2<<"\t"<<etaj2<<"\t"<<phij2<<"\t"<<mj2<<std::endl;
		}
		TVector3 J1 = TVector3(Jet1.X(), Jet1.Y(), Jet1.Z());
		TVector3 J2 = TVector3(Jet2.X(), Jet2.Y(), Jet2.Z());
		TVector3 H = TVector3(ZZsystem.X(), ZZsystem.Y(), ZZsystem.Z());
		TVector3 HJ1J1 = H + J1 + J2;
		mva_Rhard = (HJ1J1.Pt()) / (Jet1.Pt() + Jet2.Pt() + ZZsystem.Pt());
//		if(mva_Rhard > -999)
//			std::cout<<"mva_Rhard = "<<mva_Rhard<<"\t"<<HJ1J1.Pt()<<"\t"<<Jet1.Pt()<<"\t"<<Jet2.Pt()<<"\t"<<ZZsystem.Pt()<<std::endl;
		mva_zstar = (ZZsystem.Rapidity() - 0.5 * (Jet1.Rapidity() + Jet2.Rapidity())) / (Jet1.Rapidity() - Jet2.Rapidity());
//		if(mva_zstar > -999)
//			std::cout<<"mva_zstar = "<<mva_zstar<<"\t"<<ZZsystem.Rapidity()<<"\t"<<Jet1.Rapidity()<<"\t"<<Jet2.Rapidity()<<std::endl;
	}

    daughters.push_back(SimpleParticle_t((-1)*Zflavor[Z1index]*Zlep1chg[Z1index], Lep1));
    daughters.push_back(SimpleParticle_t((-1)*Zflavor[Z1index]*Zlep2chg[Z1index], Lep2));
    daughters.push_back(SimpleParticle_t((-1)*Zflavor[Z2index]*Zlep1chg[Z2index], Lep3));
    daughters.push_back(SimpleParticle_t((-1)*Zflavor[Z2index]*Zlep2chg[Z2index], Lep4));

    me_0plus_JHU=999.0; me_qqZZ_MCFM=999.0; p0plus_m4l=999.0; bkg_m4l=999.0; D_bkg_kin=999.0; D_bkg=999.0;
    D_bkg_kin_vtx_BS=999.0;
    
    p0minus_VAJHU=999.0; pg1g4_VAJHU=999.0; Dgg10_VAMCFM=999.0; D_g4=999.0; D_g1g4=999.0; D_0m=999.0; D_CP=999.0; D_0hp=999; D_int=999.0;D_L1=999.0; D_L1_int=999.0; D_L1Zg=999.0; D_L1Zgint=999.0;
    p0plus_VAJHU=9999.0; p_GG_SIG_ghg2_1_ghz1prime2_1E4_JHUGen=999.0; pDL1_VAJHU=999.0; pD_L1Zgint=999.0; p_GG_SIG_ghg2_1_ghza1prime2_1E4_JHUGen=999.0; p_GG_SIG_ghg2_1_ghz1_1_ghza1prime2_1E4_JHUGen=999.0, p_GG_SIG_ghg2_1_ghz1_1_ghz1prime2_1E4_JHUGen=999.0, p_GG_SIG_ghg2_1_ghz1_1_ghz2_1_JHUGen=999.0, p0plus_VAJHU=999.0; 

    if(RecoFourMuEvent || RecoFourEEvent || RecoTwoETwoMuEvent || RecoTwoMuTwoEEvent){

	int idL1 = lep_id[lep_Hindex[0]];
	int idL2 = lep_id[lep_Hindex[1]];
	int idL3 = lep_id[lep_Hindex[2]];
	int idL4 = lep_id[lep_Hindex[3]];
	float mass4l = massL4;
	float mass4l_vtxFSR_BS = massL4;
	float cosTheta1, cosTheta2, cosThetaStar, Phi, Phi1;
	cosTheta1=9999.0; cosTheta2=9999.0; cosThetaStar=9999.0; Phi=9999.0; Phi1=9999.0;
    float p_JJVBF_S_SIG_ghv1_1_MCFM_JECNominal;
    float p_HadZH_S_SIG_ghz1_1_MCFM_JECNominal;
    float p_HadWH_S_SIG_ghw1_1_MCFM_JECNominal;
    float p_JJVBF_SIG_ghv1_1_JHUGen_JECNominal;
    float p_HadWH_SIG_ghw1_1_JHUGen_JECNominal;
    float p_HadZH_SIG_ghz1_1_JHUGen_JECNominal;
    float p_JJQCD_SIG_ghg2_1_JHUGen_JECNominal;
    float p_JVBF_SIG_ghv1_1_JHUGen_JECNominal;
    float pAux_JVBF_SIG_ghv1_1_JHUGen_JECNominal;
    float p_JQCD_SIG_ghv1_1_JHUGen_JECNominal;
    float p_JQCD_SIG_ghg2_1_JHUGen_JECNominal;

    float p_JJVBF_BKG_MCFM_JECNominal;
    float p_HadZH_BKG_MCFM_JECNominal;
    float p_HadWH_BKG_MCFM_JECNominal;
    float p_JJQCD_BKG_MCFM_JECNominal;

    float p_HadZH_mavjj_JECNominal;
    float p_HadZH_mavjj_true_JECNominal;
    float p_HadWH_mavjj_JECNominal;
    float p_HadWH_mavjj_true_JECNominal;

    float pConst_JJVBF_S_SIG_ghv1_1_MCFM_JECNominal;
    float pConst_HadZH_S_SIG_ghz1_1_MCFM_JECNominal;
    float pConst_HadWH_S_SIG_ghw1_1_MCFM_JECNominal;
    float pConst_JJVBF_BKG_MCFM_JECNominal;
    float pConst_HadZH_BKG_MCFM_JECNominal;
    float pConst_HadWH_BKG_MCFM_JECNominal;
    float pConst_JJQCD_BKG_MCFM_JECNominal;
    float pConst_JJVBF_SIG_ghv1_1_JHUGen_JECNominal;
    float pConst_HadWH_SIG_ghw1_1_JHUGen_JECNominal;
    float pConst_HadZH_SIG_ghz1_1_JHUGen_JECNominal;
    float pConst_JJQCD_SIG_ghg2_1_JHUGen_JECNominal;

    float D_VBF_QG, D_VBF1j_QG, D_HadWH_QG, D_HadZH_QG;
    float D_bkg_VBFdec;
    p_JJVBF_S_SIG_ghv1_1_MCFM_JECNominal=999.0;
    p_HadZH_S_SIG_ghz1_1_MCFM_JECNominal=999.0;
    p_HadWH_S_SIG_ghw1_1_MCFM_JECNominal=999.0;
    p_JJVBF_BKG_MCFM_JECNominal=999.0;
    p_HadZH_BKG_MCFM_JECNominal=999.0;
    p_HadWH_BKG_MCFM_JECNominal=999.0;
    p_JJQCD_BKG_MCFM_JECNominal=999.0;
    p_HadZH_mavjj_JECNominal=999.0;
    p_HadZH_mavjj_true_JECNominal=999.0;
    p_HadWH_mavjj_JECNominal=999.0;
    p_HadWH_mavjj_true_JECNominal=999.0;
    pConst_JJVBF_S_SIG_ghv1_1_MCFM_JECNominal=999.0;
    pConst_HadZH_S_SIG_ghz1_1_MCFM_JECNominal=999.0;
    pConst_HadWH_S_SIG_ghw1_1_MCFM_JECNominal=999.0;
    pConst_JJVBF_BKG_MCFM_JECNominal=999.0;
    pConst_HadZH_BKG_MCFM_JECNominal=999.0;
    pConst_HadWH_BKG_MCFM_JECNominal=999.0;
    pConst_JJQCD_BKG_MCFM_JECNominal=999.0;

    p_JJVBF_SIG_ghv1_1_JHUGen_JECNominal=999.0;
    pConst_JJVBF_SIG_ghv1_1_JHUGen_JECNominal=999.0;
    p_HadWH_SIG_ghw1_1_JHUGen_JECNominal=999.0;
    pConst_HadWH_SIG_ghw1_1_JHUGen_JECNominal=999.0;
    p_HadZH_SIG_ghz1_1_JHUGen_JECNominal=999.0;
    pConst_HadZH_SIG_ghz1_1_JHUGen_JECNominal=999.0;

    D_HadWH=999.0; D_HadZH=999.0; 
    D_VBF=999.0; D_HadWH=999.0; D_HadZH=999.0;
    D_VBF_QG=999.0; D_VBF1j_QG=999.0; D_HadWH_QG=999.0; D_HadZH_QG=999.0;
    D_bkg_VBFdec=999.0;


		    mela->setInputEvent(&daughters, &associated, 0, 0);
                    mela->setCurrentCandidateFromIndex(0);
                    
                    mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::ZZGG);
                    mela->computeP(me_0plus_JHU, true);
                    
                    mela->setProcess(TVar::H0minus, TVar::JHUGen, TVar::ZZGG);
                    mela->computeP(p0minus_VAJHU, true);
                    
                    pg1g4_VAJHU=0.0;
                    mela->setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::ZZGG);
                    (mela->selfDHggcoupl)[0][0][0]=1.;
                    (mela->selfDHzzcoupl)[0][0][0]=1.;
                    (mela->selfDHzzcoupl)[0][3][0]=1.;
                    mela->computeP(pg1g4_VAJHU, true);
                    pg1g4_VAJHU -= me_0plus_JHU+p0minus_VAJHU;
                    
                    mela->setProcess(TVar::bkgZZ, TVar::MCFM, TVar::ZZQQB);
                    mela->computeP(me_qqZZ_MCFM, true);
                    
                    mela->computeD_gg(TVar::MCFM, TVar::D_gg10, Dgg10_VAMCFM);
                    
                    mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::ZZGG);
                    mela->computePM4l(TVar::SMSyst_None, p0plus_m4l);
                    
                    mela->setProcess(TVar::bkgZZ, TVar::JHUGen, TVar::ZZGG);
                    mela->computePM4l(TVar::SMSyst_None, bkg_m4l);

                    D_bkg_kin = me_0plus_JHU/(me_0plus_JHU+me_qqZZ_MCFM*getDbkgkinConstant(idL1*idL2*idL3*idL3,mass4l)); 
                    D_bkg_kin_vtx_BS = me_0plus_JHU/(me_0plus_JHU+me_qqZZ_MCFM*getDbkgkinConstant(idL1*idL2*idL3*idL3,mass4l_vtxFSR_BS)); 

                    D_bkg = me_0plus_JHU*p0plus_m4l/(me_0plus_JHU*p0plus_m4l+me_qqZZ_MCFM*bkg_m4l*getDbkgConstant(idL1*idL2*idL3*idL4,mass4l)); // superMELA 
                    D_g4 = me_0plus_JHU/(me_0plus_JHU+pow(2.521, 2)*p0minus_VAJHU); // D_0-                
                    D_g1g4 = pg1g4_VAJHU*2.521/(me_0plus_JHU+pow(2.521, 2)*p0minus_VAJHU); // D_CP, 2.521 since g1=1 and g4=1 is used
                    
                    TUtil::computeAngles(cosThetaStar,cosTheta1,cosTheta2,Phi,Phi1, \
                                         Lep1, lep_id[lep_Hindex[0]], Lep2, lep_id[lep_Hindex[1]], \
                                         Lep3, lep_id[lep_Hindex[2]], Lep4, lep_id[lep_Hindex[3]]);
                  
                    if (njets_pt30_eta4p7>=2){

                        mela->setProcess(TVar::HSMHiggs, TVar::MCFM, TVar::JJVBF_S);
                        mela->computeProdDecP(p_JJVBF_S_SIG_ghv1_1_MCFM_JECNominal);
                        mela->getConstant(pConst_JJVBF_S_SIG_ghv1_1_MCFM_JECNominal);

                        mela->setProcess(TVar::HSMHiggs, TVar::MCFM, TVar::Had_ZH_S);
                        mela->computeProdDecP(p_HadZH_S_SIG_ghz1_1_MCFM_JECNominal);
                        mela->getConstant(pConst_HadZH_S_SIG_ghz1_1_MCFM_JECNominal);

                        mela->setProcess(TVar::HSMHiggs, TVar::MCFM, TVar::Had_WH_S);
                        mela->computeProdDecP(p_HadWH_S_SIG_ghw1_1_MCFM_JECNominal);
                        mela->getConstant(pConst_HadWH_S_SIG_ghw1_1_MCFM_JECNominal);

                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::JJVBF);
                        mela->computeProdP(p_JJVBF_SIG_ghv1_1_JHUGen_JECNominal);
                        mela->getConstant(pConst_JJVBF_SIG_ghv1_1_JHUGen_JECNominal);

                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::Had_WH);
                        mela->computeProdP(p_HadWH_SIG_ghw1_1_JHUGen_JECNominal);
                        mela->getConstant(pConst_HadWH_SIG_ghw1_1_JHUGen_JECNominal);

                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::Had_WH);
                        mela->computeDijetConvBW(p_HadWH_mavjj_JECNominal, false);

                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::Had_WH);
                        mela->computeDijetConvBW(p_HadWH_mavjj_true_JECNominal, true);

                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::Had_ZH);
                        mela->computeProdP(p_HadZH_SIG_ghz1_1_JHUGen_JECNominal);
                        mela->getConstant(pConst_HadZH_SIG_ghz1_1_JHUGen_JECNominal);

                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::Had_ZH);
                        mela->computeDijetConvBW(p_HadZH_mavjj_JECNominal, false);

                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::Had_ZH);
                        mela->computeDijetConvBW(p_HadZH_mavjj_true_JECNominal, true);

                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::JJQCD);
                        mela->computeProdP(p_JJQCD_SIG_ghg2_1_JHUGen_JECNominal);
                        mela->getConstant(pConst_JJQCD_SIG_ghg2_1_JHUGen_JECNominal);

                        mela->setProcess(TVar::bkgZZ, TVar::MCFM, TVar::JJVBF);
                        mela->computeProdDecP(p_JJVBF_BKG_MCFM_JECNominal);
                        mela->getConstant(pConst_JJVBF_BKG_MCFM_JECNominal);

                        mela->setProcess(TVar::bkgZZ, TVar::MCFM, TVar::Had_ZH);
                        mela->computeProdDecP(p_HadZH_BKG_MCFM_JECNominal);
                        mela->getConstant(pConst_HadZH_BKG_MCFM_JECNominal);

                        mela->setProcess(TVar::bkgZZ, TVar::MCFM, TVar::Had_WH);
                        mela->computeProdDecP(p_HadWH_BKG_MCFM_JECNominal);
                        mela->getConstant(pConst_HadWH_BKG_MCFM_JECNominal);

                        mela->setProcess(TVar::bkgZZ, TVar::MCFM, TVar::JJQCD);
                        mela->computeProdDecP(p_JJQCD_BKG_MCFM_JECNominal);
                        mela->getConstant(pConst_JJQCD_BKG_MCFM_JECNominal);
                        
                        D_VBF = 1./(1.+ getDVBF2jetsConstant(mass4l)*p_JJQCD_SIG_ghg2_1_JHUGen_JECNominal/p_JJVBF_SIG_ghv1_1_JHUGen_JECNominal);
                        D_HadWH = 1./(1.+ getDWHhConstant(mass4l)*(p_HadWH_mavjj_true_JECNominal*p_JJQCD_SIG_ghg2_1_JHUGen_JECNominal)/(p_HadWH_mavjj_JECNominal*p_HadWH_SIG_ghw1_1_JHUGen_JECNominal));
                        D_HadZH =  1./(1.+ getDZHhConstant(mass4l)*(p_HadZH_mavjj_true_JECNominal*p_JJQCD_SIG_ghg2_1_JHUGen_JECNominal)/(p_HadZH_mavjj_JECNominal*p_HadZH_SIG_ghz1_1_JHUGen_JECNominal));
                        
                        //D_bkg_VBFdec
                        float DbkgVBFdecConstant = getDbkgVBFdecConstant(idL1*idL2*idL3*idL3,mass4l);

                        float vbf = p_JJVBF_S_SIG_ghv1_1_MCFM_JECNominal/pConst_JJVBF_S_SIG_ghv1_1_MCFM_JECNominal;
                        float zh = p_HadZH_S_SIG_ghz1_1_MCFM_JECNominal/pConst_HadZH_S_SIG_ghz1_1_MCFM_JECNominal;
                        float wh = p_HadWH_S_SIG_ghw1_1_MCFM_JECNominal/pConst_HadWH_S_SIG_ghw1_1_MCFM_JECNominal;
                        float constA = 1./(1./pConst_JJVBF_S_SIG_ghv1_1_MCFM_JECNominal+1./pConst_HadZH_S_SIG_ghz1_1_MCFM_JECNominal+1./pConst_HadWH_S_SIG_ghw1_1_MCFM_JECNominal);

                        float vbs = p_JJVBF_BKG_MCFM_JECNominal/pConst_JJVBF_BKG_MCFM_JECNominal;
                        float zzz = p_HadZH_BKG_MCFM_JECNominal/pConst_HadZH_BKG_MCFM_JECNominal;
                        float wzz = p_HadWH_BKG_MCFM_JECNominal/pConst_HadWH_BKG_MCFM_JECNominal;
                        float qcdzz = p_JJQCD_BKG_MCFM_JECNominal/pConst_JJQCD_BKG_MCFM_JECNominal;
                        float constB = 1./(1./pConst_JJVBF_BKG_MCFM_JECNominal+1./pConst_HadZH_BKG_MCFM_JECNominal+1./pConst_HadWH_BKG_MCFM_JECNominal+1./pConst_JJQCD_BKG_MCFM_JECNominal);

                        const float scale_Pmjj_vb=1;
                        float scale_Pmjj_z = p_HadZH_mavjj_JECNominal/p_HadZH_mavjj_true_JECNominal;
                        float scale_Pmjj_w = p_HadWH_mavjj_JECNominal/p_HadWH_mavjj_true_JECNominal;

                        vbf *= scale_Pmjj_vb;
                        vbs *= scale_Pmjj_vb;

                        zh *= scale_Pmjj_z;
                        zzz *= scale_Pmjj_z;

                        wh *= scale_Pmjj_w;
                        wzz *= scale_Pmjj_w;


                        float PA = (vbf + zh + wh)*constA;
                        float PB = (vbs + zzz + wzz + qcdzz)*constB;

                        //std::cout<<"DbkgVBFdecConstant: "<<DbkgVBFdecConstant<<std::endl;
                        //std::cout<<"PA: "<<PA<<std::endl;
                        //std::cout<<"PB: "<<PB<<std::endl;

                        D_bkg_VBFdec =  PA/(PA+DbkgVBFdecConstant*PB);


                        // D_bkg_VHdec
                        float DbkgVHdecConstant = getDbkgVHdecConstant(idL1*idL2*idL3*idL3,mass4l);

                        vbf = p_JJVBF_S_SIG_ghv1_1_MCFM_JECNominal/pConst_JJVBF_S_SIG_ghv1_1_MCFM_JECNominal;
                        zh = p_HadZH_S_SIG_ghz1_1_MCFM_JECNominal/pConst_HadZH_S_SIG_ghz1_1_MCFM_JECNominal;
                        wh = p_HadWH_S_SIG_ghw1_1_MCFM_JECNominal/pConst_HadWH_S_SIG_ghw1_1_MCFM_JECNominal;
                        constA = 1./(1./pConst_JJVBF_S_SIG_ghv1_1_MCFM_JECNominal+1./pConst_HadZH_S_SIG_ghz1_1_MCFM_JECNominal+1./pConst_HadWH_S_SIG_ghw1_1_MCFM_JECNominal);

                        vbs = p_JJVBF_BKG_MCFM_JECNominal/pConst_JJVBF_BKG_MCFM_JECNominal;
                        zzz = p_HadZH_BKG_MCFM_JECNominal/pConst_HadZH_BKG_MCFM_JECNominal;
                        wzz = p_HadWH_BKG_MCFM_JECNominal/pConst_HadWH_BKG_MCFM_JECNominal;
                        qcdzz = p_JJQCD_BKG_MCFM_JECNominal/pConst_JJQCD_BKG_MCFM_JECNominal;
                        constB = 1./(1./pConst_JJVBF_BKG_MCFM_JECNominal+1./pConst_HadZH_BKG_MCFM_JECNominal+1./pConst_HadWH_BKG_MCFM_JECNominal+1./pConst_JJQCD_BKG_MCFM_JECNominal);

                        //scale_Pmjj_vb=1;
                        scale_Pmjj_z = p_HadZH_mavjj_JECNominal/p_HadZH_mavjj_true_JECNominal;
                        scale_Pmjj_w = p_HadWH_mavjj_JECNominal/p_HadWH_mavjj_true_JECNominal;

                        vbf *= scale_Pmjj_vb;
                        vbs *= scale_Pmjj_vb;

                        zh *= scale_Pmjj_z;
                        zzz *= scale_Pmjj_z;

                        wh *= scale_Pmjj_w;
                        wzz *= scale_Pmjj_w;


                        PA = (vbf + zh + wh)*constA;
                        PB = (vbs + zzz + wzz + qcdzz)*constB;

                        D_bkg_VHdec = PA/(PA+DbkgVHdecConstant*PB);


                        /* OLD BUT WORKING
                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::JJVBF);
                        mela->computeProdP(pvbf_VAJHU, true);
                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::JJQCD);
                        mela->computeProdP(phjj_VAJHU, true);
                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::Had_WH);
                        mela->computeProdP(pwh_hadronic_VAJHU, true);
                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::Had_ZH);
                        mela->computeProdP(pzh_hadronic_VAJHU, true);
                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::Had_WH);
                        mela->computeDijetConvBW(p_HadWH_mavjj_JECNominal, false);
                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::Had_WH);
                        mela->computeDijetConvBW(p_HadWH_mavjj_true_JECNominal, true);
                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::Had_ZH);
                        mela->computeDijetConvBW(p_HadZH_mavjj_JECNominal, false);
                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::Had_ZH);
                        mela->computeDijetConvBW(p_HadZH_mavjj_true_JECNominal, true);

                        D_VBF = pvbf_VAJHU/(pvbf_VAJHU+phjj_VAJHU*helper.getDVBF2jetsConstant(mass4l) ); // VBF(2j) vs. gg->H+2j
                        //D_VBF =  1./(1.+ helper.getDVBF2jetsConstant(mass4l)*pvbf_VAJHU+phjj_VAJHU/pvbf_VAJHU);
                        
                        //D_HadWH = pwh_hadronic_VAJHU/(pwh_hadronic_VAJHU+phjj_VAJHU*helper.getDWHhConstant(mass4l) ); // W(->2j)H vs. gg->H+2j
                        //D_HadZH = pzh_hadronic_VAJHU/(pzh_hadronic_VAJHU+phjj_VAJHU*helper.getDZHhConstant(mass4l) ); // Z(->2j)H vs. gg->H+2j

                        D_HadWH =  1./(1.+ helper.getDWHhConstant(mass4l)*(p_HadWH_mavjj_true_JECNominal*phjj_VAJHU)/(p_HadWH_mavjj_JECNominal*pwh_hadronic_VAJHU));
                        D_HadZH =  1./(1.+ helper.getDZHhConstant(mass4l)*(p_HadZH_mavjj_true_JECNominal*phjj_VAJHU)/(p_HadZH_mavjj_JECNominal*pzh_hadronic_VAJHU));
                        */

                    } 
                    else {
                        D_VBF = -1.0; D_HadWH = -1.0; D_HadZH = -1.0;  D_bkg_VBFdec=-1.0; 
                    }
   	                                    
                    if (njets_pt30_eta4p7==1) {
                        
                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::JJVBF);
                        mela->computeProdP(p_JVBF_SIG_ghv1_1_JHUGen_JECNominal,true);
                        mela->getPAux(pAux_JVBF_SIG_ghv1_1_JHUGen_JECNominal);

                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::JQCD);
                        mela->computeProdP(p_JQCD_SIG_ghv1_1_JHUGen_JECNominal,true);

                        D_VBF1j = 1./(1.+ getDVBF1jetConstant(mass4l)*p_JQCD_SIG_ghv1_1_JHUGen_JECNominal/(p_JVBF_SIG_ghv1_1_JHUGen_JECNominal*pAux_JVBF_SIG_ghv1_1_JHUGen_JECNominal));

                        /*
                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::JJVBF);
                        mela->computeProdP(pvbf_VAJHU, true); // Un-integrated ME
                        mela->getPAux(pAux_vbf_VAJHU); // = Integrated / un-integrated

                        mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::JQCD);
                        mela->computeProdP(phj_VAJHU, true);

                        D_VBF1j = pvbf_VAJHU*pAux_vbf_VAJHU/(pvbf_VAJHU*pAux_vbf_VAJHU+phj_VAJHU*helper.getDVBF1jetConstant(mass4l)); // VBF(1j) vs. gg->H+1j
                        */

                    }
                    else {
                        D_VBF1j = -1.0;
                    }
		    mela->resetInputEvent();
    }	
    /*
    mela->setInputEvent(&daughters, &associated, 0, 0);
    mela->setCurrentCandidateFromIndex(0);
    mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::ZZGG);
    mela->computeP(me_0plus_JHU, true);
    
    mela->setProcess(TVar::H0minus, TVar::JHUGen, TVar::ZZGG);
    mela->computeP(p0minus_VAJHU, true);
    // additional probabilities   GG_SIG_ghg2_1_ghz2_1_JHUGen
    mela->setProcess(TVar::H0hplus, TVar::JHUGen, TVar::ZZGG);
    mela->computeP(p0plus_VAJHU, true); 
    
    // p_GG_SIG_ghg2_1_ghz1_1_ghz2_1_JHUGen, Couplings:ghg2=1,0;ghz1=1,0;ghz2=1,0 Options:SubtractP=GG_SIG_ghg2_1_ghz1_1_JHUGen,GG_SIG_ghg2_1_ghz2_1_JHUGen
    mela->setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::ZZGG);
    (mela->selfDHggcoupl)[0][gHIGGS_GG_2][0]=1.;
    (mela->selfDHzzcoupl)[0][gHIGGS_VV_1][0]=1.;
    (mela->selfDHzzcoupl)[0][gHIGGS_VV_2][0]=1.;
    mela->computeP(p_GG_SIG_ghg2_1_ghz1_1_ghz2_1_JHUGen, true);    //FIXME 

    p_GG_SIG_ghg2_1_ghz1_1_ghz2_1_JHUGen -= p0plus_VAJHU+me_0plus_JHU;  


    // p_GG_SIG_ghg2_1_ghz1prime2_1E4_JHUGen
    // Couplings:ghg2=1,0;ghz1_prime2=10000,0
    mela->setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::ZZGG);
    (mela->selfDHggcoupl)[0][gHIGGS_GG_2][0]=1.;
    (mela->selfDHzzcoupl)[0][gHIGGS_VV_1_PRIME2][0]=10000.;
    // (mela->selfDHzzcoupl)[0][3][0]=1.;
    mela->computeP(p_GG_SIG_ghg2_1_ghz1prime2_1E4_JHUGen, true);    //FIXME

	// p_GG_SIG_ghg2_1_ghz1_1_ghz1prime2_1E4_JHUGen/1e8, ghg2=1,0;ghz1=1,0;ghz1_prime2=10000,0, Options:SubtractP=GG_SIG_ghg2_1_ghz1_1_JHUGen,GG_SIG_ghg2_1_ghz1prime2_1E4_JHUGen
	mela->setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::ZZGG);
    (mela->selfDHggcoupl)[0][gHIGGS_GG_2][0]=1.;
    (mela->selfDHzzcoupl)[0][gHIGGS_VV_1][0]=1.;
    (mela->selfDHzzcoupl)[0][gHIGGS_VV_1_PRIME2][0]=10000.;
    mela->computeP(p_GG_SIG_ghg2_1_ghz1_1_ghz1prime2_1E4_JHUGen, true);    //FIXME 
    p_GG_SIG_ghg2_1_ghz1_1_ghz1prime2_1E4_JHUGen -= p_GG_SIG_ghg2_1_ghz1prime2_1E4_JHUGen+me_0plus_JHU;

	// p_GG_SIG_ghg2_1_ghza1prime2_1E4_JHUGen, ghg2=1,0;ghzgs1_prime2=10000,0	
	mela->setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::ZZGG);
    (mela->selfDHggcoupl)[0][gHIGGS_GG_2][0]=1.;
    (mela->selfDHzzcoupl)[0][gHIGGS_ZA_1_PRIME2][0]=10000.;
    // (mela->selfDHzzcoupl)[0][3][0]=1.;
    mela->computeP(p_GG_SIG_ghg2_1_ghza1prime2_1E4_JHUGen, true);    //FIXME

	// p_GG_SIG_ghg2_1_ghz1_1_ghza1prime2_1E4_JHUGen, ghg2=1,0;ghzgs1_prime2=10000,0
	mela->setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::ZZGG);
    (mela->selfDHggcoupl)[0][gHIGGS_GG_2][0]=1.;
    (mela->selfDHzzcoupl)[0][gHIGGS_VV_1][0]=1.;
    (mela->selfDHzzcoupl)[0][gHIGGS_ZA_1_PRIME2][0]=10000.;
    mela->computeP(p_GG_SIG_ghg2_1_ghz1_1_ghza1prime2_1E4_JHUGen, true);    //FIXME

	p_GG_SIG_ghg2_1_ghz1_1_ghza1prime2_1E4_JHUGen -= me_0plus_JHU+p_GG_SIG_ghg2_1_ghza1prime2_1E4_JHUGen;

	pg1g4_VAJHU=0.0;
    mela->setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::ZZGG);
    (mela->selfDHggcoupl)[0][0][0]=1.;
    (mela->selfDHzzcoupl)[0][0][0]=1.;
    (mela->selfDHzzcoupl)[0][3][0]=1.;
    mela->computeP(pg1g4_VAJHU, true);

    pg1g4_VAJHU -= me_0plus_JHU+p0minus_VAJHU;

    mela->setProcess(TVar::bkgZZ, TVar::MCFM, TVar::ZZQQB);
    mela->computeP(me_qqZZ_MCFM, true);
                    
    mela->computeD_gg(TVar::MCFM, TVar::D_gg10, Dgg10_VAMCFM);
                    
    mela->setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::ZZGG);
    mela->computePM4l(TVar::SMSyst_None, p0plus_m4l);
                    
    mela->setProcess(TVar::bkgZZ, TVar::JHUGen, TVar::ZZGG);
    mela->computePM4l(TVar::SMSyst_None, bkg_m4l);

                        ////////////////////////
                    D_bkg_kin = me_0plus_JHU/(me_0plus_JHU+me_qqZZ_MCFM*helper.getDbkgkinConstant(idL1*idL2*idL3*idL3,mass4l)); 
                    D_bkg = me_0plus_JHU*p0plus_m4l/(me_0plus_JHU*p0plus_m4l+me_qqZZ_MCFM*bkg_m4l*helper.getDbkgConstant(idL1*idL2*idL3*idL4,mass4l)); // superMELA 
                    D_g4 = me_0plus_JHU/(me_0plus_JHU+pow(2.521, 2)*p0minus_VAJHU); // D_0-                
                    D_g1g4 = pg1g4_VAJHU*2.521/(me_0plus_JHU+pow(2.521, 2)*p0minus_VAJHU); // D_CP, 2.521 since g1=1 and g4=1 is used
			////////////////////////


    D_0m = me_0plus_JHU / (me_0plus_JHU + (p0minus_VAJHU * pow(getDg4Constant(massZZ),2)));
	D_CP = pg1g4_VAJHU / (2 * sqrt(me_0plus_JHU * p0minus_VAJHU ));
    D_0hp = me_0plus_JHU / (me_0plus_JHU + (p0plus_VAJHU * pow(getDg2Constant(massZZ),2)));
	D_int = p_GG_SIG_ghg2_1_ghz1_1_ghz2_1_JHUGen / (2 * sqrt(me_0plus_JHU * p0plus_VAJHU));
    D_L1 = me_0plus_JHU / (me_0plus_JHU + ((p_GG_SIG_ghg2_1_ghz1prime2_1E4_JHUGen/1e8) * pow(getDL1Constant(massZZ),2)));
	D_L1Zg = me_0plus_JHU / (me_0plus_JHU + ((p_GG_SIG_ghg2_1_ghza1prime2_1E4_JHUGen/1e8) * pow(getDL1ZgsConstant(massZZ),2)));
    mela->resetInputEvent();
    */
    if((nTightMu+nTightEle)<4){
		foundZZCandidate = false;
//  	    std::cout<<"(nTightMu+nTightEle) foundZZCandidate = "<<foundZZCandidate<<std::endl;   
		return foundZZCandidate;
    } 

    if((abs(nTightEleChgSum)+abs(nTightMuChgSum))>(nTightMu+nTightEle-4)){
		foundZZCandidate = false;
//  	    std::cout<<"(nTightEleChgSum) foundZZCandidate = "<<foundZZCandidate<<std::endl;   
        return foundZZCandidate;
    }
    
    if(!foundZZCandidate && ZXdistributions()){
		foundZZCandidate = false;
// 	    std::cout<<"(ZXdistributions) foundZZCandidate = "<<foundZZCandidate<<std::endl;
		return foundZZCandidate;
    } 

//     std::cout<<"foundZZCandidate = "<<foundZZCandidate<<std::endl;
    return foundZZCandidate;
    

}


float H4LTools::getDg4Constant(float ZZMass){
    return spline_g4->Eval(ZZMass);
}

float H4LTools::getDg2Constant(float ZZMass){
    return spline_g2->Eval(ZZMass);
}

float H4LTools::getDL1Constant(float ZZMass){
    return spline_L1->Eval(ZZMass);
}

float H4LTools::getDL1ZgsConstant(float ZZMass){
    return spline_L1Zgs->Eval(ZZMass);
}

std::vector<float> H4LTools::mvaEstimation(TString weight){
	using namespace TMVA;
	float massZ1 = Z1.M();
	float massZ2 = Z2.M();
	float mass4l = ZZsystem.M();
	float njets_pt30_eta4p = njets_pt30_eta4p7;
	TMVA::Reader *reader = new TMVA::Reader( "!Color:Silent" );
	reader->AddVariable( "massZ1", &massZ1 );
        reader->AddVariable( "massZ2", &massZ2 );
        reader->AddVariable( "njets_pt30_eta4p7", &njets_pt30_eta4p );
        reader->AddVariable( "mj1", &mj1);
        reader->AddVariable( "mj2", &mj2 );
        reader->AddVariable( "etaj1", &etaj1 );
        reader->AddVariable( "etaj2", &etaj2 );
        reader->AddVariable( "pTj1", &pTj1 );
        reader->AddVariable( "pTj2", &pTj2 );
        reader->AddVariable( "mva_cosTheta_star", &mva_cosTheta_star );
        reader->AddVariable( "mva_phiZZ", &mva_phiZZ );
        reader->AddVariable( "mva_phi1", &mva_phi1 );
        reader->AddVariable( "mva_theta1", &mva_theta1 );
        reader->AddVariable( "mva_theta2", &mva_theta2 );
        reader->AddVariable( "mjj", &mjj );
        reader->AddVariable( "etajj", &etajj );
        reader->AddVariable( "mass4l", &mass4l );
	reader->BookMVA( "BDTG method", weight );

	std::vector<float> tmp;

	tmp.push_back((reader->EvaluateMulticlass( "BDTG method" ))[0]);
	tmp.push_back((reader->EvaluateMulticlass( "BDTG method" ))[1]);
	tmp.push_back((reader->EvaluateMulticlass( "BDTG method" ))[2]);
	tmp.push_back((reader->EvaluateMulticlass( "BDTG method" ))[3]);

	return tmp;

}

bool H4LTools::ZXdistributions(){
	
	Zlist.clear();
	Zlep1index.clear();
	Zlep2index.clear();
	Zlep1lepindex.clear();
	Zlep2lepindex.clear();
	Zflavor.clear();
	Zlep1pt.clear();
	Zlep2pt.clear();
	Zlep1eta.clear();
	Zlep2eta.clear();
	Zlep1phi.clear();
	Zlep2phi.clear();
	Zlep1mass.clear();
	Zlep2mass.clear();
	Zlep1ptNoFsr.clear();
	Zlep2ptNoFsr.clear();
	Zlep1etaNoFsr.clear();
	Zlep2etaNoFsr.clear();
	Zlep1phiNoFsr.clear();
	Zlep2phiNoFsr.clear();
	Zlep1massNoFsr.clear();
	Zlep2massNoFsr.clear();
	Zlep1chg.clear();
	Zlep2chg.clear();

	int Nlep = lep_pt.size();
	
    for(unsigned int i=0; i<Nlep; i++){
        for(unsigned int j=i+1; j<Nlep; j++){
            if((lep_id[i]+lep_id[j])!=0) continue;
            TLorentzVector li, lj;
            li.SetPtEtaPhiM(lep_pt[i],lep_eta[i],lep_phi[i],lep_mass[i]);
            lj.SetPtEtaPhiM(lep_pt[j],lep_eta[j],lep_phi[j],lep_mass[j]);

            TLorentzVector lifsr, ljfsr;
            lifsr.SetPtEtaPhiM(lepFSR_pt[i],lepFSR_eta[i],lepFSR_phi[i],lepFSR_mass[i]);
            ljfsr.SetPtEtaPhiM(lepFSR_pt[j],lepFSR_eta[j],lepFSR_phi[j],lepFSR_mass[j]);

            TLorentzVector liljfsr = lifsr+ljfsr;
            TLorentzVector Z, Z_noFSR;

            Z = lifsr+ljfsr;
            Z_noFSR = li+lj;

            if (Z.M()>0.0) {            
                        Zlist.push_back(Z);
                        Zlep1index.push_back(i);
                        Zlep2index.push_back(j);
                        Zlep1lepindex.push_back(i);
                        Zlep2lepindex.push_back(j);
						Zflavor.push_back(fabs(lep_id[j]));
                        Zlep1pt.push_back(lepFSR_pt[i]);
                        Zlep2pt.push_back(lepFSR_pt[j]);
                        Zlep1eta.push_back(lepFSR_eta[i]);
                        Zlep2eta.push_back(lepFSR_eta[j]);
                        Zlep1phi.push_back(lepFSR_phi[i]);
                        Zlep2phi.push_back(lepFSR_phi[j]);
                        Zlep1mass.push_back(lepFSR_mass[i]);
                        Zlep2mass.push_back(lepFSR_mass[j]);
                        Zlep1ptNoFsr.push_back(lep_pt[i]);
                        Zlep2ptNoFsr.push_back(lep_pt[j]);
                        Zlep1etaNoFsr.push_back(lep_eta[i]);
                        Zlep2etaNoFsr.push_back(lep_eta[j]);
                        Zlep1phiNoFsr.push_back(lep_phi[i]);
                        Zlep2phiNoFsr.push_back(lep_phi[j]);
                        Zlep1massNoFsr.push_back(lep_mass[i]);
                        Zlep2massNoFsr.push_back(lep_mass[j]);
                        if(lep_id[i] == 13 || lep_id[i] == 11)
	                        Zlep1chg.push_back(-1);
	                    else
	                        Zlep1chg.push_back(1);
                        if(lep_id[j] == 13 || lep_id[j] == 11)
	                        Zlep2chg.push_back(-1);
	                    else
	                        Zlep2chg.push_back(1);
            }

        } // lep i
    } // lep j
    
//     std::cout<<"ZXdistributions; Zlist.size() = "<<Zlist.size()<<std::endl;
    
    if(Zlist.size() > 1)
    	return true;
    else
    	return false;
   
}

