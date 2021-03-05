#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <skepu>


bool or_reduce (bool a, bool b){
	return (a || b);
}

int main(int argc, char* argv[])
{

    if (argc < 2)
	{
		if(!skepu::cluster::mpi_rank())
			std::cout << "Usage: " << argv[0] << "size backend\n";
		exit(1);
	}
    const size_t size = std::stoul(argv[1]);
    auto spec = skepu::BackendSpec{skepu::Backend::typeFromString(argv[2])};
	skepu::setGlobalBackendSpec(spec);

    skepu::Vector<bool> bool_cond(size, false);
    bool_cond[0] = true;
    auto reduce = skepu::Reduce(or_reduce);
    reduce.setStartValue(false);
    auto res = reduce(bool_cond);

}