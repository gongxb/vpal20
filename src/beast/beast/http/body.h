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

#ifndef BEAST_HTTP_BODY_H_INCLUDED
#define BEAST_HTTP_BODY_H_INCLUDED

#include <cstdint>
#include <memory>
#include <boost/asio/buffer.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/optional.hpp>
#include <beast/cxx14/memory.h> // <memory>
#include <string>

namespace beast {
namespace http {

/** Container for the HTTP content-body. */
class body
{
private:
    typedef boost::asio::streambuf buffer_type;

    // Hack: use unique_ptr because streambuf cant be moved
    std::unique_ptr <buffer_type> buf_;

public:
    typedef buffer_type::const_buffers_type const_buffers_type;

    body();
    body (body&& other);
    body& operator= (body&& other);

    body (body const&) = delete;
    body& operator= (body const&) = delete;

    void
    write (void const* data, std::size_t bytes);

    template <class ConstBufferSequence>
    void
    write (ConstBufferSequence const& buffers)
    {
        for (auto const& buffer : buffers)
            write (boost::asio::buffer_cast <void const*> (buffer),
                boost::asio::buffer_size (buffer));
    }

    std::size_t
    size() const;

    const_buffers_type
    data() const;
};

template <class = void>
std::string
to_string (body const& b)
{
    std::string s;
    auto const& data (b.data());
    auto const n (boost::asio::buffer_size (data));
    s.resize (n);
    boost::asio::buffer_copy (
        boost::asio::buffer (&s[0], n), data);
    return s;
}

//------------------------------------------------------------------------------

inline
body::body()
    : buf_ (std::make_unique <buffer_type>())
{
}

inline
body::body (body&& other)
{
    buf_ = std::move(other.buf_);
}

inline
body&
body::operator= (body&& other)
{
    buf_ = std::move(other.buf_);
    return *this;
}

inline
void
body::write (void const* data, std::size_t bytes)
{
    buf_->commit (boost::asio::buffer_copy (buf_->prepare (bytes),
        boost::asio::const_buffers_1 (data, bytes)));
}

inline
std::size_t
body::size() const
{
    return buf_->size();
}

inline
auto
body::data() const
    -> const_buffers_type
{
    return buf_->data();
}

} // http
} // beast

#endif