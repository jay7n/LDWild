#include <libOrgan/LDLayers.h>
#include <libOrgan/LDScenes.h>
#include <libOrgan/LDCCDerived.h>
#include <libBasic/LDB2Manager.h>

// - LDLayerBase -
//
//
LDLayerBase::LDLayerBase(void)
   :LDObject(),
    _touchable(false),
    _holdTouch(false),
    _moveAsHold(false),
    _name(undefined),
    _parentScene(NULL)
{

}

LDLayerBase::LDLayerBase(bool touchable,
                         bool moveAsHold,
                         const char* layerName,
                         LDScene* parentScene,
                         CoNode* conode)
   : LDObject(conode),
     _touchable(touchable),
     _holdTouch(false),
     _moveAsHold(moveAsHold),
     _name(layerName ? layerName : undefined),
     _parentScene(parentScene)
{

}

LDLayerBase::~LDLayerBase(void)
{
   RemoveAllSprites();
}


void LDLayerBase::TouchHint(const LDHint& hint)
{
   
}

LDSpriteBaseArray* LDLayerBase::GetChildren(void)
{
   return &_spriteChildren;
}

void LDLayerBase::SetMoveAsHold(bool moveAsHold)
{
   _moveAsHold = moveAsHold;
}

void LDLayerBase::AddSprite(LDSpriteBase* spriteChild, bool externOwner)
{
   if(spriteChild) {
      _spriteChildren.push_back(spriteChild);
      getconode()->addChild( spriteChild->GetCoNode() );
      RegisterObserver(spriteChild);
   }
   if(externOwner) {
      _childIdxWithExternOwner.push_back(_spriteChildren.size()-1);
   }
}

bool LDLayerBase::RemoveSprite(LDSpriteBase* spriteChild, bool forceDestroy)
{
   bool ret =false;
   LDSpriteBaseArray::iterator itr =
      std::find( _spriteChildren.begin(),_spriteChildren.end(), spriteChild );
   
   if( itr!=_spriteChildren.end() ) {
      if(forceDestroy) {
         getconode()->removeChild( (*itr)->GetCoNode(), true );
         delete *itr;
      }
      
      _spriteChildren.erase(itr);
      ret = true;
   }
   return ret;
}

void LDLayerBase::RemoveAllSprites(void)
{
   std::vector<uint>::iterator begin = _childIdxWithExternOwner.begin();
   std::vector<uint>::iterator end = _childIdxWithExternOwner.end();
   for(size_t i=0; i<_spriteChildren.size(); i++) {
      if(end == std::find( begin, end, static_cast<uint>(i) ) ) {
         delete _spriteChildren[i];
       }
      _spriteChildren[i] = NULL;
   }
   _spriteChildren.clear();
   LDSpriteBaseArray().swap(_spriteChildren);
}

CoPoint LDLayerBase::ConvertToParentScenePos(const CoPoint& worldPos)
{
   CoPoint parentBorderOrigin = (_parentScene->GetSceneBorder().origin);
   CoPoint ret = worldPos - parentBorderOrigin;
   return ret;
}

void LDLayerBase::ScheduleCB(float dt)
{
   if(_holdTouch) {
      onTouchesHolded(_touchHoldedPos);
   }
   update(dt);
}

void LDLayerBase::RespondTouchEvent(CoSet* touches, CoEvent* event, TouchEventType tet)
{
   switch(tet) {
      
   case TET_BEGAN :
   {
      CoTouch* firstTouch = static_cast<CoTouch*>(touches->anyObject());
      _touchPressedPos = g_convertPositionFromViewToGL( firstTouch->locationInView() );
      _touchHoldedPos = _touchPressedPos;
      _holdTouch = true;
      printf("touchPressedPosX=%f\n", _touchPressedPos.x);
      onTouchesBegan(touches, event);
      break;
   }
   case TET_MOVE :
   {
      if(!_moveAsHold) {
         _holdTouch = false;
      }
      else {
         CoTouch* firstTouch = static_cast<CoTouch*>( touches->anyObject() );
         _touchHoldedPos = g_convertPositionFromViewToGL( firstTouch->locationInView() );
      }
      onTouchesMoved(touches, event);
      break;
   }
   case TET_END :
   {
      _holdTouch = false;
      onTouchesEnded(touches, event);
      break;
   }
   default:
      break;
   }
}

void LDLayerBase::update(float dt)
{
   UpdateHint updatehint(dt);
   NotifyHint(updatehint);
}

// - LDLayer -
//
//
LDLayer::LDLayer(void)
   :LDLayerBase(false, false, undefined, NULL, new LDCCLayer() ),
    _ldcclayer( static_cast<LDCCLayer*>( getconode() ) )
{
   _ldcclayer->init(this);
}

LDLayer::LDLayer(bool touchable,
                 bool moveAsHold,
                 const char* layerName,
                 LDScene* parentScene,
                 LDCCLayer* ldcclayer)
   :LDLayerBase(touchable,
                moveAsHold,
                layerName,
                parentScene,
                ldcclayer ? ldcclayer : new LDCCLayer() ),
    _ldcclayer( static_cast<LDCCLayer*>( getconode() ) )
{
   _ldcclayer->init(this);   
}

LDLayer::~LDLayer(void)
{
   LD_SAFE_DELETE_CC(_ldcclayer);
}

