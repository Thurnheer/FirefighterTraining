QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase
CONFIG += c++17
CONFIG += test

INCLUDEPATH += ./../../../boost/boost_1_69_0/
INCLUDEPATH += ./../FirefighterTrainingPlaner/database
INCLUDEPATH += ./../FirefighterTrainingPlaner/ImportExport
INCLUDEPATH += ./../QXlsx/header/
INCLUDEPATH += ./../FirefighterTrainingPlaner/container

#TEMPLATE = app
message(Test build)
TARGET = UnitTests

SOURCES +=  tst_eventtest.cpp \
    tst_main.cpp \
    tst_fwdrilltypedbtest.cpp \
    tst_tablecreationtest.cpp \
    ImportExport/tst_importcalendartest.cpp \
    ImportExport/testcalendarlayout.cpp \
    ImportExport/testeventtypeparser.cpp

HEADERS += \
    tst_eventtest.hpp \
    autotest.hpp \
    tst_fwdrilltypedbtest.hpp \
    tst_tablecreationtest.hpp \
    ImportExport/tst_importcalendartest.hpp \
    container/channel.hpp \
    ImportExport/testcalendarlayout.hpp \
    ImportExport/testeventtypeparser.hpp


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QXlsx/ -lQXlsx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QXlsx/ -lQXlsxd
else:unix: LIBS += -L$$OUT_PWD/../QXlsx/ -lQXlsx

INCLUDEPATH += $$PWD/../QXlsx
DEPENDPATH += $$PWD/../QXlsx

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QXlsx/libQXlsx.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QXlsx/libQXlsxd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QXlsx/QXlsx.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QXlsx/QXlsxd.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../QXlsx/libQXlsx.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FirefighterTrainingPlaner/ -lFirefighterTrainingPlaner
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FirefighterTrainingPlaner/ -lFirefighterTrainingPlanerd
else:unix: LIBS += -L$$OUT_PWD/../FirefighterTrainingPlaner/ -lFirefighterTrainingPlaner

INCLUDEPATH += $$PWD/../FirefighterTrainingPlaner
DEPENDPATH += $$PWD/../FirefighterTrainingPlaner

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FirefighterTrainingPlaner/libFirefighterTrainingPlaner.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FirefighterTrainingPlaner/libFirefighterTrainingPlanerd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FirefighterTrainingPlaner/FirefighterTrainingPlaner.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FirefighterTrainingPlaner/FirefighterTrainingPlanerd.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../FirefighterTrainingPlaner/libFirefighterTrainingPlaner.a
