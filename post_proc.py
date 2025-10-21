#!/usr/bin/env python
import os
import sys
import argparse

from PhysicsTools.NanoAODTools.postprocessing.framework.postprocessor import PostProcessor
from PhysicsTools.NanoAODTools.postprocessing.modules.common.muonScaleResProducer import *
from PhysicsTools.NanoAODTools.postprocessing.modules.common.eleScaleSmearingProducer import *
from PhysicsTools.NanoAODTools.postprocessing.modules.common.jetJERC import *
from PhysicsTools.NanoAODTools.postprocessing.modules.common.jetVMAP import * 
from PhysicsTools.NanoAODTools.postprocessing.modules.common.jetIdProducer import *
from PhysicsTools.NanoAODTools.postprocessing.modules.jme.jetmetHelperRun2 import createJMECorrector
from PhysicsTools.NanoAODTools.postprocessing.modules.btv.btagSFProducer import btagSFProducer
from PhysicsTools.NanoAODTools.postprocessing.modules.common.puWeightProducer import *
from PhysicsTools.NanoAODTools.postprocessing.modules.common.jetIdUpdate import *

# Custom module imports
#from H4Lmodule import *
from H4LCppModule import *
from JetSFMaker import *

def parse_arguments():
    """Parse command line arguments."""
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--inputFile", default="", type=str, help="Input file name")
    parser.add_argument("-n", "--entriesToRun", default=0, type=int, help="Set  to 0 if need to run over all entries else put number of entries to run")
    parser.add_argument("-d", "--DownloadFileToLocalThenRun", default=False, type=bool, help="Download file to local then run")
    parser.add_argument("--NOsyst", default=False, action="store_true", help="Do not run systematics")
    parser.add_argument('-o', '--outputFile', default="skimmed_nano.root", type=str, help="Output file name")
    return parser.parse_args()


def getListFromFile(filename):
    """Read file list from a text file."""
    with open(filename, "r") as file:
            return ["root://cms-xrd-global.cern.ch/" + line.strip() for line in file]

