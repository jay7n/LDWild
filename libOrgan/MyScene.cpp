#include <libOrgan/MyScene.h>

using namespace cocos2d;


MyLayer::MyLayer()
{
   _moveDone = true;
}

MyLayer::~MyLayer()
{
   
}

cocos2d::CCScene* MyLayer::scene()
{
   CCScene* scene = CCScene::create();

   MyLayer* layer = MyLayer::create();

   scene->addChild(layer);

   return scene;
}


bool MyLayer::init()
{
   if( !CCLayer::init() ) {
      return false;
   }

    _cache = CCSpriteFrameCache::sharedSpriteFrameCache();
   _cache->addSpriteFramesWithFile("bearBig.plist", "bearBig.png");

   CCSize winSize = CCDirector::sharedDirector()->getWinSize();

   CCSprite* sprite = CCSprite::spriteWithSpriteFrame(
      _cache->spriteFrameByName("bear1_.png"));

   CCPoint bearPos = ccp(winSize.width/2, winSize.height/2);
   _bearPos = bearPos;
   sprite->setPosition(_bearPos);

   this->addChild(sprite, 0);

   _meSprite = sprite;
    
    createBearAnim();

    //meMove();
    //this->schedule( schedule_selector(MyLayer::everyFrame) );

   this->setTouchEnabled(true);

   return true;
}

void MyLayer::meMove(void)
{
    // static int currDisX = 5;
    // _meSprite->setPosition(ccp(currDisX,0));
    // currDisX+=5;


   CCFiniteTimeAction* moveBy = CCMoveBy::actionWithDuration(2.0f, _moveBy);
   CCFiniteTimeAction* moveDone =
      CCCallFunc::actionWithTarget(this, callfunc_selector(MyLayer::meMoveDone));
   _meSprite->runAction( CCSequence::actions(moveBy, moveDone, NULL) );
   
   if(_moveDone) {
      _meSprite->runAction(_bearMove);
      _moveDone = false;
   }
}

void MyLayer::meMoveDone(void)
{
   _meSprite->stopAction(_bearMove);
   _moveDone = true;
}

void MyLayer::everyFrame(float dt)
{//meMove(dt);
   //printf("this is test %f", dt);
}

void MyLayer::createBearAnim()
{

   CCArray* animFrames = new CCArray(8);

   char str[64];
   for(int i=1; i<=8; i++) {
      sprintf(str,"bear%d_.png", i);
      CCSpriteFrame* frame = _cache->spriteFrameByName(str);
      animFrames->addObject(frame);
   }

   CCAnimation* animation= CCAnimation::animationWithSpriteFrames(animFrames, 0.4f);
   CCActionInterval* action = CCAnimate::actionWithAnimation(animation);
   CCAction* bearMove = CCRepeatForever::actionWithAction(action);
   _bearMove = bearMove;
   _bearMove->retain();
   
}

void MyLayer::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
   CCTouch* touch = (CCTouch*)touches->anyObject();
   CCPoint location = touch->locationInView();
   location = CCDirector::sharedDirector()->convertToGL(location);
   _bearPos = _meSprite->getPosition();
   _moveBy = ccp(location.x - _bearPos.x, location.y - _bearPos.y);
   
   //_meSprite->stopAction(_bearMove);
   //_meSprite->setDisplayFrame(_cache->spriteFrameByName("bear3_.png"));

   meMove();
}
