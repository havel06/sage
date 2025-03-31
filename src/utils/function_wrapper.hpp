#pragma once
#include <stdlib.h>
#include <string.h>
#include <assert.h>

template<typename>
class Function_Wrapper;

template<typename T, typename ...Args>
class Function_Wrapper<T(Args...)>
{
public:
	Function_Wrapper()
	{
		m_dispatcher = [](void*, Args...){ };
	}

	template<typename Callable>
	Function_Wrapper(Callable c)
	{
		m_caller = new Callable(c);

		m_dispatcher = [](void* caller, Args... args){
			return ((Callable*)caller)->operator()(args...);
		};

		m_deleter = [](void** data){
			delete (Callable*)(*data);
			*data = nullptr;
		};

		m_copier = [](void* original) -> void* {
			Callable* original_casted = (Callable*)original;
			return new Callable(*original_casted);
		};
	}

	Function_Wrapper(const Function_Wrapper& other)
	{
		m_dispatcher = other.m_dispatcher;
		m_deleter = other.m_deleter;
		m_copier = other.m_copier;

		if (m_copier)
			m_caller = m_copier(other.m_caller);
	}

	Function_Wrapper(Function_Wrapper&& other)
	{
		// Just reuse move assignment operator
		*this = (Function_Wrapper&&)other;
	}

	~Function_Wrapper()
	{
		if (m_caller && m_deleter)
			m_deleter(&m_caller);
	}

	Function_Wrapper& operator=(Function_Wrapper&& other)
	{
		if (m_caller)
			m_deleter(&m_caller);

		m_caller = other.m_caller;
		m_dispatcher = other.m_dispatcher;
		m_deleter = other.m_deleter;
		m_copier = other.m_copier;
		other.m_caller = nullptr;
		other.m_dispatcher = nullptr;
		other.m_deleter = nullptr;
		other.m_copier = nullptr;

		return *this;
	}

	T operator()(Args... args)
	{
		assert(m_dispatcher);
		return m_dispatcher(m_caller, args...);
	}

private:
	void* m_caller = nullptr;
	using Dispatcher = T(*)(void*, Args...);
	Dispatcher m_dispatcher = nullptr;
	using Deleter = void(*)(void** data);
	Deleter m_deleter = nullptr;
	using Copier = void*(*)(void* data);
	Copier m_copier = nullptr;
};

