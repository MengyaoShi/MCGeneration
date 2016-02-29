// -*- C++ -*-
//
// Package:    Filter/GGHAA_FINAL_STATE_FILTER
// Class:      GGHAA_FINAL_STATE_FILTER
// 
/**\class GGHAA_FINAL_STATE_FILTER GGHAA_FINAL_STATE_FILTER.cc Filter/GGHAA_FINAL_STATE_FILTER/plugins/GGHAA_FINAL_STATE_FILTER.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Mengyao Shi
//         Created:  Fri, 30 Oct 2015 10:15:28 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
//
// class declaration
//
using namespace reco;
class GGHAA_FINAL_STATE_FILTER : public edm::EDFilter {
   public:
      explicit GGHAA_FINAL_STATE_FILTER(const edm::ParameterSet&);
      ~GGHAA_FINAL_STATE_FILTER();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() override;
      virtual bool filter(edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      edm::InputTag genParticleTag_;      
      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
GGHAA_FINAL_STATE_FILTER::GGHAA_FINAL_STATE_FILTER(const edm::ParameterSet& iConfig):
   genParticleTag_(iConfig.getParameter<edm::InputTag>("genParticleTag"))
{
}


GGHAA_FINAL_STATE_FILTER::~GGHAA_FINAL_STATE_FILTER()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
GGHAA_FINAL_STATE_FILTER::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   int check = 0;
   edm::Handle<reco::GenParticleCollection> pGenParticles;
   iEvent.getByLabel(genParticleTag_,pGenParticles);
   for(reco::GenParticleCollection::const_iterator iGenParticle=pGenParticles->begin(); iGenParticle != pGenParticles->end(); ++iGenParticle){
     if(iGenParticle->pdgId()==35 && iGenParticle->numberOfDaughters()==2&&iGenParticle->daughterRef(0)->pdgId()==36 &&iGenParticle->daughterRef(1)->pdgId()==36){
       reco::GenParticleRef child0 = iGenParticle->daughterRef(0);
       reco::GenParticleRef child1 = iGenParticle->daughterRef(1);
       if((fabs(child0->daughterRef(0)->pdgId()))== 13 && (fabs(child1->daughterRef(0)->pdgId())==15)){
         check++;
         std::cout<< "Bingo here 2mu2tau is" << std::endl;
       }
       else if(fabs(child1->daughterRef(0)->pdgId())==13&&(fabs(child0->daughterRef(0)->pdgId())==15)){
         check++;
         std::cout<< "Bingo:you got 2mu2tau" <<std::endl;
       }
       
     }
   }
   if(check==1)
     return true;
   else
     return false;       
}

// ------------ method called once each job just before starting event loop  ------------
void 
GGHAA_FINAL_STATE_FILTER::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GGHAA_FINAL_STATE_FILTER::endJob() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
GGHAA_FINAL_STATE_FILTER::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
GGHAA_FINAL_STATE_FILTER::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
GGHAA_FINAL_STATE_FILTER::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
GGHAA_FINAL_STATE_FILTER::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GGHAA_FINAL_STATE_FILTER::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(GGHAA_FINAL_STATE_FILTER);
