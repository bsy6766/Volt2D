#include "gtest/gtest.h"
#include "Sprite.h"

TEST(TEST, POS){
	Sprite* testSprite = new Sprite();
	delete testSprite;
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}