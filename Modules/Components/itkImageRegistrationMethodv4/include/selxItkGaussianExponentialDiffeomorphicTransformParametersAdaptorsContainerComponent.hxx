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

#include "selxItkGaussianExponentialDiffeomorphicTransformParametersAdaptorsContainerComponent.h"

namespace selx
{
template< int Dimensionality, class TransformInternalComputationValueType >
ItkGaussianExponentialDiffeomorphicTransformParametersAdaptorsContainerComponent< Dimensionality,
TransformInternalComputationValueType >::ItkGaussianExponentialDiffeomorphicTransformParametersAdaptorsContainerComponent( const std::string & name )
  : Superclass( name )
{
}


template< int Dimensionality, class TransformInternalComputationValueType >
ItkGaussianExponentialDiffeomorphicTransformParametersAdaptorsContainerComponent< Dimensionality,
TransformInternalComputationValueType >::~ItkGaussianExponentialDiffeomorphicTransformParametersAdaptorsContainerComponent()
{
}


template< int Dimensionality, class TransformInternalComputationValueType >
int
ItkGaussianExponentialDiffeomorphicTransformParametersAdaptorsContainerComponent< Dimensionality, TransformInternalComputationValueType >
::Set( typename itkImageDomainFixedInterface< Dimensionality >::Pointer component )
{
  auto fixedImageDomain = component->GetItkImageDomainFixed();

  for( unsigned int level = 0; level < m_shrinkFactorsPerLevel.Size(); level++ )
  {
    // We use the shrink image filter to calculate the fixed parameters of the virtual
    // domain at each level.  To speed up calculation and avoid unnecessary memory
    // usage, we could calculate these fixed parameters directly.

    typedef itk::Image< TransformInternalComputationValueType, Dimensionality > FixedImageType;

    typename FixedImageType::Pointer fixedImage = FixedImageType::New();
    fixedImage->CopyInformation( fixedImageDomain );
    //fixedImage->Allocate();

    typedef itk::ShrinkImageFilter< FixedImageType, FixedImageType > ShrinkFilterType;
    typename ShrinkFilterType::Pointer shrinkFilter = ShrinkFilterType::New();
    shrinkFilter->SetShrinkFactors( m_shrinkFactorsPerLevel[ level ] );
    shrinkFilter->SetInput( fixedImage );
    shrinkFilter->UpdateOutputInformation();

    typename TransformParametersAdaptorType::Pointer transformAdaptor = TransformParametersAdaptorType::New();
    transformAdaptor->SetRequiredSpacing( shrinkFilter->GetOutput()->GetSpacing() );
    transformAdaptor->SetRequiredSize( shrinkFilter->GetOutput()->GetLargestPossibleRegion().GetSize() );
    transformAdaptor->SetRequiredDirection( shrinkFilter->GetOutput()->GetDirection() );
    transformAdaptor->SetRequiredOrigin( shrinkFilter->GetOutput()->GetOrigin() );

    m_adaptors.push_back( transformAdaptor.GetPointer() ); // Implicit cast back to TransformParametersAdaptorBase<itk::Transform<...>>
  }

  return 0;
}


template< int Dimensionality, class TransformInternalComputationValueType >
typename ItkGaussianExponentialDiffeomorphicTransformParametersAdaptorsContainerComponent< Dimensionality,
TransformInternalComputationValueType >::TransformParametersAdaptorsContainerType
ItkGaussianExponentialDiffeomorphicTransformParametersAdaptorsContainerComponent< Dimensionality, TransformInternalComputationValueType >
::GetItkTransformParametersAdaptorsContainer()
{
  return this->m_adaptors;
}


template< int Dimensionality, class TransformInternalComputationValueType >
bool
ItkGaussianExponentialDiffeomorphicTransformParametersAdaptorsContainerComponent< Dimensionality, TransformInternalComputationValueType >
::MeetsCriterion( const ComponentBase::CriterionType & criterion )
{
  bool hasUndefinedCriteria( false );
  bool meetsCriteria( false );
  auto status = CheckTemplateProperties( this->TemplateProperties(), criterion );
  if( status == CriterionStatus::Satisfied )
  {
    return true;
  }
  else if( status == CriterionStatus::Failed )
  {
    return false;
  } // else: CriterionStatus::Unknown
  else if( criterion.first == "ShrinkFactorsPerLevel" ) //Supports this?
  {
    meetsCriteria = true;

    const int NumberOfResolutions = criterion.second.size(); // maybe check with criterion "NumberOfResolutions"?
    m_shrinkFactorsPerLevel.SetSize( NumberOfResolutions );

    unsigned int resolutionIndex = 0;
    for( auto const & criterionValue : criterion.second ) // auto&& preferred?
    {
      m_shrinkFactorsPerLevel[ resolutionIndex ] = std::stoi( criterionValue );
      ++resolutionIndex;
    }
  }

  return meetsCriteria;
}
} //end namespace selx
