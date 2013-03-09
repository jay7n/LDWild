#ifndef LDHINTS_H
#define LDHINTS_H

#include <libBasic/LDTypes.h>
#include <libBasic/LDIDAlloc.h>

// - LDHint -
class LDHint
{
public:
   uint GetSign(void) {
      return _sign;
   }
   bool IsHint(uint sign) const {
      return _sign==sign;
   }

protected:
   // the constructor is designed as a protected member function, so that it can
   // not be instanced from external, but only from its inherited classes. 
   LDHint(uint sign)
      : _sign(sign){
   }
   const uint _sign;
};

class UpdateHint : public LDHint
{
  public:
  UpdateHint(float dt)
     :LDHint( SIGN==illegal ?
              LDIDAlloc::AllocID("UpdateHint", "LDHint") : SIGN ),
      _dt(dt)
      { SIGN = GetSign(); }
   static uint SIGN;

   inline float GetDT(void) const {
      return _dt;
   }
      
  private:
   float _dt;
};

#endif //LDHINTS_H
