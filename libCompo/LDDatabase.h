#idndef LDDATABASE_H
#define LDDATABASE_H

#include <libBasic/LDBase.h>
#include <libCompo/LDLiteral.h>

class LDDatabaseImp;

class LDDatabase : public LDAny
{
public:
   static LDDatabase* Singleton(void);

   LDLiteral* GetLiteralByID(uint literalID);
   
private:
   LDDatabase(void);
   static LDDatabase* _singleton;

   LDDatabaseImp* _imp;
};

#endif // LDDATABASE_H
