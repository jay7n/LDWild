#ifndef LDSUBTITLE_H
#define LDSUBTITLE_H

#include <libBasic/LDBase.h>
#include <libBasic/LDSprites.h>  //LDLabelArray
#include <libCompo/LDLiteral.h>

class LDLayer;
class LDLiteral;
class LDLiteralSingle;
class LDLiteralParsed;
class LDDialoguePassage;
class LDDialogue;
class LDLabel;


// - LDSubtitleSys -
//
class LDSubtitleSys : public LDNotifier
{
public:
   static LDSubtitleSys* Singleton(void);
   void Destroy(void); // ---

   virtual void TouchHint(const LDHint& hint);

   LDLayer* GetHostLayer(void) const ;
   void SetPosition(const CoPoint& position);
   void SetPosition(float x, float y);
   void SetScale(float scale);
   void DisplayLiteral(LDLiteral* literal);

private:
   LDSubtitleSys(void);
   
   void update(float dt);
   void parseNdisplayDialogue(LDDialogue* lit);
   void displayDialoguePassage(LDDialoguePassage* dialoguePassage);
   bool isTimeupForDialogue(LDDialogue* dialogue);
   
   LDLabel* retrieveLabel(uint idx);
   void clearLabelsContent(void);
   void destroyLabels(bool all=false);

   void reset(bool destoryLabels = false);
   void enable(bool confirm);
   bool enable(void);
   
private:
   static LDSubtitleSys* _singleton;
   
   LDLabelArray _labels;
   LDLiteral* _currentLit;
   CoPoint _subPos;
   float _subScale;
   float _timer;
   bool _enable;
   LDLayer* _hostLayer;
   LDDialoguePassage::Iterator* _dlgPaItr;
};

#endif //LDSUBTITLE_H
