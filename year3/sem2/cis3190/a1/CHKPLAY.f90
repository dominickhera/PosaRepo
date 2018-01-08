
    LOGICAL FUNCTION CHKPLAY(TICTAC,MOVE)
    CHARACTER * 1 TICTAC(3,3)
    INTEGER MOVE
    GO TO (401,402,403,404,405,406,407,408,409) MOVE
401 IF (TICTAC(1,1) .EQ. “ “ GOTO 411
    GO TO 410
402 IF (TICTAC(1,2) .EQ. “ “ GOTO 411
    GO TO 410
403 IF (TICTAC(1,3) .EQ. “ “ GOTO 411
    GO TO 410
404 IF (TICTAC(2,1) .EQ. “ “ GOTO 411
    GO TO 410
405 IF (TICTAC(2,2) .EQ. “ “ GOTO 411
    GO TO 410
406 IF (TICTAC(2,3) .EQ. “ “ GOTO 411
    GO TO 410
407 IF (TICTAC(3,1) .EQ. “ “ GOTO 411
    GO TO 410
408 IF (TICTAC(3,2) .EQ. “ “ GOTO 411
    GO TO 410
409 IF (TICTAC(3,3) .EQ. “ “ GOTO 411
410 CHKPLAY = .FALSE.
    GOTO 412
411 CHKPLAY = .TRUE.
412 END



!gets tic tac toe board, gets the users move (number)
!checks number against that spot in the database (tictac)
!if that number is empty, otherwise  

!user any to check if that number 

logical function CHKPLAY(TICTAC, MOVE)

implicit none
character(len=1) :: TICTAC(3,3)
integer :: MOVE

select case (any(TICTAC, [,MOVE]))

    case(.TRUE.)
        CHKPLAY = .FALSE.
    case default
        CHKPLAY = .TRUE.
end select 

end function CHKPLAY