import numpy as np
import time
import pandas as pd

# Create new test data
# numlist = np.random.randint(1000000, 1000000000, 100000)

# Use the existing test numlist for apples-to-apples comparison
df = pd.read_csv('Fortran_dev/test_numlist.csv')
numlist = df['0']

# sequence to search for
testseq = 60235

"""
Approach 1:
Convert the data to strings and use string comparison to find matches
"""

numlist_str = []
start = time.process_time()
for num in numlist:
    numlist_str.append(str(num))
end = time.process_time()
placeholder = (end-start)
print("Elapsed time to convert to strings: " + str(placeholder) + "s")

str_matches = []
start = time.process_time()
teststr = str(testseq)
for entry in numlist_str:
    if teststr in entry:
        str_matches.append(entry)
end = time.process_time()
placeholder = placeholder + (end-start)
print("Elapsed time to finish search using string method: " + str(end-start) + "s")
print("matches: ")
print(str_matches)
print("Total time: " + str(placeholder) + "s\n\n")


"""
Approach 2:
Use test sequence as a mask and compare digits, keeping them as integers
"""

matches = []

start = time.process_time()
numdigits = int(np.log10(testseq) + 1)
divisor1 = 10**numdigits
divisor2 = 10**(numdigits-1)
for num in numlist:
    n = num
    while n != 0:
        out = n % divisor1
        n = int(n/10)
        if out == testseq:
            matches.append(num)
        if n < divisor2:
            break
end = time.process_time()

print("Elapsed time to finish search using mask method: " + str(end-start) + "s")
print("matches: ")
print(matches)


