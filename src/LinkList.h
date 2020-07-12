#pragma once

#include"Exception.h"
#include"Object.h"
#include"List.h"

namespace JYLib
{
	template<typename T>
    class LinkList : public List<T>
	{
	protected:
        struct Node : public Object
		{
			T value;
			Node* next;
		};

		mutable struct : public Object
		{
			char reverse[sizeof(T)];
			Node* next;
		} m_head;

		int m_length;
		int m_step;
		Node* m_current;


		Node* position(int i) const
		{
            Node* ret = reinterpret_cast<Node*>(&m_head);
			for (int p = 0; p < i; p++)
			{
				ret = ret->next;
			}

			return ret;
		}

		virtual Node* create()
		{
			return new Node();
		}

		virtual void destroy(Node* pn)
		{
			delete pn;
		}

	public:
		LinkList()
		{
			m_head.next = NULL;
			m_length = 0;
			m_step = 1;
			m_current = NULL;
		}

		bool insert(const T& e)
		{
			return insert(m_length, e);
		}

		bool insert(int i, const T& e)
		{
			bool ret = ((i >= 0) && (i <= m_length));

			Node* node = create();
			if (node != NULL)
			{
				Node* current = position(i);

				node->next = current->next;
				node->value = e;
				current->next = node;

				m_length++;
			}
			else
			{
				THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create new node for LinkList...");
			}
			return ret;
		}

		bool remove(int i)
		{
			bool ret = ((i >= 0) && (i < m_length));

			if (ret)
			{
				Node* current = position(i);

				Node* delNode = current->next;
				if (m_current == delNode)
				{
					m_current = delNode->next;
				}
				current->next = delNode->next;
				m_length--;  // 为了异常安全，这行代码需要在下面那行代码之前
				destroy(delNode);
				
			}

			return ret;
		}

		bool set(int i, const T& e)
		{
			bool ret = ((i >= 0) && (i < m_length));

			if (ret)
			{
				position(i)->next->value = e;
			}

			return ret;
		}

        virtual bool get(int i, T& e) const
		{
			bool ret = ((i >= 0) && (i < m_length));

			if (ret)
			{
				e = position(i)->next->value;
			}

			return ret;
		}

        virtual T get(int i) const
		{
			T ret;

			if (get(i, ret))
			{
				return ret;
			}
			else
			{
				THROW_EXCEPTION(IndexOutOfBoundsException, "The parameter i is invalid...");
			}
			return ret;
		}

		int find(const T& e) const
		{
			int ret = -1;
			Node* cur = m_head.next;
			int i = 0;
			while (cur)
			{
				if (cur->value == e)
				{
					ret = i;
					break;
				}
				else
				{
					i++;
					cur = cur->next;
				}
			}

			return ret;
		}

		int length() const
		{
			return m_length;
		}

		void clear()
		{
			Node* delNode;
			while (m_head.next)
			{
				delNode = m_head.next;
				m_head.next = delNode->next;
				m_length--;
				destroy(delNode);
			}

		}

        virtual bool move(int i, int step = 1)
		{
			bool ret = (i >= 0) && (i <= m_length) && (step > 0);

			if (ret)
			{
                m_current = position(i)->next;
				m_step = step;
			}

			return ret;
		}

        virtual bool end()
		{
			return (m_current == NULL);
		}

        virtual T current()
		{
			if (!end())
			{
				return m_current->value;
			}
			else
			{
                THROW_EXCEPTION(InvalidOperationException, "No value at current position...");
			}
		}

        virtual bool next()
		{
			int i = 0;
			while ((i < m_step) && (!end()))
			{
				m_current = m_current->next;
				i++;
			}

			return (i == m_step);
		}

		~LinkList()
		{
			clear();
		}
	};
}
