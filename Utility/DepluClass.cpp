#include "DepluClass.h"
#include "DepluArray.h"
#include "Exception/DepluException.h"
#include <QList>
#include <QRegularExpression>
#include <array>
#include <bitset>

DepluClass::DepluClass(QString name, QObject *parent) : QObject(parent){
}

bool DepluClass::parse(QString& depluStr){
//    using namespace std;

//    QList<int> objectStack;

//    bitset<8> flags; //

//    QMap<int, QPair<unsigned int, array<QPair<DepluParseSymbol, int>, 3>>> syntaxTree;
//    syntaxTree[1] = QPair();

//    QList<int> objectStack;
//    objectStack.append(1);

//    int stackTop = 0;
//    int lineIndex = 0;
//    int tokenCol = 0;

//    QStringList depluStrList = depluStr.split(QRegularExpression("[\'\"]"));
//    int tokenIndex = 0;

//    // Da Loop
//    while(tokenIndex != depluStrList.length()){
//        // thru the branch array
//        for(int i = 0; i < syntaxTree[objectStack[stackTop]].first; i++){
//            switch(syntaxTree[objectStack[stackTop]].second.at(i).first){
//            case(Name):
//                QRegularExpression re("^\\.+$");
//                QRegularExpressionMatch match= re.match(token);
//                if(!match.hasMatch()){
//                    /// Do cleanup
//                    /// Log error
//                    return false;
//                }
//                else{
//                    for(auto i : token){
//                        if(i == '\'' || i == '\"'){
//                            /// Do cleanup
//                            /// Log error
//                            return false;
//                        }
//                    }
//                    ///
//                }

//            case(Value):
//            case(OpenBracket):
//            case(CloseBracket):
//            case(OpenBrace):
//            case(CloseBrace):
//            case(Comma):
//            case(CommaNewLine):
//            case(Colon):
//            case(BlockEnd):
//            case(EOL):
//            case(OBJECT):
//            }
//        }
//    }
    return true;
}































