#include "uebungskartegenerator.hpp"

#include "event.h"

#include <QString>
#include <xlsxdocument.h>

UebungsKarteGenerator::UebungsKarteGenerator()
{
}

void UebungsKarteGenerator::generateUebungskarte(const QString &path)
{
    QString filename(path);
    filename.truncate(filename.lastIndexOf("."));
    filename += "_Übungskarte.xlsx";

    QList<Event*> events(m_database.getAllEvents());


    QXlsx::Document uebungsKarte;
    int index = 1;
    QDate previous;
    QXlsx::Format format;
    for(int i = 0; i<events.size(); i++)
    {
        Event* event = events[i];
        QDate date(event->startDate().date());
        QTime time(event->startDate().time());
        if(date != previous)
            index++;
        previous = date;
        uebungsKarte.write(index, 1, date.toString("dd/MM/yyyy"));
        uebungsKarte.write(index, 2, time.toString("hh.mm"));
        int col = 20;
        switch(event->eventType())
        {
        case SqlTableNames::eZug:
        {
            format.setPatternBackgroundColor(QColor(Qt::GlobalColor::green));
            QString nr(event->name());
            nr = nr[nr.indexOf(QRegExp("\\d"))];
            col = 4 + nr.toInt();
        }
            break;
        case SqlTableNames::eMaschinistenHRB:
            format.setPatternBackgroundColor(QColor(255, 127, 0)); //rgb orange
            col = 8;
            uebungsKarte.write(index, 10, event->name(), format);
            break;
        case SqlTableNames::eAtemschutz:
            format.setPatternBackgroundColor(QColor(Qt::GlobalColor::blue));
            col = 9;
            break;
        case SqlTableNames::eKader:
            format.setPatternBackgroundColor(QColor(Qt::GlobalColor::yellow));
            col = 3;
            uebungsKarte.write(index, 4, event->name(), format);
            format.setPatternBackgroundColor(QColor(Qt::GlobalColor::red));
            break;
        case SqlTableNames::eOff:
            format.setPatternBackgroundColor(QColor(Qt::GlobalColor::red));
        case SqlTableNames::eSpezialisten:
        case SqlTableNames::eZugfuehrer:
            col = 3;
            break;
        case SqlTableNames::eUof:
            format.setPatternBackgroundColor(QColor(Qt::GlobalColor::yellow));
            col = 4;
            break;
        case SqlTableNames::eKommandoZug:
            format.setPatternBackgroundColor(QColor(127, 0, 255)); //rgb violett
            col = 11;
            uebungsKarte.write(index, 12, event->name(), format);
            uebungsKarte.write(index, 13, event->name(), format);
            break;
        case SqlTableNames::eAbsturzsicherung:
            col = 14;
            break;
        case SqlTableNames::ePikettzug:
            col = 14;
            break;
        default:
            if(event->name().contains("Hauptübung", Qt::CaseInsensitive))
            {
                format.setPatternBackgroundColor(QColor(127, 0, 255)); //rgb violett
                uebungsKarte.write(index, 11, event->name(), format);
                uebungsKarte.write(index, 12, event->name(), format);
                uebungsKarte.write(index, 13, event->name(), format);
                format.setPatternBackgroundColor(QColor(Qt::GlobalColor::green));
                uebungsKarte.write(index, 5, event->name(), format);
                uebungsKarte.write(index, 6, event->name(), format);
                uebungsKarte.write(index, 7, event->name(), format);
                format.setPatternBackgroundColor(QColor(255, 127, 0)); //rgb orange
                uebungsKarte.write(index, 8, event->name(), format);
                uebungsKarte.write(index, 10, event->name(), format);
                format.setPatternBackgroundColor(QColor(Qt::GlobalColor::blue));
                uebungsKarte.write(index, 9, event->name(), format);
                format.setPatternBackgroundColor(QColor(Qt::GlobalColor::yellow));
                uebungsKarte.write(index, 4, event->name(), format);
                col = 3;
                format.setPatternBackgroundColor(QColor(Qt::GlobalColor::red)); //rgb violett
                break;
            }
            continue;
        }
        uebungsKarte.write(index, col, event->name(), format);

        if(!event->description().isEmpty())
        {
            QString desc(uebungsKarte.read(index, 14).toString());
            uebungsKarte.write(index, 14, QString(desc + event->description()));
        }
    }

    uebungsKarte.saveAs(filename);

}
