//
// Created by dboccanfuso on 3/4/26.
//

#include "RunAction.hh"
#include <G4AnalysisManager.hh>

RunAction::RunAction() {
    auto* analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetVerboseLevel(0);
    analysisManager->SetNtupleMerging(true);
    analysisManager->CreateNtuple("testBeam", "info per event");
    //primaries
    analysisManager->CreateNtupleDColumn("primary_x"); //0
    analysisManager->CreateNtupleDColumn("primary_y"); //1
    analysisManager->CreateNtupleDColumn("primary_z"); //2
    analysisManager->CreateNtupleDColumn("primary_px");//3
    analysisManager->CreateNtupleDColumn("primary_py");//4
    analysisManager->CreateNtupleDColumn("primary_pz");//5
    analysisManager->CreateNtupleDColumn("primary_E"); //6

    // VDet1
    analysisManager->CreateNtupleIColumn("vd1_hit");  //7
    analysisManager->CreateNtupleDColumn("vd1_x");    //8
    analysisManager->CreateNtupleDColumn("vd1_y");    //9
    analysisManager->CreateNtupleDColumn("vd1_z");    //10
    analysisManager->CreateNtupleDColumn("vd1_px");   //11
    analysisManager->CreateNtupleDColumn("vd1_py");   //12
    analysisManager->CreateNtupleDColumn("vd1_pz");   //13
    analysisManager->CreateNtupleDColumn("vd1_t");    //14
    analysisManager->CreateNtupleDColumn("vd1_E");    //15

    // VDet2
    analysisManager->CreateNtupleIColumn("vd2_hit");  //16
    analysisManager->CreateNtupleDColumn("vd2_x");    //17
    analysisManager->CreateNtupleDColumn("vd2_y");    //18
    analysisManager->CreateNtupleDColumn("vd2_z");    //19
    analysisManager->CreateNtupleDColumn("vd2_px");   //20
    analysisManager->CreateNtupleDColumn("vd2_py");   //21
    analysisManager->CreateNtupleDColumn("vd2_pz");   //22
    analysisManager->CreateNtupleDColumn("vd2_t");    //23
    analysisManager->CreateNtupleDColumn("vd2_E");    //24

    // VDet3
    analysisManager->CreateNtupleIColumn("vd3_hit");  //25
    analysisManager->CreateNtupleDColumn("vd3_x");    //26
    analysisManager->CreateNtupleDColumn("vd3_y");    //27
    analysisManager->CreateNtupleDColumn("vd3_z");    //28
    analysisManager->CreateNtupleDColumn("vd3_px");   //29
    analysisManager->CreateNtupleDColumn("vd3_py");   //30
    analysisManager->CreateNtupleDColumn("vd3_pz");   //31
    analysisManager->CreateNtupleDColumn("vd3_t");    //32
    analysisManager->CreateNtupleDColumn("vd3_E");    //33

    //Edep
    analysisManager->CreateNtupleDColumn("edepPlastic1"); //34
    analysisManager->CreateNtupleDColumn("edepMM1");      //35
    analysisManager->CreateNtupleDColumn("edepPlastic2"); //36
    analysisManager->CreateNtupleDColumn("edepMM2");      //37
    analysisManager->CreateNtupleDColumn("edepBox");      //38
    analysisManager->CreateNtupleDColumn("edepPreCalo");  //39
    analysisManager->CreateNtupleDColumn("edepCalo");     //40

    analysisManager->FinishNtuple();
}

void RunAction::BeginOfRunAction(const G4Run*) {
    auto* analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile("output.root"); //temporary
}

void RunAction::EndOfRunAction(const G4Run*) {
    auto* analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}
