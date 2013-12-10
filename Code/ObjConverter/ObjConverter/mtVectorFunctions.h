#pragma once

#include <Windows.h>
#include <vector>

template<class DataType>

class mtVectorFunctions
{
public:
	mtVectorFunctions()
	{
		SYSTEM_INFO sysinfo;
		GetSystemInfo( &sysinfo );

		m_noOfCores = sysinfo.dwNumberOfProcessors;
	}

	mtVectorFunctions(int noOfCores)
	{
		m_noOfCores = noOfCores;
	}

	~mtVectorFunctions()
	{
	}

	int find(std::vector<DataType>& inputVector, DataType objectToLookFor) 
	{
		m_inputVector = inputVector;
		m_objectToLookFor = objectToLookFor;

		for (int i = 0; i < m_noOfCores; ++i)
		{
			m_HandleThread.push_back(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) CheckNext, this, NULL, &m_IdThread));
			m_ThreadRunning.push_back(true);
		}
		return -1;
	}

	static int WINAPI CheckNext(mtVectorFunctions* s)
	{
		s->find();
	}

	int find()
	{
		int start = 0;
		int end = 0;

		for (int i = start; i < end; ++i)
		{
			if(m_inputVector[i] == m_objectToLookFor)
		}
	}

private:
	int m_noOfCores;

	vector<DataType>* m_inputVector;
	DataType m_objectToLookFor;

	vector<HANDLE> m_HandleThread;
	vector<bool> m_ThreadRunning;
};