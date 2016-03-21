#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "attribs.hpp"
#include "tc_range.hpp"
#include "item_composite.hpp"
#include "item_composite_to_stringlist.hpp"

using namespace std;
using namespace items;

void print_document(const ptree& tree, ostream& os)
{
	boost::copy(
		item_composite(tree, attribs{}) | item_composite_to_stringlist,
		ostream_iterator<string_type>(os, "\n")
	);
}

int main()
{
	try
	{
		ptree tree;
		read_xml("cv.xml", tree);
		print_document(tree.get_child(doc_tags::document), cout);
	}
	catch (exception& e)
	{
		cerr << e.what() << ". Exiting.\n";
		return EXIT_FAILURE;
	}
	catch(...)
	{
		cerr << "Unknown error. Exiting.\n";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
