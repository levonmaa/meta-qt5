# Copyright (C) 2012 O.S. Systems Software LTDA.

QT_MODULE ?= "${PN}"
QT_VERSION ?= "${PV}-beta1"

#SRC_URI = "http://releases.qt-project.org/qt5.0/beta1/split_sources/${QT_MODULE}-opensource-src-${QT_VERSION}.tar.xz \

SRCREV = "59009cfd0c0ac36bab5864c2a48dfc052ea29191"
SRC_URI = "git://qt.gitorious.org/qt/qtbase.git;protocol=git \
			file://0002-qmake-is-already-built-in-qt5-tools-native.patch \
			file://0003-Allow-building-a-separate-qmake-for-the-target.patch \
			file://qmake-build.conf.sh \
            file://qmake.conf.sh \
            file://qplatformdefs.h \
            file://linux.conf \
            file://g++.conf"

S = "${WORKDIR}/git"
#S = "${WORKDIR}/${QT_MODULE}-opensource-src-${QT_VERSION}"
