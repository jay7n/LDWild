#ifndef LDBASE_H
#define LDBASE_H

#include <libBasic/LDTypes.h>
#include <libBasic/LDHints.h>
#include <libBasic/LDIDAlloc.h>

// - LDObserver -
class LDObserver
{
public:
   virtual void TouchHint(const LDHint& hint) = 0;
};

// - LDSubject -
//
class LDSubject
{
public:
   
   void RegisterObserver(LDObserver* observer);
   bool DeregisterObserver(LDObserver* observer);
   
   virtual void NotifyHint(const LDHint& hint);
   
private:
   std::list<LDObserver*> _observers;   
};

// - LDNotifier
//
class LDNotifier : public LDSubject, public LDObserver
{
                      
};


// - LDAny -
//
class LDAny
{
    
};


// - LDBase -
//
class LDBase : public LDAny
{
public:
   enum LDType {
      LDObjectType = 0,
      LDSpriteType,
      LDLabelType,
      LDLayerType,
      LDLayerMasterType,
      LDLayerBackgroundType,
      LDSceneType,
      LDSceneMainTestType,
      LDFrameAnimType,
      LDSpriteLoaderType,
      LDTypeNums
   };
   virtual LDType GetType() const = 0;
};

// - LDObject -
//
class LDObject : public LDBase
{
public:
   LDObject(void);
   LDObject(CoNode* conode);
   ~LDObject(void);
   
   virtual LDType GetType() const {
      return LDObjectType;
   }
   
   CoNode* GetCoNode(void);
   
protected:
   CoNode* getconode(void);
   void setconode(CoNode* conode);
   
private:
   CoNode* _conode;
};

#endif // LDBASE_H
