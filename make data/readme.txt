Calculate Pbkn and Alpha for Ngram.

----------------
calc.cpp: = calcAlpha + calcP

input: data after run init ngram
output: unigram, bigram, trigram with Pbkn and Alpha in 3 txt file. Those txt file can use to import database by script:

```
LOAD DATA INFILE 'uni with P alpha.txt' 
INTO TABLE unidb 
FIELDS TERMINATED BY ','
LINES TERMINATED BY '\r\n'
```

----------------
mergeXX.cpp
merge 2 file results of init ngram. When your data is big, you must split it to many file, and now you use this to merge many results file.
input: 2 txt file after run init ngram
output: a txt file merge 2 file with same format as input

