#include <iostream>
#include <cmath>

#include <skepu>

float power_of_index(skepu::Index1D i, float x)
{
    return pow(x, i.i);
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		if(!skepu::cluster::mpi_rank())
			std::cout << "Usage: " << argv[0] << " x size backend\n";
		exit(1);
	}
	
    const float x = std::stof(argv[1]);
	const size_t size = std::stoul(argv[2]);
	auto spec = skepu::BackendSpec{skepu::Backend::typeFromString(argv[3])};
	skepu::setGlobalBackendSpec(spec);
    
    auto pow_index_vec = skepu::Map<0>(power_of_index);
    skepu::Vector <float> result(size);
    pow_index_vec(result, x);

    std::cout << result << std::endl;

    return 0;
}