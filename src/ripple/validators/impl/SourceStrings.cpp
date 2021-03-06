//------------------------------------------------------------------------------
/*
    Portions of this file are from Vpallab: https://github.com/vpallabs
    Copyright (c) 2013 - 2014 - Vpallab.com.
    Please visit http://www.vpallab.com/
    
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2012, 2013 Ripple Labs Inc.

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

namespace ripple {
namespace Validators {

class SourceStringsImp
    : public SourceStrings
    , public beast::LeakChecked <SourceStringsImp>
{
public:
    SourceStringsImp (std::string const& name, std::vector <std::string> const& strings)
        : m_name (name)
        , m_strings (strings)
    {
    }

    ~SourceStringsImp ()
    {
    }

    std::string to_string () const
    {
        return m_name;
    }

    std::string uniqueID () const
    {
        // VFALCO TODO This can't be right...?
        return std::string{};
    }

    std::string createParam ()
    {
        return std::string{};
    }

    void fetch (Results& results, beast::Journal journal)
    {
        results.list.reserve (m_strings.size ());

        for (int i = 0; i < m_strings.size (); ++i)
            Utilities::parseResultLine (results, m_strings [i]);

        results.success = results.list.size () > 0;
        results.expirationTime = beast::Time::getCurrentTime () +
                                 beast::RelativeTime::hours (24);
    }

private:
    std::string m_name;
    std::vector <std::string> m_strings;
};

//------------------------------------------------------------------------------

SourceStrings* SourceStrings::New (
    std::string const& name, std::vector <std::string> const& strings)
{
    return new SourceStringsImp (name, strings);
}

}
}
