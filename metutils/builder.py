import pexpect
import os
import os.path
import discovery


def build_tests(files=None,verbose=False,force=False):
    import glob
    toolchainpath = discovery.discover_toolchain_path()
    testpath = discovery.discover_testpath()
    startpath = os.path.abspath(os.getcwd())
    #Build all the single source tests
    try:
        os.chdir(testpath)
        if files == None:
            files = glob.glob("*.c")
        for csource in files:
            lastbuild = 0
            if os.path.isfile(csource[:-2]) and os.path.isfile(csource[:-2]+'.srec') and not force:
                lastbuild = min(os.path.getmtime(csource[:-2]),os.path.getmtime(csource[:-2]+'.srec'))
            
            if os.path.getmtime(csource) > lastbuild:
                output,code = pexpect.run("bash build.sh %s %s" % ( toolchainpath,csource ),withexitstatus=True)
                if code != 0:
                    print output
                    raise Exception("build of single_source %s failed with retcode %s"%(csource,code))
                print "Built: %s" % csource
    finally:
        os.chdir(startpath)
    
    
