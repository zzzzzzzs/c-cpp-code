import math
import time
from functools import wraps
import numpy
import numba
from numba import njit, prange, vectorize

# 指定并行度
numba.config.NUMBA_DEFAULT_NUM_THREADS = 4

# TODO 4种方法的并行循环


def timefn(fn):
    """计算性能的修饰器"""

    @wraps(fn)
    def measure_time(*args, **kwargs):
        t1 = time.time()
        result = fn(*args, **kwargs)
        t2 = time.time()
        print(f"@timefn: {fn.__name__} took {t2 - t1: .5f} s")
        return result

    return measure_time


@timefn
def do_trig(x, y):
    z = numpy.empty_like(x)
    for i in range(x.shape[0]):
        for j in range(x.shape[1]):
            z[i, j] = numpy.sin(x[i, j] ** 2) + numpy.cos(y[i, j])
    return z


@timefn
@njit
def do_trig_jit(x, y):
    z = numpy.empty_like(x)
    for i in range(x.shape[0]):
        for j in range(x.shape[1]):
            z[i, j] = numpy.sin(x[i, j] ** 2) + numpy.cos(y[i, j])
    return z


@timefn
def do_trig_p(x, y):
    z = numpy.empty_like(x)
    for i in prange(x.shape[0]):
        for j in prange(x.shape[1]):
            z[i, j] = numpy.sin(x[i, j] ** 2) + numpy.cos(y[i, j])
    return z


@timefn
@vectorize
def do_trig_vec(x, y):
    z = math.sin(x ** 2) + math.cos(y)
    return z

@timefn
def for_num():
    
    res = 0
    for num in arr:
        res += num
    print(res)

@timefn
@njit
def for_num_jit(arr):
    res = 0
    for num in arr:
        res += num
    print(res)

@timefn
@njit(parallel=True)
def for_num_p(arr):
    res = 0
    for i in prange(arr.shape[0]):
        res += arr[i]
    print(res)

x = numpy.random.random((1000, 1000))
y = numpy.random.random((1000, 1000))

arr = numpy.random.random(1000000000)


# for_num()
for_num_jit(arr)
for_num_p(arr)


# do_trig(x, y)
# do_trig_jit(x, y)
# do_trig_p(x, y)
# do_trig_vec(x, y)
