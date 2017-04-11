
cmake_minimum_required(VERSION 2.6)

set(SOURCES
  cities.cpp
  etable.cpp
  global.cpp
  idynamic.cpp
  iway.cpp
  stdway.cpp
  tools.cpp
  vehicle.cpp
)

set(HEADERS
  cities.h
  decl.h
  etable.h
  global.h
  idynamic.h
  iway.h
  stdway.h
  tools.h
  vehicle.h
)

set(UNIT_TESTS_SOURCES
  test_cities.cpp
  test_config.cpp
  test_vehicle.cpp
)

set(UNIT_TESTS_HEADERS
)

include_directories($ENV{GTEST_DIR}/include)
include_directories(.)

add_definitions( -DTRANSPORT_EXPORTS )

set( GTEST_LIBRARIES optimized gtest gtest_main debug gtestd gtest_maind )
link_directories( $ENV{GTEST_DIR}/lib )

add_library( transport SHARED ${SOURCES} ${HEADERS} )
add_executable( transport_tests ${UNIT_TESTS_SOURCES} ${UNIT_TESTS_HEADERS} )

add_executable( transport_example example.cpp )

target_link_libraries( transport_tests ${GTEST_LIBRARIES} transport )
target_link_libraries( transport_example transport )
