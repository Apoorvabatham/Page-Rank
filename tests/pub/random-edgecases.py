import os
from common.utils import run, expect_scores


def run_test(sut, verbose, debug):
    this_dir = os.path.dirname(os.path.abspath(__file__))
    args = '-r 100000 ../graphs/edgecases.dot'.split()

    proc, out = run(sut, args, this_dir, 3, verbose, debug)

    scores = {
        'source': 0.01,
        'cycle1': 0.066222304205007,
        'cycle2': 0.069600073784507,
        'cycle3': 0.041320033203028,
        'cycle4': 0.047188029882725,
        'cycle5': 0.052469226894453,
        'selfsink': 0.413200332030280,
        'disconnected1': 0.1,
        'disconnected2': 0.1,
        'self': 0.1,
    }

    expect_scores(proc, out, scores, 0.02, verbose, debug)
