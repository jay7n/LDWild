#include <libCompo/LDSubtitle.h>
#include <libCompo/LDLiteral.h>
#include <libOrgan/LDLayers.h>

// - LDLiteralSingleParsed -
//
class LDDialogueParsed
{
public:
   LDDialogueParsed(LDDialogue* sourceDlg)
      :_sourceDlg(sourceDlg) {
      
   }
   std::string GetSimple(void) {
      assert(_sourceDlg);
      return _sourceDlg->StrContent();
   }
   
private:
   void parse(void); // ---
   LDDialogue* _sourceDlg;
};

// - LDSubtitleSys -
//
//
LDSubtitleSys* LDSubtitleSys::_singleton = NULL;

LDSubtitleSys* LDSubtitleSys::Singleton(void)
{
   if (NULL==_singleton) {
      _singleton = new LDSubtitleSys();
   }
   return _singleton;
}

void LDSubtitleSys::Destroy(void)
{
   reset();
   if(_hostLayer) {
      // destroy _hostLayer
   }
}

LDSubtitleSys::LDSubtitleSys(void)
   :_currentLit(NULL),
    _subPos(0,0),
    _subScale(1),
    _timer(0.0f),
    _enable(false),
    _hostLayer( new LDLayer(false, false, "LDLayerSubtitle") ),
    _dlgPaItr(NULL)
{
   _hostLayer->RegisterObserver(this);
}

void LDSubtitleSys::TouchHint(const LDHint& hint)
{
   if( hint.IsHint(UpdateHint::SIGN) ) {
      const UpdateHint* updateHint =
         static_cast<const UpdateHint*>(&hint);
      update(updateHint->GetDT());
   }
}

LDLayer* LDSubtitleSys::GetHostLayer(void) const
{
   return _hostLayer;
}

void LDSubtitleSys::SetPosition(const CoPoint& position)
{
   _subPos = position;
}

void LDSubtitleSys::SetPosition(float x, float y)
{
   _subPos = CoPoint(x, y);
}

void LDSubtitleSys::SetScale(float scale)
{
   _subScale = scale;
}

void LDSubtitleSys::DisplayLiteral(LDLiteral* literal)
{
   if(literal) {
      enable(true); 
     _currentLit = literal;
      LDLiteral::Type litType = literal->GetType();
      switch(litType)
      {
      case LDLiteral::LDDialogueType:
         parseNdisplayDialogue( static_cast<LDDialogue*>(literal) );
         break;

      case LDLiteral::LDDialoguePassageType:
         displayDialoguePassage( static_cast<LDDialoguePassage*>(literal) );
         break;

      default:
         break;
      }
   }
}

void LDSubtitleSys::update(float dt)
{
   if( enable() ) {
      _timer += dt;
      if( _dlgPaItr ) { // have dialoguePassage
         LDDialogue* dialogue = NULL;
         uint idx = _dlgPaItr->GetCurrent(&dialogue);
         if( isTimeupForDialogue(dialogue) ) {
            idx = _dlgPaItr->GetNext(&dialogue);
            if(idx!=illegal && dialogue) {
               parseNdisplayDialogue( dialogue );
               _timer = 0.0f;
            } else {
               reset();
            }
         }
      }
      else if( LDLiteral::LDDialogueType == _currentLit->GetType() ) {
         LDDialogue* dialogue = static_cast<LDDialogue*>(_currentLit);
         if( isTimeupForDialogue(dialogue) ) {
            reset();
         }
      }
   }
}

void LDSubtitleSys::parseNdisplayDialogue(LDDialogue* dialogue)
{
   if(dialogue) {
      // this is the rather rough prototype.
      // and we must need use *LDDialogueParsed*.
      LDDialogueParsed parsedDlg(dialogue);
      LDLabel* label = retrieveLabel(0);
      label->SetColor(255,255,255); // as a prototype, we just simply set it as
                                    // white
      label->SetPosition(_subPos);
      label->SetScale(_subScale);
      label->SetString( parsedDlg.GetSimple().c_str() );
   }
}

void LDSubtitleSys::displayDialoguePassage(LDDialoguePassage* dlgPa)
{
   if(dlgPa) {
      _dlgPaItr = dlgPa->CreateTraverse();
      
      LDDialogue* dialogue = NULL;
      uint idx = _dlgPaItr->GetCurrent(&dialogue);
      if(idx!=illegal && dialogue) {
         parseNdisplayDialogue( dialogue );
      }
   }
}

bool LDSubtitleSys::isTimeupForDialogue(LDDialogue* dialogue)
{
   float litTimeInteral = dialogue ? dialogue->GetTimeInteral() : illegal;
   return (_timer > litTimeInteral);
}

LDLabel* LDSubtitleSys::retrieveLabel(uint idx)
{
   LDLabel* ret = NULL;
   size_t size = _labels.size();
   if( size==0 || (size-1) < idx ) {
      ret = new LDLabel;
      ret->SetPosition(_subPos.x, _subPos.y);
      _labels.reserve(idx+1);
      _labels.resize(idx);
      _labels.push_back(ret);
      _hostLayer->AddSprite(ret, true);
   }
   else {
      ret = _labels.at(idx);
   }
   return ret;
}

void LDSubtitleSys::clearLabelsContent(void)
{
   LDLabelArray::iterator itr = _labels.begin();
   LDLabelArray::iterator itrEnd = _labels.end();
   for(itr; itr!=itrEnd; itr++) {
      LDLabel* label = *itr;
      label->SetString("");
   }
}

void LDSubtitleSys::destroyLabels(bool all)
{
   LDLabelArray::iterator itr = all ? _labels.begin() : (1+_labels.begin());
   LDLabelArray::iterator itrEnd = _labels.end();
   for(itr; itr!=itrEnd; itr++) {
      delete (*itr);
   }
   
   if(all) {
      _labels.clear();
      LDLabelArray().swap(_labels);
   } else {
      _labels.resize(1);
      _labels.swap(LDLabelArray(_labels));
   }
}

void LDSubtitleSys::reset(bool destoryAllLabels)
{
   clearLabelsContent();
   destroyLabels(destoryAllLabels);
   enable(false);
   
   _currentLit = NULL;
   _subPos = CoPoint(200,200);
   _timer = 0.0f;
   if(_dlgPaItr) {
      delete _dlgPaItr;
      _dlgPaItr = NULL;
   }
}

void LDSubtitleSys::enable(bool confirm)
{
   _enable = confirm;
}

bool LDSubtitleSys::enable(void)
{
   return _enable;
}
