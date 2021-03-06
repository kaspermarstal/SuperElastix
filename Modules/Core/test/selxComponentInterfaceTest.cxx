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

#include "selxSSDMetric3rdPartyComponent.h"
#include "selxGDOptimizer3rdPartyComponent.h"
#include "selxSSDMetric4thPartyComponent.h"
#include "selxGDOptimizer4thPartyComponent.h"

#include "gtest/gtest.h"

namespace selx
{

namespace hack // see issue SELX-55 Link error selxComponentInterfaceTest #55
{
    LoggerImpl logger;
    typedef SuperElastixComponent< Accepting< >, Providing<  > > DummyBase;
    struct MyComp: DummyBase
    {
        MyComp(): DummyBase("nameless", logger) {}
        virtual bool MeetsCriterion( const CriterionType & criterion ) override { throw 42; };

    } dummy;   
}

class InterfaceTest : public ::testing::Test
{
public:

  virtual void SetUp()
  {
    LoggerImpl * logger = new LoggerImpl();
    metric3p    = std::make_shared< SSDMetric3rdPartyComponent >( "nameless", *logger );
    optimizer3p = std::make_shared< GDOptimizer3rdPartyComponent >( "nameless", *logger );

    metric4p    = std::make_shared< SSDMetric4thPartyComponent >( "nameless", *logger );
    optimizer4p = std::make_shared< GDOptimizer4thPartyComponent >( "nameless", *logger );
  }


  virtual void TearDown()
  {
    //delete metric3p;
    //delete optimizer3p;
    //delete metric4p;
    //delete optimizer4p;
  }


