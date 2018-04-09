program sieve

    implicit none

    integer :: upperLimit, i, k
    real :: startTime, endTime, clockRate
    character (len=10000000) :: fileName
    integer, allocatable, dimension(:) :: sieveArray


    do
        write(*,*) 'Enter the upper limit of prime numbers to calculate: '
        read(*,*) upperLimit
        if(upperLimit > 2) exit
        write(*,*) 'Error, Please Try Again'
    end do

    call cpu_time (startTime)

    allocate(sieveArray(2:upperLimit))
    do i = 2, upperLimit, 1
        sieveArray(i) = i
    end do

    do i = 2, upperLimit, 1
        if(mod(2*i, sieveArray(i)) == 0) then
            do k = i * 2,upperLimit, 2
                if(k < upperLimit) then
                    sieveArray(k) = 1
                end if
            end do
        end if
    end do

    do i = 2, upperLimit, 1
        if(mod(3*i, sieveArray(i)) == 0) then
            do k = i * 3,upperLimit, 3
                sieveArray(k) = 1
            end do
        end if
    end do

    do i = 2, upperLimit, 1
        if(mod(5*i, sieveArray(i)) == 0) then
            do k = i * 5,upperLimit, 5
                sieveArray(k) = 1
            end do
        end if
    end do


    open(unit=upperLimit, file='primeNumberFortranOutput.txt', status='new', action='write')

    write(upperLimit, *) "Results:"

    do i = 2, upperLimit, 1
        if(sieveArray(i) /= 1) then
            write(upperLimit,*) sieveArray(i)
        endif
        
    end do

    close(upperLimit, status='keep')

    call cpu_time(endTime)
    write(*,*) "Execution Time: ", (endTime - startTime) , " Seconds"

contains

end program sieve
