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

#ifndef RIPPLE_RESOURCE_KEY_H_INCLUDED
#define RIPPLE_RESOURCE_KEY_H_INCLUDED

namespace ripple {
namespace Resource {

// The consumer key
struct Key
{
    Kind kind;
    beast::IP::Endpoint address;
    std::string name;

    Key () = delete;

    // Constructor for Inbound and Outbound (non-Admin) keys
    Key (Kind k, beast::IP::Endpoint const& addr)
        : kind(k)
        , address(addr)
        , name()
    {
        assert(kind != kindAdmin);
    }

    // Constructor for Admin keys
    Key (Kind k, std::string const& n)
        : kind(k)
        , address()
        , name(n)
    {
        assert(kind == kindAdmin);
    }

    struct hasher
    {
        std::size_t operator() (Key const& v) const
        {
            switch (v.kind)
            {
            case kindInbound:
            case kindOutbound:
                return m_addr_hash (v.address);

            case kindAdmin:
                return m_name_hash (v.name);

            default:
                bassertfalse;
            };

            return 0;
        }

    private:
        beast::uhash <> m_addr_hash;
        beast::uhash <> m_name_hash;
    };

    struct key_equal
    {
        bool operator() (Key const& lhs, Key const& rhs) const
        {
            if (lhs.kind != rhs.kind)
                return false;

            switch (lhs.kind)
            {
            case kindInbound:
            case kindOutbound:
                return lhs.address == rhs.address;

            case kindAdmin:
                return lhs.name == rhs.name;

            default:
                bassertfalse;
            };

            return false;
        }

    private:
    };
};

}
}

#endif