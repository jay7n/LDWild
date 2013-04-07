#include <libBasic/LDTypes.h>
#include <libBasic/LDLevelScriptLoader.h>
#include <libBasic/LDTMXTiledMap.h>
#include <libBasic/LDAnim.h>
#include <libBasic/LDB2Manager.h>
#include <libCompo/LDLevelImporter.h>
#include <libCompo/LDProp.h>
#include <libOrgan/LDLayers.h>


// LDLevelImporter
//
//

LDLevelImporter::LDLevelImporter(void)
:_scriptPath("../scripts/")
{
   
}

LDLevelImporter::~LDLevelImporter(void)
{
   
}


bool LDLevelImporter::Import(const char* levelFileName,
                             LDLayer* masterHostLayer,
                             LDLayer* bgHostLayer)
{
   bool error = true;
   LDLevelScriptLoader loader;
   if( levelFileName && loader.Load( _scriptPath.append(levelFileName).c_str() )) {
      char plistFileName[200];
      char mapFileName[200];
      if( loader.GetPlistFileName( plistFileName ) &&
          loader.GetMapFileName( mapFileName ) ) {
         LDSpriteLoader sLoader(plistFileName);
         LDTMXTiledMap ldMap; bool mapOpened = ldMap.Open(mapFileName);
         if( mapOpened ) {
            LDB2Manager* ldb2Mgr = LDB2Manager::GetSingleton();
            error = !importProps( loader, ldMap, sLoader,
                                  masterHostLayer, bgHostLayer, ldb2Mgr );
         }
      }
   }
   return !error;
}

bool LDLevelImporter::importProps( const LDLevelScriptLoader& loader,
                                   const LDTMXTiledMap& ldMap,
                                   LDSpriteLoader& sLoader,
                                   LDLayer* masterHostLayer,
                                   LDLayer* bgHostLayer,
                                   LDB2Manager* ldb2Mgr )
{
   bool error = true;
   size_t propSize = loader.GetPropSize();
   for(size_t i=0; i<propSize; i++) {
      char propName[200];
      if( loader.GetPropNameByIndex(propName, i, false) ) {
         LDProp* prop = sLoader.LoadSprite<LDProp>(propName);
         if(prop) {
            CoPoint pos = ldMap.GetObjectPosition(propName, "objects");
            prop->GetCoNode()->setPosition(pos);
            masterHostLayer->AddSprite(prop);
            ldb2Mgr->CreateB2BodyTo(prop);
            error = false;
         }
      }
   }
   return !error;
}
