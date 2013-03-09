#ifndef SCENEMAINTEST_H
#define SCENEMAINTEST_H

#include <libBasic/LDBase.h>
#include <libOrgan/LDLayers.h>
#include <libOrgan/LDScenes.h>

class LDRoleMe;

// - LDSceneMainTest -
//
class LDSceneMainTest : public LDScene
{
public:
   LDSceneMainTest(void);

   virtual LDType GetType(void) {
      return LDSceneMainTestType;
   }

   void Move(const CoPoint& stepVec);
   enum AreaPart {
      AREAPART_LEFT = 0,
      AREAPART_CENTER,
      AREAPART_RIGHT, 
   };
   AreaPart TouchSceneMainTestAreaPart(const CoPoint& touchPoint );
   
protected:
   void init(void);
   
   enum LayerType {
      LAYER_BACKGROUND = 1,
      LAYER_MASTER,
      LAYER_NUMS
   };
   LDLayer* createLayer(LayerType layerType);
   LDLayer* getLayer(LayerType layerType);
      
private:
   LDRoleMe* _me;
};

#endif // SCENEMAINTEST_H
