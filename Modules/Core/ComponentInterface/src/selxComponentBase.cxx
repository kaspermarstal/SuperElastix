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

#include "selxComponentBase.h"

namespace selx
{
//TODO deprecate this method: let derived class handle this (using selxCheckTemplateProperties.h)
bool
ComponentBase::MeetsCriterionBase( const CriterionType & criterion )
{
  if( criterion.first == "NameOfClass" )
  {
    if( criterion.second.size() != 1 )
    {
      itkExceptionMacro( "The criterion NameOfClass may have only 1 value" );
    }
    return ( criterion.second[ 0 ] == this->GetNameOfClass() );
  }

  // else pass criterion to derived Component
  return this->MeetsCriterion( criterion );
}
} // end namespace selx
