#include <libCompo/LDRoleMe.h>
#include <libBasic/LDAnim.h>
#include <libBasic/LDB2Manager.h>
#include <libOrgan/LDSceneMainTest.h>

#include <sstream>

namespace {
   const char* STAY_FRAME  = "me_stand.png";
}

CoPoint LDRoleMe::_defaultStepVec = CoPoint(1.5, 0);
LDRoleMe* LDRoleMe::_singleton = NULL;

//static
LDRoleMe* LDRoleMe::GetOrCreateMe(void)
{
   if(NULL==_singleton) {
      _singleton = new LDRoleMe();
   }
   return _singleton;
}

LDRoleMe::LDRoleMe(void)
   : LDSprite(NULL, "me"),
     _mainScene(NULL),
    _meMoveAnim(NULL),
    _meArea(0,0,0,0)
{
   init();
}

bool LDRoleMe::BindScene(LDSceneMainTest* scene)
{
   if(!_mainScene) {
      _mainScene = static_cast<LDSceneMainTest*>(scene);
      return true;
   }
   return false;
}

LDRoleMe::AreaPart LDRoleMe::TouchRoleMeAreaPart(const CoPoint& touchPoint)
{
   CoRect meArea = getMeArea();
   CoSize meSize = meArea.size;
   float gapWidth = 10;
   CoPoint meAreaMax = CoPoint(meSize.width, meSize.height) + meArea.origin ;
   CoPoint meAreaMin = meArea.origin;
   AreaPart ret;
                               
   if( g_isPointLocatedInRect( touchPoint, meArea ) ) {
      ret = AREAPART_CENTER;
   }
   else if(touchPoint.x - meAreaMax.x > 0) {
      
      if(touchPoint.y - meAreaMax.y > 0) {
         ret = AREAPART_TR;
      }
      else if(touchPoint.y - meAreaMax.y < 0 &&
              touchPoint.y - meAreaMin.y > 0) {
         if(touchPoint.x - meAreaMax.x >gapWidth) {
            ret = AREAPART_RIGHT;
         }
         else {
            ret = AREAPART_RIGHT_GAP;            
         }
      }
      else {
         ret = AREAPART_BR;
      }
      
   }
   else if(touchPoint.x - meAreaMax.x < 0 &&
           touchPoint.x - meAreaMin.x > 0) {
      
      if(touchPoint.y - meAreaMax.y > 0) {
         ret = AREAPART_TOP;
      }
      else {
         ret = AREAPART_BOTTOM;
      }
      
   }
   else {
      
      if(touchPoint.y - meAreaMax.y > 0) {
         ret = AREAPART_TL;
      }
      else if(touchPoint.y - meAreaMax.y < 0 &&
              touchPoint.y - meAreaMin.y > 0) {
         if(touchPoint.x - meAreaMin.x < -gapWidth) {
            ret = AREAPART_LEFT;            
         }
         else {
            ret = AREAPART_LEFT_GAP;
         }
      }
      else {
         ret = AREAPART_BL;
      }
   }
   printf("area=%d\n", ret);
   printf("areaX=%f\n",meArea.origin.x);
   return ret;
}

void LDRoleMe::Move(const CoPoint& stepVec)
{
   LDSprite::Move(stepVec);
   _meMoveAnim->Run();

   CoPoint mePos = this->GetCoSprite()->getPosition();
   LDSceneMainTest::AreaPart sceneAreaPart = 
      _mainScene->TouchSceneMainTestAreaPart(mePos);

   if( LDSceneMainTest::AREAPART_CENTER == sceneAreaPart ) {
       _mainScene->Move( stepVec * (-1) );      
    }
}

void LDRoleMe::Standby(void)
{
   _meMoveAnim->Stop();
   CoSpriteFrame* stayFrame = _meMoveAnim->GetFrameByName(STAY_FRAME);
   this->GetCoSprite()->setDisplayFrame(stayFrame);
}

bool LDRoleMe::IsCollidedWith(LDSpriteBase* sprite)
{
   return LDB2Manager::GetSingleton()->IsTwoSpritesContact(this, sprite);
}

void LDRoleMe::init(void)
{
   CoSprite* cosprite = GetCoSprite();
   if(cosprite) {
      cosprite->setScale(0.5f);
      //init behaviour
      _meMoveAnim = new LDFrameAnim(cosprite, 4, "me_move", 0.3f, true);
      CoSpriteFrame* stayFrame = _meMoveAnim->GetFrameByName(STAY_FRAME);
      GetCoSprite()->initWithSpriteFrame(stayFrame);
   }
}

CoRect LDRoleMe::getMeArea(void)
{
   CoSprite* cosprite = GetCoSprite();
   CoSize size = cosprite->getContentSize();
   CoPoint pos = cosprite->getPosition();
   return CoRectMake(pos.x - size.width/2,
                     pos.y - size.height/2,
                     size.width,
                     size.height);
}
