cmake_minimum_required (VERSION 3.8)
add_executable (shutdown_exe "shutdown_exe.cpp" "shutdown_exe.h")
# 以下可用于添加管理员UAC，但是在此程序中没有必要。
# set_target_properties(shutdown_exe PROPERTIES LINK_FLAGS " /MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\" ")
