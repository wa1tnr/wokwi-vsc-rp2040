( COMMENTS ARE FINE )
: decimal DECIMAL ; : hex HEX ; : dup DUP ; : drop DROP ;
decimal 99 -1 *
: spit DUP . 32 EMIT ; ( n -- )
: babble 5 spit 3 spit ." * " * spit CR ;


( blinker )

: decimal DECIMAL ; : hex HEX ; : dup DUP ; : drop DROP ;
: blinks 0 DO blink LOOP ;

( END )
