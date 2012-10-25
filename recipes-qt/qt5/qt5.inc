inherit qmake5_base

DEPENDS += "qt5-tools-native virtual/libgl freetype jpeg libpng zlib openssl glib-2.0"

require qt5_arch.inc



QT_PLATFORMFLAGS ?= ""

EXTRA_OEMAKE = "-e"

EXTRA_ENV = 'QMAKE="${STAGING_BINDIR_NATIVE}/qmake -after \
             INCPATH+=${STAGING_INCDIR}/freetype2 LIBS+=-L${STAGING_LIBDIR}" \
             QMAKESPEC="${QMAKESPEC}" LINK="${CXX} -Wl,-rpath-link,${STAGING_LIBDIR}" \
             AR="${TARGET_PREFIX}ar cqs" \
             MOC="${STAGING_BINDIR_NATIVE}/moc5" UIC="${STAGING_BINDIR_NATIVE}/uic4" MAKE="make -e"'

do_configure() {

    set_endian

#    unset QMAKESPEC
#    unset QTDIR

    # Avoid problems with the linkers, since we want the linker to be g++
    unset LD
#    unset CC
#    unset CXX
#    unset CFLAGS
#    unset CXXFLAGS
#    unset RANLIB
#    unset OBJDUMP
#    unset CCLD
#    unset OE_QMAKE_UIC
#    unset OE_QMAKE_MOC
#    unset OE_QMAKE_RCC
#    unset OE_QMAKE_QMAKE
#
    mkdir -p mkspecs/${TARGET_OS}-oe-g++
    cp -f ${WORKDIR}/qplatformdefs.h mkspecs/${TARGET_OS}-oe-g++
    bash ${WORKDIR}/qmake.conf.sh > mkspecs/${TARGET_OS}-oe-g++/qmake.conf

    mkdir -p mkspecs/build-oe-g++
    cp -f ${WORKDIR}/qplatformdefs.h mkspecs/build-oe-g++
    bash ${WORKDIR}/qmake-build.conf.sh > mkspecs/build-oe-g++/qmake.conf

    bbnote "STAGING_DATADIR_NATIVE ${STAGING_DATADIR_NATIVE}"
    bbnote "STAGING_DIR_NATIVE ${STAGING_DIR_NATIVE}"
    bbnote "STAGING_DATADIR ${STAGING_DATADIR}"
    bbnote "mkspec path ${QMAKE_MKSPEC_PATH}"
    bbnote "the mkspec ${QMAKESPEC}"

    ./configure -v \
        -opensource -confirm-license \
        -prefix ${prefix}/ \
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
        -platform build-oe-g++ \
        -xplatform ${TARGET_OS}-oe-g++ \
        -nomake tests \
        -nomake examples \
        ${QT_PLATFORMFLAGS} -no-fast
}

do_compile() {
#    unset QMAKESPEC
#    unset QTDIR
#    unset LD
#    unset CC
#    unset CXX
#    unset CFLAGS
#    unset CXXFLAGS
#    unset RANLIB
#    unset OBJDUMP
#    unset CCLD

#    oe_runmake
#    oe_runmake CC="${CC}" CXX="${CXX}"

   unset CFLAGS CXXFLAGS

   #oe_runmake ${EXTRA_ENV}

   # Build target qmake

   export QMAKESPEC="${S}/mkspecs/${TARGET_OS}-oe-g++"
   #cd ${S}/qmake

   #${OE_QMAKE_QMAKE}

 
   oe_runmake CC="${CC}" CXX="${CXX}" AR="${TARGET_PREFIX}ar cqs"
   cd ${S}
}

do_compile_prepend() {

    cp ${STAGING_BINDIR_NATIVE}/qmake ${S}/bin/qmake

}


do_install() {
    #oe_runmake install INSTALL_ROOT=${D}
}
