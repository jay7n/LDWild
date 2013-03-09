#ifndef LDDIALOGUE_H
#define LDDIALOGUE_H

class LDDialogue{
public:
   LDDialogue(void);
   LDDialogue(const char* whoSays, const char* whatSays,
              int clueID, float timeInterval);
   LDDialogue(const LDDialogue& other);
   const LDDialogue& operator=(const LDDialogue& other);
   
   ~LDDialogue(void);

   void SetContent(const char* whoSays, const char* whatSays,
                   int clueID, float timeInterval);
   
private:
   std::string _whoSays;
   std::string _whatSays;
   int _clueID; // TODO: replaced by a special data structure
   float _interval; 
};
typedef std::vector<LDDialogue*> LDDialogueArray;

class LDDialogues
{
public:
   LDDialogues(void);
   ~LDDialogues(void);
   
   void AddDialogue(const LDDialogue& dialogue);
   void AddDialogue(std::string whoSays, std::string whatSays, int clueID = -1);
   LDDialogue GetDialogue(int idx);
   
private:
   LDDialogueArray _dialogues;
};
#endif //LDDIALOGUE_H
