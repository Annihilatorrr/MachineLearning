import numpy as np

def numpysum_example(n):
    a = np.arange(n) ** 2
    b = np.arange(n) ** 3
    c = a + b
    return c

def create_multidim_array_2_x(number_of_columns, dtype=np.uint32):
    ar = np.array([np.arange(number_of_columns, dtype=dtype), np.arange(number_of_columns, dtype=dtype) * 2])
    return ar

def slice_test():
    a = np.arange(10)
    print(a[2:5])

def flatten_test():
    ar = np.arange(10)
    resized = np.resize(ar, (9,3))
    ar.resize(9,3, refcheck=False)
    flatten_array = ar.flatten()
    ravel_array = ar.ravel()
    flatten_array[1] = 100
    ravel_array[1] = 200
    reshaped = ravel_array.reshape(5,4)
    ravel_array.shape = (4, 5)
    ravel_array.shape = (5, 4)
    ravel_array.resize(2,3)
    print()

def split_test():
    pass

def ranges_test():
    matrix = np.full((10, 10), 0)
    matrix[[0,1,2], [1, 2, 2]] = 1
    print(matrix)
    
    ar = [0, 1, 2, 3, 4], [5, 6, 7, 8, 9]
    arix = np.ix_([0, 1, 2], [5, 6, 7, 8, 9])
    print(arix)

def stacking_test():
    ar1d_1 = np.array(np.arange(10))
    ar1d_2 = np.array(np.arange(10)+10)
    print("********************* one-dim array examples ******************************")
    print('np.hstack((ar1d_1, ar1d_2):\n', np.hstack((ar1d_1, ar1d_2)))
    print('np.concatenate((ar1d_1, ar1d_2)):\n', np.concatenate((ar1d_1, ar1d_2), axis=0))
    print('np.vstack((ar1d_1, ar1d_2)):\n', np.vstack((ar1d_1, ar1d_2)))
    print('np.stack((ar1d_1, ar1d_2), axis=0):\n', np.stack((ar1d_1, ar1d_2), axis=0))
    print('np.stack((ar1d_1, ar1d_2), axis=1):\n', np.stack((ar1d_1, ar1d_2), axis=1))
    print('np.column_stack((ar1d_1, ar1d_2), axis=1):\n', np.column_stack((ar1d_1, ar1d_2)))
    print('np.row_stack((ar1d_1, ar1d_2), axis=1):\n', np.row_stack((ar1d_1, ar1d_2)))

    #ar4 = np.concatenate((ar1, ar2), axis=1)
    #ar5 = np.vstack((ar1, ar2))
    #ar6 = np.concatenate((ar1, ar2), axis=0)
    #ar7 = np.stack((ar1, ar2))
    #print('ar1:\n', ar1, '\n')
    #print('ar2:\n', ar2, '\n')
    #print('ar3:\n', ar3, '\n')
    #print('ar4:\n', ar4, '\n')
    #print('ar5:\n', ar5, '\n')
    #print('ar6:\n', ar6, '\n')
    #print('ar7:\n', ar7, '\n')
    
    ar3 = np.vstack((ar1d_1, ar1d_2))
    ar2d = np.column_stack((ar1d_1, ar1d_2))
    
    print('ar1d_1:\n', ar1d_1, '\n')
    print('ar1d_2:\n', ar1d_2, '\n')
    
    print('ar3 vstack:\n', ar3, '\n')

    print('ar2d after column-wise stacking:\n', ar2d, '\n')

def main():
    np.set_printoptions(linewidth=160)
    #numpysum_example(3)
    #arr = create_multidim_array_2_x(3)
    #print("Dimensions of arr: ", arr.shape)
    #print(arr[1][2], arr[1][2].dtype)
    #float64arr = create_multidim_array_2_x(3, np.float64)
    #print(float64arr[1][2], float64arr[1][2].dtype)
    #slice_test()
    #flatten_test()
    #stacking_test()
    ranges_test()

if __name__ == '__main__':
    main()
