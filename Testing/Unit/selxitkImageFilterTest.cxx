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

#include "selxSuperElastixFilter.h"

#include "selxItkSmoothingRecursiveGaussianImageFilterComponent.h"
#include "selxItkImageSink.h"
#include "selxItkImageSource.h"

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "selxDataManager.h"
#include "gtest/gtest.h"

/** this test uses the following blueprint setup

 [SourceComponent] - [itkImageFilter] - [itkImageFilter] - [SinkComponent]

 - All the nodes are identified by their Class names
 - All Connections are identified by their Interface names

 The overlord finds the Source and Sink Components and connects these to it's external pipeline (internal reader and writer filters, currently).
*/

namespace selx {

  class itkImageFilterTest : public ::testing::Test {
public:
  typedef Overlord::Pointer                 OverlordPointerType;
  typedef Blueprint::Pointer                BlueprintPointerType;
  typedef Blueprint::ConstPointer           BlueprintConstPointerType;
  typedef Blueprint::ParameterMapType       ParameterMapType;
  typedef Blueprint::ParameterValueType     ParameterValueType;
  typedef DataManager DataManagerType;

  typedef SuperElastixFilter<bool>          SuperElastixFilterType;

  typedef itk::Image<double, 3> Image3DType;
  typedef itk::ImageFileReader<Image3DType> ImageReader3DType;
  typedef itk::ImageFileWriter<Image3DType> ImageWriter3DType;

  virtual void SetUp() {


    /** register all components used for this test */
    // For testing the itkfilter pipeline
    ComponentFactory<ItkSmoothingRecursiveGaussianImageFilterComponent<3, double>>::RegisterOneFactory();
    ComponentFactory<ItkImageSinkComponent<3, double>>::RegisterOneFactory();
    ComponentFactory<ItkImageSourceComponent<3, double>>::RegisterOneFactory();
    // For testing templated components
    ComponentFactory<ItkSmoothingRecursiveGaussianImageFilterComponent<2, double>>::RegisterOneFactory();
    ComponentFactory<ItkSmoothingRecursiveGaussianImageFilterComponent<3, float>>::RegisterOneFactory();
    ComponentFactory<ItkSmoothingRecursiveGaussianImageFilterComponent<2, float>>::RegisterOneFactory();


    /** make example blueprint configuration */
    blueprint = Blueprint::New();

    /** the 2 itkImageFilter Components are ItkSmoothingRecursiveGaussianImageFilterComponent*/
    ParameterMapType componentParameters;
    componentParameters["NameOfClass"] = { "ItkSmoothingRecursiveGaussianImageFilterComponent" };
    // The parameters over which the Component is templated are criteria for the ComponentSelector too.
    componentParameters["Dimensionality"] = { "3" }; // template parameters
    componentParameters["PixelType"] = { "double" };

    // Setting of the component are considered as criteria too. If the components can interpret the parameters, it's all good. 
    componentParameters["Sigma"] = { "2.5" };

    blueprint->AddComponent("FistStageFilter", componentParameters);
    blueprint->AddComponent("SecondStageFilter", componentParameters);

    // TODO: For now, the connections to make are explicitly indicated by the Interface name. 
    // Design consideration: connections might be indicated by higher concepts ( MetricCostConnection: value and/or derivative? DefaultPipeline? ) 
    ParameterMapType connectionParameters;
    //connectionParameters["NameOfInterface"] = { "itkImageSourceInterface" };

    //TODO: check direction
    blueprint->AddConnection("FistStageFilter", "SecondStageFilter", connectionParameters);

    /** Add a description of the SourceComponent*/
    ParameterMapType sourceComponentParameters;
    sourceComponentParameters["NameOfClass"] = { "ItkImageSourceComponent" };
    blueprint->AddComponent("Source", sourceComponentParameters);

    /** Add a description of the SinkComponent*/
    ParameterMapType sinkComponentParameters;
    sinkComponentParameters["NameOfClass"] = { "ItkImageSinkComponent" };
    blueprint->AddComponent("Sink", sinkComponentParameters);
    
    /** Connect Sink and Source to the itkImageFilter Components*/
    blueprint->AddConnection("Source", "FistStageFilter", connectionParameters); // 
    blueprint->AddConnection("SecondStageFilter", "Sink", connectionParameters);
  }

  virtual void TearDown() {
    itk::ObjectFactoryBase::UnRegisterAllFactories();
  }

  BlueprintPointerType blueprint;
  Overlord::Pointer overlord;
};

  TEST_F(itkImageFilterTest, Run)
{
  // Instantiate SuperElastix
  SuperElastixFilterType::Pointer superElastixFilter;
  EXPECT_NO_THROW(superElastixFilter = SuperElastixFilterType::New());

  // Data manager provides the paths to the input and output data for unit tests
  DataManagerType::Pointer dataManager = DataManagerType::New();

  // Set up the readers and writers
  ImageReader3DType::Pointer inputImageReader = ImageReader3DType::New();
  inputImageReader->SetFileName(dataManager->GetInputFile("sphereA3d.mhd"));

  ImageWriter3DType::Pointer resultImageWriter = ImageWriter3DType::New();
  resultImageWriter->SetFileName(dataManager->GetOutputFile("itkImageFilterTest.mhd"));


  // Connect SuperElastix in an itk pipeline
  superElastixFilter->SetInput("Source", inputImageReader->GetOutput());
  resultImageWriter->SetInput(superElastixFilter->GetOutput<Image3DType>("Sink"));
  
  EXPECT_NO_THROW(superElastixFilter->SetBlueprint(blueprint));

  //Optional Update call
  //superElastixFilter->Update();

  // Update call on the writers triggers SuperElastix to configure and execute
  EXPECT_NO_THROW(resultImageWriter->Update());
}

} // namespace selx
