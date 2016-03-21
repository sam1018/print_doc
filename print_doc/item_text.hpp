#pragma once

#include "item_common.hpp"

namespace items { namespace detail {

	typedef boost::iterator_range<const_string_iter_type> item_text_base;

} }

namespace items
{
	class item_text : public detail::item_text_base
	{
	public:
		item_text(const ptree& tree) :
			detail::item_text_base(tree.data().begin(), tree.data().end())
		{}
	};
}
