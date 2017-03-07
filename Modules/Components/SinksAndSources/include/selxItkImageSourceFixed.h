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

#ifndef selxItkImageSourceFixed_h
#define selxItkImageSourceFixed_h

#include "selxSuperElastixComponent.h"
#include "selxSinksAndSourcesInterfaces.h"
#include "selxItkObjectInterfaces.h"

#include <string.h>
#include "itkImageFileReader.h"
#include "selxAnyFileReader.h"
#include "selxFileReaderDecorator.h"
namespace selx
{
template< int Dimensionality, class TPixel >
class ItkImageSourceFixedComponent :
  public SuperElastixComponent<
    Accepting< >,
    Providing< SourceInterface,
      itkImageFixedInterface< Dimensionality, TPixel >,
      itkImageDomainFixedInterface< Dimensionality >>
  >
{
public:

  /** Standard ITK typedefs. */
  typedef ItkImageSourceFixedComponent<
    Dimensionality, TPixel
  >                                     Self;
  typedef SuperElastixComponent<
    Accepting< >,
    Providing< SourceInterface,
      itkImageFixedInterface< Dimensionality, TPixel >,
      itkImageDomainFixedInterface< Dimensionality >>
  >                                     Superclass;
  typedef std::shared_ptr< Self >       Pointer;
  typedef std::shared_ptr< const Self > ConstPointer;

  ItkImageSourceFixedComponent( const std::string & name );
  virtual ~ItkImageSourceFixedComponent();

  typedef typename itkImageFixedInterface< Dimensionality, TPixel >::ItkImageType     ItkImageType;
  typedef typename itkImageDomainFixedInterface< Dimensionality >::ItkImageDomainType ItkImageDomainType;

  typedef typename itk::ImageFileReader< ItkImageType > ItkImageReaderType;
  typedef FileReaderDecorator< ItkImageReaderType >     DecoratedReaderType;

  // providing interfaces
  virtual typename ItkImageType::Pointer GetItkImageFixed() override;

  virtual void SetMiniPipelineInput( itk::DataObject::Pointer ) override;
  virtual AnyFileReader::Pointer GetInputFileReader( void ) override;

  virtual typename ItkImageDomainType::Pointer GetItkImageDomainFixed() override;

  virtual bool MeetsCriterion( const ComponentBase::CriterionType & criterion ) override;

  static const char * GetDescription() { return "ItkImageSourceFixed Component"; }

private:

  typename ItkImageType::Pointer m_Image;

protected:

  // return the class name and the template arguments to uniquely identify this component.
  static inline const std::map< std::string, std::string > TemplateProperties()
  {
    return { { keys::NameOfClass, "ItkImageSourceFixedComponent" }, { keys::PixelType, PodString< TPixel >::Get() }, { keys::Dimensionality, std::to_string( Dimensionality ) } };
  }
};
} //end namespace selx
#ifndef ITK_MANUAL_INSTANTIATION
#include "selxItkImageSourceFixed.hxx"
#endif
#endif // #define selxItkImageSourceFixed_h
