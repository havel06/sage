#pragma once

#include <assert.h>
#include "concepts.hpp"

template<typename T>
class Own_Ptr
{
public:
	Own_Ptr(T&& val) {
		m_ptr = new T((T&&)val);
	}

	Own_Ptr(T* ptr) {
		m_ptr = ptr;
	}

	Own_Ptr() = default;
	Own_Ptr(const Own_Ptr&) = delete;

	template<typename T2>
	Own_Ptr(Own_Ptr<T2>&& other) {
		m_ptr = other.release();
	}

	Own_Ptr& operator=(const Own_Ptr&) = delete;

	Own_Ptr& operator=(Own_Ptr&& other) {
		if (m_ptr)
			delete m_ptr;

		m_ptr = other.release();
		return *this;
	}

	~Own_Ptr() {
		if (m_ptr)
			delete m_ptr;
	}

	operator bool() const { return m_ptr != nullptr; }

	T& operator*() {
		assert(m_ptr);
		return *m_ptr;
	}

	T* get() {
		return m_ptr;
	}

	const T* get() const {
		return m_ptr;
	}

	const T& operator*() const {
		assert(m_ptr);
		return *m_ptr;
	}

	T* operator->() {
		assert(m_ptr);
		return m_ptr;
	}

	const T* operator->() const {
		assert(m_ptr);
		return m_ptr;
	}

	void clear() {
		delete m_ptr;
		m_ptr = nullptr;
	}

	T* release() {
		T* ptr = m_ptr;
		m_ptr = nullptr;
		return ptr;
	}
private:
	T* m_ptr = nullptr;
};

template<typename T, typename... Args>
requires Concepts::Constructible<T, Args...>
Own_Ptr<T> make_own_ptr(Args&&... args)
{
	return Own_Ptr<T>(new T((Args&&)args...));
}

