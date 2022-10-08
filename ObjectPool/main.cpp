#include <iostream>
#include <chrono>
#include "ObjectPool.h"

using namespace std;

class Test
{
public:
	int i = 0;
	double d = 1.;
	float f = 2.f;
	int ii = 2;

	Test()
	{
		//cout << "con " << endl;
	}

	void Show()
	{
		cout << i << d << f << ii << endl;
	}

	~Test()
	{
		//cout << "Destruct" << endl;
	}
};


// 1000000
// object pool
// 0.1

// new delete
// 0.3

// 1000
// object pool
// 0.001 ~ 0.002

// new delete
// 0.004


constexpr int ObjectCount = 1000;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ObjectPool<Test> testObjectPool(ObjectCount);

	int count = 100;
	while (0 < count)
	{
		auto start = std::chrono::system_clock::now();
		for (int i = 0; i < ObjectCount; ++i)
		{
			//Test* pObject = testObjectPool.GetObject();
			Test* pObject = new Test;

			pObject->i = i;
		
			//testObjectPool.ReturnToPool(pObject);
			delete pObject;
		}
		auto end = std::chrono::system_clock::now();

		std::chrono::duration<double> diff = end - start;
		cout << diff.count() << endl;

		--count;
	}
	
	return 0;
}
