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

#include "Metric3rdPartyWrapper.h"

namespace selx
{
void Metric3rdPartyWrapper::SetMetricValueComponent(MetricValueInterface* metricValueComponent)
{
  this->metricval = metricValueComponent;
}

int Metric3rdPartyWrapper::GetValue()
{
  return this->metricval->GetValue();
}

void Metric3rdPartyWrapper::SetMetricDerivativeComponent(MetricDerivativeInterface* metricDerivativeComponent)
{
  this->metricderiv = metricDerivativeComponent;
}

int Metric3rdPartyWrapper::GetDerivative()
{
  return this->metricderiv->GetDerivative();
}
} // end namespace selx