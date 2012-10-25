#cat <<EOF
#
# qmake configuration for building with openembedded
#

#MAKEFILE_GENERATOR      = UNIX
#TARGET_PLATFORM         = unix
#TEMPLATE                = app
#CONFIG                  += qt warn_on release incremental link_prl gdb_dwarf_index
#QT                      += core gui
#QMAKE_INCREMENTAL_STYLE = sublib
#
#include(../common/linux.conf)
#include(../common/gcc-base-unix.conf)
#include(../common/g++-unix.conf)
#
#QMAKE_AR              = ${BUILD_AR} cqs
#QMAKE_STRIP           = ${BUILD_STRIP}
#QMAKE_CFLAGS         += ${BUILD_CFLAGS}
#QMAKE_CXXFLAGS       += \$\$QMAKE_CFLAGS ${BUILD_CXXFLAGS}
##QMAKE_LFLAGS         += ${BUILD_LDFLAGS}
#QMAKE_LFLAGS		 += $(OE_QMAKE_LDFLAGS)
#QMAKE_CC              = ${BUILD_CC}
#QMAKE_LINK_C          = ${BUILD_CCLD}
#QMAKE_LINK_C_SHLIB    = ${BUILD_CCLD}
#QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO += ${OE_QMAKE_CFLAGS}
#QMAKE_CXX             = ${BUILD_CXX}
#QMAKE_LINK            = ${BUILD_CXX} ${BUILD_LDFLAGS}
#QMAKE_LINK_SHLIB      = ${BUILD_CXX} ${BUILD_LDFLAGS}
#QMAKE_RANLIB = ${BUILD_RANLIB}

MAKEFILE_GENERATOR      = UNIX
TARGET_PLATFORM         = unix
TEMPLATE                = app
CONFIG                  += qt warn_on release incremental link_prl gdb_dwarf_index
QT                      += core gui
QMAKE_INCREMENTAL_STYLE = sublib

include(../common/linux.conf)
include(../common/gcc-base-unix.conf)
include(../common/g++-unix.conf)


QMAKE_CC       = $(OE_QMAKE_CC)
QMAKE_CFLAGS       += -pipe $(OE_QMAKE_CFLAGS)
QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO += $(OE_QMAKE_CFLAGS)
QMAKE_CFLAGS_DEPS	+= -M
QMAKE_CFLAGS_WARN_ON	+= -Wall -W
QMAKE_CFLAGS_WARN_OFF	+= -w
QMAKE_CFLAGS_RELEASE	+=
QMAKE_CFLAGS_DEBUG	+= -g
QMAKE_CFLAGS_SHLIB	+= -fPIC
QMAKE_CFLAGS_STATIC_LIB	+= -fPIC
QMAKE_CFLAGS_YACC	+= -Wno-unused -Wno-parentheses
QMAKE_CFLAGS_HIDESYMS   += -fvisibility=hidden
QMAKE_CFLAGS_PRECOMPILE += -x c-header -c ${QMAKE_PCH_INPUT} -o ${QMAKE_PCH_OUTPUT}
QMAKE_CFLAGS_USE_PRECOMPILE += -include ${QMAKE_PCH_OUTPUT_BASE}

QMAKE_CXX      = $(OE_QMAKE_CXX)
QMAKE_CXXFLAGS     += $$QMAKE_CFLAGS $(OE_QMAKE_CXXFLAGS)
QMAKE_CXXFLAGS_DEPS	+= $$QMAKE_CFLAGS_DEPS
QMAKE_CXXFLAGS_WARN_ON	+= $$QMAKE_CFLAGS_WARN_ON
QMAKE_CXXFLAGS_WARN_OFF	+= $$QMAKE_CFLAGS_WARN_OFF
QMAKE_CXXFLAGS_RELEASE	+= $$QMAKE_CFLAGS_RELEASE
QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO += $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_CXXFLAGS_DEBUG	+= $$QMAKE_CFLAGS_DEBUG
QMAKE_CXXFLAGS_SHLIB	+= $$QMAKE_CFLAGS_SHLIB
QMAKE_CXXFLAGS_STATIC_LIB += $$QMAKE_CFLAGS_STATIC_LIB
QMAKE_CXXFLAGS_YACC	+= $$QMAKE_CFLAGS_YACC
QMAKE_CXXFLAGS_HIDESYMS += $$QMAKE_CFLAGS_HIDESYMS -fvisibility-inlines-hidden
QMAKE_CXXFLAGS_PRECOMPILE += -x c++-header -c ${QMAKE_PCH_INPUT} -o ${QMAKE_PCH_OUTPUT}
QMAKE_CXXFLAGS_USE_PRECOMPILE = $$QMAKE_CFLAGS_USE_PRECOMPILE

QMAKE_LINK     = $(OE_QMAKE_LINK)
QMAKE_LINK_SHLIB   = $(OE_QMAKE_LINK)
QMAKE_LINK_C		= $(OE_QMAKE_LINK)
QMAKE_LINK_C_SHLIB	= $(OE_QMAKE_LINK)
QMAKE_LFLAGS       += $(OE_QMAKE_LDFLAGS)
QMAKE_LFLAGS_RELEASE	+=
QMAKE_LFLAGS_DEBUG	+=
QMAKE_LFLAGS_APP	+=
QMAKE_LFLAGS_NOUNDEF	+= -Wl,--no-undefined
QMAKE_LFLAGS_RPATH        = -Wl,-rpath-link,

QMAKE_PCH_OUTPUT_EXT    = .gch

# -Bsymbolic-functions (ld) support
QMAKE_LFLAGS_BSYMBOLIC_FUNC = -Wl,-Bsymbolic-functions
QMAKE_LFLAGS_DYNAMIC_LIST = -Wl,--dynamic-list,

# some linking helper...
CONFIG += rpath_libdirs


load(qt_config)
#EOF
