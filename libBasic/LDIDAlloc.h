#ifndef LDIDALLOC_H
#define LDIDALLOC_H

#include <libBasic/LDTypes.h>

#include <string>
#include <map>
#include <vector>

// - LDIDAlloc -
//
class LDIDAlloc
{
public:
   static uint AllocID(const char* idName, const char* idGrpName = NULL);
   static void PrintAllIDs(void); // ---
   
private:
   
   struct IDGroup
   {
   IDGroup(std::string groupName, uint groupBaseID)
      :grpName(groupName), grpBaseID(groupBaseID) {}
      
      std::map<uint, std::string> map;
      std::string grpName;
      uint grpBaseID;
      uint currElemID;
   };

   static IDGroup* getIDGroup(const char* idGrpName);
   
   static uint _currGrpBaseID;
   typedef std::vector<IDGroup*> IDGroupArray;
   static IDGroupArray _idGroups;
};

#endif// LDIDALLOC_H
