// Define a grammar called Hello
grammar fs_grammar;
program : code;
code : ( instruction |for_block | pragma |declaration)+;

declaration : (input_decl | variable_decl | constant_decl | output_decl);

instruction : reg_instr | imm_instr | indep_instr | pseudo_instr | branch_instr | conv_instr | load_instr;

reg_instr : reg_opcode  operand ',' operand ',' destination;
imm_instr : imm_opcode destination ',' immediate;
load_instr: 'ldc' destination ',' FloatingPointLiteral;
branch_instr : branch_opcode operand ',' operand ',' immediate;
conv_instr : conv_opcode operand ',' operand;
indep_instr : 'stop' | 'nop';

pseudo_instr : pseudo_opcode Identifier ',' Identifier (',' Identifier)*;

operand : Identifier;
destination: Identifier;
immediate : Integer | Hexnum | Octalnum | Identifier;

float_const : FloatingPointLiteral;

reg_opcode : 'add' | 'sub' | 'mul';
conv_opcode: 'itf' | 'fti';
imm_opcode : 'ldr' ;
branch_opcode: 'ble' | 'bgt' | 'beq' | 'bne';

pseudo_opcode: 'mov';


for_block: 'for('for_decl';'for_end';'(for_incr|for_dec)')' '{'code'}';
for_incr: Identifier ('++');
for_dec: Identifier ('--');
for_decl: Identifier '=' Integer;

for_end: Identifier for_end_comp_type Integer;
for_end_comp_type : ('<' | '>' | '<=' | '>=');
pragma: '#pragma ' Identifier;


variable_decl : 'let' Identifier;
constant_decl : 'const' Identifier;
input_decl : 'input' Identifier;
output_decl : 'output' Identifier;

Identifier
   : Letter ('_' | Letter | Digit)*
   ;
Hexnum
   : '0x' HexDigit +
   ;
Integer
   : (Digit +)
   ;
Octalnum
   : ('0' .. '7') + ('o' | 'O')
   ;
fragment HexDigit
   : ('0' .. '9' | 'a' .. 'f' | 'A' .. 'F')
   ;
FloatingPointLiteral
   : ('0' .. '9') + '.' ('0' .. '9')* Exponent? | '.' ('0' .. '9') + Exponent? | ('0' .. '9') + Exponent
   ;
fragment Exponent
   : ('e' | 'E') ('+' | '-')? ('0' .. '9') +
   ;
String
   : ' \'' ('\\' . | ~ ('\\' | '\''))* '\''
   ;
fragment Letter
   : ('a' .. 'z' | 'A' .. 'Z')
   ;
fragment Digit
   : '0' .. '9'
   ;

Label
   : Identifier (':')
   ;
WS
   : (' ' | '\t' | '\n' | '\r') -> skip
   ;

BlockComment
    :   '/*' .*? '*/'
        -> skip
    ;

LineComment
    :   '//' ~[\r\n]*
        -> skip
    ;