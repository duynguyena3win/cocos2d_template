//
//  BattleOnlineManager.cpp
//  WoodyPuzzle-mobile
//
//  Created by Apple on 6/19/18.
//

#include "BattleOnlineManager.h"
//#include "BattleRoomData.h"
#include "Firebase.h"

BattleOnlineManager* BattleOnlineManager::s_pInstance = NULL;

BattleOnlineManager* BattleOnlineManager::getInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new BattleOnlineManager();
        s_pInstance->init();
    }
    return s_pInstance;
}

bool BattleOnlineManager::init()
{
    OnUpdateRooms();
    
    return true;
}

void BattleOnlineManager::OnUpdateRooms()
{
    FIRFirestore *defaultFirestore = [FIRFirestore firestore];
    auto settings = [defaultFirestore settings];
    [settings setTimestampsInSnapshotsEnabled:true];
    [defaultFirestore setSettings:settings];
    
    [[defaultFirestore collectionWithPath:@"users"] getDocumentsWithCompletion:^(FIRQuerySnapshot * _Nullable snapshot,
                                  NSError * _Nullable error) {
    
    }];
}
