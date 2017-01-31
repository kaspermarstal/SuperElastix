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

set( ${MODULE}_INCLUDE_DIRS
  ${${MODULE}_SOURCE_DIR}/include
)

# Module source files
set( ${MODULE}_SOURCE_FILES
  ${${MODULE}_SOURCE_DIR}/src/selxComponentBase.cxx
  ${${MODULE}_SOURCE_DIR}/src/selxCheckTemplateProperties.cxx
  ${${MODULE}_SOURCE_DIR}/src/selxNetworkContainer.cxx
)

# Export tests
set( ${MODULE}_TEST_SOURCE_FILES
  ${${MODULE}_SOURCE_DIR}/test/selxComponentSelectorTest.cxx
  ${${MODULE}_SOURCE_DIR}/test/selxComponentInterfaceTest.cxx
  ${${MODULE}_SOURCE_DIR}/test/selxNetworkBuilderTest.cxx
)

set( ${MODULE}_LIBRARIES 
)

set( ${MODULE}_MODULE_DEPENDENCIES 
)
