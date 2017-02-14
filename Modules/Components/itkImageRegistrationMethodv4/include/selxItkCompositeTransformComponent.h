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

#ifndef selxItkCompositeTransformComponent_h
#define selxItkCompositeTransformComponent_h

#include "selxSuperElastixComponent.h"

#include "selxItkRegistrationMethodv4Interfaces.h"
#include "selxSinksAndSourcesInterfaces.h"

#include "itkCompositeTransform.h"

namespace selx
{
template< class InternalComputationValueType, int Dimensionality >
class ItkCompositeTransformComponent :
  public SuperElastixComponent<
  Accepting< MultiStageTransformInterface< InternalComputationValueType, Dimensionality >, ReconnectTransformInterface >,
  Providing< itkTransformInterface< InternalComputationValueType, Dimensionality >,
  RegistrationControllerStartInterface >
  >
{
public:

  /** Standard ITK typedefs. */
  typedef ItkCompositeTransformComponent< InternalComputationValueType, Dimensionality > Self;
  typedef ComponentBase                                                                  Superclass;
  typedef std::shared_ptr< Self >                                                        Pointer;
  typedef std::shared_ptr< const Self >                                                  ConstPointer;

  ItkCompositeTransformComponent( const std::string & name );
  virtual ~ItkCompositeTransformComponent();

  /**  Type of the optimizer. */
  using TransformType = typename MultiStageTransformInterface< InternalComputationValueType, Dimensionality >::TransformBaseType;

  typedef typename itk::CompositeTransform< InternalComputationValueType, Dimensionality > CompositeTransformType;

  virtual int Set( typename MultiStageTransformInterface< InternalComputationValueType, Dimensionality >::Pointer ) override;

  virtual int Set( ReconnectTransformInterface::Pointer ) override;

  virtual void RegistrationControllerStart() override;

  virtual typename TransformType::Pointer GetItkTransform() override;

  virtual bool MeetsCriterion( const ComponentBase::CriterionType & criterion ) override;

  //static const char * GetName() { return "ItkCompositeTransform"; } ;
  static const char * GetDescription() { return "ItkCompositeTransform Component"; }

private:

  typename CompositeTransformType::Pointer m_CompositeTransform;
  typename std::vector< typename MultiStageTransformInterface< InternalComputationValueType, Dimensionality >::Pointer > m_registrationStages;

  std::set< ReconnectTransformInterface::Pointer > m_ReconnectTransformInterfaces;
  std::vector< std::string >                       m_ExecutionOrder;

protected:

  // return the class name and the template arguments to uniquely identify this component.
  static inline const std::map< std::string, std::string > TemplateProperties()
  {
    return { { keys::NameOfClass, "ItkCompositeTransformComponent" }, { keys::InternalComputationValueType, PodString< InternalComputationValueType >::Get() }, { keys::Dimensionality, std::to_string( Dimensionality ) } };
  }
};
} //end namespace selx
#ifndef ITK_MANUAL_INSTANTIATION
#include "selxItkCompositeTransformComponent.hxx"
#endif
#endif // #define selxItkCompositeTransformComponent_h
