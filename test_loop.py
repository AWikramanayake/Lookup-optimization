import numpy as np
import time
import pandas as pd


# Read the data
df = pd.read_csv('Fortran_dev/w_ids_list.csv')
df1 = pd.read_csv('Fortran_dev/testseq_list.csv')

numlist = df['w_id']
test_seqs = []
for i in range(24):
    test_seqs.append(df1['sequence_ID'][i])

times = []

"""
Approach 1:
Convert the data to strings and use string comparison to find matches
"""

numlist_str = []
start = time.process_time()
for num in numlist:
    numlist_str.append(str(num))
end = time.process_time()
test_seqs_str = []
for i in range(24):
    test_seqs_str.append(str(df1['sequence_ID'][i]))
placeholder = (end-start)
print("Elapsed time to convert to strings: " + str(placeholder) + "s")
times.append(placeholder)

str_matches = []
start = time.process_time()
for seq in test_seqs_str:
    for entry in numlist_str:
        if seq in entry:
            str_matches.append((seq,entry))
    end = time.process_time()
placeholder = placeholder + (end-start)
print("Elapsed time to finish search using string comparison method: " + str(end-start) + "s")
print("Number of matches: " + str(len(str_matches)))
print("Total time for string search method: " + str(placeholder) + "s\n\n")
placeholder = (end-start)
times.append(placeholder)


"""
Approach 2:
Use test sequence as a mask and compare digits, keeping them as integers
"""
i = 0
matches = []
start = time.process_time()
for entry in test_seqs:
    # print(i)
    numdigits = int(np.log10(entry) + 1)    # Calculate the number of digits in the test seq, used for the mask
    divisor1 = 10**numdigits                # Hardcode these values so they do not have to be re-calculated at each iter
    divisor2 = 10**(numdigits-1)
    for num in numlist:
        n = num
        while n != 0:
            out = n % divisor1              # Get sub seq from test integer with same number of digits as test sequence
            n = int(n/10)                   # Shift everything to the right
            if out == entry:
                matches.append((entry,num))
            if n < divisor2:                # If the remainder of the test integer has fewer digits than test seq,
                break                       # we can skip
    i += 1
end = time.process_time()
print(end-start)

print("Elapsed time to finish search using integer mask method: " + str(end-start) + "s")
print("Number of matches: " + str(len(matches)))
placeholder = (end-start)
times.append(placeholder)

print('\n\nTimes:')
print(times)
