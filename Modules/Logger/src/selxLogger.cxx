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

#include "selxLogger.h"
#include "selxLoggerImpl.h"

namespace selx {

Logger
::Logger() {
  this->m_LoggerImpl = std::make_unique<LoggerImpl>();
}

Logger::~Logger() = default;

void
Logger
::SetLogLevel( const LogLevel level )
{
  this->m_LoggerImpl->SetLogLevel( level );
}

void
Logger
::SetPattern( const std::string& pattern )
{
  this->m_LoggerImpl->SetPattern( pattern );
}

void
Logger
::SetSyncMode()
{
  this->m_LoggerImpl->SetSyncMode();
}

void
Logger
::SetAsyncMode( const bool block_on_overflow, const size_t queueSize )
{
  this->m_LoggerImpl->SetAsyncMode( block_on_overflow, queueSize );
}

void
Logger
::AsyncQueueFlush( void )
{
  this->m_LoggerImpl->AsyncQueueFlush();
}

void
Logger
::AddStream( const std::string& identifier, std::ostream& stream, const bool forceFlush )
{
  this->m_LoggerImpl->AddStream( identifier, stream, forceFlush);
}

void
Logger
::RemoveStream( const std::string& identifier )
{
  this->m_LoggerImpl->RemoveStream( identifier );
}

void
Logger
::RemoveAllStreams()
{
  this->m_LoggerImpl->RemoveAllStreams();
}


void
Logger
::Log( const LogLevel level, const std::string& message )
{
  this->m_LoggerImpl->Log( level, message );
}

void Logger::Log(const LogLevel level, const std::string& message, const std::string& argument) {
  this->m_LoggerImpl->Log( level, message, argument );
}

LoggerImpl&
Logger
::GetLoggerImpl()
{
  return *this->m_LoggerImpl;
}

} // namespace