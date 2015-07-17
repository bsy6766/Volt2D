CC=gcc
CFLAGS=-g -std=c++11
LDFLAGS=-lglfw -lglew -lfmod -lfreetype
FRAMEWORKS=-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
TARGET=JB_Engine_test

SOURCES=ActionDelay.cpp ActionFadeBy.cpp ActionFadeTo.cpp ActionMoveBy.cpp ActionMoveTo.cpp ActionObject.cpp ActionRotateBy.cpp ActionRotateTo.cpp ActionScaleBy.cpp ActionScaleTo.cpp ActionSchedule.cpp BattleScene.cpp BoundingBox.cpp Camera.cpp Director.cpp Font.cpp FontManager.cpp Layer.cpp Object.cpp Particle.cpp ParticleSystem.cpp ParticleSystemManager.cpp Program.cpp ProgressBar.cpp ProgressObject.cpp ProgressRadian.cpp RenderableObject.cpp RenderableObjectManager.cpp Scene.cpp Shader.cpp Sound.cpp SoundManager.cpp Sprite.cpp SpriteAnimation.cpp SpriteObject.cpp SpriteScheduler.cpp SpriteSheet.cpp Text.cpp TextObject.cpp Texture.cpp Timer.cpp TitleButtonLayer.cpp TitleScene.cpp Z_Float.cpp stb_image.cpp main.cpp 
OBJECTS=$(SOURCE:.cpp=.o)

INCLUDES=-I/usr/local/include -I/usr/local/include/GL -I/opt/local/include/freetype2/ -I/usr/local
LIBS=-L/usr/local/lib

# all: 
# 	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(INCLUDES) $(LIBS) $(FRAMEWORKS)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(SOURCES) -o $(TARGET)  $(LDFLAGS) $(INCLUDES) $(LIBS) $(FRAMEWORKS)

clean:
	rm -f *.o
	rm $(TARGET)