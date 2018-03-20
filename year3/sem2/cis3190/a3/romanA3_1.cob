IDENTIFICATION DIVISION.
PROGRAM-ID. ROMANNUMERALS.
ENVIRONMENT DIVISION.
INPUT-OUTPUT SECTION.
FILE-CONTROL.
	SELECT STANDARD-INPUT ASSIGN TO KEYBOARD.
	SELECT STANDARD-OUTPUT ASSIGN TO DISPLAY.

DATA DIVISION.
FILE SECTION.
FD STANDARD-INPUT.
	01 STDIN-RECORD	PICTURE X(80).
FD STANDARD-OUTPUT.
	01 STDOUT-RECORD PICTURE X(80).
WORKING-STORAGE SECTION.
77	N    PICTURE S99 USAGE IS COMPUTATIONAL.
77	TEMP PICTURE S9(8) USAGE IS COMPUTATIONAL.
77	RET  PICTURE S9 USAGE IS COMPUTATIONAL-3.
01	ARRAY-AREA.
	02 R PICTURE X(1) OCCURS 30 TIMES.
01	INPUT-AREA.
	02 IN-R   PICTURE X(1).
	02 FILLER PICTURE X(79).
01	TITLE-LINE.
	02 FILLER PICTURE X(11) VALUE SPACES.
	02 FILLER PICTURE X(24) VALUE 'ROMAN NUMBER EQUIVALENTS'.
01	UNDERLINE-1.
	02 FILLER PICTURE X(45) VALUE
		' --------------------------------------------'.
01	COL-HEADS.
	02 FILLER PICTURE X(9) VALUE SPACES.
	02 FILLER PICTURE X(12) VALUE 'ROMAN NUMBER'.
	02 FILLER PICTURE X(13) VALUE SPACES.
	02 FILLER PICTURE X(11) VALUE 'DEC. EQUIV.'.
01	UNDERLINE-2.
	02	FILLER PICTURE X(45) VALUE
		' ------------------------------   -----------'.
01	PRINT-LINE.
	02 FILLER PICTURE X VALUE SPACE.
	02 OUT-R PICTURE X(30).
	02 FILLER PICTURE X(3) VALUE SPACES.
	02 OUT-EQ PICTURE Z(9).

PROCEDURE DIVISION.
	OPEN INPUT STANDARD-INPUT, OUTPUT STANDARD-OUTPUT.
	WRITE STDOUT-RECORD FROM TITLE-LINE AFTER ADVANCING 0 LINES. 
	WRITE STDOUT-RECORD FROM UNDERLINE-1 AFTER ADVANCING 1 LINE. 
	WRITE STDOUT-RECORD FROM COL-HEADS AFTER ADVANCING 1 LINE. 
	WRITE STDOUT-RECORD FROM UNDERLINE-2 AFTER ADVANCING 1 LINE. 
L1.	MOVE 1 TO N. MOVE SPACES TO ARRAY-AREA.
L2.	READ STANDARD-INPUT INTO INPUT-AREA AT END GO TO B3.
	MOVE IN-R TO R(N).
	IF IN-R IS EQUAL TO SPACE GO TO B1.
	ADD 1 TO N. GO TO L2.
B1.	SUBTRACT 1 FROM N.
	CALL "conv" USING ARRAY-AREA, N, RET, TEMP.
	MOVE 1 TO RET.
	GO TO B2, L1 DEPENDING ON RET.
B2.	MOVE TEMP TO OUT-EQ. MOVE ARRAY-AREA TO OUT-R.
	WRITE STDOUT-RECORD FROM PRINT-LINE AFTER ADVANCING 1 LINE. 
	GO TO L1.
B3.	CLOSE STANDARD-INPUT, STANDARD-OUTPUT.
	STOP RUN.
	