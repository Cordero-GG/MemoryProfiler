# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Gui\\CMakeFiles\\Gui_autogen.dir\\AutogenUsed.txt"
  "Gui\\CMakeFiles\\Gui_autogen.dir\\ParseCache.txt"
  "Gui\\Gui_autogen"
  )
endif()
