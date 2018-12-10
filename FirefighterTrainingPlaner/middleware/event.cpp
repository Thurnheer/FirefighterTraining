/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Quick Controls module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "event.h"
#include <QString>
#include <qsqlquery.h>
#include <qdebug.h>
#include <QSqlError>
#include <QRegExp>

//------------------------------------------------------------------------------------------------
//
Event::Event(QObject *parent)
: QObject(parent)
, m_uuid()
{
}

//------------------------------------------------------------------------------------------------
//
QString Event::name() const
{
    return mName;
}

//------------------------------------------------------------------------------------------------
//
void Event::setName(const QString &name)
{
    if (name != mName) {
        mName = name;
        emit nameChanged(mName);
    }
}

//------------------------------------------------------------------------------------------------
//
QString Event::uuid() const
{
    return m_uuid;
}

//------------------------------------------------------------------------------------------------
//
void Event::setUuid(const QString& uuid)
{
    m_uuid = uuid;
}

//------------------------------------------------------------------------------------------------
//
QString Event::description() const
{
    return m_description;
}

//------------------------------------------------------------------------------------------------
//
void Event::setDescription(const QString &description)
{
    if (description != m_description) {
        m_description = description;
        emit descriptionChanged(m_description);
    }
}

//------------------------------------------------------------------------------------------------
//
QString Event::location() const
{
    return m_location;
}

//------------------------------------------------------------------------------------------------
//
void Event::setLocation(const QString& location)
{
    if (location != m_location) {
        m_location = location;
        emit locationChanged(m_location);
    }
}

//------------------------------------------------------------------------------------------------
//
QDateTime Event::startDate() const
{
    return mStartDate;
}

//------------------------------------------------------------------------------------------------
//
void Event::setStartDate(const QDateTime &startDate)
{
    if (startDate != mStartDate) {
        mStartDate = startDate;
        emit startDateChanged(mStartDate);
    }
}

//------------------------------------------------------------------------------------------------
//
int Event::eventType() const
{
    return m_eventType;
}

//------------------------------------------------------------------------------------------------
//
void Event::setEventType(int eventType)
{
    m_eventType = eventType;
}

//------------------------------------------------------------------------------------------------
//
QDateTime Event::endDate() const
{
    return mEndDate;
}

//------------------------------------------------------------------------------------------------
//
void Event::setEndDate(const QDateTime &endDate)
{
    if (endDate != mEndDate) {
        mEndDate = endDate;
        emit endDateChanged(mEndDate);
    }
}

//------------------------------------------------------------------------------------------------
//
void Event::getIndexAndNr(const QString& name, QString& index, int& uebungsNr)
{
    int cindex = name.lastIndexOf(QRegExp("\\d"));
    if(cindex > 0)
    {
        if(name.at(cindex-1) == '/')
        {
            index = name.at(cindex-2);
        }
        uebungsNr = QString(name.at(cindex)).toInt();
    }
}

//------------------------------------------------------------------------------------------------
//
void Event::save()
{
    // TODO use update to update database instead of insert
    QSqlQuery query;
    QString einteilungsIndex = "";
    int uebungsNr = 0;
    getIndexAndNr(mName, einteilungsIndex, uebungsNr);
    // We store the time as seconds because it's easier to query.
    query.exec(QString::fromLatin1("insert into Event values('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9')").arg(mName, QString::number(m_eventType),
                                                                    einteilungsIndex,
                                                                    QString::number(uebungsNr),
                                                                    mStartDate.date().toString("yyyy-MM-dd"),
                                                                    QString::number(mStartDate.time().msecsSinceStartOfDay()/1000),
                                                                    mEndDate.date().toString("yyyy-MM-dd"),
                                                                    QString::number(mEndDate.time().msecsSinceStartOfDay()/1000),
                                                                    m_uuid));
   // qDebug() << query.lastError();
}
