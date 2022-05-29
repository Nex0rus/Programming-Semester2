#include "Allocator.h"
#include <list>
#include <chrono>

using std::chrono::high_resolution_clock;

int main() 
{

	{
		

		try 
		{
			PoolAllocator<char> allocat({ {65536, 1} });
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			std::vector<char, PoolAllocator<char> > test(16384, allocat);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();

			auto duration1 = duration_cast<std::chrono::microseconds>(t2 - t1).count();
			std::cout << "Custom : " << duration1 << std::endl;
		}
		catch(std::bad_alloc) 
		{
			std::cout << "bad_alloc occured" << std::endl;
		}

	}

	{
		high_resolution_clock::time_point t3 = high_resolution_clock::now();
		std::allocator<int> al;
		std::vector<int> test2(16384, al);
		high_resolution_clock::time_point t4 = high_resolution_clock::now();

		auto duration2 = duration_cast<std::chrono::microseconds>(t4 - t3).count();
		std::cout << "Default: " << duration2 << std::endl;
	}
	/*std::vector< int, PoolAllocator<int> > v(allocat);*/
	
	//for (auto it = l.begin(); it != l.end(); ++it)
	//{
	//	std::cout << "ELEMENT: " << *it << std::endl;
	//}
	//try 
	//{
	//}
	//catch (std::bad_alloc) 
	//{
	//	std::cout << "bad_alloc occured" << std::endl;
	//}

	return 0;

}
