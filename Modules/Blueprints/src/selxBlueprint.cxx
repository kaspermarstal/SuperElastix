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

#include "selxBlueprint.h"
#include "selxBlueprintImpl.h"

namespace selx
{

Blueprint
::Blueprint()
{
  // Create default logger which redirects to std::cout
  this->m_Logger = Logger::New();
  //TODO: cannot have independent loggers redirecting to cout. 
  //this->m_Logger->AddStream("cout", std::cout);
  //TODO: this seems to affect other instantiated loggers too.
  //this->m_Logger->SetLogLevel(selx::LogLevel::INF);

  this->m_Implementation = std::make_unique<BlueprintImpl>( this->m_Logger->GetLoggerImpl() );
}


const BlueprintImpl &
Blueprint
::GetBlueprintImpl() const
{
  return *this->m_Implementation;
}


bool
Blueprint
::SetComponent( const ComponentNameType& name, const ParameterMapType& parameterMap )
{
  this->Modified();
  return this->m_Implementation->SetComponent( name, parameterMap );
}


Blueprint::ParameterMapType
Blueprint
::GetComponent( const ComponentNameType& componentName ) const
{
  return this->m_Implementation->GetComponent( componentName );
}


bool
Blueprint
::DeleteComponent( const ComponentNameType& componentName )
{
  this->Modified();
  return this->m_Implementation->DeleteComponent( componentName );
}


Blueprint::ComponentNamesType
Blueprint::GetComponentNames() const
{
  return this->m_Implementation->GetComponentNames();
}


bool
Blueprint
::SetConnection( const ComponentNameType& upstream, const ComponentNameType& downstream, const ParameterMapType& parameterMap )
{
  this->Modified();
  return this->m_Implementation->SetConnection( upstream, downstream, parameterMap );
}


Blueprint::ParameterMapType
Blueprint
::GetConnection( const ComponentNameType& upstream, const ComponentNameType& downstream ) const
{
  return this->m_Implementation->GetConnection( upstream, downstream );
}


bool
Blueprint
::DeleteConnection( const ComponentNameType& upstream, const ComponentNameType& downstream )
{
  this->Modified();
  return this->m_Implementation->DeleteConnection( upstream, downstream );
}


bool
Blueprint
::ComponentExists( const ComponentNameType& componentName ) const
{
  return this->m_Implementation->ComponentExists( componentName );
}


bool
Blueprint
::ConnectionExists( const ComponentNameType& upstream, const ComponentNameType& downstream ) const
{
  return this->m_Implementation->ConnectionExists( upstream, downstream );
}


bool
Blueprint
::ComposeWith( ConstPointer other)
{
  this->Modified();
  return this->m_Implementation->ComposeWith( other->GetBlueprintImpl() );
}


Blueprint::ComponentNamesType
Blueprint
::GetOutputNames( const ComponentNameType& name ) const
{
  return this->m_Implementation->GetOutputNames( name );
}


Blueprint::ComponentNamesType
Blueprint
::GetInputNames( const ComponentNameType& name ) const
{
  return this->m_Implementation->GetInputNames( name );
}


void
Blueprint
::Write( const std::string& filename )
{
  this->m_Implementation->Write( filename );
}

void
Blueprint
::MergeFromFile( const std::string& filename )
{
  this->m_Implementation->MergeFromFile( filename );
}

void
Blueprint
::SetLogger( Logger::Pointer logger )
{
  this->m_Logger = logger;
  this->m_Implementation->SetLoggerImpl( logger->GetLoggerImpl() );
}


} // namespace selx
