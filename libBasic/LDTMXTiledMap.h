#ifndef TMXTILEDMAP_H
#define TMXTILEDMAP_H

#include <libBasic/LDBase.h>

class LDTMXTiledMap : public LDObject
{
public:
   LDTMXTiledMap(void);
   ~LDTMXTiledMap(void);
   bool Open(const char* tmxFile);
   CoPoint GetObjectPosition(const char* objName, const char* objGrpName = NULL) const;
private:
   CoTMXTiledMap* _tMap;
};

#endif // TMXTILEDMAP_H


