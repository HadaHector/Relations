#pragma once
#include <vector>

template <class T>
class Hierarchical
{
public:
	const std::vector<Hierarchical<T>*>& GetChildren()
	{
		return m_aChildren;
	}

	Hierarchical<T>* GetParent()
	{
		return m_pParent;
	}

	void AttachChild(Hierarchical<T>* pChild)
	{
		for (Hierarchical<T>* pMyChild : m_aChildren)
		{
			if (pMyChild == pChild)
			{
				return;
			}
		}

		pChild->AttachParent(this);
	}

	void AttachParent(Hierarchical<T>* pParent)
	{
		if (m_pParent)
		{
			m_pParent->DetachChild(this);
		}

		m_pParent = pParent;
		pParent->m_aChildren.push_back(this);
	}

	void DetachChild(Hierarchical<T>* pChild)
	{
		for (unsigned int i=0; i<m_aChildren.size(); ++i)
		{
			if (m_aChildren[i] == pChild)
			{
				m_aChildren.erase(m_aChildren.begin() + i);
				pChild->m_pParent = nullptr;
			}
		}
	}

	void DetachParent()
	{
		AttachParent(nullptr);
	}

	~Hierarchical()
	{
		if (m_pParent)
		{
			m_pParent->DetachChild(this);
		}

		for (Hierarchical<T>* pChild : m_aChildren)
		{
			pChild->DetachParent();
		}
	}

private:
	Hierarchical<T>* m_pParent = nullptr;
	std::vector<Hierarchical<T>*> m_aChildren;

};