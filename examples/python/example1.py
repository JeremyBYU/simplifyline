from rich.traceback import install
from rich import print as rprint
import numpy as np
import matplotlib.pyplot as plt
import time
install()

import simplifyline
from simplifyline import simplify_line, MatrixDouble

from fixtures.points.example_1 import example_points


example_points = np.load('fixtures/points/example_1.npy')
rprint(example_points.shape)
# print(example_points)

def make_line(num_points=100, cylces=5):
    all_points = []
    start_x = 0.0
    for i in range(5):
        start_x = float(i * num_points)
        x = np.linspace(start_x, start_x + 100.0, num=num_points)
        if i % 2 == 0:
            y = np.linspace(0.0, 100.0, num=num_points)
        else:
            y = np.linspace(100.0, 0.0, num=num_points)
        points = np.column_stack((x,y))
        all_points.append(points)
    all_points = np.concatenate(all_points, axis=0)
    return all_points

def main():
    # points = make_line()
    points = example_points
    points_mat = MatrixDouble(points)

    t0 = time.perf_counter()
    simple_mat = simplify_line(points_mat, 0.1, True)
    t1 = time.perf_counter()
    rprint(f"It took {(t1-t0) * 1000} milliseconds")
    
    points_simple = np.array(simple_mat)
    rprint(points_simple.shape)

    fig, ax = plt.subplots(nrows=2, ncols=1)
    ax[0].scatter(points[:, 0], points[:, 1], c='r', s=0.1)
    ax[1].scatter(points_simple[:, 0], points_simple[:, 1], c='b', s=0.1)
    plt.show()

if __name__ == "__main__":
    main()