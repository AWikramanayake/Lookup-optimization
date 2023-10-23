import numpy as np
import time
import pandas as pd


# Read the data
df = pd.read_csv('w_ids_list.csv')
df1 = pd.read_csv('testseq_list.csv')

numlist = df['w_id']
test_seqs = []
for i in range(49):
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
for i in range(49):
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
print("Elapsed time to finish search using string method: " + str(end-start) + "s")
print("matches: ")
print(str_matches)
print("Total time: " + str(placeholder) + "s\n\n")
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
    print(i)
    numdigits = int(np.log10(entry) + 1)
    divisor1 = 10**numdigits
    divisor2 = 10**(numdigits-1)
    for num in numlist:
        n = num
        while n != 0:
            out = n % divisor1
            n = int(n/10)
            if out == entry:
                matches.append((entry,num))
            if n < divisor2:
                break
    i += 1
end = time.process_time()
print(end-start)

print("Elapsed time to finish search using mask method: " + str(end-start) + "s")
print("matches: ")
print(matches)
placeholder = (end-start)
times.append(placeholder)

print('\n\nTimes:')
print(times)
