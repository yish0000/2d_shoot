//
//  SCSceneManager.cpp
//  ShootOnline
//
//  Created by Yish on 15/6/3.
//
//

#include "cocos2d.h"
#include "SCSceneManager.h"

#include "SCSceneLoading.h"
#include "SCSceneLogin.h"
#include "SCSceneMain.h"
#include "SCSceneBattle.h"

USING_NS_CC;

SCSceneManager::SCSceneManager()
    : m_pCurScene(NULL)
{
}

SCSceneManager& SCSceneManager::getInstance()
{
    static SCSceneManager obj;
    return obj;
}

static TransitionScene* createTransitionScene(int transType, float fTime, Scene* pScene)
{
    switch(transType)
    {
        case TRANS_FADEIN:
            return TransitionFade::create(fTime, pScene, Color3B(0, 0, 0));
        case TRANS_MOVEINR:
            return TransitionMoveInR::create(fTime, pScene);
        default:
            return NULL;
    }
}

void SCSceneManager::enterScene(int sceneType, int transType, float fTime)
{
    SCSceneBase* pScene = NULL;
    switch(sceneType)
    {
        case SCENE_LOADING:
            pScene = SCSceneLoading::create();
            break;
        case SCENE_LOGIN:
            pScene = SCSceneLoading::create();
            break;
        case SCENE_MAIN:
            pScene = SCSceneMain::create();
            break;
        case SCENE_BATTLE:
            pScene = SCSceneBattle::create();
            break;
        default:
            CCLOG("SCSceneManager::enterScene, unknown scene type (%d)!", sceneType);
            return;
    }
    
	if( Director::getInstance()->getRunningScene() )
	{
		TransitionScene* pTransScene = createTransitionScene(transType, fTime, pScene);
		if( !pTransScene )
		{
			CCLOG("SCSceneManager::enterScene, failed to create the transition scene!");
			return;
		}

	    Director::getInstance()->replaceScene(pTransScene);
	}
	else
	{
		Director::getInstance()->runWithScene(pScene);
	}

	m_pCurScene = pScene;
    CCLOG("[SCSceneManager] enter scene (%d)", sceneType);
}