inherit qmake5_base

# Qt5 is dependent on icu for localization
ICU = "icu "
ICU_powerpc = "pango"

DEPENDS += "qt5-tools-native virtual/libgl freetype jpeg libpng zlib openssl glib-2.0 ${ICU}"

require qt5_arch.inc

QT_CONFIG_FLAGS ?= ""

QT_TESTS ?= "-nomake tests"
QT_EXAMPLES ?= "-nomake examples"


EXTRA_OEMAKE = "-e"

do_configure() {
    set_endian

    if [ ! -e bin/qmake ]; then
        ln -sf ${STAGING_BINDIR_NATIVE}/qmake bin/qmake
    fi

    # Avoid problems with the linkers, since we want the linker to be g++
    unset LD

    mkdir -p mkspecs/${TARGET_OS}-oe-g++
    cp -f ${WORKDIR}/qplatformdefs.h mkspecs/${TARGET_OS}-oe-g++
    bash ${WORKDIR}/qmake.conf.sh > mkspecs/${TARGET_OS}-oe-g++/qmake.conf

    mkdir -p mkspecs/build-oe-g++
    cp -f ${WORKDIR}/qplatformdefs.h mkspecs/build-oe-g++

    ## FIXME, the file nameing is dumb...
    cp ${WORKDIR}/qmake-build.conf.sh  mkspecs/build-oe-g++/qmake.conf

    ./configure -v \
        -opensource -confirm-license \
        -prefix ${prefix} \
        -bindir ${bindir} \
        -libdir ${libdir} \
        -datadir ${datadir}/${QT_DIR_NAME} \
        -sysconfdir ${sysconfdir}/${QT_DIR_NAME} \
        -docdir ${docdir}/${QT_DIR_NAME} \
        -headerdir ${includedir}/${QT_DIR_NAME} \
        -plugindir ${libdir}/${QT_DIR_NAME}/plugins \
        -importdir ${libdir}/${QT_DIR_NAME}/imports \
        -translationdir ${datadir}/${QT_DIR_NAME}/translations \
        -examplesdir ${bindir}/${QT_DIR_NAME}/examples \
        -shared \
        -no-rpath \
        -platform build-oe-g++ \
        -xplatform ${TARGET_OS}-oe-g++ \
        ${QT_TESTS} \
        ${QT_EXAMPLES} \
        ${QT_CONFIG_FLAGS} -no-fast
}

do_compile() {
    export QT_CONF_PATH="${WORKDIR}/git/bin/qt.conf"
    echo "[Paths]"                                              > $QT_CONF_PATH
    echo "Headers=${includedir}/${QT_DIR_NAME}"                 >> $QT_CONF_PATH
    echo "Libraries=${libdir}"                                  >> $QT_CONF_PATH
    echo "Data=${datadir}/${QT_DIR_NAME}"                       >> $QT_CONF_PATH
    echo "Translations=${datadir}/${QT_DIR_NAME}/translations"  >> $QT_CONF_PATH
    echo "Settings=${sysconfdir}/${QT_DIR_NAME}"                >> $QT_CONF_PATH
    echo "Examples=${bindir}/${QT_DIR_NAME}/examples"           >> $QT_CONF_PATH
    echo "HostData=${STAGING_DATADIR_NATIVE}/qt5"               >> $QT_CONF_PATH

    echo "[EffectivePaths]"                                     >> $QT_CONF_PATH
    echo "Prefix=.."                                             >> $QT_CONF_PATH
    echo "Data=${STAGING_DATADIR_NATIVE}/${QT_DIR_NAME}"                       >> $QT_CONF_PATH

    unset CFLAGS CXXFLAGS AR

    export QMAKESPEC="${S}/mkspecs/${TARGET_OS}-oe-g++"

    oe_runmake
}

do_install() {
    oe_runmake install INSTALL_ROOT=${D}
}

FILES_${PN} = "${libdir}/*.so.*"
FILES_${PN}-dbg = "${libdir}/.debug/*.so.*"
FILES_${PN}-dev = "${libdir}/cmake/* ${libdir}/pkgconfig/*.pc ${libdir}/*.la ${libdir}/*.prl ${includedir}/qt5/*"
FILES_${PN}-staticdev = "${libdir}/libQt*.a"
