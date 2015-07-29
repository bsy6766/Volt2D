//
//  TitleButtonLayer.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/10/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "TitleButtonLayer.h"

using namespace Volt2D;

TitleButtonLayer::TitleButtonLayer():
//mouseCursor(0),
newGameButton(0),
creditsButton(0),
optionsButton(0),
exitGameButton(0),
selectingArrowIcon(0),
creditScreen(0),
selectingArrowIconX(315),
selectingButtonID(NEW_GAME),
exitPressed(false),
openingCredits(false),
hasSavedData(false)
{
    
}

TitleButtonLayer::~TitleButtonLayer(){
    
}

void TitleButtonLayer::init(){
    float buttonsX = 535;
    float buttonsYGap = 40;
    float buttonsYStarting = -105;
    
    continueButton = Sprite::createSprite("continueButton", "title scene/continue_button.png");
    continueButton->setZDepth(z_buttons);
    continueButton->setPosition(glm::vec3(buttonsX, buttonsYStarting, 0));
    if(!hasSavedData)
        continueButton->setOpacity(90);
    this->addChild(continueButton);
    
    newGameButton = Sprite::createSprite("newGameButton", "title scene/new_game_button.png");
    newGameButton->setZDepth(z_buttons);
    newGameButton->setPosition(glm::vec3(buttonsX, buttonsYStarting - buttonsYGap, 0));
    this->addChild(newGameButton);
    
    optionsButton = Sprite::createSprite("optionButton", "title scene/options_button.png");
    optionsButton->setZDepth(z_buttons);
    optionsButton->setPosition(glm::vec3(buttonsX, buttonsYStarting - buttonsYGap * 2, 0));
    this->addChild(optionsButton);
    
    creditsButton = Sprite::createSprite("creditsButton", "title scene/credits_button.png");
    creditsButton->setZDepth(z_buttons);
    creditsButton->setPosition(glm::vec3(buttonsX, buttonsYStarting - buttonsYGap * 3, 0));
    this->addChild(creditsButton);
    
    exitGameButton = Sprite::createSprite("exitGameButton", "title scene/exit_game_button.png");
    exitGameButton->setZDepth(z_buttons);
    exitGameButton->setPosition(glm::vec3(buttonsX, buttonsYStarting - buttonsYGap * 4, 0));
    this->addChild(exitGameButton);
    
//    mouseCursor = Sprite::createSprite("moundIcon", "mouse_icon.png");
//    mouseCursor->setZDepth(z_mouse_cursor);
//    this->addChild(mouseCursor);
    
    selectingArrowIcon = Sprite::createSprite("selectingArrowIcon", "title scene/selecting_arrow_icon.png");
    selectingArrowIcon->setZDepth(z_selecting_icon);
    selectingArrowIcon->setPosition(glm::vec3(selectingArrowIconX, newGameButton->getPosition().y, 0));
    this->addChild(selectingArrowIcon);
    
    creditScreen = Sprite::createSprite("creditScreen", "title scene/credit_screen.png");
    creditScreen->setZDepth(z_credit_screen);
    this->addChild(creditScreen);
    creditScreen->setOpacity(0);
    creditScreen->setScale(glm::vec3(0, 0, 1));
    
//    originPoint = new Sprite();
//    originPoint->initSpriteWithTexture("test/point.png");
//    originPoint->setZDepth(998);
//    this->addObject("originPoint", originPoint);
    
//    endPoint = new Sprite();
//    endPoint->initSpriteWithTexture("test/point.png");
//    endPoint->setZDepth(999);
//    this->addObject("endPoint", endPoint);
    
//    ActionDelay delayLoading;
//    delayLoading.initDelay(3);
//    ProgressFromTo fromTo;
//    fromTo.initProgressFromTo(10, 97, 3);
//    ActionCallFunc callbackAction;
//    callbackAction.initActionCallFunc(std::bind(&TitleButtonLayer::testFunc, this));
//    ActionCallFunc cbWithParam;
//    cbWithParam.initActionCallFunc(std::bind(&TitleButtonLayer::testFunc2, this, 1));
//    loadingBar->addActions({new ActionDelay(delayLoading), new ProgressFromTo(fromTo), new ActionCallFunc(callbackAction), new ActionCallFunc(cbWithParam)}, 0);
//    auto delay = ActionDelay::createDelay(1);
//    auto moveTo = ActionMoveTo::createMoveTo(8, glm::vec3(600, -250, 0));
    
    fireBall = ParticleSystem::createWithLuaConfig("fireBallParticleLayer", "Particle/fireBall.lua");
    fireBall->setPosition(glm::vec3(-600, -250, 0));
//    fireBall->addActions({delay, moveTo, delay}, 0);
    fireBall->setZDepth(100);
    
    magicalOrbits = ParticleSystem::createWithLuaConfig("magicalOrbitsLayer", "Particle/magicalOrbits.lua");
    magicalOrbits->setPosition(vec3(-400, 0, 0));
    magicalOrbits->setZDepth(99);
    
    flame = ParticleSystem::createWithLuaConfig("flameParticleLayer", "Particle/flame.lua");
    flame->setPosition(vec3(-200, 0, 0));
    flame->setZDepth(99);
    
    blueMeteor = ParticleSystem::createWithLuaConfig("blueMeteorParticleLayer", "Particle/blueMeteor.lua");
    blueMeteor->setPosition(vec3(50, 0, 0));
    blueMeteor->setZDepth(99);
    
    muhanDojun = ParticleSystem::createWithLuaConfig("muhanDojunParticleLayer", "Particle/muhanDojun.lua");
    muhanDojun->setPosition(vec3(300, 100, 0))  ;
    muhanDojun->setZDepth(99);
}

