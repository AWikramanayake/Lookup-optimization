program loop
    use misc_functions
    use omp_lib
    implicit none
    integer :: testseq, res_length_tot, res_length1, res_length2, res_length3, res_length4, ix
    integer :: count1, count2, count3, count4, matchcount
    logical :: seq_list
    integer, allocatable ::  matches1(:), matches2(:), matches3(:), matches4(:)
    integer, allocatable :: id_slice1(:), id_slice2(:), id_slice3(:), id_slice4(:), results(:)
    real :: T1, T2
    type :: list_cont
        character(50) :: name
        integer :: len
        integer, allocatable :: dat(:)
        logical :: skip
    end type list_cont

    type(list_cont) :: w_ids, test_seqs
    integer :: omp_length, omp_length2

    print *, 'Enter Way ID list filename'
    read(*,*) w_ids%name
    print *, 'Enter length of the list'
    read(*,*) w_ids%len
    print *, 'Skip a line for list header? .TRUE./.true. -> yes , .FALSE./.false. -> no'
    read *, w_ids%skip
    print *, 'Input a list of test sequences? Else: manually input a single test sequence'
    print *, '.TRUE./.true. -> list of sequences, .FALSE./.false. -> single sequence'
    read *, seq_list
    if (seq_list .eqv. .false.) then
        print *, 'Enter integer sequence to search for'
        read *, testseq
    elseif (seq_list .eqv. .true.) then
        print *, 'Enter filename of list of sequences'
        read(*,*) test_seqs%name
        print *, 'Enter length of the list'
        read(*,*) test_seqs%len
        print *, 'Skip a line for list header? .TRUE./.true. -> yes , .FALSE./.false. -> no'
        read *, test_seqs%skip
    end if
    print *, 'Program has begun'

    allocate(w_ids%dat(w_ids%len))

    print *, 'Reads have begun'
    call cpu_time(T1)
    call listread(10, w_ids%len, w_ids%name, w_ids%dat, w_ids%skip)

    if (seq_list .eqv. .false.) then
        call cpu_time(T2)
        write(*, '(A, F12.9, A)') 'Elapsed read time: ', (T2 - T1), ' s'
        print*, 'Search for matches has begun'

        omp_length = w_ids%len / 4
        omp_length2 = w_ids%len - (omp_length * 3)
        call cpu_time(T1)
        !$omp parallel
        !$omp sections
        !$omp section
        allocate(id_slice1(omp_length))
        id_slice1 = w_ids%dat(0:omp_length-1)
        matches1 = find_matches_single(testseq, id_slice1, omp_length)
        !$omp section
        allocate(id_slice2(omp_length))
        id_slice2 = w_ids%dat(omp_length:(omp_length*2)-1)
        matches2 = find_matches_single(testseq, id_slice2, omp_length)
        !$omp section
        allocate(id_slice3(omp_length))
        id_slice3 = w_ids%dat((omp_length*2):(omp_length*3)-1)
        matches3 = find_matches_single(testseq, id_slice3, omp_length)
        !$omp section
        allocate(id_slice4(omp_length2))
        id_slice4 = w_ids%dat((omp_length*3):(omp_length*3)+omp_length2)
        matches4 = find_matches_single(testseq, id_slice4, omp_length2)
        !$omp end sections
        !$omp end parallel
        call cpu_time(T2)

        res_length1 = SIZE(matches1)
        res_length2 = SIZE(matches2)
        res_length3 = SIZE(matches3)
        res_length4 = SIZE(matches4)
        res_length_tot = res_length1 + res_length2 + res_length3 + res_length4
        allocate(results(res_length_tot))

        results(1:res_length1) = matches1
        results(res_length1 + 1 : res_length2) = matches2
        results(res_length1 + res_length2 + 1 : res_length3) = matches3
        results(res_length1 + res_length2 + res_length3 + 1 : res_length4) = matches4

        if (SIZE(results) == 0) then
            print *, 'No matches found'
        else
            print *, 'Matches: '
            do ix = 1, SIZE(results)
                print *, results(ix)
            end do

        end if

    end if

    if (seq_list .eqv. .true.) then
        allocate(test_seqs%dat(test_seqs%len))
        call listread(20, test_seqs%len, test_seqs%name, test_seqs%dat, test_seqs%skip)
        call cpu_time(T2)
        write(*, '(A, F12.9, A)') 'Combined elapsed read time for both lists: ', (T2 - T1), ' s'
        print*, 'Search for matches has begun'

        omp_length = w_ids%len / 4
        omp_length2 = w_ids%len - (omp_length * 3)
        call cpu_time(T1)
        !$omp parallel
        !$omp sections
        !$omp section
        allocate(id_slice1(omp_length))
        id_slice1 = w_ids%dat(0:omp_length-1)
        count1 = find_matches_list(test_seqs%dat, test_seqs%len, id_slice1, omp_length)
        !$omp section
        allocate(id_slice2(omp_length))
        id_slice2 = w_ids%dat(omp_length:(omp_length*2)-1)
        count2 = find_matches_list(test_seqs%dat, test_seqs%len, id_slice2, omp_length)
        !$omp section
        allocate(id_slice3(omp_length))
        id_slice3 = w_ids%dat((omp_length*2):(omp_length*3)-1)
        count3 = find_matches_list(test_seqs%dat, test_seqs%len, id_slice3, omp_length)
        !$omp section
        allocate(id_slice4(omp_length2))
        id_slice4 = w_ids%dat((omp_length*3):(omp_length*3)+omp_length2)
        count4 = find_matches_list(test_seqs%dat, test_seqs%len, id_slice4, omp_length2)
        !$omp end sections
        !$omp end parallel
        call cpu_time(T2)

        matchcount = count1 + count2 + count3 + count4
        print *, 'Match search completed'
        write(*, '(I0, A)') matchcount, ' matches found'

        !call cpu_time(T1)
        !call find_matches_list(test_seqs%dat, test_seqs%len, w_ids%dat, w_ids%len)
        !call cpu_time(T2)

        deallocate(test_seqs%dat)
    end if

    write(*, '(A, F12.9, A)') 'Elapsed search time: ', (T2 - T1), ' s'
    deallocate(w_ids%dat)

end program loop