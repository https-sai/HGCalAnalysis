#include "HGCalAnalysis/HGCalTreeMaker/interface/TupleMaker_PFJets.h"

#include "TLorentzVector.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "FWCore/Framework/interface/ESHandle.h"

TupleMaker_PFJets::TupleMaker_PFJets(const edm::ParameterSet& iConfig):
  inputTag    (iConfig.getUntrackedParameter<edm::InputTag>("source")),
  prefix      (iConfig.getUntrackedParameter<std::string>  ("Prefix")),
  suffix      (iConfig.getUntrackedParameter<std::string>  ("Suffix"))

{
  produces<std::vector<double> >(prefix +"Pt"+ suffix);
  produces<std::vector<double> >(prefix +"Eta"+ suffix);
  produces<std::vector<double> >(prefix +"Phi"+ suffix);
  produces<std::vector<double> >(prefix +"Energy"+ suffix);
  
  produces<std::vector<float> >(prefix +"recoJetschargedHadronEnergyFraction"+ suffix);
  produces<std::vector<float> >(prefix +"recoJetschargedEmEnergyFraction"+ suffix);
  produces<std::vector<float> >(prefix +"recoJetsneutralEmEnergyFraction"+ suffix);
  produces<std::vector<float> >(prefix +"recoJetsHFHadronEnergyFraction"+ suffix);
  produces<std::vector<float> >(prefix +"recoJetsmuonEnergyFraction"+ suffix);
  produces<std::vector<float> >(prefix +"recoJetsneutralEnergyFraction"+ suffix);
  produces<std::vector<float> >(prefix +"recoJetsHFEMEnergyFraction"+ suffix);  
  produces<std::vector<float> >(prefix +"PhotonEnergyFraction"+ suffix);
  produces<std::vector<float> >(prefix +"ElectronEnergyFraction"+ suffix);

  produces<std::vector<float> >(prefix +"ChargedHadronMultiplicity"+ suffix);
  produces<std::vector<float> >(prefix +"NeutralHadronMultiplicity"+ suffix);
  produces<std::vector<float> >(prefix +"PhotonMultiplicity"+ suffix);
  produces<std::vector<float> >(prefix +"ElectronMultiplicity"+ suffix);
  produces<std::vector<float> >(prefix +"MuonMultiplicity"+ suffix);

  PFJetTok_ = consumes<std::vector<reco::PFJet> >(inputTag);

  debug=false;}



