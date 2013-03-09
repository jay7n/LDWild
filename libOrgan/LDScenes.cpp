#include <libOrgan/LDScenes.h>

// - LDSceneBase -
//
//
int LDSceneBase::_currLayerIdx = 0;

LDSceneBase::LDSceneBase(const char* sceneName, CoNode* conode)
   :LDObject(conode),
    _name(sceneName ? sceneName : undefined)
{
   
}

void LDSceneBase::AddLayer(LDLayer* layerChild)
{
   _layerChildren.push_back(layerChild);
   getconode()->addChild( layerChild->GetCoNode() );
   _currLayerIdx++;
}

void LDSceneBase::SetSceneBorder(float left, float bottom, float right, float top)
{
   _sceneBorder = CoRect(left, bottom, right-left, top-bottom);
}

void LDSceneBase::SetSceneBorder(const CoRect& border)
{
   _sceneBorder = border;
}

CoRect LDSceneBase::GetSceneBorder(void)
{
   return _sceneBorder;
}

// - LDScene -
//
//
LDScene::LDScene(const char* sceneName, CoScene* coscene)
   :LDSceneBase( sceneName, coscene ? coscene : new CoScene() ),
    _coscene( static_cast<CoScene*>( getconode() ) )
{
   bool ret =false;
   if(_coscene) {
      ret = _coscene->init();
   }
}

LDScene::~LDScene(void)
{
   LD_SAFE_DELETE_CC(_coscene);
}

CoScene* LDScene::GetCoScene(void)
{
   return _coscene;
}
