#pragma once

namespace Concepts
{

template<typename Fn, typename... Params>
concept Callable = requires(Fn fn, Params... params)
{
	fn(params...);
};

template<typename C, typename... Params>
concept Constructible = requires(C c, Params&&... params)
{
	new C((Params&&)params...);
};

template<typename T>
concept Move_Constructible = Constructible<T, T&&>;

}