void TupleMaker_PFJets::produce(edm::Event& iEvent, const edm::EventSetup& iSetup){

  std::unique_ptr<std::vector<double> > pt(new std::vector<double>());
  std::unique_ptr<std::vector<double> > eta(new std::vector<double>());
  std::unique_ptr<std::vector<double> > phi(new std::vector<double>());
  std::unique_ptr<std::vector<double> > energy(new std::vector<double>());

  //PF energy fraction vectors 
  std::unique_ptr<std::vector<float> > recoJetschargedHadronEnergyFraction(new std::vector<float>());
  std::unique_ptr<std::vector<float> > recoJetschargedEmEnergyFraction(new std::vector<float>());
  std::unique_ptr<std::vector<float> > recoJetsneutralEmEnergyFraction(new std::vector<float>());
  std::unique_ptr<std::vector<float> > recoJetsmuonEnergyFraction(new std::vector<float>());
  std::unique_ptr<std::vector<float> > recoJetsneutralEnergyFraction(new std::vector<float>());
  std::unique_ptr<std::vector<float> > recoJetsHFEMEnergyFraction(new std::vector<float>());
  std::unique_ptr<std::vector<float> > recoJetsHFHadronEnergyFraction(new std::vector<float>());
  std::unique_ptr<std::vector<float> > PhotonEnergyFraction(new std::vector<float>());
  std::unique_ptr<std::vector<float> > ElectronEnergyFraction(new std::vector<float>());

  //PF object multiplicity vectors 
  std::unique_ptr<std::vector<float> > ChargedHadronMultiplicity(new std::vector<float>());
  std::unique_ptr<std::vector<float> > NeutralHadronMultiplicity(new std::vector<float>());
  std::unique_ptr<std::vector<float> > PhotonMultiplicity(new std::vector<float>());
  std::unique_ptr<std::vector<float> > ElectronMultiplicity(new std::vector<float>());
  std::unique_ptr<std::vector<float> > MuonMultiplicity(new std::vector<float>());
  

  edm::Handle<std::vector<reco::PFJet> > jets;  /// check!!!
  iEvent.getByToken(PFJetTok_, jets);

  for(unsigned int ij=0; ij < jets->size(); ij++){

    const reco::PFJet& jet = (*jets)[ij];
    
    pt->push_back(jets->at(ij).pt());
    eta->push_back(jets->at(ij).eta());
    phi->push_back(jets->at(ij).phi());
    energy->push_back(jets->at(ij).energy());

    //PF energy fractions for the jet 
    recoJetschargedHadronEnergyFraction ->push_back( jet.chargedHadronEnergyFraction() );
    recoJetsneutralEnergyFraction       ->push_back( jet.neutralHadronEnergyFraction() );
    recoJetschargedEmEnergyFraction     ->push_back( jet.chargedEmEnergyFraction()     );
    recoJetsneutralEmEnergyFraction     ->push_back( jet.neutralEmEnergyFraction()     );
    recoJetsmuonEnergyFraction          ->push_back( jet.muonEnergyFraction()          );
    PhotonEnergyFraction                ->push_back( jet.photonEnergyFraction()        );
    ElectronEnergyFraction              ->push_back( jet.electronEnergyFraction()      );
    recoJetsHFHadronEnergyFraction      ->push_back( jet.HFHadronEnergyFraction()      );
    recoJetsHFEMEnergyFraction          ->push_back( jet.HFEMEnergyFraction()          );

    //PF particle type multiplicities 
    ChargedHadronMultiplicity ->push_back( jet.chargedHadronMultiplicity() );
    NeutralHadronMultiplicity ->push_back( jet.neutralHadronMultiplicity() );
    PhotonMultiplicity        ->push_back( jet.photonMultiplicity()        );
    ElectronMultiplicity      ->push_back( jet.electronMultiplicity()      );
    MuonMultiplicity          ->push_back( jet.muonMultiplicity()          );

  }

  iEvent.put(move( pt              ) , prefix + "Pt"            + suffix );
  iEvent.put(move( eta             ) , prefix + "Eta"           + suffix );
  iEvent.put(move( phi             ) , prefix + "Phi"           + suffix );
  iEvent.put(move( energy            ) , prefix + "Energy"             + suffix );

  iEvent.put(std::move(recoJetschargedHadronEnergyFraction),prefix +"recoJetschargedHadronEnergyFraction"+ suffix);  
  iEvent.put(std::move(recoJetschargedEmEnergyFraction),prefix +"recoJetschargedEmEnergyFraction"+ suffix);
  iEvent.put(std::move(recoJetsneutralEmEnergyFraction),prefix +"recoJetsneutralEmEnergyFraction"+ suffix);
  iEvent.put(std::move(recoJetsmuonEnergyFraction),prefix +"recoJetsmuonEnergyFraction"+ suffix);
  iEvent.put(std::move(recoJetsneutralEnergyFraction),prefix +"recoJetsneutralEnergyFraction"+ suffix);
  iEvent.put(std::move(PhotonEnergyFraction),prefix +"PhotonEnergyFraction"+ suffix);
  iEvent.put(std::move(ElectronEnergyFraction),prefix +"ElectronEnergyFraction"+ suffix);
  iEvent.put(std::move(recoJetsHFHadronEnergyFraction),prefix +"recoJetsHFHadronEnergyFraction"+ suffix);
  iEvent.put(std::move(recoJetsHFEMEnergyFraction),prefix +"recoJetsHFEMEnergyFraction"+ suffix);

  iEvent.put(std::move(ChargedHadronMultiplicity),prefix + "ChargedHadronMultiplicity"+ suffix);
  iEvent.put(std::move(NeutralHadronMultiplicity),prefix + "NeutralHadronMultiplicity"+ suffix);
  iEvent.put(std::move(PhotonMultiplicity),prefix + "PhotonMultiplicity"+ suffix);
  iEvent.put(std::move(ElectronMultiplicity),prefix + "ElectronMultiplicity"+ suffix);
  iEvent.put(std::move(MuonMultiplicity),prefix + "MuonMultiplicity"+ suffix);

    
}
  
