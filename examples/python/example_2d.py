from rich.traceback import install
from rich import print as rprint
import numpy as np
import matplotlib.pyplot as plt
import time
install()

import simplifyline
from simplifyline import simplify_line_2d, MatrixDouble

example_points = np.load('fixtures/points/example_1.npy')
rprint(example_points.shape)
# print(example_points)

def make_saw_wave(num_points=100, cycles=5):
    all_points = []
    start_x = 0.0
    for i in range(cycles):
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

def make_sine_wave(num_points=100, cycles=5):
    max_x = np.pi/2.0 * (cycles + 1)
    time = np.linspace(0.0, max_x, num_points * cycles)
    y = np.sin(time)
    return np.column_stack((time, y))


def perfrom_test(points, tolerance=0.1, high_quality=True):
    rprint("")
    rprint("Raw points: {}".format(points.shape))
    points_mat = MatrixDouble(points)

    t0 = time.perf_counter()
    simple_mat = simplify_line_2d(points_mat, tolerance, high_quality)
    t1 = time.perf_counter()
    rprint(f"It took {(t1-t0) * 1000:.3f} milliseconds")
    
    points_simple = np.array(simple_mat)
    rprint("Simplified points: {}".format(points_simple.shape))

    fig, ax = plt.subplots(nrows=2, ncols=1)
    ax[0].scatter(points[:, 0], points[:, 1], c='r', s=0.1)
    ax[1].plot(points_simple[:, 0], points_simple[:, 1], c='b')
    ax[1].scatter(points_simple[:, 0], points_simple[:, 1], c='r')


    ax[0].set_title("Raw Points")
    ax[1].set_title("Simplified Points")
    fig.tight_layout()
    plt.show()

def main():
    # points = make_line()
    points = example_points
    perfrom_test(points)

    points = make_saw_wave()
    perfrom_test(points)

    points = make_sine_wave()
    # points = np.concatenate([points, points], axis=1)
    perfrom_test(points)


if __name__ == "__main__":
    main()