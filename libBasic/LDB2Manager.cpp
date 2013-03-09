#include <libBasic/LDB2Manager.h>
#include <libBasic/LDSprites.h>

const int B2WRD_VEL_ITERA = 10;
const int B2WRD_POS_ITERA = 10;

LDB2Manager* LDB2Manager::_singleton = NULL;

LDB2Manager* LDB2Manager::GetSingleton(void)
{
   if(!_singleton) {
      _singleton = new LDB2Manager;
   }
   return _singleton;
}

LDB2Manager::LDB2Manager(void)
 :_b2World(NULL),
  _contactListener(NULL)
{
   init();
}

LDB2Manager::~LDB2Manager(void)
{
   if(_b2World) {
      delete _b2World;
      _b2World = NULL;
   }
}

void LDB2Manager::init()
{
   _b2World = new b2World( b2Vec2(0.0f, 0.0f) );
   _contactListener = new LDB2ContactListener;
   _b2World->SetContactListener(_contactListener);
}

bool LDB2Manager::CreateB2BodyTo(LDSpriteBase* sprite)
{
   bool ret = false;
   if(sprite) {
      CoNode* conode = sprite->GetCoNode();
      CoPoint spritePos = conode->getPosition();
      b2BodyDef spriteBodyDef;
      spriteBodyDef.type = b2_dynamicBody;
      spriteBodyDef.position.Set(spritePos.x, spritePos.y); //PTM_RATIO ??
      spriteBodyDef.userData = sprite;
      b2Body* spriteBody = _b2World->CreateBody(&spriteBodyDef);
      sprite->SetB2Body(spriteBody);
      
      CoSize spriteSize = conode->getContentSize();
      b2PolygonShape spriteShape;
      spriteShape.SetAsBox(spriteSize.width/2, spriteSize.height/2);
      b2FixtureDef spriteFixtureDef;
      spriteFixtureDef.shape = &spriteShape;
      spriteFixtureDef.density = 10.0f;
      spriteFixtureDef.isSensor = true;
      spriteBody->CreateFixture(&spriteFixtureDef);
      
      ret = true;
   }
   return ret;
}


bool LDB2Manager::DestoryB2BodyFrom(LDSpriteBase* sprite)
{
   bool ret = false;
   b2Body* spriteBody = NULL;
   if( sprite && (spriteBody=sprite->GetB2Body()) ) {
      _b2World->DestroyBody(spriteBody);
      sprite->SetB2Body(NULL);
      ret = true;
   }
   return ret;
}

void LDB2Manager::UpdateB2World(float dt)
{
   _b2World->Step(dt, B2WRD_VEL_ITERA, B2WRD_POS_ITERA);
}

bool LDB2Manager::IsTwoSpritesContact(LDSpriteBase* spriteA, LDSpriteBase* spriteB)
{
   if(spriteA && spriteB) {
      const LDB2Contacts* contacts = _contactListener->GetContacts();
      size_t contactsSize = contacts ? contacts->size() : 0;
      for(size_t i=0; i<contactsSize; i++) {
         LDB2Contact contact = (*contacts)[i];
         b2Fixture* fixtureA = contact.Get(LDB2Contact::Fix_A);
         b2Fixture* fixtureB = contact.Get(LDB2Contact::Fix_B);
         b2Body* bodyA = fixtureA->GetBody();
         b2Body* bodyB = fixtureB->GetBody();
         if( (bodyA == spriteA->GetB2Body() && bodyB == spriteB->GetB2Body()) ||
             (bodyB == spriteA->GetB2Body() && bodyA == spriteB->GetB2Body())
           ) {
            return true;
         }
      }
   }
   return false;
}

//LDB2Contact
//
LDB2Contact::LDB2Contact(b2Fixture* fixtureA, b2Fixture* fixtureB)
 :_fixtureA(fixtureA), _fixtureB(fixtureB)
{
   
}

LDB2Contact::~LDB2Contact(void)
{
   
}

b2Fixture* LDB2Contact::Get(Fixture fix)
{
   if(fix==Fix_A) {
      return _fixtureA;
   }else if (fix==Fix_B) {
      return _fixtureB;
   }
   return NULL;
}

bool LDB2Contact::operator==(const LDB2Contact& other) const 
{
   bool ret = (_fixtureA==other._fixtureA) && (_fixtureB==other._fixtureB);
   return ret;
}

//LDB2ContactListener
//
LDB2ContactListener::LDB2ContactListener(void)
{
   
}

LDB2ContactListener::~LDB2ContactListener(void)
{
   
}

void LDB2ContactListener::BeginContact(b2Contact* contact)
{
   LDB2Contact ldb2c( contact->GetFixtureA(), contact->GetFixtureB() );
   _contacts.push_back(ldb2c);
}

void LDB2ContactListener::EndContact(b2Contact* contact)
{
   LDB2Contact ldb2c( contact->GetFixtureA(), contact->GetFixtureB() );
   LDB2Contacts::iterator pos;
   pos = std::find(_contacts.begin(), _contacts.end(), ldb2c);
   if( pos != _contacts.end() ) {
      _contacts.erase(pos);
   }
}

const LDB2Contacts* LDB2ContactListener::GetContacts(void) const {
   return &_contacts;
}
