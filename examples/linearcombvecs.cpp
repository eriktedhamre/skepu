#include <iostream>
#include <cmath>
#include <algorithm>

#include <skepu>

float scalar_mult(float a, float m)
{
    return a * m;
}

int main(int argc, char *argv[])
{
    if (argc < 4)
	{
		if(!skepu::cluster::mpi_rank())
			std::cout << "Usage: " << argv[0] << " size scalar backend\n";
		exit(1);
	}

    const size_t size = std::stoul(argv[1]);
	const size_t scalar = std::stoul(argv[2]);
	auto spec = skepu::BackendSpec{skepu::Backend::typeFromString(argv[3])};
	skepu::setGlobalBackendSpec(spec);
	
    skepu::Vector<float> vec1(size);
    vec1.randomize(1, 100);

    std::cout << "vec1: " << vec1 << '\n';

    auto  s_mult = skepu::Map<1>(scalar_mult);
    skepu::Vector <float> result(vec1.size());
    s_mult(result, vec1, scalar);

    std::cout << "result: " << result << '\n';

    return 0;
}
