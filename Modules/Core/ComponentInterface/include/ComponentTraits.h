#ifndef ComponentTraits_h
#define ComponentTraits_h

#include "GDOptimizer3rdPartyComponent.h"

namespace selx
{
// Traits to get printable interface name
// default implementation
template <typename T>
struct ComponentTraits
{
  //static_assert(false, "Please implement a template specialization for the appropriate Component");

  // I would like to be it a real Trait but this is not allowed:
  //static const char* Name = "ERROR: Please implement Name";
  //a static data member with an in - class initializer must have non - volatile const integral type
  static const char* GetDescription()
  {
    return "ERROR: Please implement Description";
  }
  static const char* GetName()
  {
    return "ERROR: Please implement Name";
  }
 
};

// a specialization for each type of those you want to support
// and don't like the string returned by typeid
template <>
struct InterfaceName < GDOptimizer3rdPartyComponent >
{
  static const char* GetDescription()
  {
    return "GD Optimizer 3rdParty Component";
  }
  static const char* GetName()
  {
    return "GDOptimizer3rdPartyComponent";
  }
};
} // end namespace selx


#endif // #define ComponentTraits_h