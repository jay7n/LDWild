#include <libBasic/LDSprites.h>

// - LDSpriteBase -
//
//
LDSpriteBase::LDSpriteBase(void)
   : LDObject(),
     _bBody(NULL),
     _name(undefined)
{
   
}

LDSpriteBase::LDSpriteBase(const char* spriteName, CoNode* conode)
  : LDObject(conode),
    _bBody(NULL),
    _name(spriteName ? spriteName : undefined)
{
   
}

LDSpriteBase::~LDSpriteBase(void)
{
   
}

void LDSpriteBase::Move(const CoPoint& stepVec)
{
   CoNode* conode = getconode();
   CoPoint pos = conode->getPosition();
   pos = pos + stepVec;
   conode->setPosition(pos);
}

void LDSpriteBase::TouchHint(const LDHint& hint)
{
   if( hint.IsHint(UpdateHint::SIGN) ) {
      const UpdateHint& updateHint =
         static_cast<const UpdateHint&>(hint);
      Update( updateHint.GetDT() );
   }
}

void LDSpriteBase::SetB2Body(b2Body* bBody)
{
   _bBody = bBody;
}

b2Body* LDSpriteBase::GetB2Body(void)
{
   return _bBody;
}

void LDSpriteBase::Update(float dt)
{
   update(dt);
   updateB2Body(dt);
}

void LDSpriteBase::update(float dt)
{
   
}

void LDSpriteBase::updateB2Body(float dt)
{
   CoNode* conode = GetCoNode();
   CoPoint position = conode->getPosition();
   b2Vec2 spritePos = position.ToB2Vec2();
   float spriteRotInDegrees = conode->getRotation();
   float spriteRotInRadians = -1 * CC_DEGREES_TO_RADIANS(spriteRotInDegrees);
   if( b2Body* bBody = GetB2Body() ) {
      bBody->SetTransform(spritePos, spriteRotInRadians);
   }
}

//------LDSprite------//
//
//
LDSprite::LDSprite(void)
   :LDSpriteBase( undefined, new CoSprite() ),
    _spriteFilePath(undefined),
    _cosprite( static_cast<CoSprite*>( getconode() ) )
{
   init();
}

LDSprite::LDSprite(const char* spriteFilePath,
                   const char* spriteName,
                   CoSprite* cosprite)
   :LDSpriteBase( spriteName,
                  cosprite ? cosprite : new CoSprite() ),
    _spriteFilePath(spriteFilePath ?
                    g_resourcePathTo(spriteFilePath) : undefined),
    _cosprite( static_cast<CoSprite*>( getconode() ) )
{
   init();
}

LDSprite::~LDSprite(void)
{
   LD_SAFE_DELETE_CC(_cosprite);
}

void LDSprite::init(void)
{
   if(_cosprite) {
      _cosprite->init();
      if( 0!=_spriteFilePath.compare(undefined) ) {
         _cosprite->initWithFile(_spriteFilePath.c_str());
      }
   }
}

CoSprite* LDSprite::GetCoSprite(void)
{
   return _cosprite;
}

// - LDLable -
//
//
LDLabel::LDLabel(void)
   :LDSpriteBase( undefined, new CoLabelBMFont() ),
    _colabelbmfont( static_cast<CoLabelBMFont*>( getconode() ) )
{
   init();
}

LDLabel:: LDLabel(const char* string,
                  const char* spriteName,
                  CoLabelBMFont* colabelbmfont)
   :LDSpriteBase( spriteName,
                   colabelbmfont ? colabelbmfont : new CoLabelBMFont() ),
    _colabelbmfont( static_cast<CoLabelBMFont*>( getconode() ) )
{
   init();
   SetString(string);
}

LDLabel::~LDLabel(void)
{
   LD_SAFE_DELETE_CC(_colabelbmfont);
}

void LDLabel::init(void)
{
   assert(_colabelbmfont);
   _colabelbmfont->init();
   _colabelbmfont->initWithString( "", g_resourcePathTo("bitmap.fnt").c_str() );
   _colabelbmfont->setAnchorPoint( CoPoint(0,0) );

   SetPosition(0,0);
   SetColor(0,0,0);
}

void LDLabel::SetPosition(float x, float y)
{
   _colabelbmfont->setPosition(x, y);
}

void LDLabel::SetPosition(const CoPoint& pos)
{
   _colabelbmfont->setPosition(pos.x, pos.y);
}

void LDLabel::SetScale(float scale)
{
   _colabelbmfont->setScale( scale );
}

void LDLabel::SetColor(int r, int g, int b)
{
   CoColor3B c3 = {
      r, g, b
   };
   _colabelbmfont->setColor(c3);
}

void LDLabel::SetString(const char* string)
{
   assert(_colabelbmfont && string);
   if(_colabelbmfont) {
      _colabelbmfont->setString(string);      
   }
}

const char* LDLabel::GetString(void) const
{
   assert(_colabelbmfont);
   return _colabelbmfont->getString();
}

