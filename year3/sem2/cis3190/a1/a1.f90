
program ticTacToe

	implicit none

! 	integer :: playerMove
! 	integer ,dimension(3,3) :: TICTAC = reshape((/1,4,7,2,5,8,3,6,9 /), (/3,3/))
! ! 	write(*,*) 'TICTAC should be', TICTAC(2,3)
! ! 	write(*,*) 'PLAY TIC-TAC-TOE. ENTER 1-9 TO PLAY', NEW_LINE, 'hi'
! 	write(*,'(A)') 'PLAY TIC-TAC-TOE. ENTER 1-9 TO PLAY', &
! 	''//NEW_LINE('A')//'         1 | 2 | 3 ', &
! 	'        ---+---+---', &
! 	'         4 | 5 | 6 ', &
! 	'        ---+---+---', &
! 	'         7 | 8 | 9 '//NEW_LINE('A')

! 	playerMove = getMove()
! 	write(*,*) 'Move is', playerMove

	call playTicTacToe()
	


contains

	subroutine playTicTacToe()

		integer :: playerMove
		character ,dimension(3,3) :: TICTAC = reshape((/' ',' ',' ',' ',' ',' ',' ',' ',' ' /), (/3,3/))
! 		(/'1','4','7','2','5','8','3','6','9' /)

! 	write(*,*) 'TICTAC should be', TICTAC(2,3)
! 	write(*,*) 'PLAY TIC-TAC-TOE. ENTER 1-9 TO PLAY', NEW_LINE, 'hi'
		write(*,'(A)') 'PLAY TIC-TAC-TOE. ENTER 1-9 TO PLAY', &
		''//NEW_LINE('A')//'         1 | 2 | 3 ', &
		'        ---+---+---', &
		'         4 | 5 | 6 ', &
		'        ---+---+---', &
		'         7 | 8 | 9 '//NEW_LINE('A')

		playerMove = getMove(TICTAC)
		write(*,*) 'Move is', playerMove
		select case (playerMove)
			case (1)
				TICTAC(1,1) = 'X'
! 				write(*,*) '1,1'
			case (2)
				TICTAC(1,2) = 'X'
! 				write(*,*) '1,2'
			case (3)
				TICTAC(1,3) = 'X'
! 				write(*,*) '1,3'
			case (4)
				TICTAC(2,1) = 'X'
! 				write(*,*) '2,1'
			case (5)
				TICTAC(2,2) = 'X'
! 				write(*,*) '2,2'
			case (6)
				TICTAC(2,3) = 'X'
! 				write(*,*) '2,3'
			case (7)
				TICTAC(3,1) = 'X'
! 				write(*,*) '3,1'
			case (8)
				TICTAC(3,2) = 'X'
! 				write(*,*) '3,2'
			case (9)
				TICTAC(3,3) = 'X'
! 				write(*,*) '3,3'
			case default
				write(*,*) 'Error Occured'
		end select
		write(*,*) 'After your move...'
		call showBoard(TICTAC)
		return 
! 		if (CHKPLAY(TICTAC, playerMove) == .FALSE.) then 



	end subroutine playTicTacToe

	subroutine showBoard(TICTAC)
		character(len=1) :: TICTAC(3,3)
		write(*,*) '        ',TICTAC(1,1),' | ',TICTAC(1,2),' | ',TICTAC(1,3),' '//NEW_LINE('A'), &
		'        ---+---+---'//NEW_LINE('A'), &
		'         ',TICTAC(2,1),' | ',TICTAC(2,2),' | ',TICTAC(2,3),' '//NEW_LINE('A'), &
		'        ---+---+---'//NEW_LINE('A'), &
		'         ',TICTAC(3,1),' | ',TICTAC(3,2),' | ',TICTAC(3,3),' '//NEW_LINE('A')

		return

	end subroutine showBoard

! 	integer function pickMove(TICTAC)

! 		integer :: htop,hmiddle,hbottom

! 		htop = count(TICTAC [,1])
! 		hmiddle = count(TICTAC [,2])
! 		hbottom = count(TICTAC [,3])

! 	end function pickMove

	integer function getMove(TICTAC)

		implicit none

		integer :: move
		character(len=1) :: TICTAC(3,3)
! 		integer, intent(inout) ,dimension(TICTAC) :: Array

		do 
			write(*,*) 'Your Move?'
			read(*,*) move
! 			if(move > 0 .AND. move < 10) exit
			if(move > 0 .AND. move < 10 .and. CHKPLAY(TICTAC, move) .eqv. .TRUE.) exit
			write(*,*) 'Error, Please Try Again'
		end do

		getMove = move

	end function getMove


	logical function CHKPLAY(TICTAC, MOVE)

		implicit none
! 		character, dimension(3,3) :: TICTAC
		character(len=1) :: TICTAC(3,3)
		integer, intent(in) :: MOVE

! 		write(*,*) 'input is ', MOVE
		select case (MOVE)
			case(1)
				if(TICTAC(1,1) == ' ') then
					CHKPLAY = .TRUE.
				else
					CHKPLAY = .FALSE.
				endif
			case (2)
				if(TICTAC(1,3) == ' ') then
					CHKPLAY = .TRUE.
				else
					CHKPLAY = .FALSE.
				endif
			case (3)
				if(TICTAC(1,3) == ' ') then
					CHKPLAY = .TRUE.
				else
					CHKPLAY = .FALSE.
				endif
			case (4)
				if(TICTAC(2,1) == ' ') then
					CHKPLAY = .TRUE.
				else
					CHKPLAY = .FALSE.
				endif
			case (5)
				if(TICTAC(2,2) == ' ') then
					CHKPLAY = .TRUE.
				else
					CHKPLAY = .FALSE.
				endif
			case (6)
				if(TICTAC(2,3) == ' ') then
					CHKPLAY = .TRUE.
				else
					CHKPLAY = .FALSE.
				endif
			case (7)
				if(TICTAC(3,1) == ' ') then
					CHKPLAY = .TRUE.
				else
					CHKPLAY = .FALSE.
				endif
			case (8)
				if(TICTAC(3,2) == ' ') then
					CHKPLAY = .TRUE.
				else
					CHKPLAY = .FALSE.
				endif
			case (9)
				if(TICTAC(3,3) == ' ') then
					CHKPLAY = .TRUE.
				else
					CHKPLAY = .FALSE.
				endif
		    case default
		        CHKPLAY = .FALSE.
		end select 
! 		return
	end function CHKPLAY


! logical function same(TICTAC, )

! end function same



end program ticTacToe
