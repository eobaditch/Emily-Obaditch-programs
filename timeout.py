#!/usr/bin/env python2.7

import getopt
import os
import sys
import time
import signal

# Global Variables

PROGRAM_NAME = os.path.basename(sys.argv[0])
SECONDS=10
VERBOSE=False
Tflag=False
Vflag=False
COMMAND=''
ChildPid = -1
ChilStatus = -1

# Functions

def error(message, exit_code=1):
    print >>sys.stderr, message
    sys.exit(exit_code)

def usage(exit_code=0):
    error('''Usage: {} [-t SECONDS] command...

Options:

    -t SECONDS  Timeout duration before killing command (default is 10 seconds)
    -v          Display verbose debugging output
    -h          Show this help message'''
    .format(PROGRAM_NAME), exit_code)

def sig_handler(signum, frame):
    os.kill(pid, signal.SIGTERM)
    debug("Alarm Triggered after {} seconds!", SECONDS)
    debug("Killing PID {}...",os.getpid())
    debug("Disabling Alarm")
    newpid, status = os.wait()
    debug("Process {} terminated with exit status {}", os.getpid(), (status))
    sys.exit(status)

def debug(message, *args):
    if VERBOSE:
        print (message.format(*args))

# Parse Command line arguments

try:
    options, arguments = getopt.getopt(sys.argv[1:], "ht:v")
except getopt.GetoptError as e:
    error(e)

for option, value in options:
    if option == '-h':
        usage(0)
    elif option == '-t':
        SECONDS=value
        Tflag=True
    elif option == '-v':
        VERBOSE=True
        Vflag=True
    else:
        usage(1)


if Tflag:
    if Vflag:
        start=sys.argv[4:]
    else:
        start=sys.argv[3:]
elif Vflag:
    start=sys.argv[2:]
else:
    start=sys.argv[1:]

args=' '.join(start[1:])

if  len(sys.argv)==1:
    error('{} Not implemented!'.format(PROGRAM_NAME))
    sys.exit(1)

# Main Execution

command=start[0]
debug('Executing "{}" for at most {} seconds...', command, SECONDS)

try:
    pid = os.fork()
    if pid == 0:
        try:
            debug("Waiting...")
            debug("Execing...")
            os.execlp(command, command, args)
            #sys.exit(1)
        except OSError as e:
            print 'exec failed'
    else:
        debug("Forking...")
        signal.signal(signal.SIGALRM, sig_handler)
        debug("Enabling Alarm...")
        signal.alarm(int(SECONDS))
        pid,status = os.wait()
        debug("Disabling Alarm...")
        debug("Process {} terminated with exit status {}", pid, status)
except OSError as e:
    sys.exit(1)



'''
if VERBOSE:
    debug(message, sys.stderr)
'''

