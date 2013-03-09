#ifndef LDANIM_H
#define LDANIM_H

#include <libBasic/LDBase.h>

class LDSprite;

class LDFrameAnim : public LDObject
{
public:
   LDFrameAnim(CoSprite* executer,
               int frames,
               const char* picFileWithoutSuffix,
               float delayForNextFrame,
               bool repeat);

   virtual LDType GetType(void) const {
      return LDFrameAnimType;
   }

   bool Run(void);
   bool Stop(void);
   CoSpriteFrame* GetFrameByName(const char* frameName);
   void SetExecuter(CoSprite* executer);
   CoSprite* GetExecuter(void);
   bool IsPlayingFinished(void);

   static CoSpriteFrameCache* GetFrameCache(void);

protected:
   void init(void);
   
private:
   CoAction* _frameAnimAction;
   static CoSpriteFrameCache* _frameCache;
   CoSprite* _executer;
   
   int _frameNums;
   char* _picFileWithoutSuffix;
   float _delayForNextFrame;
   bool _repeat;
   
   bool _stopped;
};

class LDSpriteLoader : LDObject
{
public:
   LDSpriteLoader(const char* plistFile);
   
   virtual LDType GetType(void) const {
      return LDSpriteLoaderType;
   }

   template<typename SpriteType>
   SpriteType* LoadSprite(const char* spriteNameInFile);
   
private:
   std::string _plistFileStr;
   CoSpriteFrameCache* _frameCache;
};


// - LDSpriteLoader -
//
//
template<typename SpriteType>
SpriteType* LDSpriteLoader::LoadSprite(const char* nameInFile)
{
   CoSpriteFrame* frame = _frameCache->spriteFrameByName(nameInFile);
   //CoTexture2D* texture = frame->getTexture();
   SpriteType* ldSprite = new SpriteType(NULL, nameInFile);
   ldSprite->GetCoSprite()->initWithSpriteFrame(frame);
   return ldSprite;
}


#endif //LDANIM_H
