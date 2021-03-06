﻿#include "Mainui.h"
#include "tui/TuiManager.h"
#include "tui/tagMap/Tag_main.h"
#include "dialog/MsgBox.h"

NS_MAIN_BEGIN

void Mainui::onLoadResources(){
    addImageAsync("main/mainui.png");
    addImageAsync("bag/bagui.png");
    addImageAsync("recombine/recombineui.png");
    addImageAsync("showphone/showphoneui.png");
}

void Mainui::onLoadRescourcesProgress(int idx, int count){
    CCLOG(" onLoadResourcesProgress %d,%d",idx,count);
}

void Mainui::onLoadScene()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("main/mainui.plist");
	TuiManager::getInstance()->parseScene(this,"panel_main",PATH_MAIN);

//    this->setCachable(true);
    
	//注册事件
	CControlView *ctlv = (CControlView*)this->getControl(PANEL_MAIN,CTLV_LEFT);
	ctlv->setOnControlListener(this,ccw_control_selector(Mainui::event_ctlv_left));

	CButton *pBtnOk = (CButton*)this->getControl(PANEL_MAIN,BTN_OK);
	pBtnOk->setOnClickListener(this,ccw_click_selector(Mainui::event_btn_ok));

    pBtnOk->setOnTouchBeganListener(this,ccw_touchbegan_selector(Mainui::event_btn_ok_begin));
    
	CButton *pBtnGo = (CButton*)this->getControl(PANEL_MAIN,BTN_GO);
	pBtnGo->setOnClickListener(this,ccw_click_selector(Mainui::event_btn_go));

	CButton *pBtnPhone = (CButton*)this->getControl(PANEL_MAIN, BTN_SHOWPHONE);
	pBtnPhone->setOnClickListener(this, ccw_click_selector(Mainui::event_btn_showphone));

	CButton *pBtnBag = (CButton*)this->getControl(PANEL_MAIN, BTN_BAG);
	pBtnBag->setOnClickListener(this, ccw_click_selector(Mainui::event_btn_bag));

	CButton *pBtnRecombine = (CButton*)this->getControl(PANEL_MAIN, BTN_RECOMBINE);
	pBtnRecombine->setOnClickListener(this, ccw_click_selector(Mainui::event_btn_recombine));

	CToggleView *pTgvA = (CToggleView*)this->getControl(PANEL_MAIN, TGV_A);
	pTgvA->setOnCheckListener(this, ccw_check_selector(Mainui::event_tgvA_check));

	CToggleView *pTgvB = (CToggleView*)this->getControl(PANEL_MAIN, TGV_B);
	pTgvB->setOnCheckListener(this, ccw_check_selector(Mainui::event_tgvB_check));

	MovieView *pMovie = (MovieView*)this->getControl(PANEL_MAIN, MOVIE_TEST);
	map<string, function<void()>> m;
	m["finish"] = bind(&Mainui::event_movie_finish, this);
	pMovie->setCallBack(m);
}

void Mainui::event_ctlv_left( Ref* pSender, float fx, float fy )
{
	Sprite *pIcon = (Sprite*)this->getControl(PANEL_MAIN,ANIM_COIN);
	pIcon->setPosition(pIcon->getPosition() + Arp(Vec2(fx, fy)));
}

void Mainui::event_movie_finish()
{
	CCLOG("movie finish!!");
}

void Mainui::event_tgvA_check(Ref *pSender, bool bChecked)
{
	MovieView *pMovie = (MovieView*)this->getControl(PANEL_MAIN, MOVIE_TEST);
	if (bChecked){
		pMovie->play(true);
	}else{
		pMovie->stop();
	}
}

void Mainui::event_tgvB_check(Ref *pSender, bool bChecked)
{
	MovieView *pMovie = (MovieView*)this->getControl(PANEL_MAIN, MOVIE_TEST);
	pMovie->setVisible(!bChecked);
	pMovie->isVisible() ? pMovie->play(true) : pMovie->stop();
}

void Mainui::event_btn_ok(Ref* pSender)
{
	CSceneManager::getInstance()->runUIScene(LoadScene("Main::MsgBox"));
//    CButton *pBtn = (CButton*)pSender;
//    pBtn->removeFromParent();
}

bool Mainui::event_btn_ok_begin(cocos2d::Ref *pSender, cocos2d::Touch *pTouch, float fDuration)
{
//    CButton *pBtn = static_cast<CButton*>(pSender) ;
//    pBtn->removeFromParent();
    return true;
}

void Mainui::event_btn_showphone(Ref* pSender)
{
	CSceneManager::getInstance()->replaceScene(
		CCSceneExTransitionFade::create(0.5f, LoadScene("ShowPhone::ShowPhoneui")));
}

void Mainui::event_btn_go(Ref* pSender)
{
	CSceneManager::getInstance()->replaceScene(
		CCSceneExTransitionFade::create(0.5f, LoadScene("Store::Storeui")));
	
}

void Mainui::event_btn_bag(Ref* pSender)
{
	CSceneManager::getInstance()->replaceScene(
		CCSceneExTransitionFade::create(0.5f, LoadScene("Bag::Bagui")));
}

void Mainui::event_btn_recombine(Ref* pSender)
{
	CSceneManager::getInstance()->replaceScene(
		CCSceneExTransitionFade::create(0.5f, LoadScene("Recomebineui")));
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/
Node* Mainui::getPanel( int tagPanel )
{
	Node *pPanel = nullptr;
	switch (tagPanel)
	{
	case PANEL_MAIN:
		pPanel = this->getChildByTag(PANEL_MAIN);
		break;
	}
	return pPanel;
}


NS_MAIN_END 