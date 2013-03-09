#ifndef LDB2MANAGER_H
#define LDB2MANAGER_H

#include <libBasic/LDBase.h>

class LDSpriteBase;

class LDB2ContactListener;

class LDB2Manager
{
public:
   static LDB2Manager* GetSingleton(void);
   bool CreateB2BodyTo(LDSpriteBase* sprite);
   bool DestoryB2BodyFrom(LDSpriteBase* sprite);
   void UpdateB2World(float dt);
   bool IsTwoSpritesContact(LDSpriteBase* spriteA, LDSpriteBase* spriteB);
   
private:
   LDB2Manager(void);
   ~LDB2Manager(void);
   void init(void);
   static LDB2Manager* _singleton;

private:
   b2World* _b2World;
   LDB2ContactListener* _contactListener;
};

class LDB2Contact
{
public:
   LDB2Contact(b2Fixture* fixtureA, b2Fixture* fixtureB);
   ~LDB2Contact(void);
   enum Fixture{
      Fix_A = 0,
      Fix_B
   };
   b2Fixture* Get(Fixture fix);
   bool operator==(const LDB2Contact& other) const;
private:
   b2Fixture* _fixtureA;
   b2Fixture* _fixtureB;
};

typedef std::vector<LDB2Contact> LDB2Contacts;

class LDB2ContactListener : public b2ContactListener
{
public:
   LDB2ContactListener(void);
   ~LDB2ContactListener(void);
   const LDB2Contacts* GetContacts(void) const;
   virtual void BeginContact(b2Contact* contact);
   virtual void EndContact(b2Contact* contact);
   virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold){}
   virtual void PosSolve(b2Contact* contact, const b2ContactImpulse* impulse){}
   
private:
    LDB2Contacts _contacts;   
};

#endif //LDB2MANAGER_H