  // types as if returned by our component factory
  ComponentBase::Pointer metric3p;
  ComponentBase::Pointer optimizer3p;
  ComponentBase::Pointer metric4p;
  ComponentBase::Pointer optimizer4p;
};

TEST_F( InterfaceTest, InterfaceNameTraits )
{
  EXPECT_STREQ( Properties< MetricValueInterface >::Get().at( "NameOfInterface" ).c_str(), "MetricValueInterface" );
  EXPECT_STREQ( Properties< InterfaceAcceptor< MetricValueInterface >>::Get().at( "NameOfInterface" ).c_str(), "MetricValueInterface" );
}

TEST_F( InterfaceTest, DynamicCast )
{
  int returnval;
  //metric3p should have a MetricValueInterface
  MetricValueInterface::Pointer valueIF = std::dynamic_pointer_cast< MetricValueInterface >( metric3p );
  ASSERT_NE( valueIF, nullptr );
  EXPECT_NO_THROW( returnval = valueIF->GetValue() );

  //metric3p should have a MetricDerivativeInterface
  MetricDerivativeInterface::Pointer derivativeIF = std::dynamic_pointer_cast< MetricDerivativeInterface >( metric3p );
  ASSERT_NE( derivativeIF, nullptr );
  EXPECT_NO_THROW( returnval = derivativeIF->GetDerivative() );

  //optimizer3p should have a OptimizerUpdateInterface
  OptimizerUpdateInterface::Pointer updateIF = std::dynamic_pointer_cast< OptimizerUpdateInterface >( optimizer3p );
  ASSERT_NE( updateIF, nullptr );
  //EXPECT_NO_THROW(returnval = updateIF->Update()); // Update can only be called if metric and optimizer are connected

  //optimizer3p should have a InterfaceAcceptor<MetricValueInterface>
  InterfaceAcceptor< MetricValueInterface >::Pointer valueAcceptorIF = std::dynamic_pointer_cast< InterfaceAcceptor< MetricValueInterface >>(
    optimizer3p );
  ASSERT_NE( valueAcceptorIF, nullptr );

  //optimizer3p should have a InterfaceAcceptor<MetricDerivativeInterface>
  InterfaceAcceptor< MetricDerivativeInterface >::Pointer derivativeAcceptorIF
    = std::dynamic_pointer_cast< InterfaceAcceptor< MetricDerivativeInterface >>( optimizer3p );
  ASSERT_NE( derivativeAcceptorIF, nullptr );
}

TEST_F( InterfaceTest, ConnectByName )
{
  InterfaceStatus IFstatus;
  EXPECT_NO_THROW( IFstatus = optimizer3p->CanAcceptConnectionFrom( metric3p, { { "NameOfInterface", "MetricValueInterface" } } ) );
  EXPECT_EQ( IFstatus, InterfaceStatus::success );

  EXPECT_NO_THROW( IFstatus = optimizer3p->CanAcceptConnectionFrom( metric4p, { { "NameOfInterface", "MetricValueInterface" } } ) );
  EXPECT_EQ( IFstatus, InterfaceStatus::success );

  EXPECT_NO_THROW( IFstatus = optimizer4p->CanAcceptConnectionFrom( metric3p, { { "NameOfInterface", "MetricValueInterface" } } ) );
  EXPECT_EQ( IFstatus, InterfaceStatus::success );

  EXPECT_NO_THROW( IFstatus = optimizer4p->CanAcceptConnectionFrom( metric4p, { { "NameOfInterface", "MetricValueInterface" } } ) );
  EXPECT_EQ( IFstatus, InterfaceStatus::success );

  EXPECT_NO_THROW( IFstatus = optimizer3p->CanAcceptConnectionFrom( metric3p, { { "NameOfInterface", "MetricDerivativeInterface" } } ) );
  EXPECT_EQ( IFstatus, InterfaceStatus::success );

  EXPECT_NO_THROW( IFstatus = optimizer3p->CanAcceptConnectionFrom( metric4p, { { "NameOfInterface", "MetricDerivativeInterface" } } ) );
  EXPECT_EQ( IFstatus, InterfaceStatus::noprovider );

  EXPECT_NO_THROW( IFstatus = optimizer4p->CanAcceptConnectionFrom( metric3p, { { "NameOfInterface", "MetricDerivativeInterface" } } ) );
  EXPECT_EQ( IFstatus, InterfaceStatus::noaccepter );

  EXPECT_NO_THROW( IFstatus = optimizer3p->CanAcceptConnectionFrom( metric3p, {} ) );
  EXPECT_EQ( IFstatus, InterfaceStatus::multiple );
}

TEST_F( InterfaceTest, ConnectAll )
{
  int                               connectionCount = 0;
  int                               returnval;
  OptimizerUpdateInterface::Pointer updateIF;
  EXPECT_NO_THROW( connectionCount = optimizer3p->AcceptConnectionFrom( metric3p ) );
  EXPECT_EQ( connectionCount, 2 ); // both MetricValueInterface and MetricDerivativeInterface are connected

  //optimizer3p should have a OptimizerUpdateInterface
  updateIF = std::dynamic_pointer_cast< OptimizerUpdateInterface >( optimizer3p );
  ASSERT_NE( updateIF, nullptr );
  EXPECT_NO_THROW( returnval = updateIF->Update() ); // Update can only be called if metric and optimizer are connected

  EXPECT_NO_THROW( connectionCount = optimizer3p->AcceptConnectionFrom( metric4p ) );
  EXPECT_EQ( connectionCount, 1 ); // only MetricValueInterface is connected

  //metric4p does not have MetricDerivativeInterface, so optimizer3p cannot run

  EXPECT_NO_THROW( connectionCount = optimizer4p->AcceptConnectionFrom( metric3p ) );
  EXPECT_EQ( connectionCount, 1 ); // only MetricValueInterface is connected

  updateIF = std::dynamic_pointer_cast< OptimizerUpdateInterface >( optimizer4p );
  ASSERT_NE( updateIF, nullptr );
  EXPECT_NO_THROW( returnval = updateIF->Update() );

  EXPECT_NO_THROW( connectionCount = optimizer4p->AcceptConnectionFrom( metric4p ) );
  EXPECT_EQ( connectionCount, 1 ); // only MetricValueInterface is connected

  updateIF = std::dynamic_pointer_cast< OptimizerUpdateInterface >( optimizer4p );
  ASSERT_NE( updateIF, nullptr );
  EXPECT_NO_THROW( returnval = updateIF->Update() );

  EXPECT_NO_THROW( connectionCount = metric4p->AcceptConnectionFrom( optimizer4p ) );
  EXPECT_EQ( connectionCount, 0 ); // cannot connect in this direction

  ConflictinUpdateInterface::Pointer update2IF = std::dynamic_pointer_cast< ConflictinUpdateInterface >( optimizer4p );
  ASSERT_NE( update2IF, nullptr );
  EXPECT_NO_THROW( returnval = update2IF->Update( update2IF ) );
}
} // namespace selx
