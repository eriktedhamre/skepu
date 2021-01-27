#include <iostream>
#include <cmath>
#include <random>

#include <skepu>

struct MyComplex
{
    float real;
    float imaginary;
};

MyComplex comp_mult(MyComplex &a, MyComplex &b)
{
    return MyComplex{.real = a.real * b.real - a.imaginary * b.imaginary,
                     .imaginary = a.real * b.imaginary + b.real * a.imaginary
                     };
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		if(!skepu::cluster::mpi_rank())
			std::cout << "Usage: " << argv[0] << " size backend\n";
		exit(1);
	}
	
	const size_t size = std::stoul(argv[1]);
	auto spec = skepu::BackendSpec{skepu::Backend::typeFromString(argv[2])};
	skepu::setGlobalBackendSpec(spec);
	
    skepu::Vector<MyComplex> vec1(size), vec2(size);

    float LO = 1.0;
    float HI = 10.0;
    for (int i = 0; i < size; i++)
    {
        vec1(i).real = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        vec1(i).imaginary = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        vec2(i).real = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        vec2(i).imaginary = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    }
    
    std::cout << "vec1 ";
    for (int i = 0; i < size; i++)
    {
        std::cout << vec1(i).real << " + i" << vec1(i).imaginary << ' ';
    }

    std::cout << "\n vec2 ";
    for (int i = 0; i < size; i++)
    {
        std::cout << vec2(i).real << " + i" << vec2(i).imaginary << ' ';
    }
    
    
    auto  vector_comp_mult = skepu::Map<2>(comp_mult);
    skepu::Vector <MyComplex> result(vec1.size());
    vector_comp_mult(result, vec1, vec2);

    std::cout << "\n result ";
    for (int i = 0; i < size; i++)
    {
        std::cout << result(i).real << " + i" << result(i).imaginary << ' ';
    }

    return 0;
}
