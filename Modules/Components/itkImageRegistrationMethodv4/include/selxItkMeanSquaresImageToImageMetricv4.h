#ifndef selxItkMeanSquaresImageToImageMetricv4Component_h
#define selxItkMeanSquaresImageToImageMetricv4Component_h

#include "ComponentBase.h"
#include "Interfaces.h"
#include "itkMeanSquaresImageToImageMetricv4.h"
#include <string.h>
#include "elxMacro.h"
namespace selx
{
  template <int Dimensionality, class TPixel>
  class ItkMeanSquaresImageToImageMetricv4Component : 
    public Implements<
    Accepting< >,
    Providing< itkMetricv4Interface<Dimensionality, TPixel>>
    >
  {
  public:
    elxNewMacro(ItkMeanSquaresImageToImageMetricv4Component, ComponentBase);

    //itkStaticConstMacro(Dimensionality, unsigned int, Dimensionality);

    ItkMeanSquaresImageToImageMetricv4Component();
    virtual ~ItkMeanSquaresImageToImageMetricv4Component();

    typedef TPixel PixelType;

    // fixed and moving image types are all the same, these aliases can be used to be explicit. 
    typedef itk::Image<PixelType, Dimensionality> FixedImageType; 
    typedef itk::Image<PixelType, Dimensionality> MovingImageType;

    typedef typename itk::ImageToImageMetricv4<FixedImageType, MovingImageType> ImageToImageMetricv4Type;
    //typedef typename ItkMetricv4Interface<Dimensionality, TPixel>::ImageToImageMetricv4Type ImageToImageMetricv4Type;
      //typedef ItkMetricv4Interface<Dimensionality, TPixel>::ImageToImageMetricv4Type ItkMetricv4Pointer
    typedef typename ImageToImageMetricv4Type::Pointer ItkMetricv4Pointer;
    
    typedef typename itk::MeanSquaresImageToImageMetricv4<FixedImageType, MovingImageType> TheItkFilterType;
    
    virtual ItkMetricv4Pointer GetItkMetricv4() override;

    virtual bool MeetsCriterion(const ComponentBase::CriterionType &criterion) override;    
    //static const char * GetName() { return "ItkMeanSquaresImageToImageMetricv4"; } ;
    static const char * GetDescription() { return "ItkMeanSquaresImageToImageMetricv4 Component"; };
  private:
    typename TheItkFilterType::Pointer m_theItkFilter;
  protected:
    /* The following struct returns the string name of computation type */
    /* default implementation */

    static inline const std::string GetTypeNameString()
    {
      itkGenericExceptionMacro(<< "Unknown ScalarType" << typeid(TPixel).name());
      // TODO: provide the user instructions how to enable the compilation of the component with the required template types (if desired)
      // We might define an exception object that can communicate various error messages: for simple user, for developer user, etc
    }

    static inline const std::string GetPixelTypeNameString()
    {
      itkGenericExceptionMacro(<< "Unknown PixelType" << typeid(TPixel).name());
      // TODO: provide the user instructions how to enable the compilation of the component with the required template types (if desired)
      // We might define an exception object that can communicate various error messages: for simple user, for developer user, etc
    }

  };

  // unfortunately partial specialization of member functions is not allowed, without partially specializing the entire class.

  /*
  template <int Dimensionality>
  class ItkMeanSquaresImageToImageMetricv4Component < Dimensionality, double >
  {
    static inline const std::string GetPixelTypeNameString();
  };

  template <int Dimensionality>
  inline const std::string
    ItkMeanSquaresImageToImageMetricv4Component<Dimensionality, double>
    ::GetPixelTypeNameString()
  {
    return std::string("double");
  }
  */

  template <>
  inline const std::string
    ItkMeanSquaresImageToImageMetricv4Component<2, float>
    ::GetPixelTypeNameString()
  {
    return std::string("float");
  }


  template <>
  inline const std::string
    ItkMeanSquaresImageToImageMetricv4Component<2, double>
    ::GetPixelTypeNameString()
  {
    return std::string("double");
  }

  template <>
  inline const std::string
    ItkMeanSquaresImageToImageMetricv4Component<3, float>
    ::GetPixelTypeNameString()
  {
    return std::string("float");
  }

  template <>
  inline const std::string
    ItkMeanSquaresImageToImageMetricv4Component<3, double>
    ::GetPixelTypeNameString()
  {
    return std::string("double");
  }
  template <>
  inline const std::string
    ItkMeanSquaresImageToImageMetricv4Component<2, float>
    ::GetTypeNameString()
  {
    return std::string("2_float");
  }

  template <>
  inline const std::string
    ItkMeanSquaresImageToImageMetricv4Component<2, double>
    ::GetTypeNameString()
  {
    return std::string("2_double");
  }

  template <>
  inline const std::string
    ItkMeanSquaresImageToImageMetricv4Component<3,float>
    ::GetTypeNameString()
  {
    return std::string("3_float");
  }
  
  template <>
  inline const std::string
    ItkMeanSquaresImageToImageMetricv4Component<3,double>
    ::GetTypeNameString()
  {
    return std::string("3_double");
  }
} //end namespace selx
#ifndef ITK_MANUAL_INSTANTIATION
#include "selxItkMeanSquaresImageToImageMetricv4.hxx"
#endif
#endif // #define GDOptimizer3rdPartyComponent_h