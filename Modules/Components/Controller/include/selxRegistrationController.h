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

#ifndef selxRegistrationController_h
#define selxRegistrationController_h

#include "ComponentBase.h"
#include "Interfaces.h"
#include <string.h>
#include "selxMacro.h"

namespace selx
{
  template<bool dummy = true>
  class RegistrationControllerComponent :
    public Implements <
    Accepting< RunRegistrationInterface, ReconnectTransformInterface, AfterRegistrationInterface >,
    Providing < RegistrationControllerStartInterface >
    >
  {
  public:
    selxNewMacro(RegistrationControllerComponent, ComponentBase);

    //itkStaticConstMacro(Dimensionality, unsigned int, Dimensionality);

    RegistrationControllerComponent();
    virtual ~RegistrationControllerComponent();

    
	// Accepting Interfaces:
    virtual int Set(RunRegistrationInterface*) override;
	  virtual int Set(ReconnectTransformInterface*) override;
    virtual int Set(AfterRegistrationInterface*) override;

	// Providing Interfaces:
    virtual void RegistrationControllerStart(void) override;

    virtual bool MeetsCriterion(const ComponentBase::CriterionType &criterion) override;
    static const char * GetDescription() { return "RegistrationController Component"; };
  private:
	  RunRegistrationInterface* m_RunRegistrationInterface;
	  ReconnectTransformInterface* m_ReconnectTransformInterface;
	  AfterRegistrationInterface* m_AfterRegistrationInterface;

    protected:
  };

} //end namespace selx
#ifndef ITK_MANUAL_INSTANTIATION
#include "selxRegistrationController.hxx"
#endif
#endif // #define selxRegistrationController_h