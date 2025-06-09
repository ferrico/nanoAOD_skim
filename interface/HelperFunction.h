#ifndef HelperFunction_H
#define HelperFunction_H
// -*- C++ -*-
//
// Package:     Subsystem/Package
// Class  :     HelperFunction
// 
/**\class HelperFunction HelperFunction.h "HelperFunction.h"

 Description: [one line class summary]

 Usage:
    <usage>

*/
//
// Original Author:  Tongguang Cheng
//         Created:  Mon, 21 Dec 2015 12:47:33 GMT
//

// system include files

// user include files

// forward declarations

#include <memory>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <stdlib.h>
#include <cmath>
#include <iomanip>

#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TMath.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "TFile.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "CommonTools/CandUtils/interface/CenterOfMassBooster.h"
#include "CommonTools/CandUtils/interface/Booster.h"
#include "CommonTools/CandUtils/interface/cloneDecayTree.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/PFParticle.h"
#include <cmath>
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "TrackingTools/AnalyticalJacobians/interface/JacobianCurvilinearToCartesian.h"
#include "TrackingTools/TrajectoryParametrization/interface/GlobalTrajectoryParameters.h"
#include "TrackingTools/TrajectoryParametrization/interface/CartesianTrajectoryError.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"

#include "RecoParticleFlow/PFClusterTools/interface/PFEnergyResolution.h"
#include <TMatrixD.h>

// fit result covariance matrix
#include <TMatrixDSym.h>

namespace reco { class Candidate; class Muon; class GsfElectron; class Track; class PFCandidate; }
namespace edm { class EventSetup; }

#include <vector>
#include "FWCore/Framework/interface/ESHandle.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include <TMatrixDSym.h>
#include <boost/shared_ptr.hpp>

using namespace std;


class HelperFunction
{

   public:
      HelperFunction(int year, bool isData);
      virtual ~HelperFunction();

      void setdebug(int d){debug_= d;};

      //ForZ
      double pterr(std::vector<float> Candidate, bool isData, int year);
      double pterr(TLorentzVector lepton,  double lep_ptError, reco::Candidate *c, bool isData, int year);

      //double pterr(pat::Electron electron, bool isData);
      //double pterr(pat::Muon muon, bool isData);
      double pterr(TLorentzVector fsrPhoton);

      double pterr(reco::GsfElectron* electron, bool isData);
      double pterr(reco::Muon* muon, bool isData);

      double masserror(std::vector<TLorentzVector> p4s, std::vector<double> pTErrs);

      double masserrorFullCov(std::vector<TLorentzVector> p4s, TMatrixDSym covMatrix);

      //double masserror(std::vector<TLorentzVector> p4s, )


      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

      // ---------- member functions ---------------------------

   private:

      HelperFunction(const HelperFunction&); // stop default

      const HelperFunction& operator=(const HelperFunction&); // stop default

      int debug_;

      boost::shared_ptr<TFile>     f_corr_mu;
      boost::shared_ptr<TFile>     f_corr_e_1;
      boost::shared_ptr<TFile>     f_corr_e_2;
      boost::shared_ptr<TFile>     f_corr_e_3;

      boost::shared_ptr<TH2F>      mu_corr;
      boost::shared_ptr<TH2F>      el_corr_1;
      boost::shared_ptr<TH2F>      el_corr_2;
      boost::shared_ptr<TH2F>      el_corr_3;

      TAxis* x_eletaaxis_1;
      TAxis* y_elpTErrOverpTaxis_1;
      double maxPtErrOverPtEl_1;
      double minPtErrOverPtEl_1;

      TAxis* x_elpTaxis_2;
      TAxis* y_eletaaxis_2;
      double maxPtEl_2;
      double minPtEl_2;

      TAxis* x_elpTaxis_3;
      TAxis* y_eletaaxis_3;
      double maxPtEl_3;
      double minPtEl_3;

      TAxis* x_mupTaxis;
      TAxis* y_muetaaxis;
      double maxPtMu;
      double minPtMu;
      

      // ---------- member data --------------------------------

};


#endif
