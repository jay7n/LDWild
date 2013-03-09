#ifndef LDSUBMANAGER_H
#define LDSUBMANAGER_H

clas LDDialogue;

class LDSubManager
{
public:
   static LDSubManager* GetSingleton(void);
   
   void SetSubtitlePosition(const CoPoint& position);
   CoPoint GetSubtitlePosition(void);

   void DisplayDialogues(LDDialogues* dialogues);
   
private:
   LDSubManager();
   ~LDSubManager();

   void displayDialogueOne(Dialogue* dialogue);
   
   static LDSubManager* _singleton;
   LDSubtitles _subtitles;
   
};

#endif //LDSUBMANAGER_H
