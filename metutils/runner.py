import os
import discovery
import glob
import pexpect
import sys

def read_failcache():
    try:
        cache = open("met_failed_cache",'r')
        ret = cache.read().split('\n')
        cache.close()
        return [x for x in ret if x != '']
    except IOError as e:
        return []

def write_failcache(items):
    cache = open("met_failed_cache",'w')
    for case in sorted(items):
        cache.write(case+'\n')
    cache.close()

def run_tests(command=None,verbose=False,srec=False):
    
    startpath = os.path.abspath(os.getcwd())
    failed = set()
    ntests = 0
    prevfailed = read_failcache()
    try:
        testpath = discovery.discover_testpath()
        os.chdir(testpath)
        
        tests = [x[:-2] for x in glob.glob("*.c")]
        tests.sort()
        #rerun failed tests only
        if len(prevfailed):
            tests = [x for x in tests if x in prevfailed]
        ntests = len(tests)
        for t in tests:
            kernel = t
            if srec:
                kernel += ".srec"
            print "Test: %s" %t
            logfile = None
            if verbose:
                logfile = sys.stdout
            emu = pexpect.spawn(command.format(KERNEL=kernel),logfile=logfile,timeout=5)
            try:
                idx = emu.expect(["PASS","FAIL"])
                if idx != 0:
                    print "    failed"
                    failed.add(t)
                emu.expect(pexpect.EOF)
            except pexpect.EOF:
                print "    Unexpected EOF"
                failed.add(t)
            except pexpect.TIMEOUT:
                print "    Unexpected TIMEOUT"
                failed.add(t)
    finally:
        os.chdir(startpath)
    
    write_failcache(failed)
    
    print "List of failed tests:"
    for t in sorted(failed):
        print "  " + t
    print "passed %s of %s tests" % (ntests - len(failed),ntests)
