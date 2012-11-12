require qt5.inc

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://LICENSE.LGPL;md5=02356821480f1d3d534b21e0343265b5"

#LICENSE = "LGPLv2.1 | GPLv3"
#LIC_FILES_CHKSUM = "file://LICENSE.LGPL;md5=cc5963be04f8b19c3e3c46bc31f0f6e1 \
#                    file://LICENSE.GPL;md5=d32239bcb673463ab874e80d47fae504 \
#                    file://LGPL_EXCEPTION.txt;md5=411080a56ff917a5a1aa08c98acae354"

QT_BASE_NAME = "qt5"
QT_DIR_NAME = "qt5"

export QMAKESPEC = "${STAGING_DATADIR}/${QT_DIR_NAME}/mkspecs/${TARGET_OS}-oe-g++"

# Qt uses atomic instructions not supported in thumb mode
ARM_INSTRUCTION_SET = "arm"

inherit qmake5
