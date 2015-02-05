//
//  Scene.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/26/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__Scene__
#define __OpenGL_2D_Framework__Scene__

//#include "CommonInclude.h"
//#include "SpriteManager.h"
//#include "Layer.h"

/*
	Scene class
	Base class
	User creates derive class of Scene class. 
*/

class Scene{
protected:
private:
	//std::map<std::string, Layer> layerMap;


public:
	Scene();
	~Scene();
	Scene(Scene const& other);
	void operator=(Scene const& other);

	void update();
	void render();
};

#endif /* defined(__OpenGL_2D_Framework__Scene__) */
