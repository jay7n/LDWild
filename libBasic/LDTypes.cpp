#include <libBasic/LDTypes.h>

// - CoPoint -
//
//
CoPoint::CoPoint(void)
   :cocos2d::CCPoint(0,0)
{
   
}

CoPoint::CoPoint(float x, float y)
{
   this->x = x;
   this->y = y;
}
   
CoPoint::CoPoint(const cocos2d::CCPoint& other)
{
   this->x = other.x;
   this->y = other.y;
}
CoPoint CoPoint::operator=(const cocos2d::CCPoint& other)
{
   this->x = other.x;
   this->y = other.y;
   return *this;
}
   
CoPoint CoPoint::operator+(const CoPoint& point) const
{
   CoPoint res;
   res.x = this->x + point.x;
   res.y = this->y + point.y;
   return res;
}

CoPoint CoPoint::operator-(const CoPoint& point) const
{
   CoPoint res;
   res.x = this->x - point.x;
   res.y = this->y - point.y;
   return res;
}
   
CoPoint CoPoint::operator+=(const CoPoint& point)
{
   this->x = this->x+ point.x;
   this->y = this->y+ point.y;
   return *this;
}
   
CoPoint CoPoint::operator*(int factor)
{
   CoPoint res;
   res.x = this->x * factor;
   res.y = this->y * factor;
   return res;
}

CoPoint CoPoint::operator*(int factor) const
{
   CoPoint res;
   res.x = this->x * factor;
   res.y = this->y * factor;
   return res;
}

b2Vec2 CoPoint::ToB2Vec2(float ratio) const
{
   b2Vec2 bvec2(this->x/ratio, this->y/ratio);
   return bvec2;
}

// - globals functions-
//
//
extern bool g_isPointLocatedInRect(const CoPoint& point, const CoRect& rect)
{
   return CoRect::CCRectContainsPoint(rect, point);
}

extern void g_initCString(char*& dest, const char* source, int length)
{
   dest = new char[length];
   if(source) {
      strcpy(dest, source);
   }
   else {
      strcpy(dest, "dummy");
   }
}

extern CoPoint g_convertPositionFromViewToGL(const CoPoint& locationInView )
{
   return CoDirer->convertToGL(locationInView);
}

extern std::string g_resourcePathTo(const std::string& fileName)
{
   static std::string wholePath;
   
   wholePath = std::string(RESOURCE_PATH) + fileName;;
   return wholePath;
}
