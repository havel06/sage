#pragma once

namespace Concepts
{

template<typename Fn, typename... Params>
concept Callable = requires(Fn fn, Params... params)
{
	fn(params...);
};

}
