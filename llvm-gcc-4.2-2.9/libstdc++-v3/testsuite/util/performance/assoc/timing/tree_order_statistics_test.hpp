// -*- C++ -*-

// Copyright (C) 2005, 2006 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software
// Foundation; either version 2, or (at your option) any later
// version.

// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this library; see the file COPYING.  If not, write to
// the Free Software Foundation, 59 Temple Place - Suite 330, Boston,
// MA 02111-1307, USA.

// As a special exception, you may use this file as part of a free
// software library without restriction.  Specifically, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to
// produce an executable, this file does not by itself cause the
// resulting executable to be covered by the GNU General Public
// License.  This exception does not however invalidate any other
// reasons why the executable file might be covered by the GNU General
// Public License.

// Copyright (C) 2004 Ami Tavory and Vladimir Dreizin, IBM-HRL.

// Permission to use, copy, modify, sell, and distribute this software
// is hereby granted without fee, provided that the above copyright
// notice appears in all copies, and that both that copyright notice
// and this permission notice appear in supporting documentation. None
// of the above authors, nor IBM Haifa Research Laboratories, make any
// representation about the suitability of this software for any
// purpose. It is provided "as is" without express or implied
// warranty.

/**
 * @file tree_order_statistics_test.hpp
 * Contains a test for order_statisticsing trees
 */

#ifndef PB_DS_TREE_ORDER_STATISTICS_TEST_HPP
#define PB_DS_TREE_ORDER_STATISTICS_TEST_HPP

#include <performance/time/timing_test_base.hpp>
#include <performance/io/xml_formatter.hpp>
#include <common_type/assoc/string_form.hpp>
#include <iterator>

namespace pb_ds
{
  namespace test
  {
    namespace detail
    {
#define PB_DS_STATIC_ASSERT(UNIQUE, E) \
      typedef \
      pb_ds::detail::static_assert_dumclass<sizeof(pb_ds::detail::static_assert<(bool)(E)>)> UNIQUE##static_assert_type

      template<typename Cntnr, bool Native>
      class order_statistics_functor
      {
      public:
        order_statistics_functor(Cntnr& container) : m_r_container(container)
	{ }

	void
        operator()(std::size_t resolution)
	{
	  enum
	    {
	      support_detected =
	      pb_ds::test::detail::tree_supports_order_statistics<Cntnr>::value
	    };

	  PB_DS_STATIC_ASSERT(correct_type, support_detected);

	  for (std::size_t i = 0; i < resolution; ++i)
	    {
	      typename Cntnr::const_iterator it = m_r_container.begin();
	      typename Cntnr::const_iterator e = m_r_container.end();
	      const size_t max_size = m_r_container.size();
	      while (it != e)
		if (m_r_container.order_of_key(*(it++)) > max_size)
		  abort();
	    }
	}

      private:
	Cntnr& m_r_container;
      };

      template<typename Cntnr>
      class order_statistics_functor<Cntnr, false>
      {
      public:
        order_statistics_functor(Cntnr& container) : m_r_container(container)
	{ }

	void
        operator()(std::size_t resolution)
	{
	  for (std::size_t i = 0; i < resolution; ++i)
	    {
	      typedef typename Cntnr::const_iterator const_iterator;
	      const_iterator b = m_r_container.begin();
	      const_iterator e = m_r_container.end();
	      const_iterator it = b;
	      const size_t max_size = m_r_container.size();
	      while (it != e)
		{
		  const_iterator f_it = m_r_container.find(*(it++));
		  if (static_cast<size_t>(std::distance(b, f_it)) > max_size)
		    abort();
		}
	    }
	}

      private:
	Cntnr& m_r_container;
      };
    } // namespace detail

    template<bool Support_Order_Statistics>
    class tree_order_statistics_test 
    : private pb_ds::test::detail::timing_test_base
    {
    public:
      tree_order_statistics_test(size_t vn, size_t vs, size_t vm)
      : m_vn(vn), m_vs(vs), m_vm(vm)
      { }

      template<typename Cntnr>
      void
      operator()(Cntnr);

    private:
      tree_order_statistics_test(const tree_order_statistics_test& );

      template<typename Cntnr>
      void
      order_statistics(Cntnr& r_container, pb_ds::detail::true_type);

      template<typename Cntnr>
      void
      order_statistics(Cntnr& r_container, pb_ds::detail::false_type);

    private:
      const size_t m_vn;
      const size_t m_vs;
      const size_t m_vm;
    };

    template<bool Support_Order_Statistics>
    template<typename Cntnr>
    void
    tree_order_statistics_test<Support_Order_Statistics>::
    operator()(Cntnr)
    {
      typedef xml_result_set_performance_formatter formatter_type;
      formatter_type res_set_fmt(string_form<Cntnr>::name(), 
				 string_form<Cntnr>::desc());

      for (size_t v = m_vn; v < m_vm; v += m_vs)
	{
	  Cntnr cntnr;
	  for (size_t ins = 0; ins < v; ++ ins)
            cntnr.insert((typename Cntnr::value_type)ins);

	  pb_ds::test::detail::order_statistics_functor<Cntnr, Support_Order_Statistics>
            fn(cntnr);

	  const double res =
            pb_ds::test::detail::timing_test_base::operator()(fn);

	  res_set_fmt.add_res(v, res / v);
	}
    }
  } // namespace test
} // namespace pb_ds

#endif 

