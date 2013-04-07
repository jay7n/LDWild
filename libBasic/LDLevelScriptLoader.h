#ifndef LDLEVELSCRIPTLOADER_H
#define LDLEVELSCRIPTLOADER_H

// forward declaritions
struct lua_State;

// LDLevelScriptLoader
//
class LDLevelScriptLoader
{
public:
   LDLevelScriptLoader(void);
   ~LDLevelScriptLoader(void);

   //interface
   bool Load(const char* levelFile);
   bool GetMapFileName(char* mapFileName) const ;
   bool GetPlistFileName(char* plistFileName) const;
   size_t GetPropSize(void) const;
   bool GetPropNameByIndex(char* propName, int idx, bool with_file_suffix) const ;
   void Reset(void);
   
private:
   //forbidden
   LDLevelScriptLoader(const LDLevelScriptLoader& other);
   LDLevelScriptLoader& operator=(const LDLevelScriptLoader& other);

   //methods
   bool getLevelStrValueByKey(const char* key, char*& strValue) const;

   //member
   struct lua_State* _L;
   bool _luaFileLoaded;
};

#endif // LDLEVELSCRIPTLOADER_H
