#!/bin/sh

# the argument to this script will be the file created by proxy command, i.e.
 voms-proxy-init --voms cms --valid 168:00
# Created proxy in /tmp/x509up_u62924.
# then the first argument will be x509up_u62924 only.

#proxy=${1}
#cp /tmp/${proxy} ~/
#export X509_USER_PROXY=~/${proxy}
export X509_USER_PROXY=/afs/cern.ch/user/f/ferrico/x509up_u62924
#voms-proxy-init --voms cms --valid 168:00
