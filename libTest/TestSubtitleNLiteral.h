#ifndef TEST_SUBTITLE_N_LITERAL_H
#define TEST_SUBTITLE_N_LITERAL_H

#include <libCompo/LDLiteral.h>
#include <libCompo/LDSubtitle.h>

namespace TestCase {
   
class TestSubtitleNLiteral
{
public:
   TestSubtitleNLiteral(void) {
      LDDialoguePassage dp;
      dp.Fill("lily", "what's this??");
      dp.Fill("lookof", "this is a test.", 3);
      dp.Fill("lookof", "don't be scared.", 4);
      
      LDSubtitleSys* subtSys = LDSubtitleSys::Singleton();
      subtSys->SetPosition(380, 30);
      subtSys->SetScale(0.8f);
      subtSys->DisplayLiteral(&dp);
   }
};
   
}


#endif //TEST_SUBTITLE_N_LITERAL_H
