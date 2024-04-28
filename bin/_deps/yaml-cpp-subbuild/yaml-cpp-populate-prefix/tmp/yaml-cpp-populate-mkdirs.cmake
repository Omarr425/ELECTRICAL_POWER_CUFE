# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/media/renderer/59265a2b-d6f5-4b6a-ad90-6c1b1b9d04ac/Programming/ELECTRICAL_POWER_CUFE/bin/_deps/yaml-cpp-src"
  "/media/renderer/59265a2b-d6f5-4b6a-ad90-6c1b1b9d04ac/Programming/ELECTRICAL_POWER_CUFE/bin/_deps/yaml-cpp-build"
  "/media/renderer/59265a2b-d6f5-4b6a-ad90-6c1b1b9d04ac/Programming/ELECTRICAL_POWER_CUFE/bin/_deps/yaml-cpp-subbuild/yaml-cpp-populate-prefix"
  "/media/renderer/59265a2b-d6f5-4b6a-ad90-6c1b1b9d04ac/Programming/ELECTRICAL_POWER_CUFE/bin/_deps/yaml-cpp-subbuild/yaml-cpp-populate-prefix/tmp"
  "/media/renderer/59265a2b-d6f5-4b6a-ad90-6c1b1b9d04ac/Programming/ELECTRICAL_POWER_CUFE/bin/_deps/yaml-cpp-subbuild/yaml-cpp-populate-prefix/src/yaml-cpp-populate-stamp"
  "/media/renderer/59265a2b-d6f5-4b6a-ad90-6c1b1b9d04ac/Programming/ELECTRICAL_POWER_CUFE/bin/_deps/yaml-cpp-subbuild/yaml-cpp-populate-prefix/src"
  "/media/renderer/59265a2b-d6f5-4b6a-ad90-6c1b1b9d04ac/Programming/ELECTRICAL_POWER_CUFE/bin/_deps/yaml-cpp-subbuild/yaml-cpp-populate-prefix/src/yaml-cpp-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/media/renderer/59265a2b-d6f5-4b6a-ad90-6c1b1b9d04ac/Programming/ELECTRICAL_POWER_CUFE/bin/_deps/yaml-cpp-subbuild/yaml-cpp-populate-prefix/src/yaml-cpp-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/media/renderer/59265a2b-d6f5-4b6a-ad90-6c1b1b9d04ac/Programming/ELECTRICAL_POWER_CUFE/bin/_deps/yaml-cpp-subbuild/yaml-cpp-populate-prefix/src/yaml-cpp-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
