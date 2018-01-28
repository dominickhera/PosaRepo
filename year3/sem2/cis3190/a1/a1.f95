
program ticTacToe

    implicit none

    character(len=1) :: WINNER
    logical :: OVER
    character ,dimension(3,3) :: TICTAC = reshape((/' ',' ',' ',' ',' ',' ',' ',' ',' ' /), (/3,3/))

    write(*,'(A)') 'PLAY TIC-TAC-TOE. ENTER 1-9 TO PLAY', &
    ''//NEW_LINE('A')//'         1 | 2 | 3 ', &
    '        ---+---+---', &
    '         4 | 5 | 6 ', &
    '        ---+---+---', &
    '         7 | 8 | 9 '//NEW_LINE('A')

    do
        call playTicTacToe(TICTAC)
        call CHKOVR(TICTAC, OVER, WINNER)
        if(OVER .eqv. .TRUE.) exit
        call pickMove(TICTAC)
        write(*,*) 'After my move...'
        call showBoard(TICTAC)
        call CHKOVR(TICTAC, OVER, WINNER)
        if(OVER .eqv. .TRUE.) exit
    end do

    if (WINNER == 'D') then
        write(*,*) 'Match is a draw.'
    else
        write(*,*) 'Winner is ', WINNER
    endif


contains

    subroutine playTicTacToe(TICTAC)

        integer :: playerMove
        character(len=1) :: TICTAC(3,3)

        playerMove = getMove(TICTAC)

        select case (playerMove)
            case (1)
                TICTAC(1,1) = 'X'
            case (2)
                TICTAC(1,2) = 'X'
            case (3)
                TICTAC(1,3) = 'X'
            case (4)
                TICTAC(2,1) = 'X'
            case (5)
                TICTAC(2,2) = 'X'
            case (6)
                TICTAC(2,3) = 'X'
            case (7)
                TICTAC(3,1) = 'X'
            case (8)
                TICTAC(3,2) = 'X'
            case (9)
                TICTAC(3,3) = 'X'
            case default
                write(*,*) 'Error Occured'
        end select
        write(*,*) 'After your move...'
        call showBoard(TICTAC)

        return 

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

    subroutine pickMove(TICTAC)

        character(len=1) :: TICTAC(3,3)
        integer :: i,sumB,b1,b2,b3,b4,b5,b6,b7,b8,b9,w1,w2,w3,w4,w5,w6,w7,w8

        b1 = 0
        b2 = 0
        b3 = 0
        b4 = 0
        b5 = 0
        b6 = 0
        b7 = 0
        b8 = 0
        b9 = 0
        sumB = 0

        if (TICTAC(1,1) == 'X') then
            b1 = 4
        elseif (TICTAC(1,1) == 'O') then
            b1 = 1
        endif

        if (TICTAC(1,2) == 'X') then
            b2 = 4
        elseif (TICTAC(1,2) == 'O') then
            b2 = 1
        endif

        if (TICTAC(1,3) == 'X') then
            b3 = 4
        elseif (TICTAC(1,3) == 'O') then
            b3 = 1
        endif

        if (TICTAC(2,1) == 'X') then
            b4 = 4
        elseif (TICTAC(2,1) == 'O') then
            b4 = 1
        endif

        if (TICTAC(2,2) == 'X') then
            b5 = 4
        elseif (TICTAC(2,2) == 'O') then
            b5 = 1
        endif

        if (TICTAC(2,3) == 'X') then
            b6 = 4
        elseif (TICTAC(2,3) == 'O') then
            b6 = 1
        endif

        if (TICTAC(3,1) == 'X') then
            b7 = 4
        elseif (TICTAC(3,1) == 'O') then
            b7 = 1
        endif

        if (TICTAC(3,2) == 'X') then
            b8 = 4
        elseif (TICTAC(3,2) == 'O') then
            b8 = 1
        endif

        if (TICTAC(3,3) == 'X') then
            b9 = 4
        elseif (TICTAC(3,3) == 'O') then
            b9 = 1
        endif

        w1 = b1 + b2 + b3
        w2 = b4 + b5 + b6
        w3 = b7 + b8 + b9
        w4 = b1 + b4 + b7
        w5 = b2 + b5 + b8
        w6 = b3 + b6 + b9
        w7 = b1 + b5 + b9
        w8 = b3 + b5 + b7
        sumB = b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8 + b9


        if(w1 == 2) then
                if(CHKPLAY(TICTAC, 1) .eqv. .TRUE.) then
                    TICTAC(1,1) = 'O'
            elseif (CHKPLAY(TICTAC, 2) .eqv. .TRUE.) then
                    TICTAC(1,2) = 'O'
            elseif (CHKPLAY(TICTAC, 3) .eqv. .TRUE.) then
                    TICTAC(1,3) = 'O'
            endif
        elseif (w2 == 2) then
            if(CHKPLAY(TICTAC, 4) .eqv. .TRUE.) then
                TICTAC(2,1) = 'O'
            elseif (CHKPLAY(TICTAC, 5) .eqv. .TRUE.) then
                TICTAC(2,2) = 'O'
            elseif (CHKPLAY(TICTAC, 6) .eqv. .TRUE.) then
                TICTAC(2,3) = 'O'
            endif
        elseif (w3 == 2) then
            if(CHKPLAY(TICTAC, 7) .eqv. .TRUE.) then
                TICTAC(3,1) = 'O'
            elseif (CHKPLAY(TICTAC, 8) .eqv. .TRUE.) then
                TICTAC(3,2) = 'O'
            elseif (CHKPLAY(TICTAC, 9) .eqv. .TRUE.) then
                TICTAC(3,3) = 'O'
            endif
        elseif (w4 == 2) then
            if(CHKPLAY(TICTAC, 1) .eqv. .TRUE.) then
                TICTAC(1,1) = 'O'
            elseif (CHKPLAY(TICTAC, 4) .eqv. .TRUE.) then
                TICTAC(2,1) = 'O'
            elseif (CHKPLAY(TICTAC, 7) .eqv. .TRUE.) then
                TICTAC(3,1) = 'O'
            endif
        elseif (w5 == 2) then
            if(CHKPLAY(TICTAC, 2) .eqv. .TRUE.) then
                TICTAC(1,2) = 'O'
            elseif (CHKPLAY(TICTAC, 5) .eqv. .TRUE.) then
                TICTAC(2,2) = 'O'
            elseif (CHKPLAY(TICTAC, 8) .eqv. .TRUE.) then
                TICTAC(3,2) = 'O'
            endif
        elseif (w6 == 2) then
            if(CHKPLAY(TICTAC, 3) .eqv. .TRUE.) then
                TICTAC(1,3) = 'O'
            elseif (CHKPLAY(TICTAC, 6) .eqv. .TRUE.) then
                TICTAC(2,3) = 'O'
            elseif (CHKPLAY(TICTAC, 9) .eqv. .TRUE.) then
                TICTAC(3,3) = 'O'
            endif
        elseif (w7 == 2) then
            if(CHKPLAY(TICTAC, 1) .eqv. .TRUE.) then
                TICTAC(1,1) = 'O'
            elseif (CHKPLAY(TICTAC, 5) .eqv. .TRUE.) then
                TICTAC(2,2) = 'O'
            elseif (CHKPLAY(TICTAC, 9) .eqv. .TRUE.) then
                TICTAC(3,3) = 'O'
            endif
        elseif (w8 == 2) then
            if(CHKPLAY(TICTAC, 3) .eqv. .TRUE.) then
                TICTAC(1,3) = 'O'
            elseif (CHKPLAY(TICTAC, 5) .eqv. .TRUE.) then
                TICTAC(2,2) = 'O'
            elseif (CHKPLAY(TICTAC, 7) .eqv. .TRUE.) then
                TICTAC(3,1) = 'O'
            endif
        elseif(w1 == 8) then
            if(CHKPLAY(TICTAC, 1) .eqv. .TRUE.) then
                TICTAC(1,1) = 'O'
            elseif (CHKPLAY(TICTAC, 2) .eqv. .TRUE.) then
                TICTAC(1,2) = 'O'
            elseif (CHKPLAY(TICTAC, 3) .eqv. .TRUE.) then
                TICTAC(1,3) = 'O'
            endif
        elseif (w2 == 8) then
            if(CHKPLAY(TICTAC, 4) .eqv. .TRUE.) then
                TICTAC(2,1) = 'O'
            elseif (CHKPLAY(TICTAC, 5) .eqv. .TRUE.) then
                TICTAC(2,2) = 'O'
            elseif (CHKPLAY(TICTAC, 6) .eqv. .TRUE.) then
                TICTAC(2,3) = 'O'
            endif
        elseif (w3 == 8) then
            if(CHKPLAY(TICTAC, 7) .eqv. .TRUE.) then
                TICTAC(3,1) = 'O'
            elseif (CHKPLAY(TICTAC, 8) .eqv. .TRUE.) then
                TICTAC(3,2) = 'O'
            elseif (CHKPLAY(TICTAC, 9) .eqv. .TRUE.) then
                TICTAC(3,3) = 'O'
            endif
        elseif (w4 == 8) then
            if(CHKPLAY(TICTAC, 1) .eqv. .TRUE.) then
                TICTAC(1,1) = 'O'
            elseif (CHKPLAY(TICTAC, 4) .eqv. .TRUE.) then
                TICTAC(2,1) = 'O'
            elseif (CHKPLAY(TICTAC, 7) .eqv. .TRUE.) then
                TICTAC(3,1) = 'O'
            endif
        elseif (w5 == 8) then
            if(CHKPLAY(TICTAC, 2) .eqv. .TRUE.) then
                TICTAC(1,2) = 'O'
            elseif (CHKPLAY(TICTAC, 5) .eqv. .TRUE.) then
                TICTAC(2,2) = 'O'
            elseif (CHKPLAY(TICTAC, 8) .eqv. .TRUE.) then
                TICTAC(3,2) = 'O'
            endif
        elseif (w6 == 8) then
            if(CHKPLAY(TICTAC, 3) .eqv. .TRUE.) then
                TICTAC(1,3) = 'O'
            elseif (CHKPLAY(TICTAC, 6) .eqv. .TRUE.) then
                TICTAC(2,3) = 'O'
            elseif (CHKPLAY(TICTAC, 9) .eqv. .TRUE.) then
                TICTAC(3,3) = 'O'
            endif
        elseif (w7 == 8) then
            if(CHKPLAY(TICTAC, 1) .eqv. .TRUE.) then
                TICTAC(1,1) = 'O'
            elseif (CHKPLAY(TICTAC, 5) .eqv. .TRUE.) then
                TICTAC(2,2) = 'O'
            elseif (CHKPLAY(TICTAC, 9) .eqv. .TRUE.) then
                TICTAC(3,3) = 'O'
            endif
        elseif (w8 == 8) then
            if(CHKPLAY(TICTAC, 3) .eqv. .TRUE.) then
                TICTAC(1,3) = 'O'
            elseif (CHKPLAY(TICTAC, 5) .eqv. .TRUE.) then
                TICTAC(2,2) = 'O'
            elseif (CHKPLAY(TICTAC, 7) .eqv. .TRUE.) then
                TICTAC(3,1) = 'O'
            endif
        else
