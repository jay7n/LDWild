#ifndef LDPROP_H
#define LDPROP_H

#include <libBasic/LDSprites.h>

class LDPropData;

// - LDProp -
//
class LDProp : public LDSprite
{
public:
   LDProp(const char* propFilePath,
          const char* propName);
   LDProp(const LDProp& other);
   virtual ~LDProp(void);
   
   virtual void TouchHint(const LDHint& hint);

   void BindLiteralID(uint id);
   
private:
   LDPropData* _data;
};


// - LDPropData -
//
class LDPropData
{
public:
   LDPropData(void);
   
   void SetLiteralID(uint id);
   uint GetLiteralID(void);
   
private:
   uint _literalID;
};

#endif // LDPROP_H
