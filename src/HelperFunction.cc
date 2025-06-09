// -*- C++ -*-
//
// Package:     Subsystem/Package
// Class  :     HelperFunction
// 
// Implementation:
//     [Notes on implementation]
//
// Original Author:  Tongguang Cheng
//         Created:  Mon, 21 Dec 2015 12:47:33 GMT
//

#ifndef HelperFunction_CC
#define HelperFunction_CC
// system include files

// user include files
#include "../interface/HelperFunction.h"

// fileinPath
#include "FWCore/ParameterSet/interface/FileInPath.h"

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
HelperFunction::HelperFunction(int year, bool isData)
{

        //declarations
        debug_ = 0;

        /* Legacy 7+8 TeV
        TString fmu_s = TString(edm::FileInPath ( "KinZfitter/HelperFunction/hists/ebeOverallCorrections.Legacy2013.v0.root" ).fullPath());
        TString fel_s = TString(edm::FileInPath ( "KinZfitter/HelperFunction/hists/ebeOverallCorrections.Legacy2013.v0.root" ).fullPath());

        fel = boost::shared_ptr<TFile>( new TFile(fel_s));
        fmu = boost::shared_ptr<TFile>( new TFile(fmu_s));

        muon_corr_data = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(fmu->Get( "mu_reco53x" )->Clone() )) );
        muon_corr_mc = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(fmu->Get( "mu_mc53x" )->Clone() )) );
                
        electron_corr_data = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(fel->Get( "el_reco53x" )->Clone() )) );
        electron_corr_mc = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(fel->Get( "el_mc53x" )->Clone() )) );
        */

        // ICHEP 2016 13 TeV
        /*
        TString fel_s_mc = TString(edm::FileInPath ( "KinZfitter/HelperFunction/hists/DYJetsToLL_M-50_m2eLUT_m2e.root" ).fullPath());
        TString fmu_s_mc = TString(edm::FileInPath ( "KinZfitter/HelperFunction/hists/DYJetsToLL_M-50_m2muLUT_m2mu.root" ).fullPath());
        TString fel_s_data = TString(edm::FileInPath ( "KinZfitter/HelperFunction/hists/DoubleLepton_m2eLUT_m2e.root" ).fullPath());
        TString fmu_s_data = TString(edm::FileInPath ( "KinZfitter/HelperFunction/hists/DoubleLepton_m2muLUT_m2mu.root" ).fullPath());

        fel_mc = boost::shared_ptr<TFile>( new TFile(fel_s_mc));
        fmu_mc = boost::shared_ptr<TFile>( new TFile(fmu_s_mc));
        fel_data = boost::shared_ptr<TFile>( new TFile(fel_s_data));
        fmu_data = boost::shared_ptr<TFile>( new TFile(fmu_s_data));
                
        muon_corr_data = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(fmu_data->Get( "2mu" )->Clone() )) );
        muon_corr_mc = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(fmu_mc->Get( "2mu" )->Clone() )) );
                
        electron_corr_data = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(fel_data->Get( "2e" )->Clone() )) );
        electron_corr_mc = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(fel_mc->Get( "2e" )->Clone() )) );
        */

        // MORIOND 17
        //
        //
        //  Full Run II
        //TString s_corr_e_1 = TString(edm::FileInPath ("KinZfitter/HelperFunction/hists/FullRunII/madgraph/" + (TString)year + "/LUT_m2e_1.root" ).fullPath());
        //TString s_corr_e_2 = TString(edm::FileInPath ("KinZfitter/HelperFunction/hists/FullRunII/madgraph/" + (TString)year + "/LUT_m2e_2.root" ).fullPath());
        //TString s_corr_e_3 = TString(edm::FileInPath ("KinZfitter/HelperFunction/hists/FullRunII/madgraph/" + (TString)year + "/LUT_m2e_3.root" ).fullPath());
        //TString s_corr_mu = TString(edm::FileInPath ("KinZfitter/HelperFunction/hists/FullRunII/madgraph/" + (TString)year + "/LUT_m2mu.root" ).fullPath());

        TString directory_name;
        if(!isData)
            directory_name = "/afs/cern.ch/work/f/ferrico/private/HZZ_Run3_LXP9/CMSSW_14_0_2/src/PhysicsTools/NanoAODTools/python/postprocessing/analysis/nanoAOD_skim/KinZfitter/HelperFunction/hists/FullRunII/VX_BS_Production_10_2_18/";
            //directory_name = "KinZfitter/HelperFunction/hists/FullRunII/Base_Production_10_2_18/";
        else
            directory_name = "/afs/cern.ch/work/f/ferrico/private/HZZ_Run3_LXP9/CMSSW_14_0_2/src/PhysicsTools/NanoAODTools/python/postprocessing/analysis/nanoAOD_skim/KinZfitter/HelperFunction/hists/FullRunII/Data/";
        directory_name = Form("%s%d/", directory_name.Data(), year);
        /*
        if(year == 2016)
            directory_name = "KinZfitter/HelperFunction/hists/FullRunII/madgraph/2016/";
        else if(year == 2017)
            directory_name = "KinZfitter/HelperFunction/hists/FullRunII/madgraph/2017/";        
        else if(year == 2018)
            directory_name = "KinZfitter/HelperFunction/hists/FullRunII/madgraph/2018/";
        else{
            std::cout<<" --------------------  WRONG YEAR --------------- "<<std::endl;
            return;
        }
        */

        std::cout<<" ---------------------------------------------------------- "<<std::endl;
        std::cout<<" ---------------------------------------------------------- "<<std::endl;
        std::cout<<"ABCDE ---------- LUT directory = "<<directory_name<<std::endl;
        std::cout<<" ---------------------------------------------------------- "<<std::endl;
        std::cout<<" ---------------------------------------------------------- "<<std::endl;
        TString s_corr_e_1 = TString(edm::FileInPath (directory_name + "LUT_2e_1.root").fullPath());
        TString s_corr_e_2 = TString(edm::FileInPath (directory_name + "LUT_2e_1.root").fullPath());
        TString s_corr_e_3 = TString(edm::FileInPath (directory_name + "LUT_2e_3.root").fullPath());
        TString s_corr_mu = TString(edm::FileInPath (directory_name + "LUT_2mu.root" ).fullPath());

        f_corr_e_1 = boost::shared_ptr<TFile>( new TFile(s_corr_e_1)); 
        f_corr_e_2 = boost::shared_ptr<TFile>( new TFile(s_corr_e_2)); 
        f_corr_e_3 = boost::shared_ptr<TFile>( new TFile(s_corr_e_3)); 
        f_corr_mu = boost::shared_ptr<TFile>( new TFile(s_corr_mu));
        
        el_corr_1 = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(f_corr_e_1->Get("e1")->Clone() )) );
        el_corr_2 = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(f_corr_e_2->Get("e1")->Clone() )) );
        el_corr_3 = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(f_corr_e_3->Get("e3")->Clone() )) );
        mu_corr = boost::shared_ptr<TH2F>(  (static_cast<TH2F*>(f_corr_mu->Get("2mu")->Clone() )) );
        
        x_eletaaxis_1 = el_corr_1->GetXaxis(); y_elpTErrOverpTaxis_1 = el_corr_1->GetYaxis();
        maxPtErrOverPtEl_1 = y_elpTErrOverpTaxis_1->GetXmax(); minPtErrOverPtEl_1 = y_elpTErrOverpTaxis_1->GetXmin();

