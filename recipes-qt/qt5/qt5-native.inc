DESCRIPTION = "Native version of Qt5"
DEPENDS = "zlib-native dbus-native"
SECTION = "libs"
HOMEPAGE = "http://qt-project.org"
PROVIDES = "qt5-tools-native"

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://LICENSE.LGPL;md5=02356821480f1d3d534b21e0343265b5"


#LICENSE = "LGPLv2.1 | GPLv3"
#LIC_FILES_CHKSUM = "file://LICENSE.LGPL;md5=cc5963be04f8b19c3e3c46bc31f0f6e1 \
#                    file://LICENSE.GPL;md5=d32239bcb673463ab874e80d47fae504 \
#                    file://LGPL_EXCEPTION.txt;md5=411080a56ff917a5a1aa08c98acae354"

QT_MODULE ?= "${PN}"
QT_VERSION ?= "${PV}-beta1"

#SRC_URI = "http://releases.qt-project.org/qt5.0/beta1/split_sources/${QT_MODULE}-opensource-src-${QT_VERSION}.tar.xz \

SRCREV = "59009cfd0c0ac36bab5864c2a48dfc052ea29191"
SRC_URI = "git://qt.gitorious.org/qt/qtbase.git;protocol=git \
            file://0001-qlibraryinfo-allow-to-set-qt.conf-from-the-outside-u.patch \
            file://qmake.conf.sh \
            file://qplatformdefs.h"


#S = "${WORKDIR}/${QT_MODULE}-opensource-src-${QT_VERSION}"
S = "${WORKDIR}/git"


INC_PR = "r0"

#include qt-${PV}.inc

inherit native

QT_MODULE = "qtbase"

QT_MAKE_TEST ?= "-nomake tests"
QT_MAKE_EXAMPLES ?= "-nomake examples"

EXTRA_OECONF = "-prefix ${prefix} \
                -L ${STAGING_LIBDIR_NATIVE} \
                -I ${STAGING_INCDIR_NATIVE} \
                -system-zlib \
                -no-libjpeg \
                -no-libpng \
                -no-gif \
                -no-accessibility \
                -no-cups \
                -no-nis \
                -no-gui \
                -no-qml-debug \
                -no-sql-mysql \
                -no-sql-sqlite \
                -no-opengl \
                -no-openssl \
                -verbose -release \
                -headerdir ${includedir}/qt5 \
                -no-glib \
                -no-iconv \
                -no-fast \
                -silent \
                ${QT_MAKE_TESTS} \
                ${QT_MAKE_EXAMPLES} \
                -no-rpath"

do_configure() {
	# Avoid setting QMAKE_LINK from LD (since we want the linker to be g++)
	unset LD

	(echo o; echo yes) | ./configure ${EXTRA_OECONF} || die "Configuring qt failed. EXTRA_OECONF was ${EXTRA_OECONF}"
}

do_install() {
    install -d ${D}${bindir}/
    # Install only the qmake bin for now.
    install -m 0755 ${S}/bin/qmake ${D}${bindir}/qmake
}
