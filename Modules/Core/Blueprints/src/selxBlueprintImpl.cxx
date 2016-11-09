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

#include "selxBlueprintImpl.h"

#include <stdexcept>

namespace selx
{

  // Declared outside of the class body, so it is a free function
  std::ostream &
    operator<<(std::ostream & out, const Blueprint::ParameterMapType & val)
  {
    for (auto const & mapPair : val)
    {
      out << mapPair.first << " : [ ";
      for (auto const & value : mapPair.second)
      {
        out << value << " ";
      }
      out << "]\\n";
    }
    return out;
  }


  template< class NameType, class ParameterMapType >
  class vertex_label_writer
  {
  public:

    vertex_label_writer(NameType _name, ParameterMapType _parameterMap) : name(_name), parameterMap(_parameterMap) {}
    template< class VertexOrEdge >
    void operator()(std::ostream & out, const VertexOrEdge & v) const
    {
      out << "[label=\"" << name[v] << "\n" << parameterMap[v] << "\"]";
    }


  private:

    NameType         name;
    ParameterMapType parameterMap;
  };

  template< class NameType, class ParameterMapType >
  inline vertex_label_writer< NameType, ParameterMapType >
    make_vertex_label_writer(NameType n, ParameterMapType p)
  {
    return vertex_label_writer< NameType, ParameterMapType >(n, p);
  }


  template< class ParameterMapType >
  class edge_label_writer
  {
  public:

    edge_label_writer(ParameterMapType _parameterMap) : parameterMap(_parameterMap) {}
    template< class VertexOrEdge >
    void operator()(std::ostream & out, const VertexOrEdge & v) const
    {
      out << "[label=\"" << parameterMap[v] << "\"]";
    }


  private:

    ParameterMapType parameterMap;
  };

  template< class ParameterMapType >
  inline edge_label_writer< ParameterMapType >
    make_edge_label_writer(ParameterMapType p)
  {
    return edge_label_writer< ParameterMapType >(p);
  }

  
bool
Blueprint::BlueprintImpl
::SetComponent( ComponentNameType name, ParameterMapType parameterMap )
{
  if( this->ComponentExists( name ) )
  {
    this->m_Graph[ name ].parameterMap = parameterMap;
    return true;
  }
  else
  {
    return this->m_Graph.insert_vertex( name, { name, parameterMap } ).second;
  }
}

  
Blueprint::ParameterMapType
Blueprint::BlueprintImpl
::GetComponent( ComponentNameType name ) const
{
  if( !this->ComponentExists( name ) )
  {
    std::stringstream msg;
    msg << "Blueprint does not contain component " << name << std::endl;
    throw std::runtime_error( msg.str() );
  }

  return this->m_Graph[ name ].parameterMap;
}


bool
Blueprint::BlueprintImpl
::DeleteComponent( ComponentNameType name )
{
  if( !this->ComponentExists( name ) )
  {
    this->m_Graph.remove_vertex( name );
    return true;
  }
  
  return false;
}

Blueprint::ComponentNamesType
Blueprint::BlueprintImpl
::GetComponentNames( void ) const
{
  ComponentNamesType container;
  for( auto it = boost::vertices( this->m_Graph.graph() ).first; it != boost::vertices( this->m_Graph.graph() ).second; ++it )
  {
    container.push_back( this->m_Graph.graph()[ *it ].name );
  }
  return container;
}


bool
Blueprint::BlueprintImpl
::SetConnection( ComponentNameType upstream, ComponentNameType downstream, ParameterMapType parameterMap )
{
  if( !this->ComponentExists( upstream ) || !this->ComponentExists( downstream ) )
  {
    return false;
  }
  
  if( !this->ConnectionExists( upstream, downstream ) )
  {
    boost::add_edge_by_label( upstream, downstream,  { parameterMap }, this->m_Graph );
  }
  else
  {
    this->m_Graph[ this->GetConnectionIndex( upstream, downstream ) ].parameterMap = parameterMap;
  }
  
  return true;
}


Blueprint::ParameterMapType
Blueprint::BlueprintImpl
::GetConnection( ComponentNameType upstream, ComponentNameType downstream ) const
{
  return this->m_Graph[ this->GetConnectionIndex( upstream, downstream ) ].parameterMap;
}


bool
Blueprint::BlueprintImpl
::DeleteConnection( Blueprint::ComponentNameType upstream, Blueprint::ComponentNameType downstream )
{
  if( this->ConnectionExists( upstream, downstream ) )
  {
    boost::remove_edge_by_label( upstream, downstream, this->m_Graph );
  }

  return !this->ConnectionExists( upstream, downstream );
}


bool
Blueprint::BlueprintImpl
::ComponentExists( ComponentNameType componentName ) const
{
  const GraphType::vertex_descriptor descriptor = this->m_Graph.vertex( componentName );
  return descriptor != boost::graph_traits< GraphType >::null_vertex();
}


bool
Blueprint::BlueprintImpl
::ConnectionExists( ComponentNameType upstream, ComponentNameType downstream ) const
{
  if( !this->ComponentExists( upstream ) )
  {
    return false;
  }
  if( !this->ComponentExists( downstream ) )
  {
    return false;
  }

  return boost::edge_by_label( upstream, downstream, this->m_Graph ).second;
}


Blueprint::ComponentNamesType
Blueprint::BlueprintImpl
::GetInputNames( const ComponentNameType name ) const
{
  ComponentNamesType container;
  //auto vertex = this->m_Graph.vertex(name);
  //boost::in_edges(vertex, this->m_Graph);
  InputIteratorPairType inputIteratorPair = boost::in_edges( this->m_Graph.vertex( name ), this->m_Graph );
  for( auto it = inputIteratorPair.first; it != inputIteratorPair.second; ++it )
  {
    container.push_back( this->m_Graph.graph()[ it->m_source ].name );
  }

  return container;
}


Blueprint::ComponentNamesType
Blueprint::BlueprintImpl
::GetOutputNames( const ComponentNameType name ) const
{
  ComponentNamesType     container;
  OutputIteratorPairType outputIteratorPair = boost::out_edges( this->m_Graph.vertex( name ), this->m_Graph );
  for( auto it = outputIteratorPair.first; it != outputIteratorPair.second; ++it )
  {
    container.push_back( this->m_Graph.graph()[ it->m_target ].name );
  }

  return container;
}


Blueprint::BlueprintImpl::ConnectionIndexType
Blueprint::BlueprintImpl
::GetConnectionIndex( ComponentNameType upstream, ComponentNameType downstream ) const
{
  // This function is part of the internal API and should fail hard if we use it incorrectly
  if( !this->ConnectionExists( upstream, downstream ) )
  {
    throw std::runtime_error( "Blueprint does not contain connection from component " + upstream + " to " + downstream );
  }

  return boost::edge_by_label( upstream, downstream, this->m_Graph ).first;
}


void
Blueprint::BlueprintImpl
::Write( const std::string filename )
{
  std::ofstream dotfile( filename.c_str() );
  boost::write_graphviz( dotfile, this->m_Graph,
  make_vertex_label_writer( boost::get( &ComponentPropertyType::name, this->m_Graph ),
  boost::get( &ComponentPropertyType::parameterMap, this->m_Graph ) ),
  make_edge_label_writer( boost::get( &ConnectionPropertyType::parameterMap, this->m_Graph ) ) );
}

} // namespace selx
