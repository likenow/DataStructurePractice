#include <iostream>
#include "Vector.h"
#include <string>

struct Vector3
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	int* m_MemoryBlock = nullptr;

	Vector3()
	{
		m_MemoryBlock = new int[5];
	}
	Vector3(float scalar)
		: x(scalar), y(scalar), z(scalar)
	{
		m_MemoryBlock = new int[5];
	}
	Vector3(float x, float y, float z)
		: x(x), y(y), z(z)
	{
		m_MemoryBlock = new int[5];
	}
	Vector3(const Vector3& other) = delete;
	/*
	Vector3(const Vector3& other)
		: x(other.x), y(other.y), z(other.z)
	{
		std::cout << "copyed! \n";
	}
	*/
	Vector3(Vector3&& other)
		: x(other.x), y(other.y), z(other.z)
	{
		m_MemoryBlock = other.m_MemoryBlock;
		other.m_MemoryBlock = nullptr;
		std::cout << "copyed! \n";
	}

	Vector3& operator=(const Vector3& other) = delete;
	/*
	Vector3& operator=(const Vector3& other)
	{
		if (this != &other)
		{
			std::cout << "Copy \n";
			x = other.x;
			y = other.y;
			z = other.z;
		}

		return *this;
	}
	*/

	Vector3& operator=(Vector3&& other)
	{
		if (this != &other)
		{
			std::cout << "move \n";
			m_MemoryBlock = other.m_MemoryBlock;
			other.m_MemoryBlock = nullptr;
			x = other.x;
			y = other.y;
			z = other.z;
		}

		return *this;
	}

	~Vector3()
	{
		std::cout << "destoryed! \n";
		delete[] m_MemoryBlock;
	}
};


template<typename T>
void PrintVector(const Vector<T>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
	{
		std::cout << vector[i] << std::endl;
	}
}

template<>
void PrintVector(const Vector<Vector3>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
	{
		std::cout << vector[i].x << "," << vector[i].y << "," << vector[i].z << std::endl;
	}
}

int main()
{
#if 0
	/*
	Vector<std::string> vector;
	vector.PushBack("liuxing");
	vector.PushBack("yangzi");
	vector.PushBack("xiaopang");

	PrintVector(vector);
	*/

	/*
	Vector<Vector3> vector;
	vector.PushBack(Vector3(1.0));
	vector.PushBack(Vector3(1.0,2.0,3.0));
	vector.PushBack(Vector3());
	PrintVector(vector);
	*/
	{
		Vector<Vector3> vector;
		vector.EmplaceBack(1.0f);
		vector.EmplaceBack(2.0f, 3.0f, 4.0f);
		vector.EmplaceBack(1.0f, 3.0f, 4.0f);
		vector.EmplaceBack();
		PrintVector(vector);
		vector.PopBack();
		vector.PopBack();
		PrintVector(vector);
		vector.EmplaceBack(5.0f, 2.0f, 0.0f);
		vector.EmplaceBack(1.0f, 7.0f, 9.0f);
		PrintVector(vector);

		vector.Clear();
		PrintVector(vector);
		vector.EmplaceBack(5.0f, 2.0f, 0.0f);
		vector.EmplaceBack(1.0f, 7.0f, 9.0f);
		PrintVector(vector);

		PrintVector(vector);
	}
#endif
	Vector<std::string> values;
	values.EmplaceBack("1");
	values.EmplaceBack("2");
	values.EmplaceBack("3");
	values.EmplaceBack("4");
	values.EmplaceBack("5");
	for (int i = 0; i < values.Size(); i++)
	{
		std::cout << "i = " << values[i] << std::endl;
	}

	for (std::string value : values)
	{
		std::cout << "value = " << value << std::endl;
	}

	for (Vector<std::string>::Iterator it = values.begin();
		it != values.end(); it++)
	{
		std::cout << "*it = " << *it << std::endl;
	}
	/*
	Vector<int> values;
	values.EmplaceBack(1);
	values.EmplaceBack(2);
	values.EmplaceBack(3);
	values.EmplaceBack(4);
	values.EmplaceBack(5);
	
	for (int i = 0; i < values.Size(); i++)
	{
		std::cout << "i = " << values[i] << std::endl;
	}

	for (int value : values)
	{
		std::cout << "value = " << value << std::endl;
	}

	for (Vector<int>::Iterator it = values.begin();
		it != values.end(); it++)
	{
		std::cout << "*it = " << *it << std::endl;
	}
	*/
	//std::cin.get();
}