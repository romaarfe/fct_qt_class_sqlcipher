# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/QSQLCipherClass_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/QSQLCipherClass_autogen.dir/ParseCache.txt"
  "QSQLCipherClass_autogen"
  )
endif()
