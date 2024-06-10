import os
from common.utils import run, expect_stats


def run_test(sut, verbose, debug):
    this_dir = os.path.dirname(os.path.abspath(__file__))
    args = '-s ../graphs/simplesink.dot'.split()

    proc, out = run(sut, args, this_dir, 3, verbose, debug)

    expect_stats(proc, out, 'SimpleSink', 2, 1, 0, 1, 0, 1, verbose, debug)
