cd PhysicsTools/NanoAODTools/python/postprocessing/analysis/nanoAOD_skim
git checkout ZXCR_EL9
git clone git@github.com:jbeder/yaml-cpp.git external/yaml-cpp
cd external/yaml-cpp/
git apply ../yamlcpp_pkg_py2to3.patch
mkdir build
cd build
cmake3 .. -DBUILD_SHARED_LIBS=ON
cmake3 --build .
cd $CMSSW_BASE/src
scram b -j 8
cd $CMSSW_BASE/src/PhysicsTools/NanoAODTools/python/postprocessing/analysis/nanoAOD_skim
git clone -b v2.4.2 https://github.com/JHUGen/JHUGenMELA
cd JHUGenMELA
git apply ../external/JHUGen_py2to3.patch
cd ..
sh JHUGenMELA/MELA/setup.sh -j 8
cd JHUGenMELA/MELA/data/el9_amd64_gcc12/
chmod +x *.so
