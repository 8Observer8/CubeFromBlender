#ifndef LOGICERROR_H
#define LOGICERROR_H

#include <stdexcept>

class LogicError : public std::logic_error {
public:

    LogicError( std::string argument ) : std::logic_error( "" ), m_argument( argument ) {

    }

    virtual const char *what( ) const throw () {
        return m_message.c_str( );
    }

    virtual ~LogicError( ) throw () {

    }

protected:
    std::string m_argument;
    std::string m_message;
};

#endif // LOGICERROR_H
