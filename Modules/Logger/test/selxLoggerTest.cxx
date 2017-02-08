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

#include "gtest/gtest.h"

using namespace selx;

TEST( LoggerTest, Initialization )
{
  Logger* logger = new Logger();
}

TEST( LoggerTest, Console )
{
  Logger* logger = new Logger();
  logger->AddConsole();
  logger->Log( INFO, "Console INFO message");
}

TEST( LoggerTest, File )
{
  Logger* logger = new Logger();
  logger->AddFile( "/Users/kasper/Development/build/SuperElastix.txt" );
  logger->Log( INFO, "test.log INFO message");
}

TEST( LoggerTest, DefaultChannelFile )
{
  Logger* logger = new Logger();
  logger->AddFile( "/Users/kasper/Development/build/SuperElastix.txt" );
  logger->Log( "SuperElastix", INFO, "test.log INFO message");
}


TEST( LoggerTest, ChannelFile )
{
  Logger* logger = new Logger();
  logger->AddFile( "/Users/kasper/Development/build/SuperElastix.txt", "OtherChannel" );
  logger->Log( "OtherChannel", INFO, "test.log INFO message");
}
