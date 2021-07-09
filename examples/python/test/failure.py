import numpy as np
from simplifyline import simplify_radial_dist_3d, MatrixDouble

def run():
    x = np.linspace(0.0, 100.0, num=10000)
    y = np.linspace(0.0, 100.0, num=10000)
    z = np.linspace(0.0, 100.0, num=10000)
    pc = np.column_stack((x,y,z))
    # pc = np.column_stack([pc, np.ones(pc.shape[0])])[:,:3] # uncomment to cause the failure!
    # the point cloud MUST be a contiguous array of 3D points, otherwise failure will occur
    pc_mat = MatrixDouble(pc)
    true_result = np.array(simplify_radial_dist_3d(pc_mat, 0.05))

    for i in range(1000):
        result = np.array(simplify_radial_dist_3d(pc_mat, 0.05))
        np.testing.assert_almost_equal(true_result, result, err_msg=f"Failed on {i}")
    
if __name__ == "__main__":
    run()