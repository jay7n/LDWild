#ifndef LDCCDERIVED_H
#define LDCCDERIVED_H

#include <libBasic/LDBase.h>
#include <libOrgan/LDLayers.h>

class LDCCLayer : public CoLayer
{
public:
   LDCCLayer(void) {}

   //override cocos2dx methods
   virtual bool init(LDLayer* ldlayer) {
      bool ret = false;
      if(CoLayer::init()) {
         assert(ldlayer);
         _ldlayer = ldlayer;
         this->schedule( CoScheduleSelector(LDCCLayer::scheduleCB) );
         ret = true;
      }
      return ret;
   }
   
   virtual void ccTouchesBegan(CoSet* touches, CoEvent* event) {
      if(_ldlayer) {
         _ldlayer->RespondTouchEvent(touches, event, LDLayer::TET_BEGAN);
      }
   }
   
   virtual void ccTouchesMoved(CoSet* touches, CoEvent* event) {
      if(_ldlayer) {
         _ldlayer->RespondTouchEvent(touches, event, LDLayer::TET_MOVE);
      }
   }
   
   virtual void ccTouchesEnded(CoSet* touches, CoEvent* event) {
      if(_ldlayer) {
         _ldlayer->RespondTouchEvent(touches, event, LDLayer::TET_END);
      }
   }

protected:
   void scheduleCB(float dt) {
      if(_ldlayer) {
         _ldlayer->ScheduleCB(dt);
      }
   }
   
private:
   LDLayer* _ldlayer;
};

class LDCCLayerColor : public CoLayer
{
   
};

class LDCCSprite : public CoNode
{
   
};

#endif //LDCCDERIVED_H
