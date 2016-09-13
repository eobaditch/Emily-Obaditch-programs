#!/usr/bin/env python2.7

import getopt
import os
import sys
import yaml
import time
import re
import glob

# Global Variables

PROGRAM_NAME = os.path.basename(sys.argv[0])
SECONDS=2
RULES='rorschach.yml'
VERBOSE=False
DIRECTORIES=['.']
flag=0
TIME=0
MTIME=0
FIRST=True


# Functions

def error(message, exit_code=1):
    print >>sys.stderr, message
    sys.exit(exit_code)

def usage(exit_code=0):
    error('''Usage: {} [-r RULES -t SECONDS] DIRECTORIES...

Options:

    -r RULES    Path to rules file (default is .rorschach.yml)
    -t SECONDS  Time between scans (default is 2 seconds)
    -v          Display verbose debugging output
    -h          Show this help message'''
    .format(PROGRAM_NAME), exit_code)

def check_directory(name):
    debug("checking files and directories...")
    try:
        regex=re.search(PATTERN, name)
    except:
        try:
            regex=glob.glob(PATTERN)
        except:
            return False
    if not regex:
        return False
    return True

def check_status(path,modTime):
    debug("checking status")
    global TIME
    if int(modTime+SECONDS) <= int(TIME):
        return False
    return True

def execute_action(command, args):
    debug("executing action")
    try:
        pid = os.fork()
        if pid == 0:
            try:
                os.execlp(command, command, args)
            except OSError as e:
                print 'exec failed: {}'.format(e)
                error('{} Not implemented!'.format(PROGRAM_NAME))
                sys.exit(1)
        else:
            pid,status=os.wait()
    except OSError as e:
        print 'fork failed: {}'.format(e)
        error('{} Not implemented!'.format(PROGRAM_NAME))
        sys.exit(1)

def debug(message):
    if VERBOSE:
        print message
# Parse Command line arguments

try:
    options, arguments = getopt.getopt(sys.argv[1:], "hr:t:v")
except getopt.GetoptError as e:
    error(e)

for option, value in options:
    if option == '-h':
        usage(0)
    elif option == '-r':
        RULES=value
        flag+=2
    elif option == '-t':
        SECONDS=value
        flag+=2
    elif option == '-v':
        VERBOSE=True
        flag+=1
    else:
        usage(1)

start=flag+1
if len(sys.argv) > 1:
    DIRECTORIES=sys.argv[int(start):]


# Main Execution

with open(RULES, 'r') as f:
    doc = yaml.load(f)

PATTERN=doc['pattern']
ACTION=doc['action']
ACTION=ACTION.split(' ')
commands=''
args=''
results=[]
mtime=[]

count=0
for command in ACTION:
    if command[0] == '{':
        args+='{'+str(count)+'} '
        count+=1
    else:
        commands+=command
try:
    while True:
        TIME=time.time()
        debug("walking directory to check directory and files in directory")
        for direct in DIRECTORIES:
            for root, dirs, files in os.walk(direct):
                for name in dirs+files:
                    path=os.path.join(root,name)
                    mtime.append(os.stat(path).st_mtime)
                    results.append(path)
        dictionary=dict(zip(results, mtime))
        for path, MT in dictionary.iteritems():
            if check_directory(os.path.basename(path)):
                if check_status(path,MT):
                    newargs=args.format(path)
                    execute_action(commands, newargs)
        results=[]
        mtime=[]
        time.sleep(float(SECONDS))
except KeyboardInterrupt:
    print "terminated by user"
    sys.exit(1)