void LDLayer::init(void)
{
   GetLDCCLayer()->setTouchEnabled(_touchable);
}

LDCCLayer* LDLayer::GetLDCCLayer(void)
{
   return _ldcclayer;
}

static LDRoleMe::AreaPart _prevHoldedPart = LDRoleMe::AREAPART_CENTER;
static LDRoleMe::AreaPart _tmpPrevHoldedPart = _prevHoldedPart;

// - LDLayerMaster -
//
//
LDLayerMaster::LDLayerMaster(LDScene* parentScene)
   :LDLayer(true, true, "LDLayerMaster", parentScene),
    _me(NULL),
    _hitRoleMeCenter(false)
{
   init();
   _me = LDRoleMe::GetOrCreateMe();
}

void LDLayerMaster::roleMeStandby(void)
{
   _me->Standby();
   //reset 
   _prevHoldedPart = LDRoleMe::AREAPART_CENTER;
   _tmpPrevHoldedPart = _prevHoldedPart;
}

void LDLayerMaster::handleCollisionEvent(void)
{
   size_t childrenSize = _spriteChildren.size();
   for(size_t i=0; i<childrenSize; i++) {
      LDSpriteBase* child = _spriteChildren[i];
      if(child && child!=_me) {
         if( _me->IsCollidedWith(child) ) {
            //
         }
      }
   }
}


void LDLayerMaster::onTouchesBegan(CoSet* touches, CoEvent* event)
{
   CoPoint tchPressPosInScene = ConvertToParentScenePos(_touchPressedPos);
   LDRoleMe::AreaPart touchPart =
      _me->TouchRoleMeAreaPart( tchPressPosInScene);
   _hitRoleMeCenter = ( LDRoleMe::AREAPART_CENTER ==touchPart );
}

void LDLayerMaster::onTouchesMoved(CoSet* touches, CoEvent* event)
{
      
}

void LDLayerMaster::onTouchesEnded(CoSet* touches, CoEvent* event)
{
   roleMeStandby();
   _hitRoleMeCenter = false;
}
   
void LDLayerMaster::onTouchesHolded(const CoPoint& touchHoldedPos)
{
   //TODO : Refactor this logic into LDRoleMe
   if(_hitRoleMeCenter) {
      CoPoint moveStepVec = LDRoleMe::GetDefaultStepVec();
         
      LDRoleMe::AreaPart holdedPart =
         _me->TouchRoleMeAreaPart( ConvertToParentScenePos(touchHoldedPos ) );
            
      if(_tmpPrevHoldedPart != holdedPart) {
         _prevHoldedPart = _tmpPrevHoldedPart;            
      }

      if( LDRoleMe::AREAPART_RIGHT == holdedPart ) {
         if(holdedPart!=_prevHoldedPart) {
            _me->GetCoSprite()->setFlipX(false);  
         }
         _me->Move(moveStepVec);
      }
      else if(LDRoleMe::AREAPART_RIGHT_GAP == holdedPart ) {
         if(LDRoleMe::AREAPART_RIGHT==_prevHoldedPart) {
            _me->Move(moveStepVec);
         }
         else if(LDRoleMe::AREAPART_CENTER == _prevHoldedPart) {
            roleMeStandby();
         }
      }
      else if( LDRoleMe::AREAPART_LEFT == holdedPart ) {
         if(holdedPart!=_prevHoldedPart) {
            _me->GetCoSprite()->setFlipX(true);  
         }
         _me->Move( moveStepVec * (-1) );
      }
      else if(LDRoleMe::AREAPART_LEFT_GAP == holdedPart ) {
         if(LDRoleMe::AREAPART_LEFT==_prevHoldedPart) {
            _me->Move(moveStepVec * (-1) );
         }
         else if(LDRoleMe::AREAPART_CENTER == _prevHoldedPart) {
            roleMeStandby();
         }
      }
      else if(LDRoleMe::AREAPART_CENTER == holdedPart){
         roleMeStandby();
      }
      _tmpPrevHoldedPart = holdedPart;
   }
}

void LDLayerMaster::update(float dt)
{
   LDLayerBase::update(dt);
   
   // //box2d stuff updates
   // LDB2Manager::GetSingleton()->UpdateB2World(dt);
   // size_t childrenSize = _spriteChildren.size();
   // for(size_t i=0; i<childrenSize; i++) {
   //    LDSpriteBase* sprite = _spriteChildren[i];
   //    if(sprite) {
   //       LDB2Manager::GetSingleton()->UpdateB2BodyWith(sprite);
   //    }
   // }

   //Collision Event
   handleCollisionEvent();
}


// - LDLayerBackGround -
//
//
LDLayerBackGround::LDLayerBackGround(LDScene* parentScene)
   :LDLayer(false, false, "LDLayerBackGround", parentScene)
{
   init();
}

void LDLayerBackGround::init(void)
{
   LDSprite* bgSprite = new LDSprite("background.png","bgSprite");
   CoSprite* cosprite = bgSprite->GetCoSprite();
   _bgSize = cosprite->getContentSize();
   CoPoint bgStartPos = CoPoint(_bgSize.width/2, _bgSize.height/2);
   cosprite->setPosition( bgStartPos );
   AddSprite(bgSprite);
}
