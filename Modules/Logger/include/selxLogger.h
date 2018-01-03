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

#ifndef selxLoggerController_h
#define selxLoggerController_h

#include <memory>  // For unique_ptr.
#include <string>

namespace selx
{

enum class LogLevel
{
  TRC = 0,
  DBG = 1,
  INF = 2,
  WRN = 3,
  ERR = 4,
  CRT = 5,
  OFF = 6
};

class LoggerImpl;

class Logger
{
public:

  Logger();

  // We need a destructor which is defined the cxx file, because we use a unique_ptr to an
  // incomplete LoggerImpl.
  ~Logger();

  void SetLogLevel( const LogLevel level );
  void SetPattern( const std::string& pattern );

  void SetSyncMode();
  void SetAsyncMode( const bool block_on_overflow = true, const size_t queueSize = 262144);
  void AsyncQueueFlush();

  // TODO: AddStreamWithColors, AddRotatingFileBySize, AddRotatingFileByTime
  void AddStream( const std::string& identifier, std::ostream& stream, const bool force_flush = false );
  void RemoveStream( const std::string& identifier );
  void RemoveAllStreams();

  void Log( const LogLevel level, const std::string& message );
  void Log( const LogLevel level, const std::string& message, const std::string& argument );

  LoggerImpl& GetLoggerImpl();


private:

  std::unique_ptr< LoggerImpl > m_LoggerImpl;

};

} // namespace

#endif // selxLoggerController_h
