LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/LGPL-2.1;md5=1a6d268fd218675ffea8be556788b780"

DEPENDS = "qtbase qtjsbackend"

INC_PR = "r0"

inherit qmake5

SRC_URI += " \
    file://module_qmake.conf \
    "

export QT_CONF_PATH="${WORKDIR}/qt.conf"

do_configure () {
    # Avoid setting QMAKE_LINK from LD (since we want the linker to be g++)
    unset LD

    export QT_CONF_PATH=${WORKDIR}/qt.conf
    cat > ${WORKDIR}/qt.conf <<EOF
[Paths]
Binaries = ${bindir}
Headers = ${STAGING_INCDIR}/qt5
Plugins = ${libdir}/qt5/plugins
Libraries = ${libdir}
Documentation=${docdir}/qt5
Data = ${datadir}/qt5
HostData = ${STAGING_DATADIR}/qt5
HostBinaries = ${STAGING_BINDIR_NATIVE}
EOF


    # This should not be needed. Perhaps the lack of this file is an indication
    # of an error on the native recipe...
    cp ${WORKDIR}/module_qmake.conf ${S}/.qmake.conf

    ${OE_QMAKE_QMAKE} -r -d
}

do_install() {
    oe_runmake install INSTALL_ROOT=${D}
}

FILES_${PN}-dev += "\
        ${STAGING_INCDIR}/qt5 \
        ${STAGING_DATADIR}/qt5 \
        ${libdir}/*.prl \
"
