#!/usr/bin/env python2.7

import getopt
import os
import sys

# Global Variables

BLOCKSIZE = 4096
FORCE     = False

# Functions

def error(message, exit_code=1):
    print >>sys.stderr, message
    sys.exit(exit_code)

def usage(exit_code=0):
    error('''usage: {} [-f] src dst

Options:

    -f          Overwrite existing file'''
    .format(os.path.basename(sys.argv[0])), exit_code)

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

# Parse Command line arguments

try:
    opts, args = getopt.getopt(sys.argv[1:], "hf")
except getopt.GetoptError as e:
    error(e)

for o, a in opts:
    if o == '-f':
        FORCE = True
    else:
        usage(1)

if len(args) != 2:
    usage(1)

SOURCE = args[0]
TARGET = args[1]

if os.path.exists(TARGET) and not FORCE:
    error('{} exists!'.format(TARGET))

# Do actual copying

source = open_fd(SOURCE, os.O_RDONLY)
target = open_fd(TARGET, os.O_WRONLY|os.O_CREAT|os.O_TRUNC)

data = read_fd(source, BLOCKSIZE)
while data:
    write_fd(target, data)
    data = read_fd(source, BLOCKSIZE)

os.close(source)
os.close(target)
