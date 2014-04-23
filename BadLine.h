#ifndef BADLINE_H
#define BADLINE_H

#include "LogicError.h"
#include <sstream>

class BadLine : public LogicError {
public:

    BadLine( const std::string &line, int lineNum ) :
        LogicError( line ), m_lineNum( lineNum ) {
        std::ostringstream ostr;
        ostr << "Error string \"" << line << "\" at line " << lineNum;
        m_message = ostr.str( );
    }

protected:
    int m_lineNum;
};

#endif // BADLINE_H
