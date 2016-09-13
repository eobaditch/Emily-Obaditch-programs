#!/usr/bin/env python2.7

import sys
import getopt
import os

#Globals
COUNT = False

#Usage Function

def usage(status=0):
    print '''usage: {} [-c] files

    -c  prefix lines byt the number of occurrence'''.format(os.path.basename(sys.argv[0]))
    sys.exit(status)

# Parse command line options

try:
    opts, args = getopt.getopt(sys.argv[1:], "hc")
except getopt.GetoptError as e:
    print e
    usage(1)

for o, a in opts:
    if  o == '-c':
        COUNT= True
    else:
        usage(1)

if len(args) == 0:
    args.append('-')

#Main Execution

prev_line=''
counter=1
d={}

for path in args:
    if path == '-':
        stream=sys.stdin
    else:
        stream = open(path,'r')


    for line in stream:
        line=line.strip('\n')
        if COUNT:
            if prev_line == '':
                d[line]=1
            elif prev_line != line:
                d[prev_line]=d[prev_line]
                d[line]=1
            else:
                d[line]=d[prev_line]+1

            prev_line = line

        else:
            if prev_line != line:
                print line
            elif prev_line == '':
                print line

            prev_line = line

    if COUNT:
        d_key_sorted=sorted(d.keys())
        for x in d_key_sorted:
            print '{:7} {}'.format(d[x],x)
