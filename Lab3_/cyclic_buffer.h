#pragma once
#include <iterator>
#include <functional>
#include <iostream>

template<class Buffer>
class Iterator
{
public:
	using value_type = typename Buffer::value_type;
	using pointer_type = value_type*;
	using reference_type = value_type&;
	using ConstReferenseType = const value_type&;
	using differense_type = std::ptrdiff_t;
	Iterator(pointer_type p, Buffer& buff) : ptr_(p), buf_(buff) {}


	Iterator & operator=(const Iterator & it) 
	{
		if (this->ptr_ == it.ptr_) 
		{
			return *this;
		}
		ptr_ = it.ptr_;
		buf_ = it.buf_;
		return *this;
	}


	Iterator& operator++()
	{
		if (ptr_ == &buf_.buffer_[buf_.tail_]) 
		{
			ptr_ = &buf_.buffer_[buf_.capacity_];
		}
		else if (ptr_ == &buf_.buffer_[buf_.capacity_]) 
		{
			ptr_ = &buf_.buffer_[buf_.head_];
		}
		else if (ptr_ == &buf_.buffer_[buf_.capacity_ - 1])
		{
			ptr_ = &buf_.buffer_[0];
		}
		else 
		{
			++ptr_;
		}

		return *this;
	}


	differense_type operator-(const Iterator & it) const
	{

		if (this->ptr_ == &buf_.buffer_[buf_.capacity_]) 
		{
			return buf_.size_ - (it - buf_.begin());
		}
		differense_type diff = ptr_ - it.ptr_;
		if (diff < 0) 
		{
			diff = this->buf_.capacity_ + diff;
		}
		return diff;
	}


	Iterator operator++(int)
	{
		Iterator temp = *this;
		++(*this);
		return temp;
	}


	Iterator& operator--()
	{
		if (ptr_ == &buf_.buffer_[buf_.head_])
		{
			ptr_ = &buf_.buffer_[buf_.capacity_];
		}
		else if (ptr_ == &buf_.buffer_[buf_.capacity_]) 
		{
			ptr_ = &buf_.buffer_[buf_.tail_];
		}

		else if (ptr_ == &buf_.buffer_[0]) 
		{
			ptr_ = &buf_.buffer_[buf_.capacity_ - 1];
		}
		else
		{	
			--ptr_;
		}
		return *this;
	}


	Iterator operator--(int)
	{
		Iterator temp = *this;
		--(*this);
		return temp;
	}


	Iterator & operator+=(differense_type n) 
	{
		differense_type dist = *this - buf_.begin() + n;
		if (dist % buf_.size_ == 0)
		{
			ptr_ = &buf_.buffer_[buf_.capacity_];
			return *this;
		}

		if (ptr_ = &buf_.buffer_[buf_.capacity_])
		{
			if (n > 0) 
			{
				dist = n - 1;
			}
			if (n < 0)
			{
				dist = buf_.size_ + n;
			}
			if (n == 0) 
			{
				return *this;
			}
		}
		
		ptr_ = &(buf_[dist]);
		return *this;
	}


	Iterator operator+(differense_type n) 
	{
		Iterator temp(*this);
		return (temp += n);

	}


	friend Iterator operator+(differense_type n, const Iterator & it) 
	{
		Iterator temp(it);
		return (temp += n);
	}


	Iterator & operator-=(differense_type n) 
	{
		return  (*this += -n);
	}


	Iterator operator-(differense_type n) 
	{
		Iterator temp(*this);
		return (temp -= n);
	}


	reference_type operator[](differense_type n) 
	{
		return *(*this + n);
	}


	reference_type operator*() const
	{
		return *ptr_;
	}


	pointer_type operator->() const
	{
		return ptr_;
	}


	bool operator<(const Iterator & it) const
	{
		return it - buf_.begin()> *this - buf_.begin();
	}


	bool operator>(const Iterator & it) const
	{
		return it < *this;
	}


	bool operator>=(const Iterator & it) const
	{
		return !(*this < it);
	}


	bool operator<=(const Iterator & it) const
	{
		return !(*this > it);
	}


	bool operator==(const Iterator & it) const
	{
		return !(*this < it || *this > it);
	}


	bool operator!=(const Iterator & it) const
	{
		return !(*this == it);
	}


private:
	pointer_type ptr_;
	Buffer& buf_;
};