//         x_elpTaxis_2 = el_corr_2->GetXaxis(); y_eletaaxis_2 = el_corr_2->GetYaxis();
//         maxPtEl_2 = x_elpTaxis_2->GetXmax(); minPtEl_2 = x_elpTaxis_2->GetXmin();

        x_elpTaxis_3 = el_corr_3->GetXaxis(); y_eletaaxis_3 = el_corr_3->GetYaxis();
        maxPtEl_3 = x_elpTaxis_3->GetXmax(); minPtEl_3 = x_elpTaxis_3->GetXmin();

        x_mupTaxis = mu_corr->GetXaxis(); y_muetaaxis = mu_corr->GetYaxis();
        maxPtMu = x_mupTaxis->GetXmax(); minPtMu = x_mupTaxis->GetXmin();

}

// HelperFunction::HelperFunction(const HelperFunction& rhs)
// {
//    // do actual copying here;
// }

HelperFunction::~HelperFunction()
{
}

//
// assignment operators
//
// const HelperFunction& HelperFunction::operator=(const HelperFunction& rhs)
// {
//   //An exception safe implementation is
//   HelperFunction temp(rhs);
//   swap(rhs);
//
//   return *this;
// }

//
// member functions
//

double HelperFunction:: masserrorFullCov(std::vector<TLorentzVector> p4s, TMatrixDSym covMatrix){

        int ndim = 3*p4s.size();
        if(debug_) cout<<""<<endl;

        TMatrixD jacobian(1,ndim);

        double e = 0; double mass = 0;
        double px = 0; double py = 0; double pz = 0;
        for (unsigned int ip = 0; ip < p4s.size(); ip++) {
         
            e = e + p4s[ip].E();
            px = px + p4s[ip].Px();
            py = py + p4s[ip].Py();
            pz = pz + p4s[ip].Pz();
        }

        mass = TMath::Sqrt(e*e-px*px-py*py-pz*pz);

        for (unsigned int i = 0, o = 0; i < p4s.size(); i++, o += 3) {

                double pxi = p4s[i].Px();
                double pyi = p4s[i].Py();
                double pzi = p4s[i].Pz();
                double ei = p4s[i].E();

                jacobian(0, o+0) = (e*(pxi/ei) - px)/mass;
                jacobian(0, o+1) = (e*(pyi/ei) - py)/mass;
                jacobian(0, o+2) = (e*(pzi/ei) - pz)/mass;
        }

        TMatrixDSym massCov = covMatrix.Similarity(jacobian);

        double dm2 = massCov(0,0);
        return (dm2 > 0 ? std::sqrt(dm2) : 0.0);

}


