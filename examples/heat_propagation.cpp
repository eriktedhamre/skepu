#include <iostream>
#include <cmath>

#include <skepu>


float heat_prop(skepu::Region2D<float> r)
{
    return (r(0, 1) + r(1, 0) + r(0, -1) + r(-1, 0))/4;
}

/*
float heat_prop(int ox, int oy, size_t stride, const float *m, const skepu::Mat<float> filter)
{
    float res = 0;
    res += m[-oy * (int)stride];
    res += m[oy * (int)stride];
    res += m[-ox];
    res += m[ox];
    return res /= 4;
}
*/

int main(int argc, char* argv[])
{
	if (argc < 6)
	{
		if(!skepu::cluster::mpi_rank())
			std::cout << "Usage: " << argv[0] << "size l_temp h_temp iterations backend\n";
		exit(1);
	}
	
	const size_t size = std::stoul(argv[1]);
    const size_t l_temp = std::stoul(argv[2]);
    const size_t h_temp = std::stoul(argv[3]);
    const size_t iter = std::stoul(argv[4]);
	auto spec = skepu::BackendSpec{skepu::Backend::typeFromString(argv[5])};
	skepu::setGlobalBackendSpec(spec);

    skepu::Matrix<float> in(size, size);
    in.randomize(l_temp, h_temp);

    skepu::Matrix<float> out(size, size);
    

    auto instance = skepu::MapOverlap(heat_prop);
    instance.setOverlap(1, 1);

    instance(out, in);

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            std::cout << in.at(i,j) << ' ';
        }
        std::cout << std::endl;
    }

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            std::cout << out.at(i,j) << ' ';
        }
        std::cout << std::endl;
    }
    
    /*
    for (size_t i = 0; i < iter; i++)
    {
        auto instance(out, in);
        in = out;
    }
    */

    return 0;
}