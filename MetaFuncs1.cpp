#include <iostream>
#include <tuple>

template<typename T>
void check()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}


// Compile Time Integer Sequences
template<int ... N>
struct IntList;

template<int H, int... T>
struct IntList<H, T...>
{
  static int const Head = H;
  using Tail = IntList<T...>;
};

template<>
struct IntList<>
{};

//Metafunction for defining length of the sequence
template<typename IL>
struct Length
{
  static int const value = 1 + Length<typename IL::Tail>::value;
};

template<>
struct Length<IntList<>>
{
  static const int value = 0;
};


//Metafunction for adding an element in head of the sequence
template<int N, typename IL>
struct IntCons;

template<int N, int... IL>
struct IntCons<N, IntList<IL...>>
{
  using type = IntList<N, IL...>;
};


//Generation a sequence
template<int N, typename IL=IntList<>>
struct Generate
{
  using type = typename Generate<N-1, typename IntCons<N-1, IL>::type>::type;
  
};

template<typename IL>
struct Generate<0, IL>
{
  using type = IL;
};


//Metafunctions for Unpacking Tuples for Function Calls
template<typename Fn, typename ... Arg, int ... Indices>
auto apply(Fn f, const std::tuple<Arg...>& tup, IntList<Indices...>) ->
  decltype(f(std::get<Indices>(tup)...))
{
  return f(std::get<Indices>(tup)...);
}

template<typename Fn, typename ... Arg>
auto apply(Fn f, const std::tuple<Arg...>& tup) ->
  decltype(apply(f, tup, typename Generate<sizeof...(Arg)>::type{}))
{
  return apply(f, tup, typename Generate<sizeof...(Arg)>::type{});
}


//Usage
int main()
{
  
  using primes = IntList<2,3,4,5,6,7>;
  using L2 = IntCons<1, primes>::type;
  using L3 = Generate<10>::type;
  check<L3>();
  
  auto f = [](int x, double y, double z){ return x + y + z; };
  auto t = std::make_tuple(30, 5.0, 1.6);
  auto res = apply(f, t);
  std::cout << typeid(res).name() << ":" << res << '\n';
  
  return 0;
}
