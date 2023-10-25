module misc_functions
    contains
        subroutine listread(unitnum, listlength, filename, outlist, skipheader)
            implicit none
            integer, intent(in) :: listlength
            character(len=*), intent(in) :: filename
            logical, intent(in) :: skipheader
            integer :: ix, unitnum
            integer, intent(out) :: outlist(:)

            open(unitnum, file=filename, access='sequential')
            if (skipheader .eqv. .true.) then
                read(unitnum, *) ! skip a line for column header
            end if

            do ix = 1, listlength
                read(unitnum,*) outlist(ix)
            end do
            close(unitnum)
            print *, 'List_read completed'
        end subroutine listread

        subroutine find_matches_single(testseq, inlist, listlength, outlist)
            implicit none
            integer, intent(in) :: listlength, testseq
            integer, dimension(listlength), intent(in) :: inlist
            integer, dimension(1000) :: matches_buffer ! placeholder to collect matches, assume there will be <1000
            integer, allocatable, intent(out) :: outlist(:)
            integer :: i, j, ix, n, out, numdigits, divisor1, divisor2

            numdigits = int(log10(real(testseq)) + 1)
            divisor1 = 10**numdigits
            divisor2 = 10**(numdigits-1)
            j = 0
            do i = 1, listlength
                n = inlist(i)
                do while(n /= 0)
                    out = MOD(n, divisor1)
                    n = (n / 10)
                    if (out == testseq) then
                        j = j+1
                        matches_buffer(j) = inlist(i)
                    end if
                    if (n < divisor2) then
                        exit
                    end if
                end do
            end do
            print *, 'Match search completed'

            if (j == 0) then
                print *, 'No matches found'
            else
                allocate(outlist(j))
                print *, 'Matches: '
                do ix = 1, j
                    outlist(ix) = matches_buffer(ix)
                    print *, outlist(ix)
                end do
            end if
        end subroutine find_matches_single

        subroutine find_matches_list(testlist, testlength, inlist, listlength)
            implicit none
            integer, intent(in) :: listlength, testlength
            integer, dimension(listlength), intent(in) :: inlist
            integer, dimension(testlength), intent(in) :: testlist
            integer :: i, k, numdigits, divisor1, divisor2
            integer :: n, out, matchcount
            matchcount = 0
            do k=1, testlength
                numdigits = int(log10(real(testlist(k))) + 1)
                divisor1 = 10**numdigits
                divisor2 = 10**(numdigits-1)
                do concurrent(i = 1:listlength)
                n = inlist(i)
                    do while(n /= 0)
                        out = MOD(n, divisor1)
                        n = (n / 10)
                        if (out == testlist(k)) then
                            matchcount = matchcount+1
                            !write(*, '(I0, A, I0)') testlist(k), ', ', inlist(i) ! Placeholder for function to save matches
                            ! straightforward solution: write match pair to external file or console
                            ! however that may break parallelizability of the loop
                            ! find pure function/subroutine solution
                        end if
                        if (n < divisor2) then
                            exit
                        end if
                    end do
                end do
            end do
            print *, 'Match search completed'
            write(*, '(I0, A)') matchcount, ' matches found'
        end subroutine find_matches_list

end module misc_functions




