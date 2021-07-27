
#if !defined(BINGROWSQUARE_H)
#define BINGROWSQUARE_H
#include "Symbol.h"

class BingrowSquare
{
   Symbol symbol;
   bool covered;
public:
   Symbol getSymbol(void)
   {
      return symbol;
   }
   bool getCovered(void)
   {
      return covered;
   }
   void setCovered(bool covered)
   {
      this->covered = covered;
   }
   void setSymbol(Symbol symbol)
   {
      this->symbol = symbol;
   }

   bool operator==(const BingrowSquare &other)
   {
      return ((this->symbol == other.symbol) && (this->covered == other.covered));
   }
};
#endif