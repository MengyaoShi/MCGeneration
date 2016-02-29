# MCGeneration
I write this readme for not generate events in CMSSW_7_11, but to do simulation and run filter, get our 2mu2tau final state. The main thing is in ggHaaSimulation.py, you should briefly have a look to save time.

cmsrel CMSSW_7_1_11_patch2

cd src

cmsenv

git clone everything

cd Sim_after_Gen

change line 30 of ggHaaSimulation

change everything in Submit.sh "mshi" to your own user name.

Then ./generate.sh you will get instruction how to submit.
