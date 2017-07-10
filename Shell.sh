# https://leetcode.com/problemset/shell/
:<<EOF
sed - http://saullawliet.github.io/undefined/sed.html
awk - http://saullawliet.github.io/undefined/awk.html
Regular Expression - http://saullawliet.github.io/undefined/regular-expression.html
EOF
# 192. Word Frequency
awk 'BEGIN{RS=" |\n"} $0!=""{a[$0]++} END{for(i in a) print i" "a[i]}' words.txt |sort -nrk2
:<<EOF
sort:
  -n: compare according to string numerical value
  -r: reverse the result of comparisons
  -k(KEYDEF): sort via a key; KEYDEF gives location and type
  ...
EOF


# 193. Valid Phone Numbers
# I.
grep -P "^(\d{3}-|\(\d{3}\) )\d{3}-\d{4}$" file.txt
# II.
grep -E "^([0-9]{3}-|\([0-9]{3}\) )[0-9]{3}-[0-9]{4}$" file.txt
# III.
sed -nr '/^([0-9]{3}-|\([0-9]{3}\) )[0-9]{3}-[0-9]{4}$/p' file.txt
:<<EOF
grep:
  -P Interpret PATTERN as a Perl regular expression
  -E Interpret PATTERN as an extended regular expression
  ...
EOF

# 194. Transpose File
awk '{for(i=1;i<=NF;i++) a[i]=a[i]on$i;on=" "} END{for(i in a) print a[i]}' file.txt

# 195. Tenth Line
# I.
sed -n '10p' file.txt
# II.
awk 'NR==10{print $0}' file.txt
# III.
head -n 10 file.txt |tail -n +10
:<<EOF
head:
  -n([-]NUM): print the first NUM lines instead of the first 10;
	      with the leading '-', print all but the  last  NUM  lines  of each file
  ...
tail:
  -n([+]NUM): output the last NUM lines, instead of the last 10; or use -n +NUM to output starting with line NUM
  ...
EOF
