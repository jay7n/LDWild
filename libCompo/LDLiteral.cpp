#include <libCompo/LDLiteral.h>

// - LDDialogue -
//
//
LDDialogue::LDDialogue(void)
   :_whoSays(undefined),
    _whatSays(undefined),
    _timeInterval(illegal),
    _clueID(illegal)
{
   
}

LDDialogue::LDDialogue(const char* whoSays,
                       const char* whatSays,
                       float timeInterval,
                       int clueID)
   :_whoSays(whoSays),
    _whatSays(whatSays),
    _timeInterval(timeInterval),
    _clueID(clueID)
{
   
}

std::string LDDialogue::StrContent(void)
{
   std::string ret = _whoSays;
   ret = ( ret.append(": ") ).append(_whatSays);
   return ret;
}


void LDDialogue::SetContent(const std::string whoSays,
                            const std::string whatSays,
                            int clueID,
                            float timeInterval)
{
   _whoSays = whoSays;
   _whatSays = whatSays;
   _clueID = clueID;
   _timeInterval = timeInterval;
}

void LDDialogue::GetContent(std::string& whoSays,
                            std::string& whatSays,
                            int& clueID,
                            float& timeInterval) const
{
   whoSays = _whoSays;
   whatSays = _whatSays;
   clueID = _clueID;
   timeInterval = _timeInterval;
}

float LDDialogue::GetTimeInteral(void) const
{
   return _timeInterval;
}

// - LDDialoguePassage -
//
//
LDDialoguePassage::LDDialoguePassage(void)
   : _traverseItr(NULL)
{
   
}

void LDDialoguePassage::Fill(const char* whoSays,
                             const char* whatSays,
                             float timeInterval)
{
   LDDialogue* dlg = new LDDialogue(whoSays, whatSays, timeInterval);
   _dlgPassage.push_back(dlg);
}

LDDialoguePassage::Iterator* LDDialoguePassage::CreateTraverse(void)
{
   return new Iterator( this->_dlgPassage );
}

uint LDDialoguePassage::TraversePassage(LDDialogue** dialogue)
{
   uint ret = illegal;
   *dialogue = NULL;
   if( _traverseItr->HasNext() ) {
       ret = _traverseItr->GetNext(dialogue);
   }
   return ret;
}
