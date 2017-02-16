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

#ifndef ConfigurationReader_cxx
#define ConfigurationReader_cxx

#include "selxConfigurationReader.h"
#include <ostream>

namespace selx
{
ConfigurationReader::ParameterValueType
ConfigurationReader::VectorizeValues( const ComponentOrConnectionTreeType & componentOrConnectionTree )
{
  std::string        propertySingleValue = componentOrConnectionTree.data();
  ParameterValueType propertyMultiValue;
  for( auto const & value : componentOrConnectionTree )
  {
    propertyMultiValue.push_back( value.second.data() );
  }
  if( propertyMultiValue.size() > 0 )
  {
    if( propertySingleValue != "" )
    {
      throw std::invalid_argument( "XML tree should have either 1 unnamed element or multiple named properties" );
    }
  }
  else
  {
    propertyMultiValue.push_back( propertySingleValue );
  }
  return propertyMultiValue;
}


ConfigurationReader::BlueprintPointerType
ConfigurationReader::FromFile(const PathType & filename)
{
  auto propertyTree = ReadPropertyTree(filename);
  auto includesList = FindIncludes(propertyTree);
  if (includesList.size() == 0)
  {
    return FromPropertyTree(propertyTree);
  }
  else
  {
    BlueprintPointerType baseBlueprint = BlueprintPointerType(new Blueprint());
    for (auto const & includePath : includesList)
    {
      auto blueprint = FromFile(includePath);
      baseBlueprint->ComposeWith(blueprint);
    }
    return baseBlueprint;
  }
}

ConfigurationReader::PropertyTreeType
ConfigurationReader::ReadPropertyTree(const PathType & filename)
{
  // Create empty property tree object
  PropertyTreeType propertyTree;
  if (filename.extension() == ".xml")
  {
    read_xml(filename.string(), propertyTree, boost::property_tree::xml_parser::trim_whitespace);
  }
  else if (filename.extension() == ".json")
  {
    read_json(filename.string(), propertyTree);
  }
  else
  {
    throw std::invalid_argument("Configuration file requires extension .xml or .json");
  }

  return propertyTree;
}

ConfigurationReader::PathsType 
ConfigurationReader::FindIncludes(const PropertyTreeType & propertyTree)
{
  PathsType paths;
  bool FoundIncludes = false;
  BOOST_FOREACH(const PropertyTreeType::value_type & v, propertyTree.equal_range("Include"))
  {
    if (FoundIncludes)
    {
      std::runtime_error("Only 1 listing of Includes is allowed per Blueprint file");
    }


    FoundIncludes = true;
    for (auto const & pathLeaf : v.second)
    {
      //const std::string pathString(pathChars);
      //PathType path(pathString);
      paths.push_back(pathLeaf.second.data());
    }
  }
  return paths;
}


ConfigurationReader::BlueprintPointerType
ConfigurationReader::FromPropertyTree( const PropertyTreeType & pt )
{
  BlueprintPointerType blueprint = std::unique_ptr< Blueprint >(new Blueprint());

  BOOST_FOREACH( const PropertyTreeType::value_type & v, pt.equal_range( "Component" ) )
  {
    std::string      componentName;
    ParameterMapType componentPropertyMap;
    for( auto const & elm : v.second )
    {
      const std::string & componentKey = elm.first;
      if( componentKey == "Name" )
      {
        componentName = elm.second.data();
        continue;
      }

      ParameterValueType propertyMultiValue = VectorizeValues( elm.second );
      std::string        propertyKey        = elm.first;
      componentPropertyMap[ propertyKey ] = propertyMultiValue;
    }

    blueprint->SetComponent( componentName, componentPropertyMap );
  }

  BOOST_FOREACH( const PropertyTreeType::value_type & v, pt.equal_range( "Connection" ) )
  {
    std::string connectionName = v.second.data();
    if( connectionName != "" )
    {
      std::cout << "warning connectionName " "" << connectionName << "" " is ignored" << std::endl;
    }
    std::string      outName;
    std::string      inName;
    ParameterMapType componentPropertyMap;

    for( auto const & elm : v.second )
    {
      const std::string & connectionKey = elm.first;

      if( connectionKey == "Out" )
      {
        outName = elm.second.data();
        continue;
      }
      else if( connectionKey == "In" )
      {
        inName = elm.second.data();
        continue;
      }
      else if( connectionKey == "Name" )
      {
        std::cout << "Warning: connection 'Name'-s are ignored." << std::endl;
        continue;
      }
      else
      {
        ParameterValueType propertyMultiValue = VectorizeValues( elm.second );
        std::string        propertyKey        = elm.first;
        componentPropertyMap[ propertyKey ] = propertyMultiValue;
      }
    }

    blueprint->SetConnection( outName, inName, componentPropertyMap );
  }
  return blueprint;
}
} // namespace selx

#endif // ConfigurationReader_cxx