double HelperFunction::masserror( std::vector<TLorentzVector> Lep, std::vector<double> pterr){
        // if(Lep.size()!= pterr.size()!=4) {std::cout<<" Lepsize="<<Lep.size()<<", "<<pterr.size()<<std::endl;}
        TLorentzVector compositeParticle ;
        for(unsigned int i=0; i<Lep.size(); i++){
                compositeParticle+=Lep[i];
        }
        double mass  =  compositeParticle.M();

        double masserr = 0;

        for(unsigned int i=0; i<Lep.size(); i++){
                TLorentzVector variedLep; // = Lep[i];

                variedLep.SetPtEtaPhiM(Lep[i].Pt()+ pterr[i], Lep[i].Eta(), Lep[i].Phi(), Lep[i].M());
                TLorentzVector compositeParticleVariation ;
                for(unsigned int j=0; j<Lep.size(); j++){
                        if(i!=j)compositeParticleVariation+=Lep[j];
                        else compositeParticleVariation+=variedLep;
                }
                masserr += (compositeParticleVariation.M()-mass)*(compositeParticleVariation.M()-mass);
        }

        return sqrt(masserr);
}


double HelperFunction::pterr( std::vector< float> Candidate, bool isData, int year){

	double pterrLep = Candidate[5];

	if( fabs(Candidate[4]) == 11){
		double pT_e = Candidate[0];
		double pTerrOverPt_e = (float)(Candidate[5]/pT_e);
		double eta_e = Candidate[1];
	        int xbin = x_eletaaxis_1->FindBin(fabs(eta_e));
        	int ybin = y_elpTErrOverpTaxis_1->FindBin(pTerrOverPt_e);
	        if(pTerrOverPt_e > minPtErrOverPtEl_1 && pTerrOverPt_e < maxPtErrOverPtEl_1 ){
        	        pterrLep*=el_corr_1->GetBinContent(xbin,ybin);
	        }
		else{
                	pterrLep*=1.0;
            	}
	}

	else if( fabs(Candidate[4]) == 13){
    		int xbin = x_mupTaxis->FindBin(Candidate[0]);
    		int ybin = y_muetaaxis->FindBin(fabs(Candidate[1]));
		if(Candidate[0] > minPtMu && Candidate[0] < maxPtMu ){
			pterrLep*=mu_corr->GetBinContent(xbin,ybin);
        	} else {
            		pterrLep*=1.0;
        	}
	}

	else{
		std::cout<<"problem in pterr"<<std::endl;
	}


	pterrLep = Candidate[5];
	return pterrLep;

}

