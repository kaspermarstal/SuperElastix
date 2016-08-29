/*=========================================================================
 *
 *  Copyright Leiden University Medical Center, Erasmus University Medical
 *  Center and contributors
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef selxSuperElastixComponent_hxx
#define selxSuperElastixComponent_hxx

#include "selxInterfaceTraits.h"
namespace selx
{
template< class InterfaceT >
int
InterfaceAcceptor< InterfaceT >::Connect( ComponentBase * providerComponent )
{
  InterfaceT * providerInterface = dynamic_cast< InterfaceT * >( providerComponent );
  if( !providerInterface )
  {
    //TODO log message?
    //std::cout << "providerComponent does not have required " << InterfaceName < InterfaceT >::Get() << std::endl;
    return 0;
  }
  // connect value interfaces
  this->Set( providerInterface ); // due to the input argument being uniquely defined in the multiple inheritance tree, all versions of Set() are accessible at component level
  return 1;
}

template< class InterfaceT >
bool
InterfaceAcceptor< InterfaceT >::CanAcceptConnectionFrom(ComponentBase * providerComponent)
{
  InterfaceT * providerInterface = dynamic_cast< InterfaceT * >(providerComponent);
  return bool(providerInterface);
}

//////////////////////////////////////////////////////////////////////////
template< typename AcceptingInterfaces, typename ProvidingInterfaces >
ComponentBase::interfaceStatus
SuperElastixComponent< AcceptingInterfaces, ProvidingInterfaces >::AcceptConnectionFrom( const char * interfacename, ComponentBase * other )
{
  return AcceptingInterfaces::ConnectFromImpl( interfacename, other );
}


template< typename AcceptingInterfaces, typename ProvidingInterfaces >
int
SuperElastixComponent< AcceptingInterfaces, ProvidingInterfaces >::AcceptConnectionFrom( ComponentBase * other )
{
  return AcceptingInterfaces::ConnectFromImpl( other );
}


template< typename AcceptingInterfaces, typename ProvidingInterfaces >
bool
SuperElastixComponent< AcceptingInterfaces, ProvidingInterfaces >::HasAcceptingInterface( const char * interfacename )
{
  return AcceptingInterfaces::HasInterface( interfacename );
}


template< typename AcceptingInterfaces, typename ProvidingInterfaces >
bool
SuperElastixComponent< AcceptingInterfaces, ProvidingInterfaces >::HasProvidingInterface( const char * interfacename )
{
  return ProvidingInterfaces::HasInterface( interfacename );
}

template< typename AcceptingInterfaces, typename ProvidingInterfaces >
ComponentBase::interfaceStatus
SuperElastixComponent< AcceptingInterfaces, ProvidingInterfaces >
::CanAcceptConnectionFrom(ComponentBase* other, const InterfaceCriteriaType interfaceCriteria)
{
  return AcceptingInterfaces::CanAcceptConnectionFrom(other, interfaceCriteria);
}

//////////////////////////////////////////////////////////////////////////
template< typename FirstInterface, typename ... RestInterfaces >
ComponentBase::interfaceStatus
Accepting< FirstInterface, RestInterfaces ... >::ConnectFromImpl( const char * interfacename, ComponentBase * other )
{
  // does our component have an accepting interface called interfacename?
  if( InterfaceName< InterfaceAcceptor< FirstInterface >>::Get() == std::string( interfacename ) )
  {
    // cast always succeeds since we know via the template arguments of the component which InterfaceAcceptors its base classes are.
    InterfaceAcceptor< FirstInterface > * acceptIF = this;

    // See if the other component has the right interface and try to connect them
    if( 1 == acceptIF->Connect( other ) )
    {
      //success. By terminating this function, we assume only one interface listens to interfacename and that one connection with the other component can be made by this name
      return ComponentBase::interfaceStatus::success;
    }
    else
    {
      // interfacename was found, but other component doesn't match
      return ComponentBase::interfaceStatus::noprovider;
    }
  }
  return Accepting< RestInterfaces ... >::ConnectFromImpl( interfacename, other );
}


template< typename FirstInterface, typename ... RestInterfaces >
int
Accepting< FirstInterface, RestInterfaces ... >::ConnectFromImpl( ComponentBase * other )
{
  // cast always succeeds since we know via the template arguments of the component which InterfaceAcceptors its base classes are.
  InterfaceAcceptor< FirstInterface > * acceptIF = ( this );

  // See if the other component has the right interface and try to connect them
  // count the number of successes
  return acceptIF->Connect( other ) + Accepting< RestInterfaces ... >::ConnectFromImpl( other );
}


template< typename FirstInterface, typename ... RestInterfaces >
bool
Accepting< FirstInterface, RestInterfaces ... >::HasInterface( const char * interfacename )
{
  //TODO: check on interface template arguments as well
  auto interfaceProperies = Properties< FirstInterface >::Get();

  if (interfaceProperies["Name"] == std::string(interfacename))
  {
    return true;
  }
  return Accepting< RestInterfaces ... >::HasInterface( interfacename );
}

template< typename FirstInterface, typename ... RestInterfaces >
ComponentBase::interfaceStatus
Accepting< FirstInterface, RestInterfaces ... >::CanAcceptConnectionFrom(ComponentBase* other, const ComponentBase::InterfaceCriteriaType interfaceCriteria)
{

  ComponentBase::interfaceStatus restInterfacesStatus = Accepting< RestInterfaces ... >::CanAcceptConnectionFrom(other, interfaceCriteria);
  // if multiple interfaces were a succes we do not have to check any further interfaces.
  if (restInterfacesStatus == ComponentBase::interfaceStatus::multiple)
  {
    return ComponentBase::interfaceStatus::multiple;
  }
  // if a previous interface was a success, we can have either succes or multiple (successes)
  else if (restInterfacesStatus == ComponentBase::interfaceStatus::success)
  {
    unsigned int interfaceMeetsCriteria = Count<FirstInterface>::MeetsCriteria(interfaceCriteria);
    if (interfaceMeetsCriteria == 0) // ComponentBase::interfaceStatus::noacceptor;
    {
      return ComponentBase::interfaceStatus::success;
    }
    else
    {
      InterfaceAcceptor< FirstInterface > * acceptIF = (this);
      if (acceptIF->CanAcceptConnectionFrom(other))
      {
        return ComponentBase::interfaceStatus::multiple;
      }
      else // ComponentBase::interfaceStatus::noprovider
      {
        return ComponentBase::interfaceStatus::success;
      }
    }
  }
  // if a previous interface was noprovider, we can have either succes or noprovider (we know that there was at least 1 acceptor)
  else if (restInterfacesStatus == ComponentBase::interfaceStatus::noprovider)
  {
    unsigned int interfaceMeetsCriteria = Count<FirstInterface>::MeetsCriteria(interfaceCriteria);
    if (interfaceMeetsCriteria == 0) // ComponentBase::interfaceStatus::noacceptor;
    {
      return ComponentBase::interfaceStatus::noprovider;
    }
    else
    {
      InterfaceAcceptor< FirstInterface > * acceptIF = (this);
      if (acceptIF->CanAcceptConnectionFrom(other))
      {
        return ComponentBase::interfaceStatus::success;
      }
      else // ComponentBase::interfaceStatus::noprovider
      {
        return ComponentBase::interfaceStatus::noprovider;
      }
    }
  }
  // if a previous interface was noacceptor, we can have noaccepter, succes or noprovider
  else if (restInterfacesStatus == ComponentBase::interfaceStatus::noaccepter)
  {
    unsigned int interfaceMeetsCriteria = Count<FirstInterface>::MeetsCriteria(interfaceCriteria);
    if (interfaceMeetsCriteria == 0) // ComponentBase::interfaceStatus::noacceptor;
    {
      return ComponentBase::interfaceStatus::noaccepter;
    }
    else
    {
      InterfaceAcceptor< FirstInterface > * acceptIF = (this);
      if (acceptIF->CanAcceptConnectionFrom(other))
      {
        return ComponentBase::interfaceStatus::success;
      }
      else // ComponentBase::interfaceStatus::noprovider
      {
        return ComponentBase::interfaceStatus::noprovider;
      }
    }
  }
}


  



template< typename FirstInterface, typename ... RestInterfaces >
bool
Providing< FirstInterface, RestInterfaces ... >::HasInterface( const char * interfacename )
{
  //TODO: check on interface template arguments as well
  auto interfaceProperies = Properties< FirstInterface >::Get();

  if (interfaceProperies["Name"] == std::string(interfacename))
  {
    return true;
  }
  return Providing< RestInterfaces ... >::HasInterface( interfacename );
}



template< typename FirstInterface, typename ... RestInterfaces >
unsigned int
Accepting< FirstInterface, RestInterfaces ... >::CountMeetsCriteria(const ComponentBase::InterfaceCriteriaType interfaceCriteria)
{
  return Count<FirstInterface, RestInterfaces ... >::MeetsCriteria(interfaceCriteria);
}

template< typename FirstInterface, typename ... RestInterfaces >
unsigned int
Providing< FirstInterface, RestInterfaces ... >::CountMeetsCriteria(const ComponentBase::InterfaceCriteriaType interfaceCriteria)
{
  return Count<FirstInterface, RestInterfaces ... >::MeetsCriteria(interfaceCriteria);
}


template <typename FirstInterface, typename ... RestInterfaces>
unsigned int Count<FirstInterface, RestInterfaces ...>::MeetsCriteria(const ComponentBase::InterfaceCriteriaType interfaceCriteria)
{
  auto interfaceProperies = Properties< FirstInterface >::Get();
  for (const auto keyAndValue : interfaceCriteria)
  {
    auto && key = keyAndValue.first;
    auto && value = keyAndValue.second;
    if (interfaceProperies.count(key) != 1 || interfaceProperies[key].compare(value)!=0 )
    {
      // as soon as any of the criteria fails we break the loop and test the RestInterfaces
      return Count< RestInterfaces ... >::MeetsCriteria(interfaceCriteria);
    }
  }
  // if all criteria are met for this Interface we add 1 to the count and continue with the RestInterfaces
  return 1 + Count< RestInterfaces ... >::MeetsCriteria(interfaceCriteria);
};

} // end namespace selx

#endif // #define selxSuperElastixComponent_hxx
