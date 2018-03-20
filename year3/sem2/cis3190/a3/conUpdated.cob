*> IDENTIFICATION DIVISION.
identification division.
*> PROGRAM-ID. conv.
program-id. conv.
*> ENVIRONMENT DIVISION.
environment division.
*> INPUT-OUTPUT SECTION.
input-output section.
*> FILE-CONTROL.
file-control.
	select STANDARD-OUTPUT assign to DISPLAY.

data division.
file section.
fd STANDARD-OUTPUT.
	01 STDOUT-RECORD pic X(80).

*> WORKING-STORAGE SECTION.
working-storage section.
77 I pic S99 USAGE IS COMPUTATIONAL.
77 PREV pic S9(8) USAGE IS COMPUTATIONAL.
77 D pic S9(4) USAGE IS COMPUTATIONAL.
01 ERROR-MESS.
	02 FILLER pic X(22) value ' ILLEGAL ROMAN NUMERAL'.

linkage section.
77 M    pic S99 USAGE IS COMPUTATIONAL.
77 ERR  pic S9 USAGE IS COMPUTATIONAL-3.
77 SUM1 pic S9(8) USAGE IS COMPUTATIONAL.
01 ARRAY-AREA.
	02 S pic X(1) occurs 30 times.

procedure division using ARRAY-AREA, M, ERR, SUM1.
	move 0 TO SUM1. move 1001 to PREV.
	*> move 1 to ERR. 
	perform LOOP
		varying I from 1 by 1
		until i is greater than M.
		
	*> end-perform.
	move 1 to ERR. perform B8.
	*> GO TO B8.
	*> MOVE D TO PREV.
LOOP.
	*> evaluate S(I)
	if S(I) is equal to 'I'
		move 1 to D
	else if S(I) is equal to 'V' 
		move 5 to D
	else if S(I) is equal to 'X' 
		move 10 to D
	else if S(I) is equal to 'L' 
		move 50 to D
	else if S(I) is equal to 'C'
		move 100 to D
	else if S(I) is equal to 'D'
		move 500 to D
	else if S(I) is equal to 'M'
		move 1000 to D
	else
		*> write STDOUT-RECORD from 'Test'
		go to B7
	

	add D to SUM1.
	if D is greater than PREV
		compute SUM1 = SUM1 - 2 * PREV
	


*> END-LOOP 
move D to PREV.
B7. open output STANDARD-OUTPUT.
	write STDOUT-RECORD from ERROR-MESS
		after advancing 1 line.
	move 2 to ERR. close STANDARD-OUTPUT.
B8. goback.
