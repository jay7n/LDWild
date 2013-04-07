#include <libBasic/LDTMXTiledMap.h>
#include <libBasic/LDAnim.h>
#include <libBasic/LDB2Manager.h>
#include <libBasic/LDSprites.h>
#include <libCompo/LDRoleMe.h>
#include <libCompo/LDSubtitle.h>
#include <libCompo/LDProp.h>
#include <libCompo/LDLevelImporter.h>
#include <libOrgan/LDLayers.h>
#include <libOrgan/LDSceneMainTest.h>
#include <libTest/TestSubtitleNLiteral.h>

#include <Box2D/Box2D.h>

#define GROUND_HEIGHT 20

// - LDSceneMainTest -
//
//
LDSceneMainTest::LDSceneMainTest (void)
   :LDScene("sceneMainTest"),
   _me(NULL)
{
   init();
}

void LDSceneMainTest::Move(const CoPoint& stepVec)
{
   CoScene* coscene = GetCoScene();
   CoPoint pos = coscene->getPosition();
   pos = pos + stepVec;
   coscene->setPosition(pos);

   //update scene border
   CoPoint sceneBorderOrigin = _sceneBorder.origin;
   sceneBorderOrigin += stepVec;
   _sceneBorder.origin.x = sceneBorderOrigin.x;
   _sceneBorder.origin.y = sceneBorderOrigin.y; 

   LDLayerArray::iterator itrLayer;
   LDLayerArray::iterator itrLayerEnd = _layerChildren.end();
   for(itrLayer = _layerChildren.begin(); itrLayer!=itrLayerEnd; itrLayer++) {
      LDLayer* layer = *itrLayer;
      if(layer) {
         LDSpriteBaseArray* spriteChildren = layer->GetChildren();
         LDSpriteBaseArray::iterator itrSprite;
         LDSpriteBaseArray::iterator itrSpriteEnd = spriteChildren->end();
         for(itrSprite=spriteChildren->begin(); itrSprite!=itrSpriteEnd; itrSprite++) {
            LDSpriteBase* sprite = *(itrSprite);
            if( sprite && sprite != _me ) {
               sprite->Move(stepVec);
            }
         }
      }
   }
}

void LDSceneMainTest::init(void)
{
   //create layers
   LDLayer* bgLayer = createLayer(LAYER_BACKGROUND);
   AddLayer(bgLayer);
   CoSize bgSize = static_cast<LDLayerBackGround*>(bgLayer)->GetBGSize();
   SetSceneBorder(0, 0, bgSize.width, bgSize.height);
   
   LDLayer* masterLayer = createLayer(LAYER_MASTER);
   AddLayer(masterLayer);

   LDSubtitleSys* subtitleSys = LDSubtitleSys::Singleton();
   assert(subtitleSys);
   AddLayer( subtitleSys->GetHostLayer() );
   
   if(masterLayer) {
      //create role me
      _me = LDRoleMe::GetOrCreateMe();
      _me->BindScene(this);
      CoSize winSize = CoDirer->getWinSize();
      const float ground = winSize.height/4;
      const float leftside = winSize.width/10;
      CoPoint startPos = CoPoint(leftside, ground);
      _me->GetCoSprite()->setPosition(startPos);
      masterLayer->AddSprite(_me);
      
      TestCase::TestSubtitleNLiteral();

      LDLevelImporter levelImporter;
      levelImporter.Import("lv1.lua", masterLayer, bgLayer);
   }
}


LDSceneMainTest::AreaPart LDSceneMainTest::TouchSceneMainTestAreaPart(const CoPoint& touchPoint )
{
   //TODO : implement the real
   //   return LDSceneMainTest::AREAPART_CENTER;

   const CoSize winSize = CoDirer->getWinSize();
   CoRect sceneBorder = GetSceneBorder();

   if( touchPoint.x < sceneBorder.origin.x + winSize.width/2 ) {
      return AREAPART_LEFT;
   }
   else if( touchPoint.x > sceneBorder.origin.x + sceneBorder.size.width - winSize.width/2 ) { 
      return AREAPART_RIGHT;
   }
   else {
      return AREAPART_CENTER;
   }
}

LDLayer* LDSceneMainTest::createLayer(LayerType layerType)
{
   LDLayer* layer = NULL;
   switch(layerType)
   {
      case LAYER_MASTER :
      {
         layer = new LDLayerMaster(this);
         break;
      }
      case LAYER_BACKGROUND :
      {
         layer = new LDLayerBackGround(this);
         break;
      }
      default :
         break;
   }
   return layer;
}
