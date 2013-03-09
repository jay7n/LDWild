#include <libBasic/LDAnim.h>
#include <libBasic/LDSprites.h>

CoSpriteFrameCache* LDFrameAnim:: _frameCache = CoSpriteFrameCache::sharedSpriteFrameCache();

// - LDFrameAnim -
//
//
LDFrameAnim::LDFrameAnim(CoSprite* executer,
                         int frames,
                         const char* picFileWithoutSuffix,
                         float delayForNextFrame,
                         bool repeat) :
   _executer(executer),
   _frameAnimAction(NULL),
   _frameNums(frames),
   _delayForNextFrame(delayForNextFrame),
   _repeat(repeat),
   _stopped(true)
{
   g_initCString(_picFileWithoutSuffix, picFileWithoutSuffix);
   init();
}

void LDFrameAnim::SetExecuter(CoSprite* executer)
{
   _executer = executer;
}

CoSprite* LDFrameAnim::GetExecuter(void)
{
   return _executer;
}

CoSpriteFrameCache* LDFrameAnim::GetFrameCache(void)
{
   return _frameCache;
}

void LDFrameAnim::init(void)
{
   std::stringstream tmpss;
   tmpss<<_picFileWithoutSuffix<<".plist";
   std::string strPlistPath = g_resourcePathTo( tmpss.str() );
   tmpss.str(""); //reset temss

   assert(_frameCache);
   _frameCache->addSpriteFramesWithFile(strPlistPath.c_str());
   
   CoArray* animFrames = new CoArray(_frameNums);
   for(int i=1; i<=_frameNums; i++) {
      tmpss<<_picFileWithoutSuffix<<i<<".png";
      CoSpriteFrame* sframe = _frameCache->spriteFrameByName(tmpss.str().c_str());
      animFrames->addObject(sframe);
      tmpss.str(""); //reset temss
   }

   CoAnimation* animation=
      CoAnimation::animationWithSpriteFrames(animFrames, _delayForNextFrame);
   
   CoAction* action = CoAnimate::actionWithAnimation(animation);

   if(_repeat) {
      action =
         CoRepeatForever::actionWithAction( static_cast<CoActionInterval*>(
                                               action) );
   }

   _frameAnimAction = action;
   _frameAnimAction->retain();
}

CoSpriteFrame* LDFrameAnim::GetFrameByName(const char* frameName)
{
   if(_frameCache) {
      return _frameCache->spriteFrameByName(frameName);
   }
   return NULL;
}

bool LDFrameAnim::Run(void)
{
   if( _executer && _stopped ) {
      _executer->runAction(_frameAnimAction);
      _stopped = false;
      return true;
   }
   return false;
}

bool LDFrameAnim::Stop(void)
{
   if( _executer ) {
      _executer->stopAction(_frameAnimAction);
      _stopped = true;
      return true;
   }
   return false;
}



// - LDSpriteLoader -
//
//
LDSpriteLoader::LDSpriteLoader(const char* plistFile)
   :_plistFileStr( g_resourcePathTo(plistFile) ),
    _frameCache( LDFrameAnim::GetFrameCache() )
{
   _frameCache->addSpriteFramesWithFile(_plistFileStr.c_str());
}


