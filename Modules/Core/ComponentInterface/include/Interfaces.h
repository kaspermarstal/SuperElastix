#ifndef Interfaces_h
#define Interfaces_h

#include "ComponentBase.h"
#include "InterfaceTraits.h"
#include <typeinfo>

namespace elx
{
// Define the providing interfaces abstractly
class MetricDerivativeInterface {
  public:
    virtual int GetDerivative() = 0;
};

class MetricValueInterface {
  public:
    virtual int GetValue() = 0;
};

class OptimizerUpdateInterface {
public:
  virtual int Update() = 0;
};

class ConflictinUpdateInterface {
public:
 // "error" : member function templates cannot be virtual
 // template <class ConflictinUpdateInterface> virtual int Update() = 0;
  //TODO http://en.cppreference.com/w/cpp/language/member_template

  //TODO solution: http://stackoverflow.com/questions/2004820/inherit-interfaces-which-share-a-method-name
  //TODO better?: http://stackoverflow.com/questions/18398409/c-inherit-from-multiple-base-classes-with-the-same-virtual-function-name
  virtual int Update(ConflictinUpdateInterface*) = 0;
};

// Define the accepting interfaces as templated by the providing interface

template<class InterfaceT>
class InterfaceAcceptor {
public:

  // Set() is called by a succesfull Connect()
  // The implementation of Set() must be provided by component developers. 
  virtual int Set(InterfaceT*) = 0; 

  // Connect tries to connect this accepting interface with all interfaces of the provider component.
  int Connect(ComponentBase*); 

private:
  bool isSet;
};

template<typename ... RestInterfaces>
class Accepting
{
  public:
    interfaceStatus ConnectFromImpl(const char *, ComponentBase*) { return interfaceStatus::noaccepter; }; //no interface called interfacename ;
    int ConnectFromImpl(ComponentBase*) { return 0; }; //Empty RestInterfaces does 0 successful connects ;
};

template<typename FirstInterface, typename ... RestInterfaces>
class Accepting<FirstInterface, RestInterfaces... > : public InterfaceAcceptor<FirstInterface>, public Accepting< RestInterfaces ... >
{
public:
  interfaceStatus ConnectFromImpl(const char *, ComponentBase*);
  int ConnectFromImpl(ComponentBase*);
};

template<typename... Interfaces>
class Providing : public Interfaces...
{
};

template<typename AcceptingInterfaces, typename ProvidingInterfaces>
class Implements : public AcceptingInterfaces, public ProvidingInterfaces, public ComponentBase
{
  public:
    virtual interfaceStatus ConnectFrom(const char *, ComponentBase*);
    virtual int ConnectFrom(ComponentBase*);
};

} // end namespace elx

#ifndef ITK_MANUAL_INSTANTIATION
#include "Interfaces.hxx"
#endif

#endif // #define Interfaces_h