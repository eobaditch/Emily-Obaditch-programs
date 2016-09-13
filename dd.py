#!/usr/bin/env python2.7

import sys
import getopt
import os

#Globals
FILE=0
WFILE=1
BYTES=512
COUNT=sys.maxint
SEEK=0
SKIP=0

#Usage Function

def usage(exit_code=0):
    print '''usage: {} options

    Options:

        if=FILE     Read from FILE instead of stdin
        of=FILE     Write to FILE instead of stdout

        count=N     Copy only N input blocks
        bs=BYTES    Read and write up to BYTES bytes at a time

        seek=N      Skip N obs-sized blocks at start of output
        skip=N      Skip N ibs-sized blcosk at start of input'''.format(os.path.basename(sys.argv[0]))
    sys.exit(status)

def error(message, exit_code=1):
    print >> sys.stderr,message
    sys.exit(exit_code)

def open_fd(path, mode):
    try:
        return os.open(path, mode)
    except OSError as e:
        error('Could not open {}: {}'.format(SOURCE, e))

def read_fd(fd, n):
    try:
        return os.read(fd, n)
    except OSError as e:
        error('Could not read {} bytes from FD {}: {}'.format(n, fd, e))

def write_fd(fd, data):
    try:
        return os.write(fd, data)
    except OSError as e:
        error('Could not write {} bytes from FD {}: {}'.format(len(data), fd, e))

# Parse command line options
try:
    options, arguments = getopt.getopt(sys.argv[1:], "h")
except getopt.GetoptError as e:
    error(e)

for option, value in options:
    usage(1)

count=0
args=list('')

for argument in sys.argv[1:]:
    if argument[0] == 'i':
        argument=argument.split('=')
        FILE=argument[1]
    elif argument[0] == 'o':
        argument=argument.split('=')
        WFILE=argument[1]
    elif argument[0] == 'c':
        argument=argument.split('=')
        COUNT=int(argument[1])
    elif argument[0] == 'b':
        argument=argument.split('=')
        BYTES=int(argument[1])
    elif argument[0] == 's':
        if argument[1] == 'e':
            argument=argument.split('=')
            SEEK=int(argument[1])
        else:
            argument=argument.split('=')
            SKIP=int(argument[1])

#Main

if WFILE != 1:
    fo = open_fd(WFILE, os.O_WRONLY|os.O_CREAT)
    os.lseek(fo, SEEK*BYTES, 0)
else:
    fo =1

if FILE != 0:
    fd = open_fd(FILE,os.O_RDONLY)
    os.lseek(fd, SKIP*BYTES, 0)
else:
    fd=0

data = read_fd(fd,BYTES)
counter=0
while (int(counter) != COUNT) and (data):
    write_fd(fo, data)
    data=read_fd(fd, BYTES)
    counter+=1


if WFILE != 1:
    os.close(fo)
if FILE != 0:
    os.close(fd)

