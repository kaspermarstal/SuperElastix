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

#ifndef selxLoggerImpl_h
#define selxLoggerImpl_h

#include <iterator>

#include "selxLogger.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/ostream_sink.h"
#include "spdlog/fmt/bundled/ostream.h"

namespace selx
{

class LoggerImpl
{

public:

  LoggerImpl();
  ~LoggerImpl();

  void SetLogLevel( const LogLevel& level );
  void SetPattern( const std::string& pattern );

  void SetSyncMode();
  void SetAsyncMode( const bool block_on_overflow, const size_t queueSize );
  void AsyncQueueFlush();

  void AddStream( const std::string& identifier, std::ostream& stream, const bool forceFlush = false );
  void RemoveStream( const std::string& identifier );
  void RemoveAllStreams();

  void Log( const LogLevel& level, const std::string& message );

  template < typename ... Args >
  void
  Log( const LogLevel& level, const std::string& fmt, const Args& ... args )
  {
    for( const auto& identifierAndLogger : this->m_Loggers )
    {
      identifierAndLogger.second->log( this->ToSpdLogLevel( level ), fmt.c_str(), args ... );
    }
  }


private:

  // Spdlog configuration
  spdlog::level::level_enum ToSpdLogLevel( const LogLevel& level );

  // Logger container
  using LoggerType = std::shared_ptr< spdlog::logger >;
  using LoggerVectorType = std::map< std::string, LoggerType >;
  LoggerVectorType m_Loggers;

};


// Convert std:vector to string
// TODO: Use std::copy_n to print [n1, n2, ... , n-1, n] if vector is long
template < typename T >
std::string to_string( const std::vector< T >& v ) {
  std::stringstream out;
  if (!v.empty()) {
    if (v.size() > 1) out << '[';
    std::copy(v.begin(), v.end(), std::ostream_iterator< T >(out, ", "));
    out << "\b\b";
    if (v.size() > 1) out << "]";
  }
  return out.str();
}


// Convert std::map< T, T > to string
template < typename T >
std::string to_string( const std::map< T, T >& m ) {
  std::stringstream out;
  if (!m.empty()) {
    out << "{";
    for (const auto& item : m) {
      out << item.first << ": " << item.second << ", ";
    }
    out << "\b\b}";
  }
  return out.str();
}


// Convert std::map< T, std::vector< T > > to string
template < typename T >
std::string to_string( const std::map< T, std::vector< T > >& m ) {
  std::stringstream out;
  if (!m.empty()) {
    out << "{";
    for (const auto& item : m) {
      out << item.first << ": " << this << item.second << ", ";
    }
    out << "\b\b}";
  }
  return out.str();
}


} // namespace

#endif // selxLoggerImpl_h
