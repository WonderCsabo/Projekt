#pragma once

#include <iostream>
#include <iterator>

template<typename Container>
void clearPointerContainer(Container& cont)
{
	while(!cont.empty())
	{
		delete cont.back();
		cont.pop_back();
	}
}

template<typename Iterator>
void serializePointerContainer(Iterator begin, Iterator end, std::ostream& o)
{

	auto distance = std::distance(begin, end);
	o.write((char*) &distance, sizeof(distance));

	for(; begin != end; ++begin)
		o << **begin;
}

template<typename Iterator, typename Predicate>
void serializePointerContainer(Iterator begin, Iterator end, std::ostream& o, Predicate& predicate)
{
	std::iterator_traits<Iterator>::difference_type distance = 0;

	for(auto it = begin; it != end; ++it)
		if(predicate(**it))
			++distance;

	o.write((char*) &distance, sizeof(distance));

	for(; begin != end; ++begin)
		if(predicate(**begin))
			o << **begin;
}

template<typename T, typename Container>
void deserializePointerContainer(Container& cont, std::istream& in)
{

	Container::size_type size = 0;
	in.read((char*) &size, sizeof(Container::size_type));

	for(Container::size_type i = 0; i < size; ++i)
	{
		T* t = new T();
		in >> *t;
		cont.push_back(t);
	}
}