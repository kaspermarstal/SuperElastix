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

#ifndef Interfaces_h
#define Interfaces_h

#include "ComponentBase.h"
#include <typeinfo>
#include <string>

#include "itkProcessObject.h"
#include "itkImageToImageFilter.h"
#include "itkImageToImageMetricv4.h"
namespace selx
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

  class TransformedImageInterface {
  public:
    virtual int GetTransformedImage() = 0;
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

  class itkProcessObjectInterface {
    public:
      virtual itk::ProcessObject::Pointer GetItkProcessObject() = 0;
  };

  class itkImageToImageFilterInterface {
    // An interface that exposes the entire filter
  public:
    virtual itk::ImageToImageFilter<itk::Image<double, 3>, itk::Image<double, 3>>::Pointer GetItkImageToImageFilter() = 0;
  };

  template<int Dimensionality, class TPixel>
  class itkImageSourceInterface {
    // An interface that exposes that its internal filter is derived from itkImageSource
  public:
    virtual typename itk::ImageSource<itk::Image<TPixel, Dimensionality>>::Pointer GetItkImageSource() = 0;
  };

  template<int Dimensionality, class TPixel>
  class itkImageSourceMovingInterface {
    // An interface that exposes that its internal filter which is derived from itkImageSource
  public:
    virtual typename itk::ImageSource<itk::Image<TPixel, Dimensionality>>::Pointer GetItkImageSourceMoving() = 0;
  };

  template<int Dimensionality, class TPixel>
  class itkImageSourceFixedInterface {
    // An interface that exposes that its internal filter which is derived from itkImageSource
  public:
    virtual typename itk::ImageSource<itk::Image<TPixel, Dimensionality>>::Pointer GetItkImageSourceFixed() = 0;
  };

  template<int Dimensionality, class TPixel>
  class GetItkImageInterface {
    // An interface that passes the pointer of an output image
    // This interface can be used if itk classes are not implement as true filters, i.e. if ((itk::ImageSource) filter)->GetOutput() does not work.
  public:
    virtual typename itk::Image<TPixel, Dimensionality>::Pointer GetItkImage() = 0;
  };

  template<int Dimensionality, class TPixel>
  class DisplacementFieldItkImageSourceInterface {
    // An interface that exposes that its internal filter is derived from itkImageSource
  public:
    virtual typename itk::ImageSource<itk::Image<itk::Vector< TPixel, Dimensionality >, Dimensionality>>::Pointer GetDisplacementFieldItkImageSource() = 0;
  };

  class SourceInterface {
    // A special interface: the Overlord checks components for this type of interface.
    // By this interface only Source Components can to talk to the Overlord.
    // How specific Source Components connect to the graph is up to them, i.e. they might adapt the passed Object to other types.
  public:
    virtual bool ConnectToOverlordSource(itk::Object::Pointer) = 0;
  };
  class SinkInterface {
    // A special interface: the Overlord checks components for this type of interface.
    // By this interface only Sink Components can to talk to the Overlord
    // How specific Sink Components connect to the graph is up to them, i.e. they might adapt the passed Object to other types.
  public:
    virtual bool ConnectToOverlordSink(itk::Object::Pointer) = 0;
  };

  class RunRegistrationInterface {
    // A special interface: the Overlord checks components for this type of interface.
    // This interface is for to control the execution of the network
  public:
    virtual void RunRegistration() = 0;
  };
  
  class AfterRegistrationInterface {
    // A special interface: the Overlord checks components for this type of interface.
    // This interface is for to control the execution of the network
  public:
    virtual void AfterRegistration() = 0;
  };

  class RunResolutionInterface {
    // A special interface: the Overlord checks components for this type of interface.
    // This interface is for to control the execution of the network
  public:
    virtual bool RunResolution() = 0;
  };

  template<int Dimensionality, class TPixel>
  class itkMetricv4Interface {
  public:
    typedef typename itk::Image<TPixel, Dimensionality> FixedImageType;
    typedef typename itk::Image<TPixel, Dimensionality> MovingImageType;
    typedef typename itk::ImageToImageMetricv4<FixedImageType, MovingImageType> ImageToImageMetricv4Type;

    virtual typename ImageToImageMetricv4Type::Pointer GetItkMetricv4() = 0;
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
    ComponentBase::interfaceStatus ConnectFromImpl(const char *, ComponentBase*) { return ComponentBase::interfaceStatus::noaccepter; }; //no interface called interfacename ;
    int ConnectFromImpl(ComponentBase*) { return 0; }; //Empty RestInterfaces does 0 successful connects ;
protected:
  bool HasInterface(const char *) { return false; };
};

template<typename FirstInterface, typename ... RestInterfaces>
class Accepting<FirstInterface, RestInterfaces... > : public InterfaceAcceptor<FirstInterface>, public Accepting< RestInterfaces ... >
{
public:
  ComponentBase::interfaceStatus ConnectFromImpl(const char *, ComponentBase*);
  int ConnectFromImpl(ComponentBase*);
protected:
  bool HasInterface(const char *);

};

template<typename ... RestInterfaces>
class Providing
{
protected:
  bool HasInterface(const char *) { return false; };
};

template<typename FirstInterface, typename ... RestInterfaces>
class Providing<FirstInterface, RestInterfaces... > : public FirstInterface, public Providing < RestInterfaces ... >
{
protected:
  bool HasInterface(const char *);

};

//template<typename... Interfaces>
//class Providing : public Interfaces...
//{
//};

template<typename AcceptingInterfaces, typename ProvidingInterfaces>
class Implements : public AcceptingInterfaces, public ProvidingInterfaces, public ComponentBase
{
  public:
    virtual interfaceStatus AcceptConnectionFrom(const char *, ComponentBase*);
    virtual int AcceptConnectionFrom(ComponentBase*);
protected: 
  virtual bool HasAcceptingInterface(const char *);
  virtual bool HasProvidingInterface(const char *);
};




} // end namespace selx

#ifndef ITK_MANUAL_INSTANTIATION
#include "Interfaces.hxx"
#endif

#endif // #define Interfaces_h