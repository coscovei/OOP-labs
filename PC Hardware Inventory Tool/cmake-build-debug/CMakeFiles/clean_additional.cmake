# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PC_Hardware_Inventory_Tool_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PC_Hardware_Inventory_Tool_autogen.dir\\ParseCache.txt"
  "PC_Hardware_Inventory_Tool_autogen"
  )
endif()
