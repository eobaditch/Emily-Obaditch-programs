#!/usr/bin/env python2.7

import getopt
import re
import fnmatch
import os
import sys

# Global Variables
TYPE=''
EXE=False
READ=False
WRITE=False
EMPTY=False
NAME=''
PATH=''
REGEX=''
PERM=''
NEWER=''
UID=''
GID=''

# Functions

def error(message, exit_code=1):
    print >>sys.stderr, message
    sys.exit(exit_code)

def usage(exit_code=0):
    error('''Usage: find.py directory [options]...

Options:

    -type [f|d]     File is of type f for regular file or d for directory

    -executable     File is executable and directories are searchable to
user
    -readable       File readable to user
    -writable       File is writable to user

    -empty          File or directory is empty

    -name  pattern  Base of file name matches shell pattern
    -path  pattern  Path of file matches shell pattern
    -regex pattern  Path of file matches regular expression

    -perm  mode     File's permission bits are exactly mode (octal)
    -newer file     File was modified more recently than file

    -uid   n        File's numeric user ID is n
    -gid   n        File's numeric group ID is n
    '''
    .format(os.path.basename(sys.argv[0])), exit_code)

def include(path):
    broken = False

    try:
        statinfo = os.stat(path)
    except OSError:
        broken = True
        statinfo = os.lstat(path)

    if TYPE == 'f':
        if not (os.path.isfile(path)):
            return False
    if TYPE == 'd':
        if not (os.path.isdir(path)):
            return False
    if EXE:
        if not (os.access(path,os.X_OK)):
            return False
    if READ:
        if not (os.access(path,os.R_OK)):
            return False
    if WRITE:
        if not (os.access(path,os.W_OK)):
            return False
    if EMPTY:
        if os.path.isfile(path) and os.stat(path).st_size != 0:
            return False
        if os.path.isdir(path):
            try:
                if os.listdir(path) != []:
                    return False
            except OSError:
                return False
        if os.path.islink(path) and broken:
                return False
    if NAME != '':
        if not fnmatch.fnmatch(os.path.basename(path), NAME):
            return False
    if PATH != '':
        if not fnmatch.fnmatch(path, PATH):
            return False
    if REGEX != '':
        if not re.search(REGEX, path):
            return False
    if PERM != '':
        if PERM != str(oct(statinfo.st_mode))[-3:]:
            return False
    if NEWER != '':
        if int(os.stat(NEWER).st_mtime) >= int(statinfo.st_mtime):
            return False
    if UID != '':
        if int(UID) != int(statinfo.st_uid):
            return False
    if GID != '':
        if int(GID) != int(statinfo.st_gid):
            return False

    return True

# Parse Command line arguments
args=list('')
length=0
DIRECTORY=sys.argv[1]

for argument in sys.argv[2:]:
    if argument[0] == '-':
        argument=argument.split('-')[1]
        if argument == 'h':
            usage(1)
        else:
            args.append(argument)
            length+=1
    else:
        args.append(argument)
        length+=1

count=0
while count < len(args):
    if args[count] == 'type':
        TYPE=args[int(count)+1]
        count=count+2
    elif args[count] == 'executable':
        EXE=True
        count+=1
    elif args[count] == 'readable':
        READ=True
        count+=1
    elif args[count] == 'writable':
        WRITE=True
        count+=1
    elif args[count] == 'empty':
        EMPTY=True
        count+=1
    elif args[count] == 'name':
        NAME=args[int(count)+1]
        count=count+2
    elif args[count] == 'path':
        PATH=args[int(count)+1]
        count=count+2
    elif args[count] == 'regex':
        REGEX=args[int(count)+1]
        count=count+2
    elif args[count] == 'perm':
        PERM=args[int(count)+1]
        count=count+2
    elif args[count] == 'newer':
        NEWER=args[int(count)+1]
        count=count+2
    elif args[count] == 'uid':
        UID=args[int(count)+1]
        count=count+2
    elif args[count] == 'gid':
        GID=args[int(count)+1]
        count=count+2
    else:
        usage(1)
# Main Execution
if include(DIRECTORY):
    print DIRECTORY

for root, dirs, files in os.walk(DIRECTORY, followlinks=True):
    for name in dirs + files:
        path = os.path.join(root,name)
        if include(path):
            print path


