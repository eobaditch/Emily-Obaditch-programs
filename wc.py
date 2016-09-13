#!/usr/bin/env python2.7

import sys
import getopt
import os

#Globals
cFlag=False
lFlag=False
wFlag=False
STDIN=False
NAME=''
NoDash=False

#Usage Function

def usage(status=0):
    print '''usage: {} [-c -l -w] files

    -c  print the byte/character counts
    -l  print the newline counts
    -w  print the word counts'''.format(os.path.basename(sys.argv[0]))
    sys.exit(status)

# Parse command line options

try:
    opts, args = getopt.getopt(sys.argv[1:], "hclw")
except getopt.GetoptError as e:
    print e
    usage(1)

for o, a in opts:
    if o== '-c':
        cFlag=True
    elif o== '-l':
        lFlag=True
    elif o== '-w':
        wFlag =True
    else:
        usage(1)

if len(args) == 0:
    args.append('-')
    NoDash=True

#Main
length=0
lineCount=0
wordCount=0

for path in args:
    if path == '-':
        stream=sys.stdin
        STDIN=True
    else:
        stream=open(path)


    for line in stream:
        length+=len(line)
        lineCount+=1
        words = line.split()
        wordCount+=len(words)

    stream.close()

if cFlag:
    print length,
elif lFlag:
    print lineCount,
elif wFlag:
    print wordCount,
else:
    numSet=lineCount,wordCount,length
    print '{:7}{:8}{:8}'.format(lineCount,wordCount,length,)

if STDIN==False:
    print sys.argv[2]
elif NoDash==False:
    print '-'
