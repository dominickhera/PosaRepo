
program sieve

    implicit none

!     insert primary program here
    integer :: upperLimit, i, k
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

write(*,*)"2 begin"
    do i = 2, upperLimit, 1
        write(*,*) sieveArray(i), 2*i, modulo(sieveArray(i), 2*i)
!         if(mod(sieveArray(i), (2*i)) == 0) then
        if(mod(sieveArray(i), 2*i) == 0) then
            write(*,*) "hello"
            do k = i * 2,upperLimit, 1
                write(*,*) k, i
                sieveArray(k * 2) = 0
            end do
        end if
    end do

    do i = 2, upperLimit, 1
        if(mod(sieveArray(i), 3*i) == 0) then
            do k = i * 3,upperLimit, 1
                sieveArray(k*3) = 0
            end do
        end if
    end do

    do i = 2, upperLimit, 1
        if(mod(sieveArray(i), 5*i) == 0) then
            do k = i * 5,upperLimit, 1
                sieveArray(k*5) = 0
            end do
        end if
    end do

    write(*,*) "results"

    do i = 2, upperLimit, 1
        if(sieveArray(i) /= 0) then
            write(*,*) sieveArray(i)
        endif
        
    end do

contains
! enter subroutines here

end program sieve
