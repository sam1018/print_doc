#pragma once

namespace items { namespace detail {

	struct generate_item_composite_to_stringlist {};

	template<typename item_composite_iter>
	class item_composite_to_stringlist_iterator : public boost::iterator_facade<
		item_composite_to_stringlist_iterator<item_composite_iter>,
		string_type,
		boost::forward_traversal_tag,
		string_type
	>
	{
	private:
		item_composite_iter it_item;

	public:
		item_composite_to_stringlist_iterator(item_composite_iter _it) :
			it_item(_it)
		{}

	private:
		friend class boost::iterator_core_access;

		void increment()
		{
		}
		string_type dereference() const
		{
			return string_type(it_item->begin(), it_item->end());
		}
		bool equal(item_composite_to_stringlist_iterator const& other) const
		{
			return it_item == other.it_item;
		}
	};

	template<class ItemCompositeType>
	using item_composite_to_stringlist_range_iter = item_composite_to_stringlist_iterator<
		typename ItemCompositeType::iterator
	>;

	template<class ItemCompositeType>
	using item_composite_to_stringlist_range_base = boost::iterator_range<
		item_composite_to_stringlist_range_iter<ItemCompositeType>
	>;

	template<class ItemCompositeType>
	struct item_composite_to_stringlist_range : detail::item_composite_to_stringlist_range_base<
		ItemCompositeType
	>
	{
	private:
		typedef detail::item_composite_to_stringlist_range_base<ItemCompositeType> base;

	public:
		typedef detail::item_composite_to_stringlist_range_iter<ItemCompositeType> iterator;

		item_composite_to_stringlist_range(ItemCompositeType& r) :
			base(iterator(std::begin(r)), iterator(std::end(r)))
		{}
	};
} }

namespace items
{
	const detail::generate_item_composite_to_stringlist item_composite_to_stringlist 
		= detail::generate_item_composite_to_stringlist();

	template<class ItemCompositeType>
	detail::item_composite_to_stringlist_range<ItemCompositeType>
		operator|(ItemCompositeType& r, detail::generate_item_composite_to_stringlist)
	{
		return detail::item_composite_to_stringlist_range<ItemCompositeType>(r);
	}
}
