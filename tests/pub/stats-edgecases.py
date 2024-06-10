import os
from common.utils import run, expect_stats


def run_test(sut, verbose, debug):
    this_dir = os.path.dirname(os.path.abspath(__file__))
    args = '-s ../graphs/edgecases.dot'.split()

    proc, out = run(sut, args, this_dir, 3, verbose, debug)

    expect_stats(proc, out, 'EdgecaseGraph', 10, 11, 0, 2, 1, 2, verbose, debug)
