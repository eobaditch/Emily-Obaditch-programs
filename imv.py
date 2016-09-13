#!/usr/bin/env python2.7

import getopt
import os
import sys
import tempfile

# Global Variables

PROGRAM_NAME = os.path.basename(sys.argv[0])
NAMES=list()
EDITOR='vim'

# Functions

def error(message, exit_code=1):
    print >>sys.stderr, message
    sys.exit(exit_code)

def usage(exit_code=0):
    error('''Usage: {} FILES...

Options:

    -h     Show this help message'''
    .format(PROGRAM_NAME), exit_code)

# Parse Command line arguments

try:
    options, arguments = getopt.getopt(sys.argv[1:], "h")
except getopt.GetoptError as e:
    error(e)

for option, value in options:
    if option == '-h':
        usage(0)
    else:
        usage(1)

if len(sys.argv) == 0:
    error('{} Not implemented!'.format(PROGRAM_NAME))

for name in sys.argv[1:]:
    name+='\n'
    NAMES.append(name)

# Main Execution

tempEdit=os.getenv('EDITOR')
if tempEdit != '':
    EDITOR=tempEdit

temp= tempfile.NamedTemporaryFile(delete=False)
for name in NAMES:
    temp.write(name)
temp.close()

filename=temp.name

os.system(EDITOR + ' ' + filename)
count=0
for line in open(filename, 'r'):
    name=NAMES[int(count)].rstrip('\n')
    line=line.rstrip('\n')
    try:
        os.rename(name, line)
        count+=1
    except OSError:
        print "file cannot be renamed"
        count+=1

os.unlink(filename)
