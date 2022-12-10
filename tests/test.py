import libstreamvbyte as svb
import numpy as np

N = 2**20 + 2
LOW = 0
HIGH = 2**32


def test_encode_decode():
    before_encode = np.random.randint(LOW, HIGH, N, dtype=np.uint32)

    compressed_bytes = svb.encode(before_encode)
    assert type(compressed_bytes) == np.ndarray
    assert compressed_bytes.dtype == np.uint8

    after_decode = svb.decode(compressed_bytes, len(before_encode))
    assert type(after_decode) == np.ndarray
    assert after_decode.dtype == np.uint32

    assert len(before_encode) == len(after_decode)
    assert np.array_equal(before_encode, after_decode)
