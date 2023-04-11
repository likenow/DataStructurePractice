#pragma once

/*
//1
//2
The 1 2 is we change the way  allocate and deallocate memory
TODO
shrinking
emplace or push into middle of the vector
replace or remove element form the middle of vectors
iterator
*/

template<typename Vector>
class VectorIterator
{
public:
	using ValueType = typename Vector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	VectorIterator(PointerType ptr)
		: m_Ptr(ptr)
	{
		
	}

	VectorIterator& operator++()
	{
		m_Ptr++;
		return *this;
	}

	VectorIterator& operator++(int)
	{
		VectorIterator iterator = *this;
		++(*this);
		return *this;
	}

	VectorIterator& operator--()
	{
		m_Ptr--;
		return *this;
	}

	VectorIterator& operator--(int)
	{
		VectorIterator iterator = *this;
		--(*this);
		return *this;
	}

	bool operator==(const VectorIterator& other) const
	{
		return m_Ptr == other.m_Ptr;
	}

	bool operator!=(const VectorIterator& other) const
	{
		return !(*this == other);
	}

	VectorIterator operator[](int index)
	{
		return *(m_Ptr + index);
	}

	VectorIterator operator->()
	{
		return m_Ptr;
	}

	ReferenceType operator*()
	{
		return *m_Ptr;
	}
private:
	PointerType m_Ptr;
};

template<typename T>
class Vector
{
public:
	using ValueType = T;
	using Iterator = VectorIterator<Vector<T>>;
public:
	Vector()
	{
		ReAlloc(2);

	}
	void PushBack(const T& value)
	{
		if (m_Size >= m_Capacity)
		{
			// growing this by 1.5 times every time
			ReAlloc(m_Capacity + m_Capacity / 2);
		}
		m_Data[m_Size] = value;
		m_Size++;
	}

	void PushBack(T&& value)
	{
		if (m_Size >= m_Capacity)
		{
			// growing this by 1.5 times every time
			ReAlloc(m_Capacity + m_Capacity / 2);
		}
		m_Data[m_Size] = std::move(value);
		m_Size++;
	}

	template<typename... Args>
	T& EmplaceBack(Args&&... args)
	{
		if (m_Size >= m_Capacity)
		{
			ReAlloc(m_Capacity + m_Capacity / 2);
		}
		// constructing a temporary here which is then moving
		// m_Data[m_Size] = T(std::forward<Args>(args)...);
		// new for constructing objects
		// associate that with heap allocations
		// grab the memory address of this element
		new(&m_Data[m_Size]) T(std::forward<Args>(args)...);
		m_Size++;
		return m_Data[m_Size];
	}

	void PopBack()
	{
		if (m_Size > 0)
		{
			m_Size--;
			// manual call destructor
			m_Data[m_Size].~T();
		}
	}

	void Clear()
	{
		for (size_t i = 0; i < m_Size; i++)
		{
			// manual call destructor
			m_Data[i].~T();
		}
		m_Size = 0;
	}

	// const version
	const T& operator[](size_t index) const
	{
		// assert overflow
		return m_Data[index];
	}
	// none const version
	T& operator[](size_t index)
	{
		// assert overflow
		return m_Data[index];
	}

	size_t Size() const { return m_Size; }

	Iterator begin()
	{
		return Iterator(m_Data);
	}

	Iterator end()
	{
		return Iterator(m_Data + m_Size);
	}

	~Vector()
	{
		//1
		// delete[] m_Data;
		Clear();
		::operator delete(m_Data, m_Capacity * sizeof(T));
	}
private:
	/*
	void ReAlloc(size_t newCapacity)
	{
		// 0. overflow
		if (newCapacity < m_Size)
		{
			m_Size = newCapacity;
		}
		// 1. allocate a new block of memeory
		// shouldn't be any constructors being called here at all
		T* newBlock = new T[newCapacity];
		// 2. copy/move old element to new block
		for (size_t i = 0; i < m_Size; i++)
			newBlock[i] = std::move(m_Data[i]);
		// 3. delete
		//2
		delete[] m_Data;

		m_Data = newBlock;
		m_Capacity = newCapacity;
	}
	*/
	void ReAlloc(size_t newCapacity)
	{
		// 0. overflow
		if (newCapacity < m_Size)
		{
			m_Size = newCapacity;
		}
		// 1. allocate a new block of memeory
		// malloc enough memory to fill up this new capacity
		T* newBlock = (T*)::operator new(newCapacity * sizeof(T));
		// 2. copy/move old element to new block
		//for (size_t i = 0; i < m_Size; i++)
			//newBlock[i] = std::move(m_Data[i]);

		// call constructor
		for (size_t i = 0; i < m_Size; i++)
			new (&newBlock[i]) T(std::move(m_Data[i]));

		// 3. delete
		for (size_t i = 0; i < m_Size; i++)
		{
			m_Data[i].~T();
		}
		::operator delete(m_Data, m_Capacity * sizeof(T));

		m_Data = newBlock;
		m_Capacity = newCapacity;
	}
	
private:
	T* m_Data = nullptr;
	size_t m_Size = 0;
	// an initial size or an initial allocation
	// to prevent having to reallocate
	size_t m_Capacity = 0;
};