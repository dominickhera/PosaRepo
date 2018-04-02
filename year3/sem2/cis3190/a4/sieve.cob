identification division.
program-id. sieve.
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


procedure division.
	open input STANDARD-INPUT, output STANDARD-OUTPUT.

	stop run.
