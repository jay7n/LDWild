#ifndef ROLEME_H
#define ROLEME_H

#include <libBasic/LDBase.h>
#include <libBasic/LDSprites.h>

class LDScene;
class LDSceneMainTest;
class LDFrameAnim;

class LDRoleMe : public LDSprite
{
public:
   static LDRoleMe* GetOrCreateMe(void);
   bool BindScene(LDSceneMainTest* mainScene);
   LDSceneMainTest* GetBindedMainScene(void) { return _mainScene; }

   //override BaseClasses' method


   /************************
     TL   |  top   | TR
 _________|________|_________
     |    |        |    |
left |gap | center | gap|  right
 ____|____|________|____|____
          | bottom |
     BL   |        | BR
   **************************/
   enum AreaPart {
      //      AREAPART_NONE = -1
      AREAPART_LEFT = 0,
      AREAPART_LEFT_GAP,
      AREAPART_CENTER,
      AREAPART_RIGHT_GAP,
      AREAPART_RIGHT,

      AREAPART_TL,
      AREAPART_TOP,
      AREAPART_TR,
      AREAPART_BL,
      AREAPART_BOTTOM,
      AREAPART_BR,
   };
   AreaPart TouchRoleMeAreaPart(const CoPoint& touchPoint );
   static CoPoint GetDefaultStepVec(void){ return _defaultStepVec; }
   
   //behavior
   void Move(const CoPoint& stepVec);
   void Standby(void);
   bool IsCollidedWith(LDSpriteBase* sprite);

protected:
   void init(void);
   
private:
   LDRoleMe(void);
   CoRect getMeArea(void);

private:
   static CoPoint _defaultStepVec;
   static LDRoleMe* _singleton;
   
   LDSceneMainTest* _mainScene;
   LDFrameAnim* _meMoveAnim;
   CoRect _meArea;
};

#endif //ROLEME_H
