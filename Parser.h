#ifndef PARSER_H
#define PARSER_H

#include <QList>
#include <QVector3D>
#include <QString>
#include "EmptyInput.h"
#include "BadLine.h"

class Parser {
public:
    void parseData( const QString &input, QList<QVector3D> &points, QList<QVector3D> &indexes )
    throw(EmptyInput, BadLine);
};

#endif // PARSER_H
