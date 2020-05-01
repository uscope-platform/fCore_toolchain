// Define a grammar called Hello
grammar fs_grammar;
program : code;
code : (reg_instr | imm_instr | indep_instr | for_block | pragma)+;

reg_instr : reg_opcode  fcore_reg ',' fcore_reg ',' fcore_reg;
imm_instr : imm_opcode fcore_reg ',' Integer | Hexnum | Octalnum;
indep_instr : 'stop' | 'nop';

reg_opcode : 'add' | 'sub' | 'mul' | 'mac' | 'shl' | 'shr' | 'sal' | 'sar' | 'mov';

imm_opcode : 'ldr' ;

fcore_reg : 'r0' | 'r1' | 'r2' | 'r3' | 'r4' | 'r5' | 'r6' | 'r7'
         | 'r8' | 'r9' | 'r10' | 'r11' | 'r12' | 'r13' | 'r14' | 'r15';

for_block: 'for('for_decl';'for_end';'(for_incr|for_dec)')' '{'code'}';
for_incr: Identifier ('++');
for_dec: Identifier ('--');
for_decl: Identifier '=' Integer;

for_end: Identifier for_end_comp_type Integer;
for_end_comp_type : ('<' | '>' | '<=' | '>=');
pragma: '#pragma ' Identifier;
Identifier
   : Letter ('_' | Letter | Digit)*
   ;
Hexnum
   : HexDigit + ('h' | 'H')
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