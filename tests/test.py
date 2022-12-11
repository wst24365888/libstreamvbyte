import libstreamvbyte as svb
import numpy as np

N = 2**20 + 2


def test_streamvbyte():
    original_data = np.random.randint(0, 2**32, N, dtype=np.uint32)

    compressed_bytes = svb.encode(original_data)
    assert type(compressed_bytes) == np.ndarray
    assert compressed_bytes.dtype == np.uint8

    recovered_data = svb.decode(compressed_bytes, N)
    assert type(recovered_data) == np.ndarray
    assert recovered_data.dtype == np.uint32

    assert len(original_data) == len(recovered_data)
    assert np.array_equal(original_data, recovered_data)

def test_zigzag():
    original_data = np.random.randint(-2**31, 2**31, N, dtype=np.int32)

    encoded_unsigend_integers = svb.encode_zigzag(original_data)
    assert type(encoded_unsigend_integers) == np.ndarray
    assert encoded_unsigend_integers.dtype == np.uint32

    recovered_data = svb.decode_zigzag(encoded_unsigend_integers)
    assert type(recovered_data) == np.ndarray
    assert recovered_data.dtype == np.int32

    assert len(original_data) == len(recovered_data)
    assert np.array_equal(original_data, recovered_data)

def test_integrate():
    original_data = np.random.randint(-2**31, 2**31, N, dtype=np.int32)

    compressed_bytes = svb.encode(svb.encode_zigzag(original_data))
    assert type(compressed_bytes) == np.ndarray
    assert compressed_bytes.dtype == np.uint8

    recovered_data = svb.decode_zigzag(svb.decode(compressed_bytes, N))
    assert type(recovered_data) == np.ndarray
    assert recovered_data.dtype == np.int32

    assert len(original_data) == len(recovered_data)
    assert np.array_equal(original_data, recovered_data)
