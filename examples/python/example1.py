from rich.traceback import install
from rich import print as rprint
import numpy as np
import matplotlib.pyplot as plt
install()

import simplifyline
from simplifyline import simplify_line, MatrixDouble


def main():
    num_points = 100
    x = np.linspace(0.0, 100.0, num=num_points)
    y = np.linspace(0.0, 100.0, num=num_points)
    points = np.column_stack((x,y))
    points_mat = MatrixDouble(points)
    simple_mat = simplify_line(points_mat, 1.5)
    points_simple = np.array(simple_mat)
    rprint(points_simple)

    fig, ax = plt.subplots(nrows=2, ncols=1)
    ax[0].scatter(x, y, c='r')
    ax[1].scatter(points_simple[:, 0], points_simple[:, 1], c='b')
    plt.show()

if __name__ == "__main__":
    main()