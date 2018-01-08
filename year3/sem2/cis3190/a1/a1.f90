
program ticTacToe

	implicit none

	integer, dimension(3,3) :: TICTAC = reshape((/1,4,7,2,5,8,3,6,9 /), (/3,3/))

! 	write(*,*) 'PLAY TIC-TAC-TOE. ENTER 1-9 TO PLAY', NEW_LINE, 'hi'
	write(*,'(A)') 'PLAY TIC-TAC-TOE. ENTER 1-9 TO PLAY', &
	''//NEW_LINE('A')//'         1 | 2 | 3 ', &
	'        ---+---+---', &
	'         4 | 5 | 6 ', &
	'        ---+---+---', &
	'         7 | 8 | 9 '//NEW_LINE('A')


! 	write(*, '(A)') 'Play', &
! 	'test'


contains

! 	logical function CHKPLAY(TICTAC, MOVE)

! 		implicit none
! 		character(len=1) :: TICTAC(3,3)
! 		integer :: MOVE

! 		select case (any(TICTAC, [,MOVE]))

! 		    case(.TRUE.)
! 		        CHKPLAY = .FALSE.
! 		    case default
! 		        CHKPLAY = .TRUE.
! 		end select 

! 	end function CHKPLAY

end program ticTacToe
