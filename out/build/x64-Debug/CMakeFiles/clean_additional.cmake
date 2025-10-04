# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Gui\\CMakeFiles\\Prueva3_autogen.dir\\AutogenUsed.txt"
  "Gui\\CMakeFiles\\Prueva3_autogen.dir\\ParseCache.txt"
  "Gui\\Prueva3_autogen"
  )
endif()
