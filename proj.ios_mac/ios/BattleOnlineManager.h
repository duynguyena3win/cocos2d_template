//
//  BattleOnlineManager.hpp
//  WoodyPuzzle-mobile
//
//  Created by Apple on 6/19/18.
//

#ifndef __BATTLEONLINEMANAGER_H__
#define __BATTLEONLINEMANAGER_H__

class BattleRoomData;

class BattleOnlineManager
{
public:
    static BattleOnlineManager* getInstance();
    
    void OnUpdateRooms();
private:
    static BattleOnlineManager* s_pInstance;
//    std::vector<BattleRoomData*> _rooms;
    bool init();
};

#endif /* __BATTLEONLINEMANAGER_H__ */

