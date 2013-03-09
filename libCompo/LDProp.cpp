#include <libCompo/LDProp.h>

// - LDProp -
//
//
LDProp::LDProp(const char* propFilePath, const char* propName)
   :LDSprite(propFilePath, propName),
    _data(new LDPropData)
{
   
}

LDProp::~LDProp(void)
{
   if(_data) {
      delete _data;
      _data = NULL;
   }
}

void LDProp::TouchHint(const LDHint& hint)
{
   
}

void LDProp::BindLiteralID(uint id)
{
   assert(_data);
   _data->SetLiteralID(id);
}


// - LDPropData -
//
//
LDPropData::LDPropData(void)
 :_literalID(illegal)
{
   
}

void LDPropData::SetLiteralID(uint id)
{
   _literalID = id;
}
