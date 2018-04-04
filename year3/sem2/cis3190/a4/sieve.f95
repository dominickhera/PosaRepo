
program sieve

    implicit none

!     insert primary program here
    integer :: upperLimit
!     character(len=1) :: TICTAC(3,3)
    integer, allocatable, dimension(:) :: sieveArray


    do
        write(*,*) 'Enter the upper limit of prime numbers to calculate: '
        read(*,*) upperLimit
        if(upperLimit > 2) exit
        write(*,*) 'Error, Please Try Again'
    end do

    allocate(sieveArray(2:upperLimit))
    do i = 2, upperLimit, 1
        sieveArray(i) = i
    end do

    do i = 2, upperLimit, 1
        if((sieveArray(i) % (2*i)) == 0) then
            do k = i * 2,upperLimit, 1
                sieveArray(k) = 0
            end do
        end if
    end do

    do i = 2, upperLimit, 1
        if(sieveArray(i) % 3*i .eq. 0) then
            do k = i * 3,upperLimit, 1
                sieveArray(k) = 0
            end do
        end if
    end do

    do i = 2, upperLimit, 1
        if(sieveArray(i) % 5*i .eq. 0) then
            do k = i * 5,upperLimit, 1
                sieveArray(k) = 0
            end do
        end if
    end do

    do i = 2, upperLimit, 1
        write(*,*) sieveArray(i)
    end do

contains
! enter subroutines here

end program sieve
