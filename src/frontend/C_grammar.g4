/*
 [The "BSD licence"]
 Copyright (c) 2013 Sam Harwell
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:
 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
 3. The name of the author may not be used to endorse or promote products
    derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/** C 2011 grammar built from the C11 Spec */
grammar C_grammar;

compilationUnit
    :   translationUnit? EOF
    ;

primaryExpression
    :   Identifier
    |   constant
    |   StringLiteral+
    |   '(' expression ')'
    ;

unaryExpression
    :
    ('++' |  '--' )* (
    structExpression
    | primaryExpression
    |  unaryOperator unaryExpression
    | functionCallExpression)
    | arrayAccessExpression
    ;

arrayAccessExpression
    : primaryExpression ('[' primaryExpression ']')+
    ;

unaryOperator
    :  '-' | '~' | '!'
    ;

multiplicativeOperator
    : ('*'|'/'|'%')
    ;

multiplicativeExpression
    :   unaryExpression (multiplicativeOperator unaryExpression)*
    ;


additiveOperator
    : ('+'|'-')
    ;

additiveExpression
    :   multiplicativeExpression (additiveOperator multiplicativeExpression)*
    ;


shiftOperator
    : ('<<'|'>>')
    ;

shiftExpression
    :   additiveExpression (shiftOperator additiveExpression)*
    ;

relationalOperator
    : ('<'|'>'|'<='|'>=')
    ;

relationalExpression
    :   shiftExpression (relationalOperator shiftExpression)*
    ;

equalityOperator
    : ('=='| '!=')
    ;

equalityExpression
    :   relationalExpression (equalityOperator relationalExpression)*
    ;

andExpression
    :   equalityExpression ( '&' equalityExpression)*
    ;

exclusiveOrExpression
    :   andExpression ('^' andExpression)*
    ;

inclusiveOrExpression
    :   exclusiveOrExpression ('|' exclusiveOrExpression)*
    ;

logicalAndExpression
    :   inclusiveOrExpression ('&&' inclusiveOrExpression)*
    ;

logicalOrExpression
    :   logicalAndExpression ( '||' logicalAndExpression)*
    ;

conditionalExpression
    :   logicalOrExpression ('?' expression ':' conditionalExpression)?
    ;

assignmentExpression
    :   conditionalExpression
    |   unaryExpression assignmentOperator assignmentExpression
    |   DigitSequence // for
    ;

assignmentOperator
    :   '=' | '*=' | '/=' | '%=' | '+=' | '-=' | '<<=' | '>>=' | '&=' | '^=' | '|='
    ;

expression
    :   assignmentExpression (',' assignmentExpression)*
    ;

constantExpression
    :   conditionalExpression
    ;

declaration
    :   Const? typeSpecifier initDeclaratorList?
    ;


initDeclaratorList
    :   initDeclarator (',' initDeclarator)*
    ;

initDeclarator
    :   declarator ('=' initializer)?
    ;


typeSpecifier
    :   ('void'
    |   'char'
    |   'short'
    |   'int'
    |   'long'
    |   'float'
    |   'signed'
    |   'unsigned'
    )
    | structSpecifier
    |   typedefName
    ;

structExpression
    : primaryExpression ('.'  Identifier)+
    ;


structSpecifier
    : 'struct' Identifier? '{' structDeclarationList '}'
    | 'struct' Identifier
    ;

structDeclarationList
    : structDeclaration+
    ;

specifierQualifierList
    :   (typeSpecifier| Const) specifierQualifierList?
    ;

structDeclaration // The first two rules have priority order and cannot be simplified to one expression.
    : specifierQualifierList structDeclaratorList ';'
    | specifierQualifierList ';'
    ;


structDeclaratorList
    : structDeclarator (',' structDeclarator)*
    ;

structDeclarator
    : declarator
    | declarator? ':' constantExpression
    ;

declarator
    :   directDeclarator
    ;

directDeclarator
    :   Identifier
    |   '(' declarator ')'
    |   directDeclarator arrayDeclarator+
    |   directDeclarator '(' parameterTypeList ')'
    |   directDeclarator '(' identifierList? ')'
    |   Identifier ':' DigitSequence  // bit field
    ;

arrayDeclarator
    : '[' Const? assignmentExpression? ']'
    ;

nestedParenthesesBlock
    :   (   ~('(' | ')')
        |   '(' nestedParenthesesBlock ')'
        )*
    ;


parameterTypeList
    :   parameterList (',' '...')?
    ;

parameterList
    :   parameterDeclaration (',' parameterDeclaration)*
    ;

parameterDeclaration
    :   Const? typeSpecifier declarator
    |   Const? structSpecifier declarator
    ;

identifierList
    :   Identifier (',' Identifier)*
    ;

typeName
    :   specifierQualifierList ?
    ;

typedefName
    :   Identifier
    ;

initializer
    :   assignmentExpression
    |   '{' initializerList ','? '}'
    ;

