DEPENDS_prepend = "${@["qtbase ", ""][(d.getVar('BPN', True)[:12] == 'qtbase')]}"

inherit qmake5

QT_BASE_NAME = "qt5"
QT_DIR_NAME = "qt5"
QT_LIBINFIX = ""

export QMAKESPEC = "${STAGING_DATADIR}/${QT_DIR_NAME}/mkspecs/${TARGET_OS}-oe-g++"

# Qt uses atomic instructions not supported in thumb mode
ARM_INSTRUCTION_SET = "arm"