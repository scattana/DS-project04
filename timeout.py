#!/usr/bin/env python2.7

import getopt
import errno
import os
import signal
import sys

# Global Variables

PROGRAM_NAME = os.path.basename(sys.argv[0])
SECONDS      = 10
VERBOSE      = False
PID          = None

# Functions

def error(message, exit_code=1):
    print >>sys.stderr, message
    sys.exit(exit_code)

def debug(message, *args):
    if VERBOSE:
        print >>sys.stderr, message.format(*args)

def usage(exit_code=0):
    error('''Usage: {} [-t SECONDS] command...

Options:

    -t SECONDS  Timeout duration before killing command (default is 10 seconds)
    -v          Display verbose debugging output'''
    .format(PROGRAM_NAME), exit_code)

def alarm_handler(signum, frame):
    debug('Alarm Triggered after {} seconds!', SECONDS)
    debug('Killing PID {}...', PID)
    try:
        os.kill(PID, signal.SIGTERM)
    except OSError as e:
        error(e)

# Parse Command line arguments

try:
    options, arguments = getopt.getopt(sys.argv[1:], "ht:v")
except getopt.GetoptError as e:
    error(e)

for option, value in options:
    if option == '-h':
        usage(0)
    elif option == '-t':
        SECONDS = int(value)
    elif option == '-v':
        VERBOSE = True
    else:
        usage(1)

if not arguments:
    usage(1)

COMMAND = ' '.join(arguments)

# Main Execution

debug('Executing "{}" for at most {} seconds...', COMMAND, SECONDS)

try:
    debug('Forking...')

    PID = os.fork()
    if PID == 0:    # Child
        debug('Execing...')
        os.execvp(arguments[0], arguments)
    else:           # Parent
        debug('Enabling Alarm...')
        signal.signal(signal.SIGALRM, alarm_handler)
        signal.alarm(SECONDS)

        debug('Waiting...')
        try:
            pid, status = os.wait()
        except OSError as e:
            if e.errno == errno.EINTR:
                pid, status = os.wait()
            else:
                error(e)

        debug('Disabling Alarm...')
        signal.alarm(0)

        debug('Process {} terminated with exit status {}', pid, status)
        sys.exit(status)

except OSError as e:
    error(e)
