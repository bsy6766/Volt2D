//
//  TitleButtonLayer.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 7/10/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "TitleButtonLayer.h"

TitleButtonLayer::TitleButtonLayer():
mouseCursor(0),
newGameButton(0),
creditsButton(0),
optionsButton(0),
exitGameButton(0),
selectingArrowIcon(0),
creditScreen(0),
selectingArrowIconX(315),
selectingButtonID(NEW_GAME),
exitPressed(false),
openingCredits(false)
{
    
}

TitleButtonLayer::~TitleButtonLayer(){
    
}

void TitleButtonLayer::init(){
    float buttonsX = 469;
    float buttonsYGap = 40;
    float buttonsYStarting = -41;
    
    newGameButton = new Sprite();
    newGameButton->initSpriteWithTexture(GL_TEXTURE_2D, "title scene/new_game_button.png");
    newGameButton->setZDepth(z_buttons);
    newGameButton->setPosition(glm::vec3(buttonsX, buttonsYStarting, 0));
    this->addObject("newGameButton", newGameButton);
    
    optionsButton = new Sprite();
    optionsButton->initSpriteWithTexture(GL_TEXTURE_2D, "title scene/options_button.png");
    optionsButton->setZDepth(z_buttons);
    optionsButton->setPosition(glm::vec3(buttonsX, buttonsYStarting - buttonsYGap, 0));
    this->addObject("optionsButton", optionsButton);
    
    creditsButton = new Sprite();
    creditsButton->initSpriteWithTexture(GL_TEXTURE_2D, "title scene/credits_button.png");
    creditsButton->setZDepth(z_buttons);
    creditsButton->setPosition(glm::vec3(buttonsX, buttonsYStarting - buttonsYGap * 2, 0));
    this->addObject("creditsButton", creditsButton);
    
    exitGameButton = new Sprite();
    exitGameButton->initSpriteWithTexture(GL_TEXTURE_2D, "title scene/exit_game_button.png");
    exitGameButton->setZDepth(z_buttons);
    exitGameButton->setPosition(glm::vec3(buttonsX, buttonsYStarting - buttonsYGap * 3, 0));
    this->addObject("exitGameButton", exitGameButton);
    
    mouseCursor = new Sprite();
    mouseCursor->initSpriteWithTexture(GL_TEXTURE_2D, "mouse_icon.png");
    mouseCursor->setZDepth(z_mouse_cursor);
    this->addObject("mouseCursor", mouseCursor);
    
    selectingArrowIcon = new Sprite();
    selectingArrowIcon->initSpriteWithTexture(GL_TEXTURE_2D, "title scene/selecting_arrow_icon.png");
    selectingArrowIcon->setZDepth(z_selecting_icon);
    selectingArrowIcon->setPosition(glm::vec3(selectingArrowIconX, newGameButton->getPosition().y, 0));
    this->addObject("selectingArrowIcon", selectingArrowIcon);
    
    creditScreen = new Sprite();
    creditScreen->initSpriteWithTexture(GL_TEXTURE_2D, "title scene/credit_screen.png");
    creditScreen->setZDepth(z_credit_screen);
    this->addObject("creditScreen", creditScreen);
    creditScreen->setOpacity(0);
    creditScreen->setScale(glm::vec3(0, 0, 1));
    
    originPoint = new Sprite();
    originPoint->initSpriteWithTexture(GL_TEXTURE_2D, "test/point.png");
    originPoint->setZDepth(998);
    this->addObject("originPoint", originPoint);
    
    endPoint = new Sprite();
    endPoint->initSpriteWithTexture(GL_TEXTURE_2D, "test/point.png");
    endPoint->setZDepth(999);
    this->addObject("endPoint", endPoint);
}

void TitleButtonLayer::exit(){
    
}

void TitleButtonLayer::update(){
    BoundingBox* bb = creditScreen->getBoundingBox();
    originPoint->setPosition(glm::vec3(bb->origin.x, bb->origin.y, 0));
    endPoint->setPosition(glm::vec3(bb->end.x, bb->end.y, 0));
    
    //must call base class update()
    Layer::update();
}

void TitleButtonLayer::openCredits(){
    if(!openingCredits){
        ActionFadeTo fadeIn;
        fadeIn.initFadeTo(255, 0.2);
        
        ActionScaleTo scaleIn;
        scaleIn.initScaleTo(glm::vec3(1,1,1), 0.3);
        
        creditScreen->addAction(new ActionFadeTo(fadeIn), 0);
        creditScreen->addAction(new ActionScaleTo(scaleIn), 0);
    }
}

void TitleButtonLayer::closeCredits(){
    if(openingCredits){
        ActionFadeTo fadeOut;
        fadeOut.initFadeTo(0, 0.2);
        
        ActionScaleTo scaleOut;
        scaleOut.initScaleTo(glm::vec3(0,0,1), 0.3);
        
        creditScreen->addAction(new ActionFadeTo(fadeOut), 0);
        creditScreen->addAction(new ActionScaleTo(scaleOut), 0);
    }
}

void TitleButtonLayer::keyPressed(int key, int mods){
    if(key == GLFW_KEY_ENTER){
        //        Director::getInstance().pushScene(new BattleScene());
        //        Director::getInstance().transitionToNextScene(true);
        switch (selectingButtonID) {
            case EXIT_GAME:
				if (!openingCredits)
					Director::getInstance().terminateApp();
                break;
                
            default:
                break;
        }
    }
	if (!openingCredits){
		if (key == GLFW_KEY_UP){
			if (selectingButtonID > 0){
				selectingButtonID--;
				float y;
				switch (selectingButtonID) {
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
			if (selectingButtonID < EXIT_GAME){
				selectingButtonID++;
				float y;
				switch (selectingButtonID) {
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

	if (key == GLFW_KEY_KP_SUBTRACT){
		SoundManager* sm = Director::getInstance().getSoundManager();
		float curVolume = sm->getVolume("titleSceneBgm");
		cout << "cur vol = " << curVolume << endl;
		curVolume -= 0.1f;
		if (curVolume < 0)
			curVolume = 0;
		sm->setVolume("titleSceneBgm", curVolume);
	}
	else if (key == GLFW_KEY_KP_ADD){
		SoundManager* sm = Director::getInstance().getSoundManager();
		float curVolume = sm->getVolume("titleSceneBgm");
		cout << "cur vol = " << curVolume << endl;
		curVolume += 0.1f;
		if (curVolume > 1)
			curVolume = 1;
		sm->setVolume("titleSceneBgm", curVolume);
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
                    Director::getInstance().terminateApp();
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
	mouseCursor->setPosition(mousePoint);
	if (!openingCredits){
		if (newGameButton->getBoundingBox()->containsPoint(glm::vec2(mousePoint))){
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