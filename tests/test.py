import libstreamvbyte as svb
import numpy as np

N = 2**20 + 2


def test_streamvbyte():
    before_encode = np.random.randint(0, 2**32, N, dtype=np.uint32)

    compressed_bytes = svb.encode(before_encode)
    assert type(compressed_bytes) == np.ndarray
    assert compressed_bytes.dtype == np.uint8

    after_decode = svb.decode(compressed_bytes, len(before_encode))
    assert type(after_decode) == np.ndarray
    assert after_decode.dtype == np.uint32

    assert len(before_encode) == len(after_decode)
    assert np.array_equal(before_encode, after_decode)

def test_zigzag():
    before_encode = np.random.randint(-2**31, 2**31, N, dtype=np.int32)

    after_encode = svb.encode_zigzag(before_encode)
    assert type(after_encode) == np.ndarray
    assert after_encode.dtype == np.uint32

    after_decode = svb.decode_zigzag(after_encode)
    assert type(after_decode) == np.ndarray
    assert after_decode.dtype == np.int32

    assert len(before_encode) == len(after_decode)
    assert np.array_equal(before_encode, after_decode)

def test_integrate():
    before_encode = np.random.randint(-2**31, 2**31, N, dtype=np.int32)

    compressed_bytes = svb.encode(svb.encode_zigzag(before_encode))
    assert type(compressed_bytes) == np.ndarray
    assert compressed_bytes.dtype == np.uint8

    after_decode = svb.decode_zigzag(svb.decode(compressed_bytes, len(before_encode)))
    assert type(after_decode) == np.ndarray
    assert after_decode.dtype == np.int32

    assert len(before_encode) == len(after_decode)
    assert np.array_equal(before_encode, after_decode)