functionCallExpression
    : typedefName '(' argumentExpressionList? ')'
    ;

argumentExpressionList
    :   argumentExpression (',' argumentExpression)*
    ;

argumentExpression
    :    assignmentExpression
    ;

initializerList
    :   designation? initializer (',' designation? initializer)*
    ;

designation
    :   designatorList '='
    ;

designatorList
    :   designator+
    ;

designator
    :   '[' constantExpression ']'
    |   '.' Identifier
    ;

statement
    :   expressionStatement ';'
    |   selectionStatement
    |   iterationStatement
    |   returnStatement
    |  '(' (logicalOrExpression (',' logicalOrExpression)*)? (':' (logicalOrExpression (',' logicalOrExpression)*)?)* ')' ';'
    ;

compoundStatement
    :   '{' blockItem* '}'
    ;

blockItem
    :   statement
    |   declaration ';'
    ;

expressionStatement
    :   expression?
    ;

ifContent
    :  ('{' conditionalBlockItem* '}'| conditionalBlockItem )
    ;

elseContent
    :  ('{' conditionalBlockItem* '}'| conditionalBlockItem )
    ;

conditionalBlockItem
    :   statement
    |   declaration ';'
    ;


conditionContent
    : expression
    ;

selectionStatement
    :   'if' '(' conditionContent ')' ifContent ('else' elseContent)?
    ;

iterationStatement
    :  For '(' forDeclaration ';' forExitCondition ';' forIterationExpression ')' forContent
    ;


forContent
    : ('{' forBlockItem* '}'| forBlockItem )
    ;

forBlockItem
    :   statement
    |   declaration ';'
    ;

forExitCondition
    : assignmentExpression
    ;

forDeclaration
    :   declaration
    ;

forIterationExpression
    :   assignmentExpression (',' assignmentExpression)*
    ;

returnStatement
    :
     'return' expression?';'
    ;

translationUnit
    :   externalDeclaration+
    ;

externalDeclaration
    :   functionDefinition
    |   declaration ';'
    |   ';' // stray ;
    ;

functionDefinition
    :   (Const? typeSpecifier)? declarator declarationList? compoundStatement
    ;

declarationList
    :   (declaration ';')+
    ;

Case : 'case';
Char : 'char';
Const : 'const';


Else : 'else';
Float : 'float';
For : 'for';
If : 'if';
Int : 'int';
Long : 'long';
Return : 'return';
Short : 'short';
Signed : 'signed';
Typedef : 'typedef';
Unsigned : 'unsigned';
Void : 'void';
Volatile : 'volatile';
While : 'while';




LeftParen : '(';
RightParen : ')';
LeftBracket : '[';
RightBracket : ']';
LeftBrace : '{';
RightBrace : '}';

Less : '<';
LessEqual : '<=';
Greater : '>';
GreaterEqual : '>=';
LeftShift : '<<';
RightShift : '>>';

Plus : '+';
PlusPlus : '++';
Minus : '-';
MinusMinus : '--';
Star : '*';
Div : '/';
Mod : '%';

And : '&';
Or : '|';
AndAnd : '&&';
OrOr : '||';
Caret : '^';
Not : '!';
Tilde : '~';

Question : '?';
Colon : ':';
Semi : ';';
Comma : ',';

Assign : '=';
// '*=' | '/=' | '%=' | '+=' | '-=' | '<<=' | '>>=' | '&=' | '^=' | '|='
StarAssign : '*=';
DivAssign : '/=';
ModAssign : '%=';
PlusAssign : '+=';
MinusAssign : '-=';
LeftShiftAssign : '<<=';
RightShiftAssign : '>>=';
AndAssign : '&=';
XorAssign : '^=';
OrAssign : '|=';

Equal : '==';
NotEqual : '!=';

Arrow : '->';
Dot : '.';
Ellipsis : '...';

Identifier
    :   IdentifierNondigit
        (   IdentifierNondigit
        |   Digit
        )*
    ;

fragment
IdentifierNondigit
    :   Nondigit
    |   UniversalCharacterName
    //|   // other implementation-defined characters...
    ;

fragment
Nondigit
    :   [a-zA-Z_]
    ;

fragment
Digit
    :   [0-9]
    ;

fragment
UniversalCharacterName
    :   '\\u' HexQuad
    |   '\\U' HexQuad HexQuad
    ;

fragment
HexQuad
    :   HexadecimalDigit HexadecimalDigit HexadecimalDigit HexadecimalDigit
    ;


constant
    :   ('-')? IntegerConstant
    |   ('-')? FloatingConstant
    |   CharacterConstant
    ;


IntegerConstant
    :   DecimalConstant IntegerSuffix?
    |   OctalConstant IntegerSuffix?
    |   HexadecimalConstant IntegerSuffix?
    |	BinaryConstant
    ;

fragment
BinaryConstant
	:	'0' [bB] [0-1]+
	;

