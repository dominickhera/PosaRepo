identification division.
program-id. ROMANNUMERALS.
environment division.
input-output section.
file-control.
	select STANDARD-INPUT assign to KEYBOARD.
	select STANDARD-OUTPUT assign to DISPLAY.

data division.
file section.
fd STANDARD-INPUT.
	01 STDIN-RECORD	pic X(80).
fd STANDARD-OUTPUT.
	01 STDOUT-RECORD pic X(80).
working-storage section.
77	N    pic S99 usage is comp.
77	TEMP pic S9(8) usage is comp.
77	RET  pic S9 usage is comp-3.
01	ARRAY-AREA.
	02 R pic X(1) occurs 30 times.
01	INPUT-AREA.
	02 IN-R   pic X(1).
	02 FILLER pic X(79).
01	TITLE-LINE.
	02 FILLER pic X(11) value SPACES.
	02 FILLER pic X(24) value 'ROMAN NUMBER EQUIVALENTS'.
01	UNDERLINE-1.
	02 FILLER pic X(45) value
		' --------------------------------------------'.
01	COL-HEADS.
	02 FILLER pic X(9) value SPACES.
	02 FILLER pic X(12) value 'ROMAN NUMBER'.
	02 FILLER pic X(13) value SPACES.
	02 FILLER pic X(11) value 'DEC. EQUIV.'.
01	UNDERLINE-2.
	02 FILLER pic X(45) value
		' ------------------------------   -----------'.
01	PRINT-LINE.
	02 FILLER pic X value SPACE.
	02 OUT-R pic X(30).
	02 FILLER pic X(3) value SPACES.
	02 OUT-EQ pic Z(9).

procedure division.
	open input STANDARD-INPUT, output STANDARD-OUTPUT.
	write STDOUT-RECORD from TITLE-LINE after advancing 0 lines. 
	write STDOUT-RECORD from UNDERLINE-1 after advancing 1 line. 
	write STDOUT-RECORD from COL-HEADS after advancing 1 line. 
	write STDOUT-RECORD from UNDERLINE-2 after advancing 1 line. 
L1.	move 1 to N. move SPACES to ARRAY-AREA.
L2.	read STANDARD-INPUT into INPUT-AREA at end perform B3.
	move IN-R to R(N).
	if IN-R is equal to SPACE
		perform B1.
	add 1 to N. perform L2.
B1.	subtract 1 from N.
	call "conv" using ARRAY-AREA, N, RET, TEMP.
	move 1 to RET.
	evaluate RET
		when 1 perform B2
		when 0 perform L1.
	
B2.	move TEMP to OUT-EQ. move ARRAY-AREA to OUT-R.
	write STDOUT-RECORD from PRINT-LINE after advancing 1 line. 
	go to L1.
B3.	close STANDARD-INPUT, STANDARD-OUTPUT.
	stop run.
