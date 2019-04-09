#!/bin/bash
export SCRAM_ARCH=slc6_amd64_gcc630
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /u/user/suoh/scratch/SKFlat/CMSSW_9_4_10/src
eval `scramv1 runtime -sh`
cd /u/user/suoh/scratch/SKFlat/CMSSW_9_4_10/src/SKFlatMaker/SKFlatMaker/test/ZpNN/submit_batch/scripts/
cp x509up_u41043 /tmp/x509up_u$UID