#include <iostream>
#include <cmath>

#include <skepu>


skepu::multiple <float , float, float>
max_min_avg(float a, float b, int size){

    float max = a > b ? a : b;
    float min = a < b ? a : b;
    float average = a/size + b/size;
    return skepu::ret(max, min, average);
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		if(!skepu::cluster::mpi_rank())
			std::cout << "Usage: " << argv[0] << "size backend\n";
		exit(1);
	}
	
	const size_t size = std::stoul(argv[1]);
	auto spec = skepu::BackendSpec{skepu::Backend::typeFromString(argv[2])};
	skepu::setGlobalBackendSpec(spec);

    skepu::Vector<float> vec(size);
    vec.randomize(1, 100);
    
    auto instance = skepu::Reduce<1>(max_min_avg);
    auto result = instance(vec, size);

    std::cout << result << std::endl;

    return 0;
}