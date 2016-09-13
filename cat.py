#!/usr/bin/env python2.7

import sys

count=0

for path in sys.argv[1:]:
    stream=open(path)

    for line in open(stream):
        if count <= num:
            print line,
            count = count +1
        else:
            sys.exit
