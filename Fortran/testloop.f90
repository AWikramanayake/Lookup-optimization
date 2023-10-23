program loop
    use misc_functions
    implicit none
    character(100) :: file_name, test_name
    integer :: list_length, test_seq, test_length
    logical :: skip_header, seq_list, skip_header_test
    integer, allocatable :: w_ids(:), matches(:), test_seqs(:)
    real :: T1, T2

    print *, 'Enter Way ID list filename'
    read(*,*) file_name
    print *, 'Enter length of the list'
    read(*,*) list_length
    print *, 'Skip a line for list header? .TRUE./.true. -> yes , .FALSE./.false. -> no'
    read *, skip_header
    print *, 'Input a list of test sequences? Else: manually input a single test sequence'
    print *, '.TRUE./.true. -> list of sequences, .FALSE./.false. -> single sequence'
    read *, seq_list
    if (seq_list .eqv. .false.) then
        print *, 'Enter integer sequence to search for'
        read *, test_seq
    elseif (seq_list .eqv. .true.) then
        print *, 'Enter filename of list of sequences'
        read(*,*) test_name
        print *, 'Enter length of the list'
        read(*,*) test_length
        print *, 'Skip a line for list header? .TRUE./.true. -> yes , .FALSE./.false. -> no'
        read *, skip_header_test
    end if
    print *, 'Program has begun'

    allocate(w_ids(list_length))

    print *, 'Reads have begun'
    call cpu_time(T1)
    call listread(10, list_length, file_name, w_ids, skip_header)

    if (seq_list .eqv. .false.) then
        call cpu_time(T2)
        write(*, '(A, F12.9, A)') 'Elapsed read time : ', (T2 - T1), ' s'
        print*, 'Search for matches has begun'
        call cpu_time(T1)
        call find_matches_single(test_seq, w_ids, list_length, matches)
        call cpu_time(T2)
    end if

    if (seq_list .eqv. .true.) then
        allocate(test_seqs(test_length))
        call listread(20, test_length, test_name, test_seqs, skip_header_test)
        call cpu_time(T2)
        write(*, '(A, F12.9, A)') 'Combined elapsed read time for both lists : ', (T2 - T1), ' s'
        print*, 'Search for matches has begun'
        call cpu_time(T1)
        call find_matches_list(test_seqs, test_length, w_ids, list_length)
        call cpu_time(T2)
    end if

    write(*, '(A, F12.9, A)') 'Elapsed read time for both lists : ', (T2 - T1), ' s'
    deallocate(w_ids)

end program loop