fragment
DecimalConstant
    :   NonzeroDigit Digit*
    ;

fragment
OctalConstant
    :   '0' OctalDigit*
    ;

fragment
HexadecimalConstant
    :   HexadecimalPrefix HexadecimalDigit+
    ;

fragment
HexadecimalPrefix
    :   '0' [xX]
    ;

fragment
NonzeroDigit
    :   [1-9]
    ;

fragment
OctalDigit
    :   [0-7]
    ;

fragment
HexadecimalDigit
    :   [0-9a-fA-F]
    ;

fragment
IntegerSuffix
    :   UnsignedSuffix LongSuffix?
    |   UnsignedSuffix LongLongSuffix
    |   LongSuffix UnsignedSuffix?
    |   LongLongSuffix UnsignedSuffix?
    ;

fragment
UnsignedSuffix
    :   [uU]
    ;

fragment
LongSuffix
    :   [lL]
    ;

fragment
LongLongSuffix
    :   'll' | 'LL'
    ;


FloatingConstant
    :   DecimalFloatingConstant
    |   HexadecimalFloatingConstant
    ;

fragment
DecimalFloatingConstant
    :   FractionalConstant ExponentPart? FloatingSuffix?
    |   DigitSequence ExponentPart FloatingSuffix?
    ;

fragment
HexadecimalFloatingConstant
    :   HexadecimalPrefix (HexadecimalFractionalConstant | HexadecimalDigitSequence) BinaryExponentPart FloatingSuffix?
    ;

fragment
FractionalConstant
    :   DigitSequence? '.' DigitSequence
    |   DigitSequence '.'
    ;

fragment
ExponentPart
    :   [eE] Sign? DigitSequence
    ;

fragment
Sign
    :   [+-]
    ;

DigitSequence
    :   Digit+
    ;

fragment
HexadecimalFractionalConstant
    :   HexadecimalDigitSequence? '.' HexadecimalDigitSequence
    |   HexadecimalDigitSequence '.'
    ;

fragment
BinaryExponentPart
    :   [pP] Sign? DigitSequence
    ;

fragment
HexadecimalDigitSequence
    :   HexadecimalDigit+
    ;

fragment
FloatingSuffix
    :   [flFL]
    ;


CharacterConstant
    :   '\'' CCharSequence '\''
    |   'L\'' CCharSequence '\''
    |   'u\'' CCharSequence '\''
    |   'U\'' CCharSequence '\''
    ;

fragment
CCharSequence
    :   CChar+
    ;

fragment
CChar
    :   ~['\\\r\n]
    |   EscapeSequence
    ;

fragment
EscapeSequence
    :   SimpleEscapeSequence
    |   OctalEscapeSequence
    |   HexadecimalEscapeSequence
    |   UniversalCharacterName
    ;

fragment
SimpleEscapeSequence
    :   '\\' ['"?abfnrtv\\]
    ;

fragment
OctalEscapeSequence
    :   '\\' OctalDigit OctalDigit? OctalDigit?
    ;

fragment
HexadecimalEscapeSequence
    :   '\\x' HexadecimalDigit+
    ;

StringLiteral
    :   EncodingPrefix? '"' SCharSequence? '"'
    ;

fragment
EncodingPrefix
    :   'u8'
    |   'u'
    |   'U'
    |   'L'
    ;

fragment
SCharSequence
    :   SChar+
    ;

fragment
SChar
    :   ~["\\\r\n]
    |   EscapeSequence
    |   '\\\n'   // Added line
    |   '\\\r\n' // Added line
    ;

ComplexDefine
    :   '#' Whitespace? 'define'  ~[#\r\n]*
        -> skip
    ;

IncludeDirective
    :   '#' Whitespace? 'include' Whitespace? (('"' ~[\r\n]* '"') | ('<' ~[\r\n]* '>' )) Whitespace? Newline
        -> skip
    ;

// ignore the following asm blocks:
/*
    asm
    {
        mfspr x, 286;
    }
 */
AsmBlock
    :   'asm' ~'{'* '{' ~'}'* '}'
	-> skip
    ;

// ignore the lines generated by c preprocessor
// sample line : '#line 1 "/home/dm/files/dk1.h" 1'
LineAfterPreprocessing
    :   '#line' Whitespace* ~[\r\n]*
        -> skip
    ;

LineDirective
    :   '#' Whitespace? DecimalConstant Whitespace? StringLiteral ~[\r\n]*
        -> skip
    ;

PragmaDirective
    :   '#' Whitespace? 'pragma' Whitespace ~[\r\n]*
        -> skip
    ;

Whitespace
    :   [ \t]+
        -> skip
    ;

Newline
    :   (   '\r' '\n'?
        |   '\n'
        )
        -> skip
    ;

BlockComment
    :   '/*' .*? '*/'
        -> skip
    ;

LineComment
    :   '//' ~[\r\n]*
        -> skip
    ;