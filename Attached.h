#pragma once
#include <vector>

template <class T>
class Attached
{
public:
	const std::vector<Attached<T>*>& GetChildren()
	{
		return m_aConnections;
	}

	void Attach(Attached<T>* pElem)
	{
		pElem->m_aConnections.push_back(this);
		m_aConnections.push_back(this);
	}
	void Detach(Attached<T>* pElem)
	{
		for (unsigned int i=0; i<m_aConnections.size(); ++i)
		{
			if (m_aConnections[i] == pElem)
			{
				m_aConnections.erase(m_aConnections.begin() + i);
				break;
			}
		}
		for (unsigned int i = 0; i<pElem->m_aConnections.size(); ++i)
		{
			if (pElem->m_aConnections[i] == this)
			{
				pElem->m_aConnections.erase(pElem->m_aConnections.begin() + i);
				break;
			}
		}
	}

	~Attached()
	{
		for (unsigned int j = 0; j < m_aConnections.size(); ++j)
		{
			Attached<T>* pElem = m_aConnections[j];
			for (unsigned int i = 0; i < pElem->m_aConnections.size(); ++i)
			{
				if (m_aConnections[i] == this)
				{
					pElem->m_aConnections.erase(pElem->m_aConnections.begin() + i);
					break;
				}
			}
		}
	}

private:
	std::vector<Attached<T>*> m_aConnections;

};