
# 
# 添加库文件
# 
# dios_find_add_libraries(MODULE LIBRARIES1 LIBRARIES)
MACRO(dios_find_add_libraries MODULE)

	# 调整ios的包含;
	LIST(APPEND DIOS_FIND_${MODULE}_LIBRARIES ${ARGN})	

ENDMACRO()


