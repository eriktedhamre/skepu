#include <iostream>
#include <cmath>

#include <skepu>

float roll_avg(skepu::Region1D<float> region, skepu::Vec<float> weights)
{
    float sum = 0;
    int w_i;
    for (int i = -region.oi + 1, w_i = 1; i <= 0; ++i, w_i++)
    {
        sum += region(i) * weights[w_i];
        //std::cout << "abs(i): "<< abs(i) <<" weight: "<< weights[w_i] << ' ';
    }
    //std::cout << std::endl;
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
    skepu::Vector<float> weights(r + 1);
    
    float min_weight  = 1.0/((float)(r+1));
    for (int i = 0; i < r+1; i++)
    {
        weights[i] = min_weight + i * min_weight;
    }
    /*
    for (int i = 0; i < r+1; i++)
    {
        std::cout << "weights["<< i << "]: " << weights[i] << ' ';
    }
    */
    //std::cout << std::endl;

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

    result = instance(result, vec, weights);

    for (size_t i = 0; i < size; i++)
    {
        std::cout << result[i] << ' ';
    }
    

    return 0;
}