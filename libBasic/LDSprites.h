#ifndef LDSPRITES_H
#define LDSPRITES_H

#include <libBasic/LDBase.h>

// - LDSpriteBase -
//
class LDSpriteBase : public LDObject, public LDNotifier
{
public:
   LDSpriteBase(void);
   LDSpriteBase(const char* spriteName, CoNode* conode = NULL);
   virtual ~LDSpriteBase(void);
   
   virtual LDType GetType(void) const = 0;
   virtual void Move(const CoPoint& stepVec);
   virtual void TouchHint(const LDHint& hint);
   
   //void SetParentLayer(LDLayer* parentLayer);
   //LDLayer* GetParentLayer(void);
   void Update(float dt);
   void SetB2Body(b2Body* bBody);
   b2Body* GetB2Body(void);
   
protected:
   virtual void update(float dt);
   void updateB2Body(float dt);
   
protected:
   b2Body* _bBody;
   std::string _name;
};
typedef std::vector<LDSpriteBase*> LDSpriteBaseArray;

// - LDSprite -
//
class LDSprite : public LDSpriteBase
{
public:
   LDSprite(void);
   LDSprite(const char* spriteFilePath,
            const char* spriteName = undefined,
            CoSprite* cosprite = NULL);
   virtual ~LDSprite(void);

   virtual LDType GetType(void) const {
      return LDSpriteType;
   }
   
   CoSprite* GetCoSprite(void);

protected:
   void init(void);
   
private:
   std::string _spriteFilePath;
   CoSprite* _cosprite;
   uint _literalID;
};

// - LDLabel -
//
class LDLabel : public LDSpriteBase
{
  public:
   LDLabel(void);
   LDLabel(const char* string,
           const char* spriteName = undefined,
           CoLabelBMFont* colabelbmfont = NULL);
   virtual ~LDLabel(void);

   virtual LDType GetType(void) const {
      return LDLabelType;
   }

   void SetPosition(float x, float y);
   void SetPosition(const CoPoint& pos);
   void SetScale(float scale);
   void SetColor(int r, int g, int b);
   void SetString(const char* string);
   const char* GetString(void) const;

protected:
   void init(void);
   
private:
   CoLabelBMFont* _colabelbmfont;
};
typedef std::vector<LDLabel*> LDLabelArray;

#endif //LDSPRITES_H
