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

#ifndef itkTransformComponent1_h
#define itkTransformComponent1_h

#include "Interfaces.h"
#include "ComponentBase.h"

namespace selx
{
class TransformComponent1 : 
  public Implements <
  Accepting< >,
  Providing < TransformedImageInterface >
  >
{
public:
  /** Standard class typedefs. */
  typedef TransformComponent1                        Self;
  typedef ComponentBase Superclass;
  typedef itk::SmartPointer< Self >             Pointer;
  typedef itk::SmartPointer< const Self >       ConstPointer;

  /** New macro for creation of through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(TransformComponent1, ComponentBase);

  typedef Superclass::CriteriaType CriteriaType;
  typedef Superclass::CriterionType CriterionType;

  virtual int GetTransformedImage() override{ return 0; };
  virtual bool MeetsCriterion(const CriterionType &criterion) override;
  static const char * GetDescription(){ return "Example Transform Component 1"; };

protected:
  TransformComponent1();
  virtual ~TransformComponent1()
  {
  }

private:
  TransformComponent1(const Self &);      // purposely not implemented
  void operator=(const Self &); // purposely not implemented

  //virtual bool MeetsCriteria(const CriteriaType&);
  
};
} // end namespace selx

//#ifndef ITK_MANUAL_INSTANTIATION
//#include "itkTransformComponent1.hxx"
//#endif

#endif
