
Python Benchmarks
======================

These benchmarks are not finished and are preliminary. Even after including many test cases I would still take any benchmark with a huge grain of salt!
The test names are organized as "test_TESTDATA_LIBRARY[_lowquality]". ``TESTDATA`` refers to the test line set, the library is either ``simplifyline`` or simplification_ which is a similar rust library with the implemented RDP algorithm. 
Our implementation follows the SimplifyJS_ library trick which can use a radial distance pre-filter when placed in ``lowquality`` mode (high_quality=False). 


Note that the simplification_ library has way more features then this library and is probably a safer bet for use. I didn't know about it until after I made this library. I also still desire a drop in C++ replacement with CMake library as well. 


.. code-block:: text

    ------------------------------------------------------------------------------------------------------ benchmark: 3 tests -----------------------------------------------------------------------------------------------------
    Name (time in us)                                Min                    Max                   Mean              StdDev                 Median                 IQR            Outliers         OPS            Rounds  Iterations
    -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    test_example1_simplifyline_lowquality       605.1000 (1.0)         806.2000 (1.0)         636.5691 (1.0)       16.2028 (1.0)         642.0000 (1.0)       21.8500 (1.0)         404;9  1,570.9213 (1.0)        1575           1
    test_example1_simplifyline                3,734.1000 (6.17)      5,241.5000 (6.50)      3,835.5558 (6.03)     144.7665 (8.93)      3,805.7000 (5.93)      96.0000 (4.39)          5;4    260.7184 (0.17)        260           1
    test_example1_simplification              9,910.6000 (16.38)    10,614.7000 (13.17)    10,140.0295 (15.93)     93.2924 (5.76)     10,119.3000 (15.76)    106.6250 (4.88)         18;4     98.6190 (0.06)         95           1
    -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



.. _SimplifyJS: https://mourner.github.io/simplify-js/

.. _simplification: https://github.com/urschrei/simplification