void TitleButtonLayer::exit(){
    
}

void TitleButtonLayer::update(double dt){
//    BoundingBox* bb = creditScreen->getBoundingBox();
//    originPoint->setPosition(glm::vec3(bb->origin.x, bb->origin.y, 0));
//    endPoint->setPosition(glm::vec3(bb->end.x, bb->end.y, 0));
    
    PS3ControllerWrapper* joystick = Volt2D::Director::getInstance().getJoyStick(0);
    if(joystick) {
        if(!joystickMap[DPAD_DOWN] && joystick->getKeyStatus(DPAD_DOWN) == GLFW_PRESS){
            joystickMap[DPAD_DOWN] = true;
            keyPressed(GLFW_KEY_DOWN, 0);
            cout << "DPAD down pressed" << endl;
        }
        else if(joystickMap[DPAD_DOWN] && joystick->getKeyStatus(DPAD_DOWN) == GLFW_RELEASE){
            joystickMap[DPAD_DOWN] = false;
            //        keyRe(GLFW_KEY_DOWN, 0);
            cout << "DPAD down released" << endl;
        }
        
        if(!joystickMap[DPAD_UP] && joystick->getKeyStatus(DPAD_UP) == GLFW_PRESS){
            joystickMap[DPAD_UP] = true;
            keyPressed(GLFW_KEY_UP, 0);
            cout << "DPAD up pressed" << endl;
        }
        else if(joystickMap[DPAD_UP] && joystick->getKeyStatus(DPAD_UP) == GLFW_RELEASE){
            joystickMap[DPAD_UP] = false;
            //        keyRe(GLFW_KEY_DOWN, 0);
            cout << "DPAD up released" << endl;
        }
    }

    
    
    //must call base class update()
    Layer::update(dt);
}

void TitleButtonLayer::openCredits(){
    if(!openingCredits){
//        auto fadeIn = ActionFadeTo::createFadeTo(0.2, 255.0);
//        auto scaleIn = ActionScaleTo::createScaleTo(0.3, glm::vec3(1, 1, 1));
//        
//        creditScreen->addAction(fadeIn, 0);
//        creditScreen->addAction(scaleIn, 0);
//        creditScreen->runAction();
//        
//        delete fadeIn;
//        delete scaleIn;
    }
}

void TitleButtonLayer::closeCredits(){
    if(openingCredits){
//        auto fadeOut = ActionFadeBy::createFadeBy(0.2, -255);
//        auto scaleOut = ActionScaleTo::createScaleTo(0.3, glm::vec3(0, 0, 1));
//        
//        creditScreen->addAction(fadeOut, 0);
//        creditScreen->addAction(scaleOut, 0);
//        creditScreen->runAction();
//        
//        delete fadeOut;
//        delete scaleOut;
    }
}

