#include <iostream>
#include <cmath>

#include <skepu>


struct MaxMinSum
{
	float max;
	float min;
    float sum;
};

MaxMinSum kernel(MaxMinSum a, MaxMinSum b){
    MaxMinSum res;
	res.max = (a.max > b.max) ? a.max : b.max;
	res.min = (a.min < b.min) ? a.min : b.min;
    res.sum = a.sum + b.sum;
	return res; 
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

    skepu::Vector<MaxMinSum> vec(size);
    
    for (size_t i = 0; i < size; i++)
    {
        MaxMinSum elem;
        float val = (float)(rand()% 100 + 1);
        elem.max = val;
        elem.min = val;
        elem.sum = val;
        vec[i] = elem; 
    }
    std::cout << std::endl;
    
    auto instance = skepu::Reduce(kernel);
    instance.setStartValue({-INFINITY, INFINITY, 0});
    auto result = instance(vec);

    std::cout << "Max: " << result.max <<" Min: " << result.min << " Avg: " << result.sum/size << std::endl;

    return 0;
}