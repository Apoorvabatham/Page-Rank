import os
from common.utils import run, expect_stats


def run_test(sut, verbose, debug):
    this_dir = os.path.dirname(os.path.abspath(__file__))
    args = '-s ../graphs/biggraph.dot'.split()

    proc, out = run(sut, args, this_dir, 3, verbose, debug)

    expect_stats(proc, out, 'BigGraph', 200, 30000, 112, 179, 114, 183, verbose, debug)


# More info about the graph:

# Minin: 112 at ncoik
# Maxin: 179 at ogvhn
#
# Minout: 114 at jdkxo
# Maxout: 183 at lzaag