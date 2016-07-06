#=========================================================================
#
#  Copyright Leiden University Medical Center, Erasmus University Medical 
#  Center and contributors
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
#=========================================================================

set( MODULE ModuleExamples )

# Export include files
set( ${MODULE}_INCLUDE_DIRS
  ${${MODULE}_SOURCE_DIR}/include
)

# Collect header files for Visual Studio Project
file(GLOB ${MODULE}_HEADER_FILES "${${MODULE}_SOURCE_DIR}/include/*.*")

# Export libraries
set( ${MODULE}_LIBRARIES 
  ${MODULE}
)

# Module source files
set( ${MODULE}_SOURCE_FILES
  ${${MODULE}_SOURCE_DIR}/src/Example3rdPartyCode.cxx
  ${${MODULE}_SOURCE_DIR}/src/Example4thPartyCode.cxx
  ${${MODULE}_SOURCE_DIR}/src/GDOptimizer3rdPartyComponent.cxx
  ${${MODULE}_SOURCE_DIR}/src/GDOptimizer4thPartyComponent.cxx
  ${${MODULE}_SOURCE_DIR}/src/Metric3rdPartyWrapper.cxx
  ${${MODULE}_SOURCE_DIR}/src/Metric4thPartyWrapper.cxx
  ${${MODULE}_SOURCE_DIR}/src/SSDMetric3rdPartyComponent.cxx
  ${${MODULE}_SOURCE_DIR}/src/SSDMetric4thPartyComponent.cxx
  ${${MODULE}_SOURCE_DIR}/src/TransformComponent1.cxx
  ${${MODULE}_SOURCE_DIR}/src/MetricComponent1.cxx
)

# Compile library

add_library( ${MODULE} STATIC "${${MODULE}_SOURCE_FILES}" ${${MODULE}_HEADER_FILES})

target_link_libraries( ${MODULE} ${SUPERELASTIX_LIBRARIES} )
