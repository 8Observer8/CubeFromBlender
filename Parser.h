#ifndef PARSER_H
#define PARSER_H

#include <QList>
#include <QVector3D>
#include <QString>

class Parser {
public:
    void parseData( const QString &input, QList<QVector3D> &points, QList<QVector3D> &indexes );
};

#endif // PARSER_H