template<class T>
class cyclic_buffer 
{
public:
	using value_type = T;
	using reference_type = value_type&;
	using const_reference_type = const value_type&;
	using pointer_type = value_type*;
	template<class Buffer_> friend class Iterator;
	using iterator = Iterator<cyclic_buffer<T>>;

private:
	size_t size_;
	size_t head_;
	size_t tail_;
	size_t capacity_;
	value_type* buffer_ = nullptr;


public:
	cyclic_buffer() {};


	cyclic_buffer & operator=(const cyclic_buffer & other) 
	{
		if (this == &other) 
		{
			return *this;
		}
		size_ = other.size_;
		head_ = other.head_;
		tail_ = other.tail_;
		capacity_ = other.capacity_;
		buffer_ = new value_type[capacity_];
		for (size_t i = 0; i < capacity_; ++i)
		{
			buffer_[i] = other.buffer_[i];
		}
		return *this;

	}


	cyclic_buffer(const cyclic_buffer& other)
	{
		*this = other;
	}


	cyclic_buffer(size_t n) : capacity_(n)
	{
		size_ = 0;
		try 
		{
			buffer_ = new value_type[capacity_];
			head_ = 0;
			tail_ = -1;
		}
		catch (std::bad_alloc)
		{
			std::cout << "Failed to allocate memory. Proccess terminated\n";
		}
	}


	template<std::input_iterator InputIt>
	cyclic_buffer(const InputIt first, const InputIt last) 
	{
		capacity_ = last - first;
		size_ = last - first;
		buffer_ = new value_type[capacity_];
		size_t index = 0;
		for (auto temp = first; temp != last; ++temp, ++index)
		{
			buffer_[index] = *temp;
		}
		head_ = 0;
		tail_ = size_ - 1;
	}

	cyclic_buffer(std::initializer_list<value_type> init) : cyclic_buffer(init.begin(), init.end()) {}


	~cyclic_buffer() 
	{
		delete[] buffer_;
	}

	void push_back(const_reference_type val) 
	{
		if (size_ == capacity_)
		{
			throw std::overflow_error("Overflow error occured, failed to push into full buffer\n");
		}
		size_ += 1;
		tail_ = (tail_ + 1) % capacity_;
		buffer_[tail_] = val;

	}


	void pop_back() 
	{
		if (size_ == 0) 
		{
			throw std::underflow_error("Underflow error occured, failed to pop from empty buffer\n");
		}
		size_ -= 1;
		buffer_[tail_] = 0;
		if (tail_ == capacity_ - 1)
		{
			tail_ = 0;
		}
		else
		{
			tail_ -= 1;
		}
	}


	reference_type back() 
	{
		return buffer_[tail_];
	}


	void push_front(const value_type val) 
	{
		if (size_ == capacity_) 
		{
			throw std::overflow_error("Overflow error occured, failed to push into full buffer\n");
		}
		size_ += 1;
		if (head_ == 0) 
		{
			head_ = capacity_ - 1;
		}
		else 
		{
			head_ -= 1;
		}
		buffer_[head_] = val;
	}


	void pop_front() 
	{
		if (size_ == 0)
		{
			throw std::underflow_error("Underflow error occured, failed to pop from empty buffer\n");
		}
		size_ -= 1;
		buffer_[head_] = 0;
		head_ = (head_ + 1) % capacity_;
	}

	reference_type front() 
	{
		return buffer_[head_];
	}


	reference_type operator[](size_t index) 
	{
		return buffer_[( head_ + (index % size_) ) % capacity_];
	}


	size_t size() 
	{
		return size_;
	}


	bool empty() 
	{
		return size_ == 0;
	}


	void resize(size_t count) 
	{
		if (count == capacity_) 
		{
			return;
		}

		value_type* temp = new value_type[count];
		size_t temp_size = size_;
		if (count < capacity_) 
		{
			if (count < size_)
			{
				temp_size = count;
			}
			for (size_t i = 0; i < temp_size; ++i)
			{
				temp[i] = (*this)[i];
			}

		}

		else if (count > capacity_)
		{
			for (int i = 0; i < size_; i++) 
			{
				temp[i] = (* this)[i];
			}
		}

		size_ = temp_size;
		delete[] buffer_;
		buffer_ = temp;
		head_ = 0;
		tail_ = head_ + size_ - 1;
		capacity_ = count;
	}


	iterator begin() 
	{
		return iterator(&buffer_[head_], *this);
	}


	iterator end() 
	{
		return iterator((&buffer_[capacity_]), *this);
	}

};