void TitleButtonLayer::keyPressed(int key, int mods){
    if(key == GLFW_KEY_PERIOD){
        this->addChild(magicalOrbits);
        this->addChild(flame);
        this->addChild(blueMeteor);
        this->addChild(muhanDojun);
        fireBall->runAction();
        this->addChild(fireBall);
    }
    
    if(key == GLFW_KEY_ENTER){
        switch (selectingButtonID) {
            case NEW_GAME:
                Volt2D::Director::getInstance().pushScene(new BattleScene());
                Volt2D::Director::getInstance().transitionToNextScene(true);
                Volt2D::Director::getInstance().getSoundManager()->playSFX("titleSceneMenuSelect", 0.1);
                break;
            case EXIT_GAME:
				if (!openingCredits)
					Volt2D::Director::getInstance().terminateApp();
                break;
            case CREDITS:
                if (!openingCredits){
                    openCredits();
                    openingCredits = true;
                    Volt2D::Director::getInstance().getSoundManager()->playSFX("titleSceneMenuSelect");
                }
                break;
            case OPTIONS:
                Volt2D::Director::getInstance().getSoundManager()->playSFX("titleSceneMenuSelect", 0.1);
                break;
            default:
                break;
        }
    }
    
	if (!openingCredits){
        if (key == GLFW_KEY_UP){
            Volt2D::Director::getInstance().getSoundManager()->playSFX("titleSceneMenuBrowse", 1.0);
			if (selectingButtonID > 0){
				selectingButtonID--;
				float y;
                switch (selectingButtonID) {
                case CONTINUE:
                    y = continueButton->getPosition().y;
                    break;
				case NEW_GAME:
					y = newGameButton->getPosition().y;
					break;
				case OPTIONS:
					y = optionsButton->getPosition().y;
					break;
				case CREDITS:
					y = creditsButton->getPosition().y;
					break;
				case EXIT_GAME:
					y = exitGameButton->getPosition().y;
					break;

				default:
					break;
				}
				selectingArrowIcon->setPosition(glm::vec3(selectingArrowIconX, y, 0));
			}
		}
        else if (key == GLFW_KEY_DOWN){
            Volt2D::Director::getInstance().getSoundManager()->playSFX("titleSceneMenuBrowse", 0.5);
			if (selectingButtonID < EXIT_GAME){
				selectingButtonID++;
				float y;
				switch (selectingButtonID) {
                case CONTINUE:
                    y = continueButton->getPosition().y;
                    break;
				case NEW_GAME:
					y = newGameButton->getPosition().y;
					break;
				case OPTIONS:
					y = optionsButton->getPosition().y;
					break;
				case CREDITS:
					y = creditsButton->getPosition().y;
					break;
				case EXIT_GAME:
					y = exitGameButton->getPosition().y;
					break;

				default:
					break;
				}
				selectingArrowIcon->setPosition(glm::vec3(selectingArrowIconX, y, 0));
			}
		}
	}
	else{
		if (key == GLFW_KEY_ESCAPE){
			closeCredits();
			openingCredits = false;
		}
	}

	if (key == GLFW_KEY_KP_SUBTRACT || key == GLFW_KEY_MINUS){
		Volt2D::SoundManager* sm = Volt2D::Director::getInstance().getSoundManager();
        float curBgmVol = 0;
        if(mods == GLFW_MOD_SHIFT){
            if(sm->getChannelGroupVolume("BGMGroup", curBgmVol)){
                cout << "current ch group volume = " << curBgmVol << endl;
                curBgmVol -= 0.1f;
                if (curBgmVol < 0)
                    curBgmVol = 0;
                sm->setChannelGroupVolume("BGMGroup", curBgmVol);
            }
            else{
                cout << "failed to get volume" << endl;
            }
        }
        else{
            if(sm->getSoundVolume("titleSceneBgm", curBgmVol)){
                cout << "current volume = " << curBgmVol << endl;
                curBgmVol -= 0.1f;
                if (curBgmVol < 0)
                    curBgmVol = 0;
                sm->setSoundVolume("titleSceneBgm", curBgmVol);
            }
            else{
                cout << "failed to get volume" << endl;
            }
        }
	}
	else if (key == GLFW_KEY_KP_ADD || key == GLFW_KEY_EQUAL){
        Volt2D::SoundManager* sm = Volt2D::Director::getInstance().getSoundManager();
        float curBgmVol = 0;
        if(mods == GLFW_MOD_SHIFT) {
            if(sm->getChannelGroupVolume("BGMGroup", curBgmVol)){
                cout << "current ch group volume = " << curBgmVol << endl;
                curBgmVol += 0.1f;
                if (curBgmVol > 1.0f)
                    curBgmVol = 1.0f;
                sm->setChannelGroupVolume("BGMGroup", curBgmVol);
            }
            else{
                cout << "failed to get volume" << endl;
            }        }
        else{
            if(sm->getSoundVolume("titleSceneBgm", curBgmVol)){
                cout << "current volume = " << curBgmVol << endl;
                curBgmVol += 0.1f;
                if (curBgmVol > 1.0f)
                    curBgmVol = 1.0f;
                sm->setSoundVolume("titleSceneBgm", curBgmVol);
            }
            else{
                cout << "failed to get volume" << endl;
            }
        }
	}

	cout << "key #" << key << endl;
}

