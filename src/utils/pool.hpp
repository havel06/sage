#pragma once

template <typename T, int Size>
class Pool
{
public:
	Pool();
	Pool& operator=(const Pool& other);
	Pool(const Pool& other);
	Pool(Pool&&) = delete;

	void clear();
	int add();
	int add(T&& value);
	void remove(int index);

	int count() const;
	const T* get(int index) const;
	T* get(int index);
	// Callable takes 2 arguments, int (index) and const T&
	template<typename Callable>
	void for_each_active(Callable c) const;
	// Callable takes 2 arguments, int (index) and T&
	template<typename Callable>
	void for_each_active(Callable c);

private:
	struct node {
		T value = {};
		bool active = false;
		node* next_free = nullptr;
	};

	node m_data[Size];
	node* m_first_free = nullptr;
};

// Implementation

template <typename T, int Size>
Pool<T, Size>::Pool()
{
	clear();
}

template <typename T, int Size>
Pool<T, Size>& Pool<T, Size>::operator=(const Pool& other)
{
	clear();
	other.for_each_active([this](const T& value){
		add(T{value});
		return true;
	});
	return *this;
};

template <typename T, int Size>
Pool<T, Size>::Pool(const Pool& other) : Pool()
{
	// TODO - optimise?
	other.for_each_active([this](const T& value){
		add(T{value});
		return true;
	});
};


template <typename T, int Size>
void Pool<T, Size>::clear()
{
	for (int i = 0; i < Size - 1; i++)
	{
		m_data[i].next_free = &(m_data[i + 1]);
	}

	m_first_free = &m_data[0];
}

template <typename T, int Size>
int Pool<T, Size>::add()
{
	assert(m_first_free);
	int index = m_first_free - m_data;

	m_first_free->active = true;
	m_first_free = m_first_free->next_free;
	return index;
}

template <typename T, int Size>
int Pool<T, Size>::add(T&& value)
{
	int index = add();
	*get(index) = (T&&)(value);
	return index;
}

template <typename T, int Size>
void Pool<T, Size>::remove(int index)
{
	m_data[index].active = false;
	m_data[index].next_free = m_first_free;
	m_first_free = &m_data[index];
}

template <typename T, int Size>
int Pool<T, Size>::count() const
{
	int i = 0;
	for (const node& n : m_data)
	{
		if (n.active)
			i++;
	}
	return i;
}

template <typename T, int Size>
const T* Pool<T, Size>::get(int index) const
{
	if (m_data[index].active)
		return &(m_data[index].value);
	else
		return nullptr;
}

template <typename T, int Size>
T* Pool<T, Size>::get(int index)
{
	if (m_data[index].active)
		return &(m_data[index].value);
	else
		return nullptr;
}

template <typename T, int Size>
template<typename Callable>
void Pool<T, Size>::for_each_active(Callable c) const
{
	for (int i = 0; i < Size; i++)
	{
		if (!m_data[i].active)
			continue;

		c(i, m_data[i].value);
	}
}

template <typename T, int Size>
template<typename Callable>
void Pool<T, Size>::for_each_active(Callable c)
{
	for (int i = 0; i < Size; i++)
	{
		if (!m_data[i].active)
			continue;

		c(i, m_data[i].value);
	}
}
