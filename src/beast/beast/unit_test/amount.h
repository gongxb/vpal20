//------------------------------------------------------------------------------
/*
    Portions of this file are from Vpallab: https://github.com/vpallabs
    Copyright (c) 2013 - 2014 - Vpallab.com.
    Please visit http://www.vpallab.com/
    
    This file is part of Beast: https://github.com/vinniefalco/Beast
    Copyright 2013, Vinnie Falco <vinnie.falco@gmail.com>

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef BEAST_UNIT_TEST_AMOUNT_H_INLCUDED
#define BEAST_UNIT_TEST_AMOUNT_H_INLCUDED

#include <cstddef>
#include <ostream>
#include <string>

namespace beast {
namespace unit_test {

/** Utility for producing nicely composed output of amounts with units. */
class amount
{
private:
    std::size_t n;
    std::string const& what;

public:
    amount (amount const&) = default;
    amount& operator= (amount const&) = delete;

    amount (std::size_t n_, std::string const& what_)
        : n (n_)
        , what (what_)
    {
    }

    friend
    std::ostream&
    operator<< (std::ostream& s, amount const& t)
    {
        s << t.n << " " << t.what << ((t.n != 1) ? "s" : "");
        return s;
    }
};

} // unit_test
} // beast

#endif
