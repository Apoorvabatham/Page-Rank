import os
from common.utils import run, expect_stats


def run_test(sut, verbose, debug):
    this_dir = os.path.dirname(os.path.abspath(__file__))
    args = '-s ../graphs/biggraph2.dot'.split()

    proc, out = run(sut, args, this_dir, 3, verbose, debug)

    expect_stats(proc, out, 'BigGraph2', 2000, 2000, 0, 5, 0, 5, verbose, debug)


# More info about the graph:

# Minin: 0 at uktgb
# Maxin: 5 at myamn
#
# Minout: 0 at qxgkd
# Maxout: 5 at jjvoh