void TitleButtonLayer::mouseButton(double x, double y, int button, int action){
    if(button == GLFW_MOUSE_BUTTON_LEFT){
        if(action == GLFW_PRESS){
            if(openingCredits){
                if(!creditScreen->getBoundingBox()->containsPoint(glm::vec2(x, y))){
                    closeCredits();
                    openingCredits = false;
                }
            }
            else{
                if(exitGameButton->getBoundingBox()->containsPoint(glm::vec2(x, y))){
                    exitPressed = true;
                }
                else if(creditsButton->getBoundingBox()->containsPoint(glm::vec2(x, y))){
                    openCredits();
                    openingCredits = true;
                }
            }
        }
        else if(action == GLFW_RELEASE){
            if(exitGameButton->getBoundingBox()->containsPoint(glm::vec2(x, y))){
                if(exitPressed)
                    Volt2D::Director::getInstance().terminateApp();
            }
            else{
                exitPressed = false;
            }
        }
    }
    else if(action == GLFW_MOUSE_BUTTON_RIGHT){
        
    }
}

void TitleButtonLayer::mouseMove(double x, double y){
	glm::vec3 mousePoint = glm::vec3(x, y, 0);
//	mouseCursor->setPosition(mousePoint);
	if (!openingCredits){
        if (continueButton->getBoundingBox()->containsPoint(glm::vec2(mousePoint))){
            selectingButtonID = CONTINUE;
            selectingArrowIcon->setY(continueButton->getPosition().y);
        }
		else if (newGameButton->getBoundingBox()->containsPoint(glm::vec2(mousePoint))){
			selectingButtonID = NEW_GAME;
			selectingArrowIcon->setY(newGameButton->getPosition().y);
		}
		else if (optionsButton->getBoundingBox()->containsPoint(glm::vec2(mousePoint))){
			selectingButtonID = OPTIONS;
			selectingArrowIcon->setY(optionsButton->getPosition().y);
		}
		else if (creditsButton->getBoundingBox()->containsPoint(glm::vec2(mousePoint))){
			selectingButtonID = CREDITS;
			selectingArrowIcon->setY(creditsButton->getPosition().y);
		}
		else if (exitGameButton->getBoundingBox()->containsPoint(glm::vec2(mousePoint))){
			selectingButtonID = EXIT_GAME;
			selectingArrowIcon->setY(exitGameButton->getPosition().y);
		}
	}
}

void TitleButtonLayer::testFunc(){
    cout << "test" << endl;
//    loadingBar->setPercentage(50);
}

void TitleButtonLayer::testFunc2(int num){
    cout << "test2 " << num << endl;
//    loadingBar->setPercentage(25);
//    Volt2D::Director::getInstance().changeWindowSize(640, 360);
}