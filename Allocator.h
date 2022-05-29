#pragma once
#include <stdarg.h>
#include <map>
#include <iostream>
#include <vector>
#include <exception>
#include <memory>

struct Chunk 
{
	Chunk* next;
};


struct Bucket 
{
	unsigned chunk_size;
	Bucket* next = nullptr;
	Chunk* available_chunk = nullptr;
};


template <class T>
class PoolAllocator 
{

public:
	using value_type = T;
	using byte = unsigned char;

private:
	Bucket* available_bucket = nullptr;
	std::shared_ptr<byte> global_memory;
public:
	explicit PoolAllocator(std::map<unsigned, unsigned>&& data_map) 
	{
		std::map<unsigned, unsigned> buckets_map = std::move(data_map);// key is a number of bytes in a particular number of chunks, value is a number of such chunk
	
		unsigned total_bytes = 0;
		for (auto it = buckets_map.begin(); it != buckets_map.end(); ++it) 
		{
			std::cout << it->first << " " << it->second << std::endl;
			total_bytes += it->first * it->second + sizeof(Bucket);
		}
		//std::cout << "Total bytes : " << total_bytes << std::endl;
		void * raw = ::operator new(total_bytes);
		//std::cout << "Global memory adress: " << raw << std::endl;
		global_memory.reset((byte*)raw);
		byte* p = global_memory.get();

		unsigned count;
		unsigned n;
		Bucket* curr_bucket = nullptr;
		Bucket* prev_bucket = nullptr;
		for (auto it = buckets_map.begin(); it != buckets_map.end(); ++it) 
		{
			n = it->first;
			count = it->second;
			//std::cout << "New bucket of " << n << " bytes " << count << " times" << std::endl;
			curr_bucket = reinterpret_cast<Bucket*>(p);
			if (available_bucket == nullptr) 
			{
				available_bucket = curr_bucket;
				prev_bucket = curr_bucket;
			}
			else 
			{
				prev_bucket->next = curr_bucket;
				//std::cout << "prev_bucket : " << prev_bucket << " prev_bucket->next : " << prev_bucket->next << "sizeof(Bucket): " << sizeof(Bucket) << std::endl;
			}

			p += sizeof(Bucket);
			Chunk* prev_chunk = reinterpret_cast<Chunk*>(p);
			Chunk* curr_chunk = reinterpret_cast<Chunk*>(p);
			//std::cout << "First Chunk at : " << prev_chunk << std::endl;
			curr_bucket->chunk_size = n;
			curr_bucket->available_chunk = curr_chunk;
			p += n;
			for (size_t chunk = 1; chunk < count; ++chunk) 
			{
				curr_chunk = reinterpret_cast<Chunk*>(p);
				prev_chunk->next = curr_chunk;
				//std::cout << "Chunk at : " << curr_chunk << "	Prev chunk next is: " << prev_chunk->next << std::endl;

				prev_chunk = curr_chunk;
				p += curr_bucket->chunk_size;
			}
			curr_chunk->next = nullptr;
			prev_bucket = curr_bucket;

		}
		curr_bucket->next = nullptr;
	}

	std::shared_ptr<byte> get_mem_ptr() const
	{
		return global_memory;
	}

	Bucket* get_bucket_ptr() const
	{
		return available_bucket;
	}

	template<class OtherType>
	PoolAllocator(PoolAllocator<OtherType> const& other) 
	{
		global_memory = other.get_mem_ptr();
		available_bucket = other.get_bucket_ptr();
	}

	//PoolAllocator(const PoolAllocator & other) 
	//{
	//	//std::cout << "Regular copy ctor" << std::endl;
	//	global_memory = other.global_memory;
	//	available_bucket = other.available_bucket;
	//}

	PoolAllocator & operator=(const PoolAllocator & other) 
	{
		global_memory = other.global_memory;
		available_bucket = other.available_bucket;
	}

	T* allocate(size_t n) 
	{
		unsigned bytes_count = n * sizeof(T);
		if (available_bucket == nullptr)
		{
			throw std::bad_alloc();
		}
		Bucket* target_bucket = available_bucket;
		while ( (target_bucket->chunk_size < bytes_count || target_bucket->available_chunk == nullptr) && target_bucket->next != nullptr) 
		{
			target_bucket = target_bucket->next;
		}
		if (target_bucket->chunk_size < bytes_count || target_bucket->available_chunk == nullptr)
		{
			throw std::bad_alloc();
		}

		T* memory_ptr = (T*)target_bucket->available_chunk;
		target_bucket->available_chunk = target_bucket->available_chunk->next;

		return memory_ptr;
	}

	void deallocate(T* p, std::size_t n) 
	{
		auto bucket_ptr = reinterpret_cast<Bucket*>(global_memory.get());
		for (bucket_ptr; bucket_ptr->next != nullptr; bucket_ptr = bucket_ptr->next) 
		{
			if (reinterpret_cast<byte*>(bucket_ptr->next) >= reinterpret_cast<byte*>(p) ) 
			{
				break;
			}
		}

		Chunk* next_chunk = reinterpret_cast<Chunk*>(p);
		next_chunk->next = bucket_ptr->available_chunk;
		reinterpret_cast<Bucket*>(bucket_ptr)->available_chunk = next_chunk;


	}

	template<class ... Args>
	void construct(T* p, Args&&... args) 
	{
		std::construct_at(p, std::forward<Args>(args)...);
	}

	void destroy(T* p) 
	{
		std::destroy_at(p);
	}

	~PoolAllocator()
	{
		global_memory.~shared_ptr();
	}

	template <class Type> struct rebind {
		typedef PoolAllocator<Type> other;
	};

};