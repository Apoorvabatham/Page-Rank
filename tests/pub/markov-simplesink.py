import os
from common.utils import run, expect_scores


def run_test(sut, verbose, debug):
    this_dir = os.path.dirname(os.path.abspath(__file__))
    args = '-p 50 -m 100 ../graphs/simplesink.dot'.split()

    proc, out = run(sut, args, this_dir, 3, verbose, debug)

    scores = {
        'node1': 0.4,
        'node2': 0.6,
    }

    expect_scores(proc, out, scores, 1e-10, verbose, debug)