def main():
    args = parse_arguments()

    # Initial setup
    testfilelist = []
    modulesToRun = []
    isMC = True
    isFSR = True
    year = None
    year_tag = None
    cfgFile = None
    jsonFileName = None
    sfFileName = None

    entriesToRun = int(args.entriesToRun)
    DownloadFileToLocalThenRun = args.DownloadFileToLocalThenRun

    # Determine list of files to process
    if args.inputFile.endswith(".txt"):
        testfilelist = getListFromFile(args.inputFile)
    elif args.inputFile.endswith(".root"):
        testfilelist.append(args.inputFile)
    else:
        print("INFO: No input file specified. Using default file list.")
        testfilelist = getListFromFile("ExampleInputFileList.txt")
    print("DEBUG: Input file list: {}".format(testfilelist))
    if len(testfilelist) == 0:
        print("ERROR: No input files found. Exiting.")
        exit(1)

    """Determine the year and type (MC or Data) of input ROOT file:
    For data the string "/data/" is always there. So, we take this
    as handle to decide if the root file is MC or data.
    """
    first_file = testfilelist[0]
    isMC = "/data/" not in first_file
    isMC = "ata"  not in first_file

    if "Summer24" in first_file or "Run2024" in first_file:
        year = 2024
        jsonFileName = "golden_Json/Cert_Collisions2024_378981_386951_Golden.json"
        sfFileName = "DeepCSV_102XSF_V2.csv" # FIXME: Update for year 2024
        year_tag = 2024
        cfgFile = "Input_2024.yml"
        modulesToRun.extend([getMuonScaleRes(year, "", isMC, overwritePt=True)])   
        modulesToRun.extend([getEleScaleRes(2024, 2024, isMC, overwritePt=True, EtDependent=True)])
        modulesToRun.extend([getJetIdProducer(2024, "2024")])
        #modulesToRun.extend([jetIdUpdate()])
        modulesToRun.extend([getJetCorrected(2024, "2024", isMC, overwritePt=True)])
        modulesToRun.extend([getJetVetoMap(2024, "2024")])

    if "Summer23" in first_file or "Run2023" in first_file:
        """ 2023 run """
        year = 2023
        jsonFileName = "golden_Json/Cert_Collisions2023_366442_370790_Golden.json"
        sfFileName = "DeepCSV_102XSF_V2.csv" # FIXME: Update for year 2023
        if "BPix" in first_file or "Run2023D" in first_file:
            year_tag = 20235
            cfgFile = "Input_20235.yml"
            modulesToRun.extend([getMuonScaleRes(year, "BPix", isMC, overwritePt=True)])   
            modulesToRun.extend([getEleScaleRes(year, year_tag, isMC, overwritePt=True, EtDependent=True)])
            modulesToRun.extend([getJetCorrected(year, "BPix", isMC, overwritePt=True)])
            #modulesToRun.extend([getJetIdProducer(year, "BPix")])
            modulesToRun.extend([getJetVetoMap(year, "BPix")])
        else:
            year_tag = 20230
            cfgFile = "Input_20230.yml"
            modulesToRun.extend([getMuonScaleRes(year, "", isMC, overwritePt=True)]) 
            modulesToRun.extend([getEleScaleRes(year, year_tag, isMC, overwritePt=True, EtDependent=True)])
            modulesToRun.extend([getJetCorrected(year, "", isMC, overwritePt=True)])
            #modulesToRun.extend([getJetIdProducer(year, "")])
            modulesToRun.extend([getJetVetoMap(year, "")])

    if "Summer22" in first_file or "Run2022" in first_file:
        """Summer22 and Run2022 for identification of 2022 MC and data respectiverly
        """
        year = 2022
        jsonFileName = "golden_Json/Cert_Collisions2022_355100_362760_Golden.json"
        sfFileName = "DeepCSV_102XSF_V2.csv" # FIXME: Update for year 2022
        if "EE" in first_file or "Run2022E" in first_file or "Run2022F" in first_file or "Run2022G" in first_file:
            year_tag = 20225
            cfgFile = "Input_20225.yml"
            jet_tag = "EE"
            if "Run2022E" in first_file: jet_tag = "2022E"
            if "Run2022F" in first_file: jet_tag = "2022F"
            if "Run2022G" in first_file: jet_tag = "2022G"
            modulesToRun.extend([getMuonScaleRes(year, "EE", isMC, overwritePt=True)]) 
            modulesToRun.extend([getEleScaleRes(year, year_tag, isMC, overwritePt=True, EtDependent=False)])
            modulesToRun.extend([getJetCorrected(year, jet_tag, isMC, overwritePt=True)])
            #modulesToRun.extend([getJetIdProducer(year, "EE")])
            modulesToRun.extend([getJetVetoMap(year, "EE")])
        else:
            year_tag = 20220
            cfgFile = "Input_20220.yml"
            modulesToRun.extend([getMuonScaleRes(year, "", isMC, overwritePt=True)]) 
            modulesToRun.extend([getEleScaleRes(year, year_tag, isMC, overwritePt=True, EtDependent=False)])
            modulesToRun.extend([getJetCorrected(year, "", isMC, overwritePt=True)])
            #modulesToRun.extend([getJetIdProducer(year, "")])
            modulesToRun.extend([getJetVetoMap(year, "")])

    print("Input json file: {}".format(jsonFileName))
    print("Input cfg file: {}".format(cfgFile))
    print("isMC: {}".format(isMC))
    print("isFSR: {}".format(isFSR))
    print("year: {}".format(year))
    print("year_tag: {}".format(year_tag))
    print("first_file: {}".format(first_file))

    H4LCppModule = lambda: HZZAnalysisCppProducer(year_tag,cfgFile, isMC, isFSR)
    modulesToRun.extend([H4LCppModule()])

    if isMC:
        #if (not args.NOsyst):
            # FIXME: JES not used properly
            #jetmetCorrector = createJMECorrector(isMC=isMC, dataYear=year, jesUncert="All", jetType = "AK4PFchs")
            #fatJetCorrector = createJMECorrector(isMC=isMC, dataYear=year, jesUncert="All", jetType = "AK8PFPuppi")
            # btagSF = lambda: btagSFProducer("UL"+str(year), algo="deepjet",selectedWPs=['L','M','T','shape_corr'], sfFileName=sfFileName)
            #btagSF = lambda: btagSFProducer(era = "UL"+str(year), algo = "deepcsv")
            #puidSF = lambda: JetSFMaker("%s" % year)
            #modulesToRun.extend([jetmetCorrector(), fatJetCorrector()])#, puidSF()
            # # modulesToRun.extend([jetmetCorrector(), fatJetCorrector(), btagSF(), puidSF()])
        if year == 2022:
            if year_tag == 20225:
                modulesToRun.extend([puWeight(2022, "")])
            else:
                modulesToRun.extend([puWeight(2022, "pre_EE")])
        if year == 2023:
            if year_tag == 20235:
                modulesToRun.extend([puWeight(2023, "")])
            else:
                modulesToRun.extend([puWeight(2023, "pre_BPix")])
        #if year == 2024:
        #        modulesToRun.extend([puWeight(2024, "")]) ----> aggiorna in Input_2024 i root file

        # INFO: Keep the `fwkJobReport=False` to trigger `haddnano.py`
        #            otherwise the output file will have larger size then expected. Reference: https://github.com/cms-nanoAOD/nanoAOD-tools/issues/249
        p=PostProcessor(".",testfilelist, None, None,modules = modulesToRun, provenance=True,fwkJobReport=True,haddFileName="skimmed_nano.root", maxEntries=entriesToRun, prefetch=DownloadFileToLocalThenRun, outputbranchsel="keep_and_drop.txt")
    else:
        #if (not args.NOsyst):
            # FIXME: JES not used properly
            #jetmetCorrector = createJMECorrector(isMC=isMC, dataYear=year, jesUncert="All", jetType = "AK4PFchs")
            #fatJetCorrector = createJMECorrector(isMC=isMC, dataYear=year, jesUncert="All", jetType = "AK8PFPuppi")
            #modulesToRun.extend([jetmetCorrector(), fatJetCorrector()])

        p=PostProcessor(".",testfilelist, None, None, modules = modulesToRun, provenance=True, fwkJobReport=True,haddFileName="skimmed_nano.root", jsonInput=jsonFileName, maxEntries=entriesToRun, prefetch=DownloadFileToLocalThenRun, outputbranchsel="keep_and_drop_data.txt")

    p.run()


if __name__ == "__main__":
    main()
