import numpy as np
import pynoise2d
from matplotlib import pyplot as plt
from time import perf_counter

generator = pynoise2d.PerlinNoiseGenerator(256, 256, octaves=8, scale=200)

for _ in range(1000):
    start_time = perf_counter()

    result = generator.generate()

    end_time = perf_counter()

    print(f'generation took {(end_time - start_time) * 1000:.2f} ms.')
    print(result.shape, result.dtype)

    plt.imshow(result, cmap='gray')
    plt.show()
