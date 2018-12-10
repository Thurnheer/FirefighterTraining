QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase
CONFIG += c++17

INCLUDEPATH += ./../../../boost/boost_1_60_0/
INCLUDEPATH += ./../FirefighterTrainingPlaner/database

TEMPLATE = app

SOURCES +=  tst_eventtest.cpp \
    tst_main.cpp \
    tst_fwdrilltypedbtest.cpp \
    tst_tablecreationtest.cpp

HEADERS += \
    tst_eventtest.hpp \
    autotest.hpp \
    tst_fwdrilltypedbtest.hpp \
    tst_tablecreationtest.hpp
