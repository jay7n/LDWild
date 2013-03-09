#ifndef LAYERS_H
#define LAYERS_H

#include <libBasic/LDBase.h>
#include <libCompo/LDRoleMe.h>

#include<vector>
#include<string>

class LDScene;
class LDCCLayer;
class LDRoleMe;

// - LDLayerBase -
//
class LDLayerBase : public LDObject, public LDNotifier
{
public:
   LDLayerBase(void);
   LDLayerBase(bool touchable,
               bool moveAsHold,
               const char* layerName = NULL,
               LDScene* parentScene = NULL,
               CoNode* conode = NULL);
   ~LDLayerBase(void); 

   virtual LDType GetType(void) const = 0;
   virtual void TouchHint(const LDHint& hint);
   
   LDSpriteBaseArray* GetChildren(void);
   void SetMoveAsHold(bool moveAsHold);
   void AddSprite(LDSpriteBase* spriteChild, bool externOwner = false);
   bool RemoveSprite(LDSpriteBase* spriteChild, bool forceDestroy=true);
   void RemoveAllSprites(void);
   CoPoint ConvertToParentScenePos(const CoPoint& worldPos);
   
   void ScheduleCB(float dt);
   enum TouchEventType {
      TET_BEGAN = 0,
      TET_MOVE,
      TET_END
   };
   void RespondTouchEvent(CoSet* touches, CoEvent* event, TouchEventType tet);

   
protected:
   virtual void update(float dt);
   //just for single touch event for temporary
   virtual void onTouchesBegan(CoSet* touches, CoEvent* event){ }
   virtual void onTouchesMoved(CoSet* touches, CoEvent* event){ }
   virtual void onTouchesEnded(CoSet* touches, CoEvent* event){ }
   virtual void onTouchesHolded(const CoPoint& touchHoldedPos){ }

   bool _touchable;
   bool _holdTouch;
   bool _moveAsHold;
   CoPoint _touchPressedPos;
   CoPoint _touchHoldedPos;
   std::string _name;
   LDSpriteBaseArray _spriteChildren;
   std::vector<uint> _childIdxWithExternOwner; // TODO : will use shared_ptr instead
   LDScene* _parentScene;
};


// - LDLayer -
//
class LDLayer : public LDLayerBase
{
public:
   LDLayer(void);
   LDLayer(bool touchable,
           bool moveAsHold,
           const char* layerName = NULL,
           LDScene* parentScene = NULL,
           LDCCLayer* ldcclayer = NULL);
   ~LDLayer(void);
   
   virtual LDType GetType(void) const {
      return LDLayerType;
   }

   LDCCLayer* GetLDCCLayer(void);

protected:
   virtual void init(void);

private:
   LDCCLayer* _ldcclayer;
};
typedef std::vector<LDLayer*> LDLayerArray;

// - LDLayerMaster -
//
class LDLayerMaster : public LDLayer
{
public:
   LDLayerMaster(LDScene* parentScene);
      
protected:
   void roleMeStandby(void);
   void handleCollisionEvent(void);
      
   virtual void onTouchesBegan(CoSet* touches, CoEvent* event);
   virtual void onTouchesMoved(CoSet* touches, CoEvent* event);
   virtual void onTouchesEnded(CoSet* touches, CoEvent* event);
   virtual void onTouchesHolded(const CoPoint& touchHoldedPos);

   virtual void update(float dt);

private:
   LDRoleMe* _me;
   bool _hitRoleMeCenter;
};

// - LDLayerBackGround -
//
class LDLayerBackGround :  public LDLayer
{
public:
   LDLayerBackGround(LDScene* parentScene);
   CoSize GetBGSize(void){ return _bgSize; }

protected:
   void init(void);
private:
   CoSize _bgSize;

};

#endif // LAYERS_H
