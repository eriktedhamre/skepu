#include <iostream>
#include <cmath>

#include <skepu>

float plus(float a, float b)
{
    return a + b;
}

float average(float a, float b)
{
    return a + b
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		if(!skepu::cluster::mpi_rank())
			std::cout << "Usage: " << argv[0] << "row col backend\n";
		exit(1);
	}
	
	const size_t row = std::stoul(argv[1]);
    const size_t col = std::stoul(argv[2]);
	auto spec = skepu::BackendSpec{skepu::Backend::typeFromString(argv[3])};
	skepu::setGlobalBackendSpec(spec);

    skepu::Matrix<float> mat(row, col);
    return 0;
}