#! /usr/bin/python

#note, this docstring is parsed by docopt so dont change it unless you are sure
"""
Mips Emulator Tester.

Usage:
  met.py build [-vf]
  met.py run [-vs] EMU

Options:
  -h --help     Show this screen.
  -v --verbose  Be more verbose :)
  -f --force    Force a rebuild
  -s --srec     use an srec instead of elf.
"""



from docopt import docopt
from metutils import builder
from metutils import runner
import time

def main():
    startt = time.time()
    args = docopt(__doc__)
    if args['build']:
        builder.build_tests(verbose=args['--verbose'],force=args['--force'])
    elif args['run']:
        runner.run_tests(command=args['EMU'],verbose=args['--verbose'],srec=args['--srec'])
    else:
        print __doc__
    endt = time.time()
    dur = endt-startt
    print("Elapsed %dm %ds" % (dur//60,int(dur % 60)))
    

if __name__ == '__main__':
    main()
