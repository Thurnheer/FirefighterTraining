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

#ifndef EVENT_H
#define EVENT_H

#include <QDateTime>
#include <QObject>
#include <QString>

class Event : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QDateTime startDate READ startDate WRITE setStartDate NOTIFY startDateChanged)
    Q_PROPERTY(QDateTime endDate READ endDate WRITE setEndDate NOTIFY endDateChanged)
    Q_PROPERTY(int EventType READ eventType WRITE setEventType NOTIFY eventTypeChanged)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
public:
    explicit Event(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);


    QString description() const;
    void setDescription(const QString &description);

    QDateTime startDate() const;
    void setStartDate(const QDateTime &startDate);

    QDateTime endDate() const;
    void setEndDate(const QDateTime &endDate);

    QDate date() const { return startDate().date(); }

    int eventType() const;
    void setEventType(int eventType);

    QString location() const;
    void setLocation(const QString& location);

    QString uuid() const;
    void setUuid(const QString& uuid);

    void save();

signals:
    void nameChanged(const QString &name);
    void startDateChanged(const QDateTime &startDate);
    void endDateChanged(const QDateTime &endDate);
    void eventTypeChanged(int eventType);
    void locationChanged(const QString& location);
    void descriptionChanged(const QString& location);

private:
    void getIndexAndNr(const QString& name, QString& index, int& uebungsNr);
    QString mName;
    QString m_uuid;
    QString m_location;
    QString m_description;
    QDateTime mStartDate;
    QDateTime mEndDate;
    int m_eventType;
};

#endif
