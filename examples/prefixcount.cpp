#include <iostream>
#include <cmath>

#include <skepu>

float prefix_count(float a, float b){
    int non_zero = (b == 0) ? 0 : 1;
    return a + non_zero;
    
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

    for (size_t i = 0; i < size; i++)
    {
        float elem = rand() % 100 + 1;
        elem = (float)(((int)elem % 2 == 0) ? elem : 0);
        vec[i] = elem;
    }
    
    for (size_t i = 0; i < size; i++)
    {
        std::cout << vec[i] << ' ';
    }
    std::cout << std::endl;

    auto instance = skepu::Scan(prefix_count);
    instance.setStartValue(0);
    instance.setBackend(spec);
    instance.setScanMode(skepu::ScanMode::Exclusive);
    skepu::Vector<float> result(size);
    instance(result, vec);
    
    for (size_t i = 0; i < size; i++)
    {
        std::cout << result[i] << ' ';
    }
    

    return 0;
}