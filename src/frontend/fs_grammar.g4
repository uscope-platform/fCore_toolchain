// Define a grammar called Hello
grammar fs_grammar;
program : code;
code : ( instruction |for_block | pragma | variable_decl | constant_decl)+;

instruction : reg_instr | imm_instr | indep_instr | pseudo_instr | branch_instr| imm_alu_instr;

reg_instr : reg_opcode  operand ',' operand ',' destination;
imm_instr : imm_opcode destination ',' (Integer | Hexnum | Octalnum | Identifier);
imm_alu_instr : imm_alu_opcode operand ',' (Integer | Hexnum | Octalnum | Identifier) ',' destination;
branch_instr : branch_opcode operand ',' operand ',' immediate;
indep_instr : 'stop' | 'nop';

pseudo_instr : pseudo_opcode Identifier ',' Identifier (',' Identifier)*;

operand : ( Identifier);
destination: (Identifier);
reg_opcode : 'add' | 'sub' | 'mul' | 'mac' | 'shl' | 'shr' | 'sar';
imm_alu_opcode: 'addi' | 'subi' | 'muli' | 'maci' | 'shli' | 'shri' | 'sari';
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

immediate : Integer | Hexnum | Octalnum;


variable_decl : 'let' Identifier;
constant_decl : 'const' Identifier;
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