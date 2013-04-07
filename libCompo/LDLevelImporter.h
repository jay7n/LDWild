#ifndef LDLEVELIMPORTER_H
#define LDLEVELIMPORTER_H

//forward declarations
class LDLevelScriptLoader;
class LDLayer;

class LDLevelImporter
{
public:
   //interface
   LDLevelImporter(void);
   ~LDLevelImporter(void);

   bool Import( const char* levelFileName,
                LDLayer* masterHostLayer,
                LDLayer* bgHostLayer );

private:
   //forbidden
   LDLevelImporter( const LDLevelImporter& );
   LDLevelImporter& operator=( const LDLevelImporter& );

   //methods
   bool importProps( const LDLevelScriptLoader& loader,
                     const LDTMXTiledMap& ldMap,
                     LDSpriteLoader& sLoader,
                     LDLayer* masterHostLayer,
                     LDLayer* bgHostLayer,
                     LDB2Manager* ldb2Mgr );

   //member
   std::string _scriptPath;
};

#endif // LDLEVELIMPORTER_H