! 			user did first move
            if(sumB == 4) then
! 				if user starts in a corner
                if(b1 == 4 .or. b3 == 4 .or. b7 == 4 .or. b9 == 4) then
                    if(CHKPLAY(TICTAC, 2) .eqv. .TRUE.) then
                        TICTAC(1,2) = 'O'
                    elseif (CHKPLAY(TICTAC, 6) .eqv. .TRUE.) then
                        TICTAC(2,3) = 'O'
                    elseif (CHKPLAY(TICTAC, 8) .eqv. .TRUE.) then
                        TICTAC(3,2) = 'O'
                    elseif (CHKPLAY(TICTAC, 4) .eqv. .TRUE.) then
                        TICTAC(2,1) = 'O'
                    endif
                elseif(b2 == 4 .or. b6 == 4 .or. b8 == 4 .or. b4 == 4) then

                    if(CHKPLAY(TICTAC, 5) .eqv. .TRUE.) then
                        TICTAC(2,2) = 'O'
                    endif

                elseif(b5 == 4) then
                    if(CHKPLAY(TICTAC, 1) .eqv. .TRUE.) then
                        TICTAC(1,1) = 'O'
                    elseif (CHKPLAY(TICTAC, 3) .eqv. .TRUE.) then
                        TICTAC(1,3) = 'O'
                    elseif (CHKPLAY(TICTAC, 9) .eqv. .TRUE.) then
                        TICTAC(3,3) = 'O'
                    elseif (CHKPLAY(TICTAC, 7) .eqv. .TRUE.) then
                        TICTAC(3,1) = 'O'
                    endif
                endif
            else
                do i = 1, 9, 1
                    if(CHKPLAY(TICTAC, i) .eqv. .TRUE.) exit
                end do

                select case (i)
                    case (1)
                        TICTAC(1,1) = 'O'
                    case (2)
                        TICTAC(1,2) = 'O'
                    case (3)
                        TICTAC(1,3) = 'O'
                    case (4)
                        TICTAC(2,1) = 'O'
                    case (5)
                        TICTAC(2,2) = 'O'
                    case (6)
                        TICTAC(2,3) = 'O'
                    case (7)
                        TICTAC(3,1) = 'O'
                    case (8)
                        TICTAC(3,2) = 'O'
                    case (9)
                        TICTAC(3,3) = 'O'
                    case default
                        write(*,*) 'Error has occured'
                    end select
            endif
        endif

    end subroutine pickMove

    integer function getMove(TICTAC)

        implicit none

        integer :: move
        character(len=1) :: TICTAC(3,3)


        do
            write(*,*) 'Your Move?'
            read(*,*) move
            if(move > 0 .AND. move < 10 .and. CHKPLAY(TICTAC, move) .eqv. .TRUE.) exit
            write(*,*) 'Error, Please Try Again'
        end do

        getMove = move

    end function getMove


    logical function CHKPLAY(TICTAC, MOVE)

        implicit none
        character(len=1) :: TICTAC(3,3)
        integer, intent(in) :: MOVE

        select case (MOVE)
            case(1)
                if(TICTAC(1,1) == ' ') then
                    CHKPLAY = .TRUE.
                else
                    CHKPLAY = .FALSE.
                endif
            case (2)
                if(TICTAC(1,2) == ' ') then
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
    end function CHKPLAY

    subroutine CHKOVR(TICTAC, OVER, WINNER)

        character(len=1) :: TICTAC(3,3), WINNER, BLANK, DRAW
        logical :: DSAME, OVER
        integer :: IR, IC

        BLANK = ' '
        DRAW = 'D'
        OVER = .TRUE.

        do IR = 1, 3
            if (same(TICTAC(IR,1), TICTAC(IR,2), TICTAC(IR,3))) then
                WINNER = TICTAC(IR,1)
                return
            endif
        end do

        do IC = 1, 3
            if (same(TICTAC(1,IC), TICTAC(2,IC), TICTAC(3,IC))) then
                WINNER = TICTAC(1,IC)
                return
            endif
        end do
        DSAME = same(TICTAC(1,1), TICTAC(2,2), TICTAC(3,3)) .OR. same(TICTAC(1,3),TICTAC(2,2), TICTAC(3,1))
        if (DSAME) then
            WINNER = TICTAC(2,2)
            return
        endif

        do IR = 1, 3
            do IC = 1,3
                if(TICTAC(IR,IC) == BLANK) then
                    OVER = .FALSE.
                    return
                endif
            end do
        end do

        WINNER = DRAW

        return

    end subroutine CHKOVR



! calls 3 different direct locations on map, compare 
! values of 3 to see if they are the same or not

    logical function same(SPOT1, SPOT2, SPOT3)

        character(len=1) :: SPOT1,SPOT2,SPOT3

        if((SPOT1 == 'X' .and. SPOT2 == 'X' .and. SPOT3 == 'X') .or. (SPOT1 == 'O' .and. SPOT2 == 'O' .and. SPOT3 == 'O')) then
            same = .TRUE.
        else
            same = .FALSE.
        endif


    end function same

end program ticTacToe
