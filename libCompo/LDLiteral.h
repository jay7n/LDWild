#ifndef LDLITERAL_H
#define LDLITERAL_H

#include <libBasic/LDBase.h>
#include <string>
#include <vector>

// - LDLiteral -
//
class LDLiteral
{
public:
   enum Type {
      LDDialogueType = 0,
      LDDialoguePassageType,
   };
   virtual Type GetType(void) = 0;
};

const float LDDIALOGUE_DEFAULT_TIME_INTERVAL = 2.0f;

// - LDDialogue -
//
class LDDialogue : public LDLiteral
{
public:
   LDDialogue(void);
   LDDialogue(const char* whoSays,
              const char* whatSays,
              float timeInterval = LDDIALOGUE_DEFAULT_TIME_INTERVAL,
              int clueID = illegal);
   
   Type GetType(void) {
      return LDDialogueType;
   }

   std::string StrContent(void);
   
   void SetContent(const std::string whoSays,
                   const std::string whatSays,
                   int clueID,
                   float timeInterval);
   
   void GetContent(std::string& whoSays,
                   std::string& whatSays,
                   int& clueID,
                   float& timeInterval) const;

   float GetTimeInteral(void) const;
   
private:
   std::string _whoSays;
   std::string _whatSays;
   float _timeInterval;
   int _clueID; // TODO: replaced by a special data structure
};
typedef std::vector<LDDialogue*> LDDialogueArray;


// - LDDialoguePassage -
//
class LDDialoguePassage : public LDLiteral
{
public:
   class Iterator
   {
   public:
      Iterator(const LDDialogueArray& dlgArray)
         :_dlgPassage(dlgArray),
          _curItr( _dlgPassage.begin() ) {}

      ~Iterator(void) {
         
      }

      uint GetCurrent(LDDialogue** dlg) {
         if( _curItr!=_dlgPassage.end() ) {
            *dlg = *_curItr;
            return ( _curItr-_dlgPassage.begin() );
         } else {
            *dlg = NULL;
            return illegal;
         }
      }
      
      uint GetNext(LDDialogue** dlg) {         
         if( HasNext() ) {
            _curItr++;
         }
		 uint currIdx = GetCurrent(dlg);
         return currIdx;
      }
      
      bool HasNext(void) {
         return ( _dlgPassage.end() - _curItr > 0 );
      }
      
   private:
      LDDialogueArray _dlgPassage; //reference memeber
      LDDialogueArray::iterator _curItr;
   };

   LDDialoguePassage(void);
   
   void Fill(const char* whoSays,
             const char* whatSays,
             float timeInterval = LDDIALOGUE_DEFAULT_TIME_INTERVAL);
   
   Type GetType(void) {
      return LDDialoguePassageType;
   }

   Iterator* CreateTraverse(void);
   uint TraversePassage(LDDialogue** dialogue);
   
private:
   LDDialogueArray _dlgPassage;
   Iterator* _traverseItr;
};

#endif //LDLITERAL_H
