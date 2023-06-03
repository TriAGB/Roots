add_library(
  lib 
  bisect.hpp 
  chord.hpp 
  combine.hpp 
  findrootresult.hpp function_choice.hpp integ.hpp LineSearch.hpp readfromfile.hpp tangent.hpp
)
target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(lib PROPERTIES LINKER_LANGUAGE CXX)

# target_compile_options(lib PRIVATE
#   $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
#   $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
# )
