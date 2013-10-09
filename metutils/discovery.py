import os
import os.path
import pexpect

def assert_sane_testdir(path):
    sanityfile = (os.path.join(path,'sanity.c'))
    if not os.path.isfile(sanityfile):
        raise Exception("%s is not a sane test directory! could not find %s"%(path,sanityfile))
        
def discover_testpath():
    ret = os.path.abspath("./tests")
    assert_sane_testdir(ret)
    return ret
    
def is_toolchain_dir(path):
    if os.path.isfile(os.path.join(path,"mips-baremetal-elf-gcc")):
        return True
    return False


def discover_toolchain_path():
    
    #first see if its already added to path    
    out,status = pexpect.run("which mips-baremetal-elf-gcc",withexitstatus=True)
    if status == 0:
        ret = os.path.dirname(os.path.abspath(out))
        if not is_toolchain_dir(ret):
            raise Exception("Bad toolchain dir %s"%ret)
        return ret
    
    raise Exception("could not find a baremetal mips toolchain")
    
