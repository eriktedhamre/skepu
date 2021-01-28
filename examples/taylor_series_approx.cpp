#include <iostream>
#include <cmath>

#include <skepu>

float nth_taylor_term(skepu::Index1D i, float x)
{
    int n = i.i + 1;
    float sign = (n % 2 == 0) ? -1 : 1;
    return sign * pow(x, n)/n;
}

float plus(float a, float b)
{
    return a + b;
}


int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		if(!skepu::cluster::mpi_rank())
			std::cout << "Usage: " << argv[0] << " x n backend\n";
		exit(1);
	}
	
    const float x = std::stof(argv[1]);
	const size_t n = std::stoul(argv[2]);
	auto spec = skepu::BackendSpec{skepu::Backend::typeFromString(argv[3])};
	skepu::setGlobalBackendSpec(spec);
    
    auto taylor_approx = skepu::MapReduce<0>(nth_taylor_term, plus);
    taylor_approx.setDefaultSize(n);
    float approx_to_nth_term = taylor_approx(x - 1);

    std::cout << "log(" << x << ") approximated by " << n << " taylor terms: " << approx_to_nth_term << std::endl;

    return 0;
}