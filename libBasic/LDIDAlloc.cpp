#include <libBasic/LDIDAlloc.h>
#include <libBasic/LDBase.h>

//const globals
static const uint IDALLOC_GROUP_INTERVAL = 10000;

// - LDIDAlloc -
//
//

//static
uint LDIDAlloc::_currGrpBaseID = 0;
LDIDAlloc::IDGroupArray LDIDAlloc::_idGroups;

//static
uint LDIDAlloc::AllocID(const char* pmIdName, const char* pmIdGrpName)
{
   IDGroup* group = getIDGroup(pmIdGrpName);
   if( !group ) {
      group = new IDGroup(pmIdGrpName, _currGrpBaseID);
      _idGroups.push_back(group);
      _currGrpBaseID+= IDALLOC_GROUP_INTERVAL;
   }

   uint idIdx = group->grpBaseID + group->currElemID;
   std::string idName = pmIdName;
   group->map.insert( std::pair<uint, std::string>(idIdx, idName) );
   group->currElemID++;

   return idIdx;
}

LDIDAlloc::IDGroup* LDIDAlloc::getIDGroup(const char* idGrpName)
{
   IDGroupArray::iterator itr = _idGroups.begin();
   IDGroupArray::iterator end = _idGroups.end();
   for(itr; itr!=end; itr++) {
      IDGroup* group = *itr;
      if( group && ( 0==group->grpName.compare(idGrpName) ) ) {
         return group;
      }
   }
   return NULL;
}


