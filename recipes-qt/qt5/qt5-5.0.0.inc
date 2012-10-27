# Copyright (C) 2012 O.S. Systems Software LTDA.

QT_MODULE ?= "${PN}"
QT_VERSION ?= "${PV}-beta1"

#SRC_URI = "http://releases.qt-project.org/qt5.0/beta1/split_sources/${QT_MODULE}-opensource-src-${QT_VERSION}.tar.xz \

SRCREV = "59009cfd0c0ac36bab5864c2a48dfc052ea29191"
SRC_URI = "git://qt.gitorious.org/qt/qtbase.git;protocol=git \
			file://qmake-build.conf.sh \
            file://qmake.conf.sh \
            file://qplatformdefs.h"

S = "${WORKDIR}/git"
#S = "${WORKDIR}/${QT_MODULE}-opensource-src-${QT_VERSION}"
