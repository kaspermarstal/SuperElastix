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

#ifndef selxRegistrationMethodv4Interfaces_h
#define selxRegistrationMethodv4Interfaces_h

#include <string>

#include "itkProcessObject.h"
#include "itkImageToImageFilter.h"
#include "itkImageToImageMetricv4.h"
#include "itkObjectToObjectOptimizerBase.h"
#include "itkTransformParametersAdaptorBase.h"
#include "itkGaussianExponentialDiffeomorphicTransformParametersAdaptor.h"
#include "itkGaussianExponentialDiffeomorphicTransform.h"

#include "itkCompositeTransform.h"

#include "itkImage.h"
#include "itkMesh.h"



namespace selx
{
// Define the providing interfaces abstractly
template< int Dimensionality, class TPixel >
class itkImageInterface
{
  // An interface that provides the pointer of an output image

public:

  typedef typename itk::Image< TPixel, Dimensionality > ItkImageType;
  virtual typename ItkImageType::Pointer GetItkImage() = 0;
};

template< int Dimensionality, class TPixel >
class itkImageFixedInterface
{
  // An interface that provides the smart pointer to an itk image

public:

  typedef typename itk::Image< TPixel, Dimensionality > ItkImageType;
  virtual typename ItkImageType::Pointer GetItkImageFixed() = 0;
};

template< int Dimensionality >
class itkImageDomainFixedInterface
{
  // An interface that provides the smart pointer to the base class of an itk image
  // that holds the origin/spacing/ etc domain information.

public:

  typedef typename itk::ImageBase< Dimensionality > ItkImageDomainType;
  virtual typename ItkImageDomainType::Pointer GetItkImageDomainFixed() = 0;
};

template< int Dimensionality, class TPixel >
class itkImageMovingInterface
{
  // An interface that provides the smart pointer to an itk image

public:

  typedef typename itk::Image< TPixel, Dimensionality > ItkImageType;
  virtual typename ItkImageType::Pointer GetItkImageMoving() = 0;
};

template< int Dimensionality, class TPixel >
class DisplacementFieldItkImageSourceInterface
{
  // An interface that passes the pointer of an output image

public:

  typedef typename itk::Image< itk::Vector< TPixel, Dimensionality >, Dimensionality > ItkImageType;
  virtual typename ItkImageType::Pointer GetDisplacementFieldItkImage() = 0;
};

template< int Dimensionality, class TPixel >
class itkMeshInterface
{
  // An interface that passes the pointer of an output mesh

public:

  virtual typename itk::Mesh< TPixel, Dimensionality >::Pointer GetItkMesh() = 0;
};

template< int Dimensionality, class TPixel, class InternalComputationValueType >
class itkMetricv4Interface
{
public:

  using FixedImageType   = itk::Image< TPixel, Dimensionality >;
  using MovingImageType  = FixedImageType;
  using VirtualImageType = FixedImageType;
  typedef typename itk::ImageToImageMetricv4< FixedImageType, MovingImageType, VirtualImageType,
    InternalComputationValueType > ImageToImageMetricv4Type;

  virtual typename ImageToImageMetricv4Type::Pointer GetItkMetricv4() = 0;
};

template< class TInternalComputationValueType >
class itkOptimizerv4Interface
{
public:

  /**  Type of the optimizer. */
  typedef TInternalComputationValueType                                            InternalComputationValueType;
  typedef itk::ObjectToObjectOptimizerBaseTemplate< InternalComputationValueType > OptimizerType;
  typedef typename OptimizerType::Pointer                                          Optimizerv4Pointer;
  virtual Optimizerv4Pointer GetItkOptimizerv4() = 0;
};

template< class TInternalComputationValueType, int Dimensionality >
class itkTransformInterface
{
public:

  typedef TInternalComputationValueType                                                            InternalComputationValueType;
  typedef typename itk::Transform< TInternalComputationValueType, Dimensionality, Dimensionality > TransformType;
  typedef typename TransformType::Pointer                                                          TransformPointer;

  virtual TransformPointer GetItkTransform() = 0;
};

template< class TransformInternalComputationValueType, int Dimensionality >
class itkTransformParametersAdaptorsContainerInterface
{
public:

  // TransformBaseType acts as a container of the types: TParametersValueType, NInputDimensions, NOutputDimensions
  using TransformBaseType                        = itk::Transform< TransformInternalComputationValueType, Dimensionality, Dimensionality >;
  using TransformParametersAdaptorBaseType       = itk::TransformParametersAdaptorBase< TransformBaseType >;
  using TransformParametersAdaptorsContainerType = std::vector< typename TransformParametersAdaptorBaseType::Pointer >;

  virtual TransformParametersAdaptorsContainerType GetItkTransformParametersAdaptorsContainer() = 0;
};

template< class TransformInternalComputationValueType, int Dimensionality >
class itkGaussianExponentialDiffeomorphicTransformParametersAdaptorsContainerInterface
{
public:

  using TransformBaseType                  = itk::Transform< TransformInternalComputationValueType, Dimensionality, Dimensionality >;
  using TransformParametersAdaptorBaseType = itk::TransformParametersAdaptorBase< TransformBaseType >;

  using GaussianExponentialDiffeomorphicTransformType
      = itk::GaussianExponentialDiffeomorphicTransform< TransformInternalComputationValueType, Dimensionality >;

  using TransformParametersAdaptorType
      = itk::GaussianExponentialDiffeomorphicTransformParametersAdaptor<
    GaussianExponentialDiffeomorphicTransformType >;
  using TransformParametersAdaptorPointer = typename TransformParametersAdaptorType::Pointer;
  //using TransformParametersAdaptorsContainerType = std::vector<TransformParametersAdaptorPointer>;
  using TransformParametersAdaptorsContainerType = std::vector< typename TransformParametersAdaptorBaseType::Pointer >;

  //using TransformParametersAdaptorsContainerType = typename TransformParametersAdaptorType::TransformParametersAdaptorsContainerType;

  virtual TransformParametersAdaptorsContainerType GetItkGaussianExponentialDiffeomorphicTransformParametersAdaptorsContainer() = 0;
};

template< class InternalComputationValueType, int Dimensionality >
class MultiStageTransformInterface
{
public:
  using TransformBaseType = itk::Transform< InternalComputationValueType, Dimensionality, Dimensionality >;
  using CompositeTransformType = itk::CompositeTransform<InternalComputationValueType, Dimensionality >;
  virtual void SetFixedInitialTransform(typename CompositeTransformType::Pointer) = 0;
  virtual void RunRegistration(void) = 0;
  virtual void SetMovingInitialTransform(typename CompositeTransformType::Pointer) = 0;
  virtual typename TransformBaseType::Pointer GetItkTransform() = 0;
  virtual const typename std::string GetComponentName() = 0;
};
} // end namespace selx

#endif // #define selxRegistrationMethodv4Interfaces_h
