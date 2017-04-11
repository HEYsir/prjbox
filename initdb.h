/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
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
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
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

#ifndef INITDB_H
#define INITDB_H

#include <QtSql>
#include <QVariant>

void addPrj(QSqlQuery &q, const QString &no, const QString &con, const QString &code, const QString &prj, const QString &dev, const QString &oa,
                const QString &refcode, const QString &refprj, const QString &inheritcode, const QString &inheritprj, int rating)
{
    q.addBindValue(no);
    q.addBindValue(con);
    q.addBindValue(code);
    q.addBindValue(prj);
    q.addBindValue(dev);
    q.addBindValue(oa);
    q.addBindValue(refcode);
    q.addBindValue(refprj);
    q.addBindValue(inheritcode);
    q.addBindValue(inheritprj);
    q.addBindValue(rating);
    q.exec();
}

QSqlError initDb()
{
    QString dbFileName = "localprj.db";
#if 0
    QFile dbFile(dbFileName);
    if (false == dbFile.open(QIODevice::Append))
    {
        return QString::fromLocal8Bit("打开数据库文件失败。");
    }
    dbFile.close();
#endif
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbFileName);

    if (!db.open())
        return db.lastError();

    QStringList tables = db.tables();
    if (tables.contains("prjinfo", Qt::CaseInsensitive))
       return QSqlError();

    QSqlQuery q;
    if (!q.exec(QLatin1String("create table prjinfo(id integer primary key, no varchar, con varchar, code varchar, prj varchar, dev varchar, oa varchar,"
                              "refcode varchar, refprj varchar, inheritcode varchar, inheritprj varchar, rating integer)")))
        return q.lastError();

    if (!q.prepare(QLatin1String("insert into prjinfo(no, con, code, prj, dev, oa, refcode, refprj, inheritcode, inheritprj, rating) values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")))
        return q.lastError();
    addPrj(q, QLatin1String("DZ1001"), QLatin1String("数据库创建测试"), QLatin1String("svn:\\bbb"), QLatin1String("svn:\\aaa"), "", "", "", "", "", "", 3);

    return QSqlError();

}

#endif // INITDB_H
