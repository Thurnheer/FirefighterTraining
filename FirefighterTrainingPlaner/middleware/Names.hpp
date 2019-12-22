#ifndef NAMES_HPP
#define NAMES_HPP

#include "qregularexpression.h"
#include "qvector.h"
#include "../ImportExport/calendarparser.hpp"

//-------------------------------------------------------------------------------------------------------------------------
//
// regular expressions
//
//-------------------------------------------------------------------------------------------------------------------------

static const QRegularExpression zug("Zug", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression exerciseAll("bung alle", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression hauptuebung("Haupt", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression brandhaus("Brandhaus", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression fahrertag("Fahrertag", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression jahresplanung("Jahresplanung", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression ausbildung("Ausbildung", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression zugsrapport("Zugsrapport", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression wasistneu("Was ist neu", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression friedenslicht("Friedenslicht", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression neujahr("Neujahrsa", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression zug1("^Zug 1/\\d.*", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression zug2("^Zug 2/\\d.*", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression zug3("^Zug 3/\\d.*", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression kommandoZug("^K-Zug \\d.*", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression absturz("Abst", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression piketzug("Piket", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression masch("^MD ", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression maschA("^MD A/\\d.*", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression maschB("^MD B/\\d.*", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression maschC("^MD C/\\d.*", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression atemschutz("^AS ", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression atemschutzA("^AS A/\\d.*", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression atemschutzB("^AS B/\\d.*", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression atemschutzC("^AS C/\\d.*", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression kader("^Kader", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression uof("Uof", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression off("OFF", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression zugfuehrer("^Zugf", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression spezialisten("^Spezialisten", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression wbk("WBK", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression day("Tag", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression neue("Neue AS", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression infoabend("Infoab", QRegularExpression::CaseInsensitiveOption);
static const QRegularExpression parkdienst("Parkdienst", QRegularExpression::CaseInsensitiveOption);

//-------------------------------------------------------------------------------------------------------------------------
//
// exercise definitions
//
//-------------------------------------------------------------------------------------------------------------------------

static const QVector<QRegularExpression> allEvents{ zug, exerciseAll, hauptuebung, brandhaus, fahrertag, jahresplanung, ausbildung,
            zugsrapport, wasistneu, friedenslicht, neujahr, absturz, piketzug, masch, atemschutz, kader, uof, off, zugfuehrer,
            spezialisten, wbk, neue, infoabend, parkdienst};
static const QVector<QRegularExpression> exerciseZug1{ zug1, exerciseAll, hauptuebung };
static const QVector<QRegularExpression> exerciseZug2{ zug2, exerciseAll, hauptuebung };
static const QVector<QRegularExpression> exerciseZug3{ zug3, exerciseAll, hauptuebung };
static const QVector<QRegularExpression> exerciseKommandoZug{ kommandoZug, exerciseAll, hauptuebung };
static const QVector<QRegularExpression> exerciseAbsturz{ absturz };
static const QVector<QRegularExpression> exercisePiketzug{ piketzug };
static const QVector<QRegularExpression> exerciseMaschA{ maschA, fahrertag, parkdienst };
static const QVector<QRegularExpression> exerciseMaschB{ maschB, fahrertag, parkdienst };
static const QVector<QRegularExpression> exerciseMaschC{ maschC, fahrertag, parkdienst };
static const QVector<QRegularExpression> exerciseAsA{ atemschutzA, brandhaus };
static const QVector<QRegularExpression> exerciseASB{ atemschutzB, brandhaus };
static const QVector<QRegularExpression> exerciseAsC{ atemschutzC, brandhaus };
static const QVector<QRegularExpression> exerciseUof{ uof, kader, zugsrapport};
static const QVector<QRegularExpression> exerciseOff{ off, kader, zugsrapport, wasistneu};
static const QVector<QRegularExpression> exerciseZugfuehrer{ zugfuehrer, jahresplanung, ausbildung };
static const QVector<QRegularExpression> exerciseSpezialisten{ spezialisten, neue };
static const QVector<QRegularExpression> sonstiges{ neujahr, friedenslicht, infoabend };


//-------------------------------------------------------------------------------------------------------------------------
//
// exercise times
//
//-------------------------------------------------------------------------------------------------------------------------
static const IO::EventTime zugtime { {zug, exerciseAll, absturz, piketzug, masch, off, wasistneu, spezialisten, kader, neue, infoabend, parkdienst}, QTime(19, 15), QTime(21, 15)};
static const IO::EventTime hautpuebungtime { {hauptuebung}, QTime(18, 00), QTime(23, 00)};
static const IO::EventTime brandhaustime { {brandhaus}, QTime(17, 15), QTime(23, 00)};
static const IO::EventTime fahrertagtime { {fahrertag, day, wbk}, QTime(7, 00), QTime(12, 00)};
static const IO::EventTime atemschutztime { {atemschutz}, QTime(19, 15), QTime(22, 15)};
static const IO::EventTime rapporttime { exerciseZugfuehrer, QTime(19, 00), QTime(21, 00)};
static const IO::EventTime neujahrstime { {neujahr}, QTime(18, 00), QTime(21, 00)};
static const IO::EventTime friedenslichttime { {friedenslicht}, QTime(17, 30), QTime(20, 00)};

static const QVector<IO::EventTime> times{ zugtime, fahrertagtime, atemschutztime, hautpuebungtime, brandhaustime, rapporttime, neujahrstime, friedenslichttime };

#endif // NAMES_HPP
