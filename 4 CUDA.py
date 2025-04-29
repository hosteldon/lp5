try:
    import cupy as cp
except ImportError:
    raise ImportError("CuPy is not installed. Install it using pip: pip install cupy-cuda12x (replace 12x with your CUDA version)")

def initialize_vector(size):
    return cp.random.randint(0, 10, size, dtype=cp.int32)

def initialize_matrix(size):
    return cp.random.randint(0, 10, (size, size), dtype=cp.int32)

def add_vectors(A, B):
    return A + B

def multiply_matrices(A, B):
    return A @ B  # or cp.matmul(A, B)

def print_vector(vector):
    print('[' + ' '.join(map(str, cp.asnumpy(vector))) + ']')

def print_matrix(matrix):
    mat = cp.asnumpy(matrix)
    for row in mat:
        print('[' + ' '.join(map(str, row)) + ']')
    print()

def main():
    try:
        if cp.cuda.runtime.getDeviceCount() == 0:
            print("No CUDA device found.")
            return
    except cp.cuda.runtime.CUDARuntimeError as e:
        print("CUDA runtime error:", e)
        return

    N = 4

    # Vector addition
    A = initialize_vector(N)
    B = initialize_vector(N)

    print("Vector A:")
    print_vector(A)

    print("Vector B:")
    print_vector(B)

    C = add_vectors(A, B)

    print("Addition (A + B):")
    print_vector(C)

    # Matrix multiplication
    D = initialize_matrix(N)
    E = initialize_matrix(N)

    print("\nMatrix D:")
    print_matrix(D)

    print("Matrix E:")
    print_matrix(E)

    F = multiply_matrices(D, E)

    print("Multiplication (D @ E):")
    print_matrix(F)

if _name_ == "_main_":
    main()
