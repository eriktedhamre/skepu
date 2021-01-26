#include <iostream>
#include <cmath>
#include <algorithm>

#include <skepu>

int modular_add(int a, int b, int m)
{
    return (a + b) % m;
}

int main(int argc, char* argv[])
{
	if (argc < 4)
	{
		if(!skepu::cluster::mpi_rank())
			std::cout << "Usage: " << argv[0] << " size modulo backend\n";
		exit(1);
	}
	
	const size_t size = std::stoul(argv[1]);
	const size_t modulo = std::stoul(argv[2]);
	auto spec = skepu::BackendSpec{skepu::Backend::typeFromString(argv[3])};
	skepu::setGlobalBackendSpec(spec);
	
    skepu::Vector<int> vec1(size);
    skepu::Vector<int> vec2(size);

    vec1.randomize(1, 100);
    vec2.randomize(1, 100);
    
    std::cout << "vec1: " << vec1 << '\n';
    std::cout << "vec2: " << vec2 << '\n'; 


    auto  m_vsum = skepu::Map<2>(modular_add);
    skepu::Vector <int> result(vec1.size());
    m_vsum(result, vec1, vec2, modulo);

    std::cout << "result: " << result << '\n';

    return 0;
}