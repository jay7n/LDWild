#include <libBasic/LDTMXTiledMap.h>

namespace
{
   CoPoint g_GetRectCenter(CoPoint lf_bt_pos, CoSize size)
   {
      CoPoint ret(lf_bt_pos.x + size.width/2,
                  lf_bt_pos.y + size.height/2);
      return ret;
   }
}

LDTMXTiledMap::LDTMXTiledMap(void)
 :LDObject( new CoTMXTiledMap() ),
  _tMap( static_cast<CoTMXTiledMap*>( getconode() ) )
{
   
}

LDTMXTiledMap::~LDTMXTiledMap(void)
{
   LD_SAFE_DELETE_CC(_tMap);
}

bool LDTMXTiledMap::Open(const char* tmxFile)
{
   if(!_tMap) {
      _tMap = new CoTMXTiledMap;
   }
   bool ret = _tMap->initWithTMXFile( g_resourcePathTo(tmxFile).c_str() );
   return ret;
}

CoPoint LDTMXTiledMap::GetObjectPosition(const char* objName,
                                         const char* objGrpName) const
{
   assert(_tMap);
   CoPoint ret(0,0);
   CoDictionary* tDict = NULL;
   if(objGrpName) {
      CoTMXObjectGroup* tObjGrp = _tMap->objectGroupNamed(objGrpName);
      tDict = tObjGrp ? tObjGrp->objectNamed(objName) : NULL;
   }
   else {
      CoArray* grps = _tMap->getObjectGroups();
      CoObject* object = NULL;
      {
         using cocos2d::CCObject;
         CCARRAY_FOREACH(grps, object) {
            CoTMXObjectGroup* tObjGrp = static_cast<CoTMXObjectGroup*>(object);
            tDict = tObjGrp ? tObjGrp->objectNamed(objName) : NULL;
            if(tDict) { break; }
         }
      }
   }
   if(tDict) {
      const CoString* strXPos = tDict->valueForKey("x");
      const CoString* strYPos = tDict->valueForKey("y");
      float xPos = strXPos->floatValue();
      float yPos = strYPos->floatValue();
      CoPoint left_bottom_pos(xPos, yPos);

      const CoString* strWidth =  tDict->valueForKey("width");
      const CoString* strHeight = tDict->valueForKey("height");
      float width = strWidth->floatValue();
      int height = strHeight->floatValue();
      CoSize size(width, height);
      //however we actually need to return the center position of the
      //object. 'cause in cocos2dx the position we set is the center position.
      CoPoint centerPos = g_GetRectCenter(left_bottom_pos, size);
      ret = centerPos;
   }
   return ret;
}
