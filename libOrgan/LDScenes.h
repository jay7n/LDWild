#ifndef LDSCENES_H
#define LDSCENES_H

#include <libBasic/LDBase.h>
#include <libOrgan/LDLayers.h>

#include <string>

class LDLayer;

typedef std::vector<LDLayer*> LDLayerArray;
// - LDSceneBase - 
//
class LDSceneBase : public LDObject
{
public:
   LDSceneBase(const char* sceneName = NULL, CoNode* conode = NULL);
   
   virtual LDType GetType(void) = 0;

   void AddLayer(LDLayer* layerChild);
   void SetSceneBorder(float left, float top, float right, float bottom);
   void SetSceneBorder(const CoRect& border);
   CoRect GetSceneBorder(void);
   
protected:
   std::string _name;
   CoRect _sceneBorder;
   LDLayerArray _layerChildren;
   static int _currLayerIdx;
};

// - LDScene -
//
class LDScene : public LDSceneBase
{
public:
   LDScene(const char* sceneName = NULL, CoScene* coscene = NULL);
   ~LDScene(void);
   
   virtual LDType GetType(void) const {
      return LDSceneType;
   }
   virtual CoScene* GetCoScene(void);
   
private:
   CoScene* _coscene;
};

#endif// LDSCENES_H
