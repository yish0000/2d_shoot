//
//  SCSceneManager.h
//  ShootOnline
//
//  Created by Yish on 15/6/3.
//
//

#ifndef ShootOnline_SCSceneManager_h
#define ShootOnline_SCSceneManager_h

#include "SCSceneBase.h"

class SCSceneManager
{
public:
    
    enum
    {
        SCENE_LOADING,
        SCENE_LOGIN,
        SCENE_MAIN,
        SCENE_BATTLE,
    };
    
    enum
    {
        TRANS_MOVEINR,
        TRANS_FADEIN,
    };
    
public:
    SCSceneManager();
    
    void enterScene(int sceneType, int transType, float fTime);
    SCSceneBase* getCurScene() { return m_pCurScene; }
    
    static SCSceneManager& getInstance();
    
protected:
    SCSceneBase* m_pCurScene;
};

#endif
