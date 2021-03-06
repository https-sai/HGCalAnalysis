#include "HGCalAnalysis/HGCalTreeMaker/interface/TupleMaker_GenJets.h"

#include "TLorentzVector.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "FWCore/Framework/interface/ESHandle.h"

TupleMaker_GenJets::TupleMaker_GenJets(const edm::ParameterSet& iConfig):
  inputTag    (iConfig.getUntrackedParameter<edm::InputTag>("source")),
  prefix      (iConfig.getUntrackedParameter<std::string>  ("Prefix")),
  suffix      (iConfig.getUntrackedParameter<std::string>  ("Suffix"))

{
  //produces<std::vector<TLorentzVector> >(prefix +"jetsLVec"+ suffix);
  produces<std::vector<double> >(prefix +"Pt"+ suffix);
  produces<std::vector<double> >(prefix +"Eta"+ suffix);
  produces<std::vector<double> >(prefix +"Phi"+ suffix);
  produces<std::vector<double> >(prefix +"Energy"+ suffix);

  GenJetTok_ = consumes<std::vector<reco::GenJet> >(inputTag);

  debug=false;}

void TupleMaker_GenJets::produce(edm::Event& iEvent, const edm::EventSetup& iSetup){

  //std::unique_ptr<std::vector<TLorentzVector> > jetsLVec(new std::vector<TLorentzVector>());

  std::unique_ptr<std::vector<double> > pt(new std::vector<double>());
  std::unique_ptr<std::vector<double> > eta(new std::vector<double>());
  std::unique_ptr<std::vector<double> > phi(new std::vector<double>());
  std::unique_ptr<std::vector<double> > energy(new std::vector<double>());
  

  edm::Handle<std::vector<reco::GenJet> > jets;  /// check!!!
  iEvent.getByToken(GenJetTok_, jets);

  for(unsigned int ij=0; ij < jets->size(); ij++){
    
    //const reco::GenJet& jet = (*jets)[ij];
						
    pt->push_back(jets->at(ij).pt());
    eta->push_back(jets->at(ij).eta());
    phi->push_back(jets->at(ij).phi());
    energy->push_back(jets->at(ij).energy());


  }

  //iEvent.put(std::move(jetsLVec), "jetsLVec");
  
  iEvent.put(move( pt              ) , prefix + "Pt"            + suffix );
  iEvent.put(move( eta             ) , prefix + "Eta"           + suffix );
  iEvent.put(move( phi             ) , prefix + "Phi"           + suffix );
  iEvent.put(move( energy            ) , prefix + "Energy"             + suffix );


    
}
  
