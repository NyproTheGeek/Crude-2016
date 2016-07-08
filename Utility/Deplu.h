#ifndef DEPLU_H
#define DEPLU_H

#include <QObject>

enum class DepluValue
{
    Null, Empty
};

enum class DepluType
{
    Attrib, Class, AttribArray, ClassArray
};

enum class DepluParseSymbol{
    Name,
    Value,
    OpenBracket, // '('
    CloseBracket, // ')'
    OpenBrace, // '['
    CloseBrace, // ']'
    Comma, // ','
    CommaNewLine, // ',' or '\n'
    Colon, // ':'
    BlockEnd, // '..'
    EOL,
    OBJECT
};

#endif // DEPLU_H
