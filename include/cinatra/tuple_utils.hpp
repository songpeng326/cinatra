#pragma once
template<int...>
struct IndexTuple{};

template<int N, int... Indexes>
struct MakeIndexes : MakeIndexes<N - 1, N - 1, Indexes...>{};

template<int... indexes>
struct MakeIndexes<0, indexes...>
{
	typedef IndexTuple<indexes...> type;
};

template<typename F, int ... Indexes, typename ... Args>
static inline auto apply_helper(const F& f, IndexTuple<Indexes...>, const std::tuple<Args...>& tup)->decltype(f(std::get<Indexes>(tup)...))
{
	return f(std::get<Indexes>(tup)...);
}

template<typename F, typename ... Args>
static inline auto apply(const F& f, const std::tuple<Args...>& tp)->decltype(apply_helper(f, typename MakeIndexes<sizeof... (Args)>::type(), tp))
{
	return apply_helper(f, typename MakeIndexes<sizeof... (Args)>::type(), tp);
}

template<typename F, typename Self, int ... Indexes, typename ... Args>
static inline void apply_member_helper(const F& f, Self* self, IndexTuple<Indexes...>, const std::tuple<Args...>& tup)//->decltype(self->f(std::get<Indexes>(tup)...))
{
	 (*self.*f)(std::get<Indexes>(tup)...);
}

template<typename F, typename Self, typename ... Args>
static inline void apply_member(const F& f, Self* self, const std::tuple<Args...>& tp)//->decltype(apply_member_helper(f, self, typename MakeIndexes<sizeof... (Args)>::type(), tp))
{
	 apply_member_helper(f, self, typename MakeIndexes<sizeof... (Args)>::type(), tp);
}
