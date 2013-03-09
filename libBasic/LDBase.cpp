#include <libBasic/LDBase.h>

// - LDSubject -
//
//
void LDSubject::RegisterObserver(LDObserver* observer)
{
   _observers.push_back(observer);
}


// - LDSubject -
//
//
bool LDSubject::DeregisterObserver(LDObserver* observer)
{
   std::list<LDObserver*>::iterator itr =
      std::find(_observers.begin(), _observers.end(), observer);
   if( itr!=_observers.end() ) {
      _observers.erase(itr);
      return true;
   }
   return false;
}

void LDSubject::NotifyHint(const LDHint& hint)
{
   std::list<LDObserver*>::iterator itr = _observers.begin();
   std::list<LDObserver*>::iterator end = _observers.end();
   for(itr; itr!=end; itr++) {
      if( (*itr) ) {
         (*itr)->TouchHint(hint);
      }
   }
}

// - LDBase -
//
//

// - LDObject -
//
//
LDObject::LDObject(void)
   :_conode( new CoNode() )
{
   
}

LDObject::LDObject(CoNode* conode)
   :_conode( conode ? conode : new CoNode() )
{
   
}

LDObject::~LDObject(void)
{
   LD_SAFE_DELETE_CC(_conode);
}

CoNode* LDObject::GetCoNode(void)
{
   return  _conode;
}

CoNode* LDObject::getconode(void)
{
   return _conode;
}

void LDObject::setconode(CoNode* conode)
{
   LD_SAFE_DELETE_CC(conode);
   _conode = conode;
}
