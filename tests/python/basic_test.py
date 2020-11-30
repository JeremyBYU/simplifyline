import pytest
import simplifyline

def test_hello():
    resp = simplifyline.hello("Jeremy")
    assert resp == "Hello Jeremy"


def test_multiply():
    vec = simplifyline.VectorDouble([0.0, 1.0, 2.0])
    resp = simplifyline.multiply_by_scalar_double(vec, 2.0)
    assert list(resp) == [0.0, 2.0, 4.0]