#include <iostream>
#include <cmath>
#include <algorithm>

#include <skepu>

float scalar_mult(float a, float m)
{
    return a * m;
}

float linear_combination(float i, float j, float a, float b)
{
    return i * a + j * b;
}

int main(int argc, char *argv[])
{
    if (argc < 5)
	{
		if(!skepu::cluster::mpi_rank())
			std::cout << "Usage: " << argv[0] << " size a b backend\n";
		exit(1);
	}

    const size_t size = std::stoul(argv[1]);
	const float a = std::stoul(argv[2]);
    const float b = std::stoul(argv[3]);
	auto spec = skepu::BackendSpec{skepu::Backend::typeFromString(argv[4])};
	skepu::setGlobalBackendSpec(spec);
	
    skepu::Vector<float> vec1(size);
    skepu::Vector<float> vec2(size);
    vec1.randomize(1, 10);
    vec2.randomize(1, 10);

    std::cout << "vec1: " << vec1 << '\n';
    std::cout << "vec2: " << vec2 << '\n';

    // auto  s_mult = skepu::Map<1>(scalar_mult);
    auto linear_comb = skepu::Map<2>(linear_combination);
    skepu::Vector <float> result(vec1.size());
    
    // s_mult(result, vec1, scalar);
    linear_comb(result, vec1, vec2, a, b);

    std::cout << "result: " << result << '\n';

    return 0;
}
