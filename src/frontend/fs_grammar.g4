// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.

grammar fs_grammar;
program : code;
code : ( instruction |for_block | pragma |declaration)+;

declaration : (input_decl | variable_decl | constant_decl | output_decl);

instruction : reg_instr | imm_instr | indep_instr | pseudo_instr | branch_instr | conv_instr | load_instr;

reg_instr : reg_opcode  operand ',' operand ',' destination;
imm_instr : imm_opcode destination ',' immediate;
load_instr: 'ldc' destination ',' FloatingPointLiteral;
branch_instr : branch_opcode operand ',' operand ',' operand;
conv_instr : conv_opcode operand ',' operand;
indep_instr : 'stop' | 'nop';

pseudo_instr : pseudo_opcode operand ',' operand  (',' operand)*;

operand : Register | Identifier;


destination: Register | Identifier;
immediate : Integer | Hexnum | Octalnum | Identifier;

float_const : FloatingPointLiteral;

reg_opcode : 'add' | 'sub' | 'mul' | 'and' | 'or' | 'satp' | 'satn';
conv_opcode: 'itf' | 'fti' | 'not' ;
imm_opcode : 'ldr';
branch_opcode: 'ble' | 'bgt' | 'beq' | 'bne';

pseudo_opcode: 'mov';


for_block: 'for('for_decl';'for_end';'(for_incr|for_dec)')' '{'code'}';
for_incr: Identifier ('++');
for_dec: Identifier ('--');
for_decl: Identifier '=' Integer;

for_end: Identifier for_end_comp_type Integer;
for_end_comp_type : ('<' | '>' | '<=' | '>=');
pragma: '#pragma ' Identifier;


variable_decl : 'let' (Register | Identifier);
constant_decl : 'const' (Register | Identifier);
input_decl : 'input' (Register | Identifier);
output_decl : 'output' (Register | Identifier);

Register: 'r' (Digit +);

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
   : '-'? ('0' .. '9') + '.' ('0' .. '9')* Exponent? | '.' ('0' .. '9') + Exponent? | ('0' .. '9') + Exponent
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