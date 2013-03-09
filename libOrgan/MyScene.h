#ifndef __MYSCENE_H__
#define __MYSCENE_H__

#include "cocos2d.h"

class MyLayer : public cocos2d::CCLayer
{
public:
   
   static cocos2d::CCScene* scene();

   MyLayer();
   ~MyLayer();
   
   virtual bool init();

   CREATE_FUNC(MyLayer);

   void everyFrame(float dt);

   void meMove(void);

   void meMoveDone(void);

   void createBearAnim();

private:

   virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
   
   cocos2d::CCSprite* _meSprite;
   cocos2d::CCSpriteFrameCache* _cache;
   cocos2d::CCAction* _bearMove;
   cocos2d::CCPoint _moveBy;
   cocos2d::CCPoint _bearPos;
   bool _moveDone;
};

#endif //__MYSCENE_H
