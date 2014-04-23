#ifndef EMPTYINPUT_H
#define EMPTYINPUT_H

#include "LogicError.h"

class EmptyInput : public LogicError {
public:

    EmptyInput( std::string argument ) : LogicError( argument ) {
        m_message = "Input argument is empty.";
    }
};

#endif // EMPTYINPUT_H
