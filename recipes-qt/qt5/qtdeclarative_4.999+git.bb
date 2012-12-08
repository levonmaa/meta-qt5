#SRCREV = "90ac5018823ab1109d084cbe0e9e63a4cd531faa"
SRCREV = "425260c2b2a60c0c145a5e76a3b7835eadd0fd0d"
SRC_URI += "git://gitorious.org/qt/qtdeclarative.git;protocol=git"
S = "${WORKDIR}/git"

require qtdeclarative.inc

PR = "${INC_PR}.0"
