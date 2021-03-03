__kernel void matrix_kernel(
    const int n,
    const int k,
    const int m,
	__global const double* a, 
	__global const double* b, 
	__global double* c )
{
    //Get index into global data array
    const int row = get_global_id(0);
    const int col = get_global_id(1); 

    if (row >= n || col >= m) return;

    double summ = 0;

    for(int i = 0; i < k; i++)
    {
        summ += a[row * k + i] * b[i * m + col]; 
    }

    c[row * m + col] = summ;
}