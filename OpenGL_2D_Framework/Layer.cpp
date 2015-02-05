//
//  Layer.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 2/3/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Layer.h"

Layer::Layer(int z):z(z){
    
}

Layer::~Layer(){

}

int Layer::getZ(){
	return z;
}