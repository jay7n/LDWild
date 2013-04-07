#include <libBasic/LDLevelScriptLoader.h>

#include<stdio.h>
#include<assert.h>
#include<string.h>

extern "C" {
 #include<lua.h>
 #include<lauxlib.h>
 #include<lualib.h>
}

static void errmsg(lua_State* L, const char* msg = NULL) {
   if(!msg) {
      fprintf( stderr, "%s", lua_tostring(L, -1) );
      lua_pop(L, 1);
   } else {
      fprintf( stderr, "%s", msg );
   }
}

//LDLevelScriptLoader
//
//
LDLevelScriptLoader::LDLevelScriptLoader(void)
   : _L(NULL),
     _luaFileLoaded(false)
{
   
}

LDLevelScriptLoader::~LDLevelScriptLoader(void)
{
   if(_L) {
      //delete _L;
   }
}

bool LDLevelScriptLoader::Load(const char* levelFile)
{
   _L = luaL_newstate();
   bool error = true;
   if( _L && levelFile ) {
      luaL_openlibs(_L);
      error = luaL_loadfile(_L, levelFile) || lua_pcall(_L,0,0,0);
   }
   if(error) {
      errmsg(_L);
   }
   _luaFileLoaded = !error;
   return _luaFileLoaded;
}

bool LDLevelScriptLoader::GetMapFileName(char* mapFileName) const 
{
   return getLevelStrValueByKey("mapname", mapFileName);
}

bool LDLevelScriptLoader::GetPlistFileName(char* plistFileName) const 
{
   return getLevelStrValueByKey("plistname", plistFileName);
}

size_t LDLevelScriptLoader::GetPropSize(void) const
{
   bool error = true;
   size_t ret = -1;
   if(_luaFileLoaded) {
      lua_getglobal(_L, "level");
      if( lua_istable(_L, -1) ) {
         lua_getfield(_L, -1, "propscontent");
         if( lua_istable(_L, -1) ) {
            ret =  lua_objlen(_L, -1);
            error =false;
         }
         lua_pop(_L, 1);
      }
      lua_pop(_L, 1);
   }
   return ret;
}


bool LDLevelScriptLoader::GetPropNameByIndex(char* propName,
                                             int idx, 
                                             bool withFileSuffix) const
{
   bool error = true;
   if(_luaFileLoaded) {
      lua_getglobal(_L, "level");
      if( lua_istable(_L, -1) ) {
         lua_getfield(_L, -1, "getprop");
         lua_pushinteger(_L, idx + 1); // since lua counts number starting from 1
         lua_pushboolean(_L, int(withFileSuffix));
         lua_pcall(_L, 2, 1, 0);
         if( LUA_TSTRING==lua_type(_L, -1) ) {
            const char* tmp = lua_tostring(_L, -1);
            strcpy(propName, tmp);
            error = false;
         }
         lua_pop(_L, 1);
      }
      lua_pop(_L, 1);
   }
   if(error) {
      errmsg(_L, "sorry, but error happened at \
             LDLevelScriptLoader::GetPropNameByIndex.");      
   }
   return !error;
}

bool LDLevelScriptLoader::getLevelStrValueByKey(const char* key, char*& strValue) const
{
   bool error = true;
   if(_luaFileLoaded) {
      lua_getglobal(_L, "level");
      if( lua_istable(_L, -1) ) {
         lua_getfield(_L, -1, key);
         if( LUA_TSTRING==lua_type(_L, -1) ) {
            const char * tmp = lua_tostring(_L, -1);
            strcpy(strValue, tmp);
            error = false;
         }
         lua_pop(_L, 1);
      }
      lua_pop(_L, 1);
   }
   if(error) {
      errmsg(_L, "sorry, but error happened at \
             LDLevelScriptLoader::getLevelStrValueByKey.");
   }
   return !error;
}

