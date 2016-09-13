#!/usr/bin/env python2.7

import sys
import getopt
import os

#Globals
DELIM="\t"
FIELDS=''
ERROR=True
MULT=False

#Usage Function

def usage(status=0):
    print '''usage: {} [-d DELIM -f] files

    -d DELIM use DELIM instead of TAB for field delimiter
    -f FIELDS select only these fields'''.format(os.path.basename(sys.argv[0]))
    sys.exit(status)

# Parse command line options

try:
    opts, args = getopt.getopt(sys.argv[1:], "d:f:")
except getopt.GetoptError as e:
    print e
    usage(1)

for o, a in opts:
    if  o == '-d':
        DELIM=a
    elif o == '-f':
        FIELDS=set(a.split(","))
        ERROR=False
    else:
        usage(1)

if len(args) == 0:
    args.append('-')

#Main
multList=list('')

if int(len(FIELDS)) > 1:
    MULT=True

if ERROR:
    print "Error: you must enter -f"
    sys.exit

for path in args:
    if path == '-':
        stream=sys.stdin
    else:
        stream=open(path)

    for line in stream:
        line=line.rstrip('\n')
        newline=list(line.split(DELIM))
        length=len(newline)
        for i in FIELDS:
            if int(i) <= int(length):
                strippedLine=newline[int(i)-1].rstrip()
                if MULT:
                    multList.append(strippedLine)
                else:
                    print strippedLine
        if MULT:
            temp=multList[1]
            multList[1]=multList[2]
            multList[2]=temp
            print (DELIM.join(multList))
            multList=[]
stream.close()
