program loop
    use misc_functions
    implicit none
    integer :: testseq
    logical :: seq_list
    integer, allocatable ::  matches(:)
    real :: T1, T2
    type :: list_cont
        character(50) :: name
        integer :: len
        integer, allocatable :: dat(:)
        logical :: skip
    end type list_cont

    type(list_cont) :: w_ids, test_seqs

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
        call cpu_time(T1)
        call find_matches_single(testseq, w_ids%dat, w_ids%len, matches)
        call cpu_time(T2)
    end if

    if (seq_list .eqv. .true.) then
        allocate(test_seqs%dat(test_seqs%len))
        call listread(20, test_seqs%len, test_seqs%name, test_seqs%dat, test_seqs%skip)
        call cpu_time(T2)
        write(*, '(A, F12.9, A)') 'Combined elapsed read time for both lists: ', (T2 - T1), ' s'
        print*, 'Search for matches has begun'
        call cpu_time(T1)
        call find_matches_list(test_seqs%dat, test_seqs%len, w_ids%dat, w_ids%len)
        call cpu_time(T2)
        deallocate(test_seqs%dat)
    end if

    write(*, '(A, F12.9, A)') 'Elapsed search time: ', (T2 - T1), ' s'
    deallocate(w_ids%dat)

end program loop