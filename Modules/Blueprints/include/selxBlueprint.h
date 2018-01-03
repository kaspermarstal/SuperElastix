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

#ifndef selxBlueprint_h
#define selxBlueprint_h

#include "itkDataObject.h"
#include "itkObjectFactory.h"
#include "selxLogger.h"

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace selx
{

class BlueprintImpl;

class Blueprint : public itk::DataObject
{
public:

  /** Standard ITK typedefs. */
  using Self = Blueprint;
  using Superclass = itk::ProcessObject;
  using Pointer = itk::SmartPointer< Self >;
  using ConstPointer = itk::SmartPointer< const Self >;

  /** Method for creation through the object factory. */
  itkNewMacro( Self );

  /** Run-time type information (and related methods). */
  itkTypeMacro( Self, itk::DataObject );

  using ParameterKeyType = std::string;
  using ParameterValueType = std::vector< std::string >;
  using ParameterMapType = std::map< ParameterKeyType, ParameterValueType >;
  using ComponentNameType = std::string;
  using ComponentNamesType = std::vector< ComponentNameType >;

  /* m_Implementation is initialized in the default constructor */
  Blueprint();

  /** The actual blueprint is a pimpled member variable */
  typedef std::unique_ptr< BlueprintImpl > BlueprintImplPointer;

  const BlueprintImpl & GetBlueprintImpl() const; 

  // Adds component to blueprint or replaces it if already existing. Returns if connection was succesfully established.
  bool SetComponent( const ComponentNameType&, const ParameterMapType& parameterMap );

  // Adds component to blueprint or replaces it if already existing.
  ParameterMapType GetComponent( const ComponentNameType& componentName ) const;

  // Deletes component with given name from blueprint.
  bool DeleteComponent( const ComponentNameType& componentName );

  // Returns if component with given name exists.
  bool ComponentExists( const ComponentNameType& componentName ) const;

  // Returns a vector of the all Component names in the graph.
  ComponentNamesType GetComponentNames() const;

  // Adds a connection between upstream and downstream components with given parameters.
  // If connection already exists, existing parameters will be replaced with given parameters.
  // Returns if connection was succesfully added.
  bool SetConnection( const ComponentNameType& upstream, const ComponentNameType& downstream, const ParameterMapType& parameterMap );

  // Returns parameters for connection between upstream and downstream.
  ParameterMapType GetConnection( const ComponentNameType& upstream, const ComponentNameType& downstream ) const;

  // Delete connection between upstream and downstream.
  bool DeleteConnection( const ComponentNameType& upstream, const ComponentNameType& downstream );

  // Returns if a connections exists between upstream and downstream.
  bool ConnectionExists( const ComponentNameType& upstream, const ComponentNameType& downstream ) const;

  // "functional" composition of blueprints is done by adding settings of other to this blueprint. Redefining/overwriting properties is not allowed and returns false.
  bool ComposeWith( ConstPointer other );

  // Returns a vector of the Component names at the incoming direction
  ComponentNamesType GetInputNames( const ComponentNameType& name ) const;

  // Returns a vector of the Component names at the outgoing direction
  ComponentNamesType GetOutputNames( const ComponentNameType& name ) const;

  // Write graphviz dot file
  void Write( const std::string& filename );

  //! ..??..
  void MergeFromFile(const std::string& filename);

  //! Set a custom logger.
  void SetLogger( Logger::Pointer logger );

private:

  BlueprintImplPointer m_Implementation;
  Logger::Pointer m_Logger;
};
}

#endif // #define selxBlueprint_h