double HelperFunction::pterr( TLorentzVector lepton, double lep_ptError, reco::Candidate *c, bool isData, int year){

  reco::GsfElectron *gsf; reco::Muon *mu;
  reco::PFCandidate *pf;

  pat::Muon *patmu;

  double pterrLep = 0.0;

  if ((gsf = dynamic_cast<reco::GsfElectron *> (&(*c)) ) != 0)
  {

    pterrLep=pterr(gsf, isData);

    double pT_e = gsf->pt();
    double pTerrOverPt_e = (float)(pterrLep/pT_e);
    double eta_e = gsf->eta();
    
    if (gsf->ecalDriven()) {
    	int xbin = x_eletaaxis_1->FindBin(fabs(eta_e));
    	int ybin = y_elpTErrOverpTaxis_1->FindBin(pTerrOverPt_e);
    	if(pTerrOverPt_e > minPtErrOverPtEl_1 && pTerrOverPt_e < maxPtErrOverPtEl_1 ){
    		pterrLep*=el_corr_1->GetBinContent(xbin,ybin);    		
	    }
	    else{
    		pterrLep*=1.0;
	    }
    }
    else{
    	int xbin = x_elpTaxis_3->FindBin(pT_e);
        int ybin = y_eletaaxis_3->FindBin(fabs(eta_e));
        if(pT_e > minPtEl_3 && pT_e < maxPtEl_3 ){
            pterrLep*=el_corr_3->GetBinContent(xbin,ybin);
        }
        else{
            pterrLep*=1.0;
        }
    }
    

  }
  else if ((mu = dynamic_cast<reco::Muon *> (&(*c)) ) != 0)
  {
    pterrLep=lep_ptError;

    int xbin = x_mupTaxis->FindBin(lepton.Pt());
    int ybin = y_muetaaxis->FindBin(fabs(lepton.Eta()));
    if(lepton.Pt()>minPtMu && lepton.Pt()<maxPtMu ){
            pterrLep*=mu_corr->GetBinContent(xbin,ybin);
        } else {
            pterrLep*=1.0;
        }
      }
  else if ((pf = dynamic_cast<reco::PFCandidate *> (&(*c)) ) != 0)
      { 
        pterrLep=1;//pterr(c, isData, year);
      }

      return pterrLep;

    }

    double HelperFunction::pterr( reco::Muon* mu, bool isData){

            double pterr = mu->muonBestTrack()->ptError();

            return pterr;
    }


    double HelperFunction::pterr( reco::GsfElectron * elec, bool isData ){

            if(debug_) cout<<"reco:gsfelectron pt err"<<endl; 

            double perr = elec->p();

            if (elec->ecalDriven()){
               perr = elec->p4Error(reco::GsfElectron::P4_COMBINATION);         
            }
            else{

                     double ecalEnergy = elec->correctedEcalEnergy() ;

                     if(debug_)cout<<"ecalEnergy "<<ecalEnergy<<endl;
                     double err2 = 0.0;
                     if (elec->isEB()) {
                            err2 += (5.24e-02*5.24e-02)/ecalEnergy;
                            err2 += (2.01e-01*2.01e-01)/(ecalEnergy*ecalEnergy);
                            err2 += 1.00e-02*1.00e-02;
                     } else if (elec->isEE()) {
                            err2 += (1.46e-01*1.46e-01)/ecalEnergy;
                            err2 += (9.21e-01*9.21e-01)/(ecalEnergy*ecalEnergy);
                            err2 += 1.94e-03*1.94e-03;
                     }
                     perr = ecalEnergy * sqrt(err2);

            }
             
            double pterr = perr*elec->pt()/elec->p();

            return pterr;

    }


    double HelperFunction::pterr(TLorentzVector ph){

             if(debug_) cout<<"perr for pf photon"<<endl;

             double perr = PFEnergyResolution().getEnergyResolutionEm(ph.E(), ph.Eta());

             double pterr = perr*ph.Pt()/ph.P();

             return pterr;
    }


    //
    // const member functions
    //

    //
    // static member functions
    //
#endif
