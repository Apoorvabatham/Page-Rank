import os
from common.utils import run, expect_scores


def run_test(sut, verbose, debug):
    this_dir = os.path.dirname(os.path.abspath(__file__))
    args = '-m 50 -p 100 ../graphs/prog2graph.dot'.split()

    proc, out = run(sut, args, this_dir, 3, verbose, debug)

    scores = {
        'CMS': 0.1666666667,
        'dCMS': 0.1666666667,
        'dGit': 0.1666666667,
        'guide': 0.1666666667,
        'forum': 0.1666666667,
        'leaderboard': 0.1666666667,
    }

    expect_scores(proc, out, scores, 1e-10, verbose, debug)
