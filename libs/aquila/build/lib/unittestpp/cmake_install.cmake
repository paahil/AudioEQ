# Install script for directory: C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Aquila")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/msys64/mingw64/bin/objdump.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Ohjelmointi/AudioEQ/libs/aquila/build/lib/unittestpp/libUnitTest++.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/UnitTest++" TYPE FILE FILES
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/AssertException.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/CheckMacros.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/Checks.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/CompositeTestReporter.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/Config.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/CurrentTest.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/DeferredTestReporter.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/DeferredTestResult.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/ExceptionMacros.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/ExecuteTest.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/HelperMacros.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/MemoryOutStream.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/ReportAssert.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/ReportAssertImpl.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/Test.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/TestDetails.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/TestList.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/TestMacros.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/TestReporter.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/TestReporterStdout.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/TestResults.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/TestRunner.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/TestSuite.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/TimeConstraint.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/TimeHelpers.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/UnitTest++.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/UnitTestPP.h"
    "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/XmlTestReporter.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/UnitTest++/Win32" TYPE FILE FILES "C:/Ohjelmointi/AudioEQ/libs/aquila/lib/unittestpp/UnitTest++/Win32/TimeHelpers.h")
endif()

