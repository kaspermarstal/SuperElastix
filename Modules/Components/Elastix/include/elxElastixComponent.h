#ifndef ElastixComponent_h
#define ElastixComponent_h

#include "elxMacro.h"

#include "itkProcessObject.h"
#include "itkImageSource.h"
#include "itkImage.h"
#include "itkVectorContainer.h"

#include "boost/any.hpp"

#include "elastixlib.h"

namespace selx {

template< typename TOutputImage >
class ElastixComponent : public itk::ImageSource< TOutputImage >
{
public:

  elxNewMacro( ElastixComponent, itk::ImageSource );

  ElastixComponent( void );

  typedef itk::ProcessObject::DataObjectIdentifierType    DataObjectIdentifierType;

  typedef elastix::ELASTIX ElastixType;

  // TODO: Parameter map should be a DataObject

  typedef std::vector< std::string >                    ParameterValuesType;
  typedef std::map< std::string, ParameterValuesType >  ParameterMapType;
  typedef std::vector< ParameterMapType >               ParameterMapListType;


  void SetParameterMapList( ParameterMapListType parameterMapList ) {
    this->m_ParameterMapList = parameterMapList;
  };

  ParameterMapListType GetParameterMapList( void ) {
    return this->m_ParameterMapList;
  };

  // Make SetInput public
  using itk::ProcessObject::SetInput;

protected:

  void GenerateData( void );

private:

  std::string           m_OutputFolder;
  bool                  m_LogToConsole;
  ParameterMapListType  m_ParameterMapList;

};

} // namespace selx

#ifndef ITK_MANUAL_INSTANTIATION
#include "elxElastixComponent.hxx"
#endif

#endif // ElastixComponent_h