import os
import discovery
import glob
import pexpect
import sys

def run_tests(command=None,verbose=False,srec=False):
    
    
    startpath = os.path.abspath(os.getcwd())
    failed = {}
    
    try:
        testpath = discovery.discover_testpath()
        os.chdir(testpath)
        tests = [x[:-2] for x in glob.glob("*.c")]
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
                emu.expect(pexpect.EOF)
            except pexpect.EOF:
                print "    Unexpected EOF"
            except pexpect.TIMEOUT:
                print "    Unexpected TIMEOUT"
    finally:
        os.chdir(startpath)
    
        
    
