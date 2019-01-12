TEMPLATE = subdirs
CONFIG += ordered
CONFIG += c++17

QMAKE_CC = /usr/bin/clang
QMAKE_CXX = /usr/bin/clang++


SUBDIRS += \
    FirefighterTrainingPlaner \
    FirefighterTrainingPlanerTest \
    QXlsx \
    Main

FirefighterTrainingPlaner.depends = QXlsx
FirefighterTrainingPlanerTest.depends = QXlsx
FirefighterTrainingPlanerTest.depends = FirefighterTrainingPlaner
