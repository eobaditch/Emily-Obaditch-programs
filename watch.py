#!/usr/bin/env python2.7

import getopt
import os
import time
import sys

# Global Variables

PROGRAM_NAME = os.path.basename(sys.argv[0])
INTERVAL=2
COMMAND=''
VALUE=False

# Functions

def error(message, exit_code=1):
    print >>sys.stderr, message
    sys.exit(exit_code)

def usage(exit_code=0):
    error('''Usage: {}

Options:

    -h              Show this help message
    -n INTERVAL     Specify update interval (in seconds)'''
    .format(PROGRAM_NAME), exit_code)

# Parse Command line arguments

try:
    options, arguments = getopt.getopt(sys.argv[1:], "hn:")
except getopt.GetoptError as e:
    error(e)

for option, value in options:
    if option == '-h':
        usage(0)
    elif option == '-n':
        INTERVAL=value
        VALUE=True
    else:
        usage(1)

if len(sys.argv) == 1:
    error('{} Not implemented!'.format(PROGRAM_NAME))


# Main Execution

if VALUE:
    for command in sys.argv[3:]:
        command+=' '
        COMMAND+=command
   #COMMAND = sys.argv[3]
else:
    for command in sys.argv[1:]:
        command+=' '
        COMMAND+=command

print "Every", INTERVAL, "seconds: ", COMMAND

try:
    while True:
        os.system(COMMAND)
        time.sleep(float(INTERVAL))
        os.system("clear")
except KeyboardInterrupt:
    print "Program terminated by user."



