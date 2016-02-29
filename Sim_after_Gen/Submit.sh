
#!/bin/bash

export SCRAM_ARCH=slc6_amd64_gcc481
cd /afs/cern.ch/user/m/mshi/GHHAA2MUMUTAUTAU_GEN/CMSSW_7_1_11_patch2/src
eval `scramv1 runtime -sh`
cd -
source /afs/cern.ch/cms/caf/setup.sh
cp /afs/cern.ch/user/m/mshi/GHHAA2MUMUTAUTAU_GEN/CMSSW_7_1_11_patch2/src/Sim_after_Gen/BSUB/DIRNAME/GENERATOR.py .
cmsRun GENERATOR.py
cmsStage -f DIRNAME_NUM.root /store/user/mshi/DIRNAME
rm DIRNAME_NUM.root GENERATOR.py
if [ -e histProbFunction_NUM.root ]
    then
    rm histProbFunction_NUM.root*
fi

exit 0
