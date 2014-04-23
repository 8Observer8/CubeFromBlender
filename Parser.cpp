#include "Parser.h"
#include <QStringList>

void Parser::parseData( const QString &input, QList<QVector3D> &points, QList<QVector3D> &indexes ) throw(EmptyInput, BadLine) {

    if ( input.isEmpty( ) ) {
        throw( EmptyInput( input.toStdString( ) ) );
    }

    QStringList list = input.split( "\n" );

    for ( std::size_t i = 0; i < list.size( ); ++i ) {
        // Poitns
        if ( list[i][0] == QChar( 'v' ) ) {
            QStringList listForPoints = list[i].split( " " );
            if ( listForPoints.size( ) == 4 ) {
                bool ok;
                float x = listForPoints[1].toFloat( &ok );
                if ( !ok ) {
                    throw( BadLine( list[i].toStdString(), i ) );
                }

                float y = listForPoints[2].toFloat( &ok );
                if ( !ok ) {
                    throw( BadLine( list[i].toStdString(), i ) );
                }

                float z = listForPoints[3].toFloat( &ok );
                if ( !ok ) {
                    throw( BadLine( list[i].toStdString(), i ) );
                }

                points.append( QVector3D( x, y, z ) );
            } else {
                throw( BadLine( list[i].toStdString(), i ) );
            }
        }

        // Indexes
        if ( list[i][0] == QChar( 'f' ) ) {
            QStringList listForIndexes = list[i].split( " " );
            if ( listForIndexes.size( ) == 4 ) {
                bool ok;
                float x = listForIndexes[1].toFloat( &ok );
                if ( !ok ) {
                    throw( BadLine( list[i].toStdString(), i ) );
                }

                float y = listForIndexes[2].toFloat( &ok );
                if ( !ok ) {
                    throw( BadLine( list[i].toStdString(), i ) );
                }

                float z = listForIndexes[3].toFloat( &ok );
                if ( !ok ) {
                    throw( BadLine( list[i].toStdString(), i ) );
                }

                indexes.append( QVector3D( x, y, z ) );
            } else {
                throw( BadLine( list[i].toStdString(), i ) );
            }
        }
    }
}
