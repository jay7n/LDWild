#ifndef LDTYPES_H
#define LDTYPES_H

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include <string>

typedef unsigned int uint;

typedef cocos2d::CCNode                    CoNode;
typedef cocos2d::CCScene                   CoScene;
typedef cocos2d::CCLayer                   CoLayer;
typedef cocos2d::CCSprite                  CoSprite;
typedef cocos2d::CCSize                    CoSize;
typedef cocos2d::CCDirector                CoDirector;
typedef cocos2d::CCAnimation               CoAnimation;
typedef cocos2d::CCAnimate                 CoAnimate;
typedef cocos2d::CCArray                   CoArray;
typedef cocos2d::CCAction                  CoAction;
typedef cocos2d::CCSpriteFrame             CoSpriteFrame;
typedef cocos2d::CCMoveBy                  CoMoveBy;
typedef cocos2d::CCFiniteTimeAction        CoFiniteTimeAction;
typedef cocos2d::CCCallFunc                CoCallFunc;
typedef cocos2d::CCSequence                CoSequence;
typedef cocos2d::CCRepeatForever           CoRepeatForever;
typedef cocos2d::CCRect                    CoRect;
typedef cocos2d::CCSpriteFrameCache        CoSpriteFrameCache;
typedef cocos2d::CCTime                    CoTime;
typedef cocos2d::CCTouch                   CoTouch;
typedef cocos2d::CCSet                     CoSet;
typedef cocos2d::CCEvent                   CoEvent;
typedef cocos2d::CCActionInterval          CoActionInterval;
typedef cocos2d::CCLayerColor              CoLayerColor;
typedef cocos2d::CCTMXTiledMap             CoTMXTiledMap;
typedef cocos2d::CCTMXObjectGroup          CoTMXObjectGroup;
typedef cocos2d::CCDictionary              CoDictionary;
typedef cocos2d::CCString                  CoString;
typedef cocos2d::CCObject                  CoObject;
typedef cocos2d::CCTexture2D               CoTexture2D;
typedef cocos2d::CCLabelTTF                CoLabelTTF;
typedef cocos2d::CCLabelBMFont             CoLabelBMFont;
typedef cocos2d::ccColor3B                 CoColor3B;

typedef unsigned int uint;

#define CoDirer CoDirector::sharedDirector()
#define CoScheduleSelector(sel) cocos2d::SEL_SCHEDULE(&sel)
#define CoRectMake cocos2d::CCRectMake
#define CoCCC4 cocos2d::ccc4

#define LD_SAFE_DELETE_CC(p)                     \
{                                                \
   if( (p) ) {                                   \
      delete (p);                                \
      (p) = NULL;                                \
      this->setconode((p));                      \
   }                                             \
}

// - global const variables -
//
const char undefined[] = "undefined";
const int illegal = -1;
const char RESOURCE_PATH[] = "..//Resources//";

class CoPoint;

// - global functions-
//
bool g_isPointLocatedInRect(const CoPoint& point, const CoRect& rect);
void g_initCString(char*& dest, const char* source, int length = 30);
CoPoint g_convertPositionFromViewToGL(const CoPoint& locationInView );
std::string g_resourcePathTo(const std::string& fileName);

// - LDVec3 - 
//
template<typename T>
struct LDVec3
{
   T v[3];
   LDVec3(T v0, T v1, T v2) {
      v[0] = v0; v[1] = v1, v[2] = v2;
   }
   LDVec3(const LDVec3& other) {
      v[0] = other.v[0];
      v[1] = other.v[1];
      v[2] = other.v[2];
   }
   const LDVec3& operator=(const LDVec3& other) {
      v[0] = other.v[0];
      v[1] = other.v[1];
      v[2] = other.v[2];
      return v;
   }
};


// - CoPoint
//
class CoPoint : public cocos2d::CCPoint
{
public:
   CoPoint(void);
   CoPoint(float x, float y);
   CoPoint(const cocos2d::CCPoint& other);
   
   CoPoint operator=(const cocos2d::CCPoint& other);
   CoPoint operator+(const CoPoint& point) const;
   CoPoint operator-(const CoPoint& point) const;
   CoPoint operator+=(const CoPoint& point);
   CoPoint operator*(int factor);
   CoPoint operator*(int factor) const;
   b2Vec2 ToB2Vec2(float ratio=1) const;
};

#endif //LDTYPES_H
