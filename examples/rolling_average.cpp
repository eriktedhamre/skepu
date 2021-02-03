#include <iostream>
#include <cmath>

#include <skepu>

float roll_avg(skepu::Region1D<float> region)
{
    float sum = 0;
    for (int i = -region.oi + 1; i <= 0; ++i)
    {
        sum += region(i) * (1.0 - abs((float)i)/region.oi);
    }
    return sum/=(region.oi);
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		if(!skepu::cluster::mpi_rank())
			std::cout << "Usage: " << argv[0] << " r size backend\n";
		exit(1);
	}
	
    const size_t r = std::stoul(argv[1]);
	const size_t size = std::stoul(argv[2]);
	auto spec = skepu::BackendSpec{skepu::Backend::typeFromString(argv[3])};
	skepu::setGlobalBackendSpec(spec);

    skepu::Vector<float> vec(size);

    vec.randomize(1, 10);

    for (size_t i = 0; i < size; i++)
    {
        std::cout << vec[i] << ' ';
    }
    std::cout << std::endl;

    auto instance = skepu::MapOverlap(roll_avg);
    instance.setOverlap(r);
    instance.setEdgeMode(skepu::Edge::Duplicate);

    skepu::Vector<float> result(size);

    result = instance(result, vec);

    for (size_t i = 0; i < size; i++)
    {
        std::cout << result[i] << ' ';
    }
    

    return 0;
}