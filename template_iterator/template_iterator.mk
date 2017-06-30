#=======================================================================================#
# template_iterator.mk
#=======================================================================================#
#  Created on: Oct 3, 2015
#      Author: puch
#=======================================================================================#

#=======================================================================================#
# DEFINE PACKAGE RULE
#=======================================================================================#
define $(_flavor_)_$(_feat_)_MAKE
#=======================================================================================#
# OBJECTS DIRECTORY
# e.g: 
#     $(_flavor_)_$(_feat_)_src_dir=pk_module_N_code/_src
#     or
#     $(_flavor_)_$(_feat_)_src_dir=_src
#=======================================================================================#
$(_flavor_)_$(_feat_)_inc=citerator.h citerator.c
#=======================================================================================#
# END PACKAGE RULE
#=======================================================================================#
endef
#=======================================================================================#
# LOCAL VARIABLES
#=======================================================================================#

#=======================================================================================#
# LOCAL DEFINES 
#=======================================================================================#

#=======================================================================================#
# LOCAL DEFINE EXPANSIONS
#=======================================================================================#

#=======================================================================================#
# LOCAL RULES EXPANSIONS
#=======================================================================================#

#=======================================================================================#
# INCLUDE PK PROJECT UTILITY
#=======================================================================================#
include $(PROJ_MAK_DIR)/epilog.mk
#=======================================================================================#
# template_iterator.mk
#=======================================================================================#
# Changes Log
#
#
#=======================================================================================#